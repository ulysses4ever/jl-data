"""
The **pcl_features** library contains data structures and mechanisms for 3D
feature estimation from point cloud data

http://docs.pointclouds.org/trunk/group__features.html

## Exports

$(EXPORTS)
"""
module PCLFeatures

export AbstractFeature, AbstractNormal, AbstractSHOT,
    setSearchSurface, getSearchSurface, setSearchMethod, getSearchMethod,
    getSearchParameter, setKSearch, getKSearch, setRadiusSearch, getRadiusSearch,
    setInputNormals, compute,
    NormalEstimation, NormalEstimationOMP, SHOTEstimation, SHOTEstimationOMP,
    BOARDLocalReferenceFrameEstimation, setFindHoles

using DocStringExtensions
using LibPCL
using PCLCommon
using Cxx

const libpcl_features = LibPCL.find_library_e("libpcl_features")
try
    Libdl.dlopen(libpcl_features, Libdl.RTLD_GLOBAL)
catch e
    warn("You might need to set DYLD_LIBRARY_PATH to load dependencies proeprty.")
    rethrow(e)
end

cxx"""
#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/shot_omp.h>
#include <pcl/features/board.h>
"""

abstract AbstractFeature <: PCLBase
abstract AbstractNormal <: AbstractFeature
abstract AbstractSHOT <: AbstractFeature

### Abstract methods for Feature ###

setSearchSurface(f::AbstractFeature, cloud) =
    icxx"$(f.handle)->setSearchSurface($(cloud.handle));"
getSearchSurface(f::AbstractFeature) = icxx"$(f.handle)->getSearchSurface();"
setSearchMethod(f::AbstractFeature, tree) =
    icxx"$(f.handle)->setSearchMethod($(tree.handle));"
getSearchMethod(f::AbstractFeature) = icxx"$(f.handle)->getSearchMethod();"
getSearchParameter(f::AbstractFeature) = icxx"$(f.handle)->getSearchParameter();"
setKSearch(f::AbstractFeature, k::Integer) =  icxx"$(f.handle)->setKSearch($k);"
getKSearch(f::AbstractFeature) = icxx"$(f.handle)->getKSearch();"
setRadiusSearch(f::AbstractFeature, rad::AbstractFloat) =
    icxx"$(f.handle)->setRadiusSearch($rad);"

# TODO: this is actally not a method for pcl::Feature, should put into another
# place
setInputNormals(n::AbstractFeature, normals::PointCloud) =
    icxx"$(n.handle)->setInputNormals($(normals.handle));"

compute(f::AbstractFeature, descriptors::PointCloud) =
    icxx"$(f.handle)->compute(*$(descriptors.handle));"

## Feature types ###

for (name, type_params, supername) in [
    (:NormalEstimation, (:PT,:NT), AbstractNormal),
    (:NormalEstimationOMP, (:PT,:NT), AbstractNormal),
    (:SHOTEstimation, (:PT,:NT,:OT), AbstractSHOT),
    (:SHOTEstimationOMP, (:PT,:NT,:OT), AbstractSHOT),
    (:BOARDLocalReferenceFrameEstimation, (:T,:N,:F),  AbstractFeature),
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

setFindHoles(rfe::BOARDLocalReferenceFrameEstimation, v::Bool) =
    icxx"$(rfe.handle)->setFindHoles($v);"

end # module
