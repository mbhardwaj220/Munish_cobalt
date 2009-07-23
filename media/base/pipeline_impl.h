// Copyright (c) 2008-2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Implementation of Pipeline.

#ifndef MEDIA_BASE_PIPELINE_IMPL_H_
#define MEDIA_BASE_PIPELINE_IMPL_H_

#include <string>
#include <vector>
#include <set>

#include "base/message_loop.h"
#include "base/ref_counted.h"
#include "base/thread.h"
#include "base/time.h"
#include "media/base/filter_host.h"
#include "media/base/pipeline.h"

namespace media {


// PipelineImpl runs the media pipeline.  Filters are created and called on the
// message loop injected into this object. PipelineImpl works like a state
// machine to perform asynchronous initialization. Initialization is done in
// multiple passes by InitializeTask(). In each pass a different filter is
// created and chained with a previously created filter.
//
// Here's a state diagram that describes the lifetime of this object.
//
// [ *Created ] -> [ InitDataSource ] -> [ InitDemuxer ] ->
// [ InitAudioDecoder ] -> [ InitAudioRenderer ] ->
// [ InitVideoDecoder ] -> [ InitVideoRenderer ] -> [ Started ]
//        |                    |                         |
//        .-> [ Error ]        .->      [ Stopped ]    <-.
//
// Initialization is a series of state transitions from "Created" to
// "Started". If any error happens during initialization, this object will
// transition to the "Error" state from any state. If Stop() is called during
// initialization, this object will transition to "Stopped" state.
class PipelineImpl : public Pipeline, public FilterHost {
 public:
  explicit PipelineImpl(MessageLoop* message_loop);

  // Pipeline implementation.
  virtual bool Start(FilterFactory* filter_factory,
                     const std::string& uri,
                     PipelineCallback* start_callback);
  virtual void Stop(PipelineCallback* stop_callback);
  virtual void Seek(base::TimeDelta time, PipelineCallback* seek_callback);
  virtual bool IsRunning() const;
  virtual bool IsInitialized() const;
  virtual bool IsRendered(const std::string& major_mime_type) const;
  virtual float GetPlaybackRate() const;
  virtual void SetPlaybackRate(float playback_rate);
  virtual float GetVolume() const;
  virtual void SetVolume(float volume);
  virtual base::TimeDelta GetCurrentTime() const;
  virtual base::TimeDelta GetBufferedTime() const;
  virtual base::TimeDelta GetDuration() const;
  virtual int64 GetBufferedBytes() const;
  virtual int64 GetTotalBytes() const;
  virtual void GetVideoSize(size_t* width_out, size_t* height_out) const;
  virtual PipelineError GetError() const;

 private:
  virtual ~PipelineImpl();

  // Reset the state of the pipeline object to the initial state.  This method
  // is used by the constructor, and the Stop() method.
  void ResetState();

  // Simple method used to make sure the pipeline is running normally.
  bool IsPipelineOk();

  // Helper method to tell whether we are in the state of initializing.
  bool IsPipelineInitializing();

  // FilterHost implementation.
  virtual void SetError(PipelineError error);
  virtual base::TimeDelta GetTime() const;
  virtual void SetTime(base::TimeDelta time);
  virtual void SetDuration(base::TimeDelta duration);
  virtual void SetBufferedTime(base::TimeDelta buffered_time);
  virtual void SetTotalBytes(int64 total_bytes);
  virtual void SetBufferedBytes(int64 buffered_bytes);
  virtual void SetVideoSize(size_t width, size_t height);

  // Method called during initialization to insert a mime type into the
  // |rendered_mime_types_| set.
  void InsertRenderedMimeType(const std::string& major_mime_type);

  // Method called during initialization to determine if we rendered anything.
  bool HasRenderedMimeTypes() const;

  // Callback executed by filters upon completing initialization and seeking.
  void OnFilterInitialize();
  void OnFilterSeek();

  // The following "task" methods correspond to the public methods, but these
  // methods are run as the result of posting a task to the PipelineInternal's
  // message loop.
  void StartTask(FilterFactory* filter_factory,
                 const std::string& url,
                 PipelineCallback* start_callback);

  // InitializeTask() performs initialization in multiple passes. It is executed
  // as a result of calling Start() or InitializationComplete() that advances
  // initialization to the next state. It works as a hub of state transition for
  // initialization.
  void InitializeTask();

  // Stops and destroys all filters, placing the pipeline in the kStopped state
  // and setting the error code to PIPELINE_STOPPED.
  void StopTask(PipelineCallback* stop_callback);

  // Carries out stopping and destroying all filters, placing the pipeline in
  // the kError state.
  void ErrorChangedTask(PipelineError error);

  // Carries out notifying filters that the playback rate has changed.
  void PlaybackRateChangedTask(float playback_rate);

  // Carries out notifying filters that the volume has changed.
  void VolumeChangedTask(float volume);

  // Carries out notifying filters that we are seeking to a new timestamp.
  void SeekTask(base::TimeDelta time, PipelineCallback* seek_callback);

  // Internal methods used in the implementation of the pipeline thread.  All
  // of these methods are only called on the pipeline thread.

  // The following template functions make use of the fact that media filter
  // derived interfaces are self-describing in the sense that they all contain
  // the static method filter_type() which returns a FilterType enum that
  // uniquely identifies the filter's interface.  In addition, filters that are
  // specific to audio or video also support a static method major_mime_type()
  // which returns a string of "audio/" or "video/".
  //
  // Uses the FilterFactory to create a new filter of the Filter class, and
  // initializes it using the Source object.  The source may be another filter
  // or it could be a string in the case of a DataSource.
  //
  // The CreateFilter() method actually does much more than simply creating the
  // filter.  It also creates the filter's thread and injects a FilterHost and
  // MessageLoop.  Finally, it calls the filter's type-specific Initialize()
  // method to initialize the filter.  If the required filter cannot be created,
  // PIPELINE_ERROR_REQUIRED_FILTER_MISSING is raised, initialization is halted
  // and this object will remain in the "Error" state.
  template <class Filter, class Source>
  void CreateFilter(FilterFactory* filter_factory,
                    Source source,
                    const MediaFormat& source_media_format);

  // Creates a Filter and initializes it with the given |source|.  If a Filter
  // could not be created or an error occurred, this method returns NULL and the
  // pipeline's |error_| member will contain a specific error code.  Note that
  // the Source could be a filter or a DemuxerStream, but it must support the
  // GetMediaFormat() method.
  template <class Filter, class Source>
  void CreateFilter(FilterFactory* filter_factory, Source* source) {
    CreateFilter<Filter, Source*>(filter_factory,
                                  source,
                                  source->media_format());
  }

  // Creates a DataSource (the first filter in a pipeline).
  void CreateDataSource();

  // Creates a Demuxer.
  void CreateDemuxer();

  // Creates a decoder of type Decoder. Returns true if the asynchronous action
  // of creating decoder has started. Returns false if this method did nothing
  // because the corresponding audio/video stream does not exist.
  template <class Decoder>
  bool CreateDecoder();

  // Creates a renderer of type Renderer and connects it with Decoder. Returns
  // true if the asynchronous action of creating renderer has started. Returns
  // false if this method did nothing because the corresponding audio/video
  // stream does not exist.
  template <class Decoder, class Renderer>
  bool CreateRenderer();

  // Examine the list of existing filters to find one that supports the
  // specified Filter interface. If one exists, the |filter_out| will contain
  // the filter, |*filter_out| will be NULL.
  template <class Filter>
  void GetFilter(scoped_refptr<Filter>* filter_out) const;

  // Stops every filters, filter host and filter thread and releases all
  // references to them.
  void DestroyFilters();

  // Message loop used to execute pipeline tasks.
  MessageLoop* message_loop_;

  // Lock used to serialize access for the following data members.
  mutable Lock lock_;

  // Whether or not the pipeline is running.
  bool running_;

  // Duration of the media in microseconds.  Set by filters.
  base::TimeDelta duration_;

  // Amount of available buffered data in microseconds.  Set by filters.
  base::TimeDelta buffered_time_;

  // Amount of available buffered data.  Set by filters.
  int64 buffered_bytes_;

  // Total size of the media.  Set by filters.
  int64 total_bytes_;

  // Video width and height.  Set by filters.
  size_t video_width_;
  size_t video_height_;

  // Current volume level (from 0.0f to 1.0f).  This value is set immediately
  // via SetVolume() and a task is dispatched on the message loop to notify the
  // filters.
  float volume_;

  // Current playback rate (>= 0.0f).  This value is set immediately via
  // SetPlaybackRate() and a task is dispatched on the message loop to notify
  // the filters.
  float playback_rate_;

  // Current playback time.  Set by filters.
  base::TimeDelta time_;

  // Status of the pipeline.  Initialized to PIPELINE_OK which indicates that
  // the pipeline is operating correctly. Any other value indicates that the
  // pipeline is stopped or is stopping.  Clients can call the Stop() method to
  // reset the pipeline state, and restore this to PIPELINE_OK.
  PipelineError error_;

  // Vector of major mime types that have been rendered by this pipeline.
  typedef std::set<std::string> RenderedMimeTypesSet;
  RenderedMimeTypesSet rendered_mime_types_;

  // The following data members are only accessed by tasks posted to
  // |message_loop_|.

  // Member that tracks the current state.
  enum State {
    kCreated,
    kInitDataSource,
    kInitDemuxer,
    kInitAudioDecoder,
    kInitAudioRenderer,
    kInitVideoDecoder,
    kInitVideoRenderer,
    kStarted,
    kStopped,
    kError,
  };
  State state_;

  // Filter factory as passed in by Start().
  scoped_refptr<FilterFactory> filter_factory_;

  // URL for the data source as passed in by Start().
  std::string url_;

  // Callbacks for various pipeline operations.
  scoped_ptr<PipelineCallback> start_callback_;
  scoped_ptr<PipelineCallback> seek_callback_;
  scoped_ptr<PipelineCallback> stop_callback_;

  // Vector of our filters and map maintaining the relationship between the
  // FilterType and the filter itself.
  typedef std::vector<scoped_refptr<MediaFilter> > FilterVector;
  FilterVector filters_;

  typedef std::map<FilterType, scoped_refptr<MediaFilter> > FilterTypeMap;
  FilterTypeMap filter_types_;

  // Vector of threads owned by the pipeline and being used by filters.
  typedef std::vector<base::Thread*> FilterThreadVector;
  FilterThreadVector filter_threads_;

  DISALLOW_COPY_AND_ASSIGN(PipelineImpl);
};

}  // namespace media

#endif  // MEDIA_BASE_PIPELINE_IMPL_H_
