#!/usr/bin/env python
#
# Copyright 2019 The Cobalt Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


################################################################################
#                                  API                                         #
################################################################################


def MakeCobaltArchive(output_archive_path,
                      input_file_list,
                      platform_name,
                      platform_sdk_version,
                      additional_buildinfo_dict={}):
  b = Bundler(archive_zip_path=output_archive_path)
  b.MakeArchive(platform_name=platform_name,
                platform_sdk_version=platform_sdk_version,
                file_list=input_file_list,
                additional_buildinfo_dict=additional_buildinfo_dict)


def ExtractCobaltArchive(input_zip_path, output_directory_path, outstream=None):
  b = Bundler(archive_zip_path=input_zip_path)
  b.ExtractTo(output_dir=output_directory_path, outstream=outstream)


def ReadCobaltArchiveInfo(input_zip_path):
  b = Bundler(archive_zip_path=input_zip_path)
  return b.ReadDeployInfo()


################################################################################
#                                 IMPL                                         #
################################################################################


import argparse
import hashlib
import json
import md5
import os
import random
import shutil
import subprocess
import sys
import tempfile
import time
import traceback
import zipfile

from sets import Set

import _env

from starboard.build.port_symlink \
    import IsSymLink, IsWindows, MakeSymLink, ReadSymLink, Rmtree, OsWalk

from starboard.build.filelist import \
    FileList, GetFileType, TempFileSystem, \
    TYPE_NONE, TYPE_SYMLINK_DIR, TYPE_DIRECTORY, TYPE_FILE


class Bundler:
  """Bundler is a utility for managing device bundles of codes. It is used
  for creating the zip file and also unzipping."""
  def __init__(self, archive_zip_path):
    self.archive_zip_path = archive_zip_path

  def ExtractTo(self, output_dir, outstream=None):
    outstream = outstream if outstream else sys.stdout
    assert(os.path.exists(self.archive_zip_path))
    print('UNZIPPING ' + self.archive_zip_path + ' -> ' + output_dir)
    _ExtractFilesAndSymlinks(self.archive_zip_path, output_dir, outstream)

  def ReadDeployInfo(self):
    with zipfile.ZipFile(self.archive_zip_path, 'r') as zf:
      deploy_info_str = zf.read('deploy_info.json')
    return json.loads(deploy_info_str)

  def MakeArchive(self,
                  platform_name,
                  platform_sdk_version,
                  file_list,  # class FileList
                  additional_buildinfo_dict={}):
    build_info_str = _GenerateBuildInfoStr(
        platform_name=platform_name,
        platform_sdk_version=platform_sdk_version,
        additional_buildinfo_dict=additional_buildinfo_dict)
    with zipfile.ZipFile(self.archive_zip_path, mode='w',
                         compression=zipfile.ZIP_DEFLATED,
                         allowZip64=True) as zf:
      zf.writestr('deploy_info.json', build_info_str)
      for file_path, archive_path in file_list.file_list:
        # TODO: Use and implement _FoldIdenticalFiles() to reduce duplicate
        # files. This will help platforms like nxswitch which include a lot
        # of duplicate files for the sdk.
        zf.write(file_path, arcname=archive_path)
      for root_dir, link_path, physical_path in file_list.symlink_dir_list:
        zinfo = zipfile.ZipInfo(physical_path)
        zinfo.filename = link_path
        zinfo.comment = json.dumps({'symlink': physical_path})
        zf.writestr(zinfo, zinfo.comment, compress_type=zipfile.ZIP_DEFLATED)


def _CheckChildPathIsUnderParentPath(child_path, parent_path):
  parent_path = os.path.join(
      os.path.realpath(parent_path), '')
  f = os.path.realpath(child_path)
  common_prefix = os.path.commonprefix([child_path, parent_path])
  if common_prefix != parent_path:
    raise ValueError('Bundle files MUST be located under ' + \
                       parent_path + ', BadFile = ' + f)


def _MakeDirs(path):
  if not os.path.isdir(path):
    os.makedirs(path)

# TODO: Implement into bundler. This is unit tested at this time.
# Returns files_list, copy_list, where file_list is a list of physical
# files, and copy_list contains a 2-tuple of [physical_file, copy_location]
# that describes which files should be copied.
# Example:
#  files, copy_list = _FoldIdenticalFiles(['in0/test.txt', 'in1/test.txt'])
#  Output:
#    files => ['in0/test.txt']
#    copy_list => ['in0/test.txt', 'in1/test.txt']
def _FoldIdenticalFiles(file_path_list):
  # Remove duplicates.
  file_path_list = list(Set(file_path_list))
  file_path_list.sort()
  def Md5File(fpath):
    hash_md5 = hashlib.md5()
    with open(fpath, 'rb') as f:
      for chunk in iter(lambda: f.read(4096), b''):
        hash_md5.update(chunk)
    return hash_md5.hexdigest()
  # Output
  phy_file_list = []
  copy_list = []
  # Temp data structure.
  file_map = {}
  for file_path in file_path_list:
    name = os.path.basename(file_path)
    fsize = os.stat(file_path).st_size
    entry = (name, fsize)
    files = file_map.get(entry, [])
    files.append(file_path)
    file_map[entry] = files
  for (fname, fsize), path_list in file_map.iteritems():
    assert(len(path_list))
    phy_file_list.append(path_list[0])
    if len(path_list) == 1:
      continue
    else:
      md5_dict = { Md5File(path_list[0]): path_list[0]  }
      for tail_file in path_list[1:]:
        new_md5 = Md5File(tail_file)
        matching_file = md5_dict.get(new_md5, None)
        if matching_file != None:
          # Match found.
          copy_list.append((matching_file, tail_file))
        else:
          phy_file_list.append(tail_file)
          md5_dict[new_md5] = tail_file
  return phy_file_list, copy_list


def _GenerateBuildInfoStr(platform_name, platform_sdk_version,
                          additional_buildinfo_dict):
  from time import gmtime, strftime
  build_info = dict(additional_buildinfo_dict)  # Copy dict.
  build_info['archive_time_RFC_2822'] = \
      strftime("%a, %d %b %Y %H:%M:%S +0000", gmtime())
  build_info['archive_time_local'] = time.asctime()
  build_info['platform'] = platform_name
  build_info['sdk_version'] = platform_sdk_version
  # Can be used by clients for caching reasons.
  build_info['random_uint64'] = random.randint(0, 0xffffffffffffffff)
  build_info_str = json.dumps(build_info)
  return build_info_str


def _AddFilesAndSymlinksToZip(open_zipfile, archive_file_list):
  sym_links = []
  for path, archive_name in archive_file_list:
    if IsSymLink(path):
      sym_links.append([path, archive_name])
    else:
      open_zipfile.write(path, arcname=archive_name)
  for path, archive_name in sym_links:
    zinfo = zipfile.ZipInfo(path)
    link_path = ReadSymLink(path)
    zinfo.filename = rel_path
    zinfo.comment = json.dumps({'symlink': link_path})
    open_zipfile.writestr(zinfo, rel_path, compress_type=zipfile.ZIP_DEFLATED)


def _ExtractFilesAndSymlinks(input_zip_path, output_dir, outstream):
  with zipfile.ZipFile(input_zip_path, 'r') as zf:
    for zinfo in zf.infolist():
      if not zinfo.comment:
        # If no comment then this is a regular file or directory so
        # extract normally.
        try:
          zf.extract(zinfo, path=output_dir)
        except Exception as err:
          msg = 'Exception happend during bundle extraction: ' + str(err) + '\n'
          outstream.write(msg)
      else:
        # Otherwise a dictionary containing the symlink will be stored in the
        # comment space.
        try:
          comment = json.loads(zinfo.comment)
          target_path = comment.get('symlink')
          if not target_path:
            print('Expected symbolic-link for archive member ' + \
                  zinfo.filename)
          else:
            full_path = os.path.join(output_dir, target_path)
            _MakeDirs(os.path.join(output_dir, target_path))
            rel_path = os.path.relpath(full_path,
                                       os.path.join(output_dir, zinfo.filename))
            MakeSymLink(from_folder=rel_path,
                        link_folder=os.path.join(output_dir, zinfo.filename))
        except Exception as err:
          msg = 'Exception happend during bundle extraction: ' + str(err) + '\n'
          outstream.write(msg)


################################################################################
#                              UNIT TEST                                       #
################################################################################


def UnitTestBundler_ExtractTo():
  flist = FileList()
  tf = TempFileSystem()
  tf.Clear()
  tf.Make()
  flist.AddSymLink(tf.root_in_tmp, tf.sym_dir)
  bundle_zip = os.path.join(tf.root_tmp, 'bundle.zip')
  b = Bundler(bundle_zip)
  b.MakeArchive('fake', 'fake_sdk', flist)
  out_dir = os.path.join(tf.root_tmp, 'out')
  b.ExtractTo(out_dir)
  out_from_dir = os.path.join(out_dir, 'from_dir')
  out_from_dir_lnk = os.path.join(out_dir, 'from_dir_lnk')
  assert(GetFileType(out_from_dir) == TYPE_DIRECTORY)
  assert(GetFileType(out_from_dir_lnk) == TYPE_SYMLINK_DIR)
  assert(os.path.abspath(out_from_dir) == os.path.abspath(ReadSymLink(out_from_dir_lnk)))


def UnitTestBundler_MakesDeployInfo():
  flist = FileList()
  tf = TempFileSystem()
  tf.Clear()
  tf.Make()
  bundle_zip = os.path.join(tf.root_tmp, 'bundle.zip')
  b = Bundler(bundle_zip)
  b.MakeArchive(platform_name='fake',
                platform_sdk_version='fake_sdk',
                file_list=flist)
  out_dir = os.path.join(tf.root_tmp, 'out')
  b.ExtractTo(out_dir)
  out_deploy_file = os.path.join(out_dir, 'deploy_info.json')
  assert(GetFileType(out_deploy_file) == TYPE_FILE)
  with open(out_deploy_file) as fd:
    text = fd.read()
    js = json.loads(text)
    assert(js)
    assert(js['sdk_version'] == 'fake_sdk')
    assert(js['platform'] == 'fake')


def UnitTest_FoldIdenticalFiles():
  tf_root = TempFileSystem('bundler_fold')
  tf_root.Clear()
  tf1 = TempFileSystem(os.path.join('bundler_fold', '1'))
  tf2 = TempFileSystem(os.path.join('bundler_fold', '2'))
  tf1.Make()
  tf2.Make()
  flist = FileList()
  subdirs = [tf1.root_in_tmp, tf2.root_in_tmp]
  flist.AddAllFilesInPaths(tf_root.root_tmp, subdirs)
  flist.Print()
  identical_files = [tf1.test_txt, tf2.test_txt]
  physical_files, copy_files = _FoldIdenticalFiles(identical_files)
  assert(tf1.test_txt == physical_files[0])
  assert(tf1.test_txt in copy_files[0][0])
  assert(tf2.test_txt in copy_files[0][1])


def UnitTest():
  tests = [
    ['UnitTestBundler_ExtractTo', UnitTestBundler_ExtractTo],
    ['UnitTestBundler_MakesDeployInfo', UnitTestBundler_MakesDeployInfo],
    ['UnitTest_FoldIdenticalFiles', UnitTest_FoldIdenticalFiles],
  ]
  failed_tests = []
  for name, test in tests:
    try:
      print('\n' + name + ' started.')
      test()
      print(name + ' passed.')
    except Exception as err:
      failed_tests.append(name)
      traceback.print_exc()
      print('Error happened during test ' + name)

  if failed_tests:
    print '\n\nThe following tests failed: ' + ','.join(failed_tests)
    return 1
  else:
    return 0


# Interactive test to test the archive/unarchive feature.
def MakeBundleTest():
  root_directory = raw_input('root_directory: ')
  dirs = []
  while True:
    d = raw_input('include dir: ')
    if not d:
      break
    dirs.append(d)
  assert(dirs)
  output_zip = raw_input('output zip path: ')
  unzip_dir = raw_input('unzip output: ')
  assert(os.path.isdir(root_directory))
  tf = TempFileSystem();
  flist = FileList()
  flist.AddAllFilesInPaths(root_directory, dirs)
  b = Bundler(output_zip)
  b.MakeArchive('fake', 'fake_sdk', flist)
  b.ExtractTo(unzip_dir)


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '--make_bundle_test',
      help='Make a bundle from a filder',
      action='store_true')
  args = parser.parse_args()

  if args.make_bundle_test:
    MakeBundleTest()
  else:
    sys.exit(UnitTest())

