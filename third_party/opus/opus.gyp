# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'use_system_opus%': 0,
    'conditions': [
      ['OS=="android"', {
        'use_opus_floating_point%': 0,
      }, {
        'use_opus_floating_point%': 1,
      }],
    ],
  },
  'conditions': [
    ['use_system_opus==0', {
      'targets': [
        {
          'target_name': 'opus',
          'type': 'static_library',
          'defines': [
            'OPUS_BUILD',
            'OPUS_EXPORT=',
            'WORDS_BIGENDIAN',
          ],
          'include_dirs': [
            'src/celt',
            'src/include',
            'src/silk',
          ],
          'direct_dependent_settings': {
            'include_dirs': [
              'src/include',
            ],
          },
          'sources': [
            'src/celt/_kiss_fft_guts.h',
            'src/celt/arch.h',
            'src/celt/bands.c',
            'src/celt/bands.h',
            'src/celt/celt.c',
            'src/celt/celt.h',
            'src/celt/celt_lpc.c',
            'src/celt/celt_lpc.h',
            'src/celt/cwrs.c',
            'src/celt/cwrs.h',
            'src/celt/ecintrin.h',
            'src/celt/entcode.c',
            'src/celt/entcode.h',
            'src/celt/entdec.c',
            'src/celt/entdec.h',
            'src/celt/entenc.c',
            'src/celt/entenc.h',
            'src/celt/fixed_debug.h',
            'src/celt/fixed_generic.h',
            'src/celt/float_cast.h',
            'src/celt/kiss_fft.c',
            'src/celt/kiss_fft.h',
            'src/celt/laplace.c',
            'src/celt/laplace.h',
            'src/celt/mathops.c',
            'src/celt/mathops.h',
            'src/celt/mdct.c',
            'src/celt/mdct.h',
            'src/celt/mfrngcod.h',
            'src/celt/modes.c',
            'src/celt/modes.h',
            'src/celt/os_support.h',
            'src/celt/pitch.c',
            'src/celt/pitch.h',
            'src/celt/quant_bands.c',
            'src/celt/quant_bands.h',
            'src/celt/rate.c',
            'src/celt/rate.h',
            'src/celt/stack_alloc.h',
            'src/celt/static_modes_fixed.h',
            'src/celt/static_modes_float.h',
            'src/celt/vq.c',
            'src/celt/vq.h',
            'src/include/opus.h',
            'src/include/opus_custom.h',
            'src/include/opus_defines.h',
            'src/include/opus_multistream.h',
            'src/include/opus_types.h',
            'src/silk/A2NLSF.c',
            'src/silk/ana_filt_bank_1.c',
            'src/silk/API.h',
            'src/silk/biquad_alt.c',
            'src/silk/bwexpander.c',
            'src/silk/bwexpander_32.c',
            'src/silk/check_control_input.c',
            'src/silk/CNG.c',
            'src/silk/code_signs.c',
            'src/silk/control.h',
            'src/silk/control_audio_bandwidth.c',
            'src/silk/control_codec.c',
            'src/silk/control_SNR.c',
            'src/silk/debug.c',
            'src/silk/debug.h',
            'src/silk/dec_API.c',
            'src/silk/decode_core.c',
            'src/silk/decode_frame.c',
            'src/silk/decode_indices.c',
            'src/silk/decode_parameters.c',
            'src/silk/decode_pitch.c',
            'src/silk/decode_pulses.c',
            'src/silk/decoder_set_fs.c',
            'src/silk/define.h',
            'src/silk/enc_API.c',
            'src/silk/encode_indices.c',
            'src/silk/encode_pulses.c',
            'src/silk/errors.h',
            'src/silk/fixed/apply_sine_window_FIX.c',
            'src/silk/fixed/autocorr_FIX.c',
            'src/silk/fixed/burg_modified_FIX.c',
            'src/silk/fixed/corrMatrix_FIX.c',
            'src/silk/fixed/encode_frame_FIX.c',
            'src/silk/fixed/find_LPC_FIX.c',
            'src/silk/fixed/find_LTP_FIX.c',
            'src/silk/fixed/find_pitch_lags_FIX.c',
            'src/silk/fixed/find_pred_coefs_FIX.c',
            'src/silk/fixed/k2a_FIX.c',
            'src/silk/fixed/k2a_Q16_FIX.c',
            'src/silk/fixed/LTP_analysis_filter_FIX.c',
            'src/silk/fixed/LTP_scale_ctrl_FIX.c',
            'src/silk/fixed/main_FIX.h',
            'src/silk/fixed/noise_shape_analysis_FIX.c',
            'src/silk/fixed/pitch_analysis_core_FIX.c',
            'src/silk/fixed/prefilter_FIX.c',
            'src/silk/fixed/process_gains_FIX.c',
            'src/silk/fixed/regularize_correlations_FIX.c',
            'src/silk/fixed/residual_energy16_FIX.c',
            'src/silk/fixed/residual_energy_FIX.c',
            'src/silk/fixed/schur64_FIX.c',
            'src/silk/fixed/schur_FIX.c',
            'src/silk/fixed/solve_LS_FIX.c',
            'src/silk/fixed/structs_FIX.h',
            'src/silk/fixed/vector_ops_FIX.c',
            'src/silk/fixed/warped_autocorrelation_FIX.c',
            'src/silk/fixed/structs_FIX.h',
            'src/silk/float/apply_sine_window_FLP.c',
            'src/silk/float/autocorrelation_FLP.c',
            'src/silk/float/burg_modified_FLP.c',
            'src/silk/float/bwexpander_FLP.c',
            'src/silk/float/corrMatrix_FLP.c',
            'src/silk/float/encode_frame_FLP.c',
            'src/silk/float/energy_FLP.c',
            'src/silk/float/find_LPC_FLP.c',
            'src/silk/float/find_LTP_FLP.c',
            'src/silk/float/find_pitch_lags_FLP.c',
            'src/silk/float/find_pred_coefs_FLP.c',
            'src/silk/float/inner_product_FLP.c',
            'src/silk/float/k2a_FLP.c',
            'src/silk/float/levinsondurbin_FLP.c',
            'src/silk/float/LPC_analysis_filter_FLP.c',
            'src/silk/float/LPC_inv_pred_gain_FLP.c',
            'src/silk/float/LTP_analysis_filter_FLP.c',
            'src/silk/float/LTP_scale_ctrl_FLP.c',
            'src/silk/float/main_FLP.h',
            'src/silk/float/noise_shape_analysis_FLP.c',
            'src/silk/float/pitch_analysis_core_FLP.c',
            'src/silk/float/prefilter_FLP.c',
            'src/silk/float/process_gains_FLP.c',
            'src/silk/float/regularize_correlations_FLP.c',
            'src/silk/float/residual_energy_FLP.c',
            'src/silk/float/scale_copy_vector_FLP.c',
            'src/silk/float/scale_vector_FLP.c',
            'src/silk/float/schur_FLP.c',
            'src/silk/float/SigProc_FLP.h',
            'src/silk/float/solve_LS_FLP.c',
            'src/silk/float/sort_FLP.c',
            'src/silk/float/structs_FLP.h',
            'src/silk/float/warped_autocorrelation_FLP.c',
            'src/silk/float/wrappers_FLP.c',
            'src/silk/gain_quant.c',
            'src/silk/HP_variable_cutoff.c',
            'src/silk/init_decoder.c',
            'src/silk/init_encoder.c',
            'src/silk/Inlines.h',
            'src/silk/inner_prod_aligned.c',
            'src/silk/interpolate.c',
            'src/silk/lin2log.c',
            'src/silk/log2lin.c',
            'src/silk/LP_variable_cutoff.c',
            'src/silk/LPC_analysis_filter.c',
            'src/silk/LPC_inv_pred_gain.c',
            'src/silk/MacroCount.h',
            'src/silk/MacroDebug.h',
            'src/silk/macros.h',
            'src/silk/main.h',
            'src/silk/NLSF2A.c',
            'src/silk/NLSF_decode.c',
            'src/silk/NLSF_del_dec_quant.c',
            'src/silk/NLSF_encode.c',
            'src/silk/NLSF_stabilize.c',
            'src/silk/NLSF_unpack.c',
            'src/silk/NLSF_VQ.c',
            'src/silk/NLSF_VQ_weights_laroia.c',
            'src/silk/NSQ.c',
            'src/silk/NSQ_del_dec.c',
            'src/silk/pitch_est_defines.h',
            'src/silk/pitch_est_tables.c',
            'src/silk/PLC.c',
            'src/silk/PLC.h',
            'src/silk/process_NLSFs.c',
            'src/silk/quant_LTP_gains.c',
            'src/silk/resampler.c',
            'src/silk/resampler_down2.c',
            'src/silk/resampler_down2_3.c',
            'src/silk/resampler_private.h',
            'src/silk/resampler_private_AR2.c',
            'src/silk/resampler_private_down_FIR.c',
            'src/silk/resampler_private_IIR_FIR.c',
            'src/silk/resampler_private_up2_HQ.c',
            'src/silk/resampler_rom.c',
            'src/silk/resampler_rom.h',
            'src/silk/resampler_structs.h',
            'src/silk/shell_coder.c',
            'src/silk/sigm_Q15.c',
            'src/silk/SigProc_FIX.h',
            'src/silk/sort.c',
            'src/silk/stereo_decode_pred.c',
            'src/silk/stereo_encode_pred.c',
            'src/silk/stereo_find_predictor.c',
            'src/silk/stereo_LR_to_MS.c',
            'src/silk/stereo_MS_to_LR.c',
            'src/silk/stereo_quant_pred.c',
            'src/silk/structs.h',
            'src/silk/sum_sqr_shift.c',
            'src/silk/table_LSF_cos.c',
            'src/silk/tables.h',
            'src/silk/tables_gain.c',
            'src/silk/tables_LTP.c',
            'src/silk/tables_NLSF_CB_NB_MB.c',
            'src/silk/tables_NLSF_CB_WB.c',
            'src/silk/tables_other.c',
            'src/silk/tables_pitch_lag.c',
            'src/silk/tables_pulses_per_block.c',
            'src/silk/tuning_parameters.h',
            'src/silk/typedef.h',
            'src/silk/VAD.c',
            'src/silk/VQ_WMat_EC.c',
            'src/src/opus.c',
            'src/src/opus_decoder.c',
            'src/src/opus_encoder.c',
            'src/src/opus_multistream.c',
            'src/src/repacketizer.c',
          ],
          'conditions': [
            ['OS!="win"', {
              'defines': [
                'HAVE_LRINT',
                'HAVE_LRINTF',
                'VAR_ARRAYS',
              ],
            }, {
              'defines': [
                'USE_ALLOCA',
                'inline=__inline',
              ],
              'msvs_disabled_warnings': [
                4305,  # Disable truncation warning in celt/pitch.c .
              ],
            }],
            ['use_opus_floating_point==1', {
              'include_dirs': [
                'src/silk/float',
              ],
              'sources/': [
                ['exclude', '/fixed/[^/]*_FIX.(h|c)$'],
              ],
            }, {
              'defines': [
                'FIXED_POINT',
              ],
              'include_dirs': [
                'src/silk/fixed',
              ],
              'sources/': [
                ['exclude', '/float/[^/]*_FLP.(h|c)$'],
              ],
            }],
          ],
        },  # target opus
        {
          'target_name': 'opus_demo',
          'type': 'executable',
          'dependencies': [
            'opus'
          ],
          'conditions': [
            ['OS == "win"', {
              'defines': [
                'inline=__inline',
              ],
            }],
            ['OS=="android"', {
              'link_settings': {
                'libraries': [
                  '-llog',
                ],
              },
            }]
          ],
          'sources': [
            'src/src/opus_demo.c',
          ],
          'include_dirs': [
            'src/celt',
            'src/silk',
          ],
        },  # target opus_demo
      ]
    }, {  # use_system_opus != 0
      'targets': [
        {
          'target_name': 'opus',
          'type': 'none',
          'direct_dependent_settings': {
            'cflags': [
              '<!@(pkg-config --cflags opus)',
            ],
            'defines': [
              'USE_SYSTEM_OPUS',
            ],
          },
          'link_settings': {
            'ldflags': [
              '<!@(pkg-config --libs-only-L --libs-only-other opus)',
            ],
            'libraries': [
              '<!@(pkg-config --libs-only-l opus)',
            ],
          },
        },  # target opus
      ],
    }],
  ],
}
