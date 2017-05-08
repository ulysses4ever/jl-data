using PCLCommon
using PCLIO
using Cxx
using Base.Test

import PCLCommon: StdVector

milk_cartoon_path = joinpath(dirname(@__FILE__), "data",
    "milk_cartoon_all_small_clorox.pcd")

@testset "PoindCloud with PCD File IO" begin
    milk_cloud = PointCloud{PointXYZRGBA}(milk_cartoon_path)
    @test (@cxx (milk_cloud.handle)->get()) != C_NULL

    @test width(milk_cloud) == 640
    @test height(milk_cloud) == 480
    @test !is_dense(milk_cloud)

    ps = points(milk_cloud)
    @test length(ps) == 640 * 480
    @test isa(ps, StdVector)
    @test isa(ps[1], PointXYZRGBARef)
    @test isa(ps[1], PointXYZRGBAValOrRef)

    cloud = PointCloud{PointXYZ}(2,3)
    @test width(cloud) == 2
    @test height(cloud) == 3

    @test typeof(PointCloud{eltype(cloud)}()) == typeof(cloud)
    @test typeof(similar(cloud)) == typeof(cloud)
end

@testset "PointCloud conversions" begin
    milk_cloud = PointCloud{PointXYZRGBA}(milk_cartoon_path)
    non_nan_idx = 100000
    @assert non_nan_idx < length(milk_cloud)

    milk_cloud_xyzrgb = convert(PointCloud{PointXYZRGB}, milk_cloud)
    @test isa(milk_cloud_xyzrgb, typeof(PointCloud{PointXYZRGB}()))
    for (s, T) in [(:x, Float32), (:y, Float32), (:z, Float32),
            (:r, UInt8), (:g, UInt8), (:b, UInt8)]
        @test T(milk_cloud_xyzrgb[non_nan_idx,s]) == T(milk_cloud[non_nan_idx,s])
    end

    milk_cloud_xyz = convert(PointCloud{PointXYZ}, milk_cloud)
    @test isa(milk_cloud_xyz, typeof(PointCloud{PointXYZ}()))
    for (s, T) in [(:x, Float32), (:y, Float32), (:z, Float32)]
        @test T(milk_cloud_xyzrgb[non_nan_idx,s]) == T(milk_cloud[non_nan_idx,s])
    end
end

@testset "loadPCDFile" begin
    cloudxyz = PointCloud{PointXYZ}()
    @test loadPCDFile(milk_cartoon_path, cloudxyz) == 0
    cloud_xyzrgb = PointCloud{PointXYZRGB}()
    @test loadPCDFile(milk_cartoon_path, cloud_xyzrgb) == 0
end
