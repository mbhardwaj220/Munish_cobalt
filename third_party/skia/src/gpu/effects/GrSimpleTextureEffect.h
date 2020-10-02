/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * This file was autogenerated from GrSimpleTextureEffect.fp; do not modify.
 */
#ifndef GrSimpleTextureEffect_DEFINED
#define GrSimpleTextureEffect_DEFINED
#include "SkTypes.h"
#if SK_SUPPORT_GPU
#include "GrFragmentProcessor.h"
#include "GrCoordTransform.h"
#include "GrColorSpaceXform.h"
#include "effects/GrProxyMove.h"
class GrSimpleTextureEffect : public GrFragmentProcessor {
public:
    sk_sp<GrColorSpaceXform> colorXform() const { return fColorXform; }
    SkMatrix44 matrix() const { return fMatrix; }

    static sk_sp<GrFragmentProcessor> Make(sk_sp<GrTextureProxy> proxy,
                                           sk_sp<GrColorSpaceXform>
                                                   colorSpaceXform,
                                           const SkMatrix& matrix) {
        return sk_sp<GrFragmentProcessor>(new GrSimpleTextureEffect(
                std::move(proxy), std::move(colorSpaceXform), matrix,
                GrSamplerParams(SkShader::kClamp_TileMode, GrSamplerParams::kNone_FilterMode)));
    }

    static sk_sp<GrFragmentProcessor> Make(sk_sp<GrTextureProxy> proxy,
                                           sk_sp<GrColorSpaceXform>
                                                   colorSpaceXform,
                                           const SkMatrix& matrix,
                                           GrSamplerParams::FilterMode filterMode) {
        return sk_sp<GrFragmentProcessor>(
                new GrSimpleTextureEffect(std::move(proxy), std::move(colorSpaceXform), matrix,
                                          GrSamplerParams(SkShader::kClamp_TileMode, filterMode)));
    }

    static sk_sp<GrFragmentProcessor> Make(sk_sp<GrTextureProxy> proxy,
                                           sk_sp<GrColorSpaceXform>
                                                   colorSpaceXform,
                                           const SkMatrix& matrix,
                                           const GrSamplerParams& p) {
        return sk_sp<GrFragmentProcessor>(
                new GrSimpleTextureEffect(std::move(proxy), std::move(colorSpaceXform), matrix, p));
    }
    const char* name() const override { return "SimpleTextureEffect"; }

private:
    GrSimpleTextureEffect(sk_sp<GrTextureProxy> image, sk_sp<GrColorSpaceXform> colorXform,
                          SkMatrix44 matrix, GrSamplerParams samplerParams)
            : INHERITED((OptimizationFlags)kCompatibleWithCoverageAsAlpha_OptimizationFlag |
                        (GrPixelConfigIsOpaque(image->config())
                                 ? kPreservesOpaqueInput_OptimizationFlag
                                 : kNone_OptimizationFlags))
            , fImage(std::move(image), samplerParams)
            , fColorXform(colorXform)
            , fMatrix(matrix)
            , fImageCoordTransform(matrix, fImage.proxy()) {
        this->addTextureSampler(&fImage);
        this->addCoordTransform(&fImageCoordTransform);
        this->initClassID<GrSimpleTextureEffect>();
    }
    GrGLSLFragmentProcessor* onCreateGLSLInstance() const override;
    void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
    bool onIsEqual(const GrFragmentProcessor&) const override;
    GR_DECLARE_FRAGMENT_PROCESSOR_TEST
    TextureSampler fImage;
    sk_sp<GrColorSpaceXform> fColorXform;
    SkMatrix44 fMatrix;
    GrCoordTransform fImageCoordTransform;
    typedef GrFragmentProcessor INHERITED;
};
#endif
#endif