module PCLRecognition

export AbstractRecognizer, setInputRf, setSceneCloud, setSceneRf,
    setModelSceneCorrespondences, recognize,
    AbstractVerifier, verify,
    GeometricConsistencyGrouping, Hough3DGrouping, GlobalHypothesesVerification,
    setGCSize, setGCThreshold,
    setHoughBinSize, setHoughThreshold, setUseInterpolation,
    setUseDistanceWeight, setOcclusionCloud, addModels,
    setInlierThreshold, setOcclusionThreshold, setRegularizer, setRadiusClutter,
    setClutterRegularizer, setRadiusNormals, setDetectClutter, getMask




using LibPCL
using PCLCommon
using PCLSearch
using PCLFeatures
using Cxx
using CxxStd

const libpcl_recognition = LibPCL.find_library_e("libpcl_recognition")
try
    Libdl.dlopen(libpcl_recognition, Libdl.RTLD_GLOBAL)
catch e
    warn("You might need to set DYLD_LIBRARY_PATH to load dependencies proeprty.")
    rethrow(e)
end

cxx"""
#include <pcl/recognition/cg/hough_3d.h>
#include <pcl/recognition/cg/geometric_consistency.h>
#include <pcl/recognition/hv/hv_go.h>
"""

### AbstractRecognizer ###

abstract AbstractRecognizer <: PCLBase

for f in [:setInputRf, :setSceneCloud, :setSceneRf]
    body = Expr(:macrocall, Symbol("@icxx_str"),
        "\$(recognizer.handle)->$f(\$(cloud.handle));")
    @eval $f(recognizer::AbstractRecognizer, cloud::PointCloud) = $body
end
function setModelSceneCorrespondences(recognizer::AbstractRecognizer,
    corr::Correspondences)
    icxx"$(recognizer.handle)->setModelSceneCorrespondences(
        $(corr.handle));"
end
recognize(recognizer::AbstractRecognizer, rototranslations, clustered_corrs) =
    icxx"$(recognizer.handle)->recognize($rototranslations, $clustered_corrs);"

### AbstractVerifier ###

abstract AbstractVerifier <: PCLBase

verify(ver::AbstractVerifier) = icxx"$(ver.handle)->verify();"
for f in [:setSceneCloud]
    body = Expr(:macrocall, Symbol("@icxx_str"),
        "\$(verifier.handle)->$f(\$(cloud.handle));")
    @eval $f(verifier::AbstractVerifier, cloud::PointCloud) = $body
end

### Concrete types and methods ###

for (name, type_params, supername) in [
    (:GeometricConsistencyGrouping, (:MT,:ST), AbstractRecognizer),
    (:Hough3DGrouping, (:T1,:T2,:R1,:R2), AbstractRecognizer),
    (:GlobalHypothesesVerification, (:MT,:ST), AbstractVerifier),
    ]
    cxxname = "pcl::$name"
    name_with_params = Expr(:curly, name, type_params...)
    valname_with_params = Expr(:curly, Symbol(name, "Val"), type_params...)
    @eval begin
        @defpcltype $name_with_params <: $supername $cxxname
        @defptrconstructor $name_with_params() $cxxname
        @defconstructor $valname_with_params() $cxxname
    end
end

for f in [:setGCSize, :setGCThreshold]
    body = Expr(:macrocall, Symbol("@icxx_str"), "\$(g.handle)->$f(\$s);")
    @eval $f(g::GeometricConsistencyGrouping, s) = $body
end

for f in [
        :setHoughBinSize,
        :setHoughThreshold,
        :setUseInterpolation,
        :setUseDistanceWeight,
        ]
    body = Expr(:macrocall, Symbol("@icxx_str"), "\$(h.handle)->$f(\$s);")
    @eval $f(h::Hough3DGrouping, s) = $body
end

for f in [:setOcclusionCloud]
    body = Expr(:macrocall, Symbol("@icxx_str"),
        "\$(ver.handle)->$f(\$(cloud.handle));")
    @eval $f(ver::GlobalHypothesesVerification, cloud::PointCloud) = $body
end

function addModels(ver::GlobalHypothesesVerification, models::CxxStd.StdVector,
    occlusion_reasoning=false)
    icxx"$(ver.handle)->addModels($models, $occlusion_reasoning);"
end

for f in [
        :setInlierThreshold,
        :setOcclusionThreshold,
        :setRegularizer,
        :setRadiusClutter,
        :setClutterRegularizer,
        :setRadiusNormals,
        :setDetectClutter,
        ]
    body = Expr(:macrocall, Symbol("@icxx_str"), "\$(ver.handle)->$f(\$v);")
    @eval $f(ver::GlobalHypothesesVerification, v) = $body
end

getMask(ver::GlobalHypothesesVerification, mask::CxxStd.StdVector) =
    icxx"$(ver.handle)->getMask($mask);"

end # module
