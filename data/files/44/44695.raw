using CVCore
using CVImgProc
using CVImgCodecs
using Base.Test

lenapng = Pkg.dir("OpenCV", "test", "lena.png")
lenamat = imread(lenapng)
@test size(lenamat) == (512,512,3)
@assert all(!isnan(lenamat))

@testset "UMat{T,N}" begin
    umat = UMat{UInt8}(3, 3)
    mat = Mat(umat)
    @test isa(mat, Mat)
    @test size(umat) == (3, 3)

    # make sure resize doesn't change the type of mat
    umat_resized = resize(umat, size(umat))
    @test isa(umat_resized, UMat)
    @test size(umat) == size(umat_resized)
end

@testset "cv::resize" begin
    mat = copy(lenamat)
    rows,cols,cn = size(mat)

    # shape as a tuple, acts like column-major
    mat2 = resize(mat, (200,300))
    @test size(mat2) == (200,300,3)

    # shape as a cv::Size, acts like row-major
    mat3 = resize(mat, CVCore.cvSize(200,300))
    @test size(mat3) == (300,200,3)
end
