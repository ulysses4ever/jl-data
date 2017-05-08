using CVCore
using CVImgProc
using Base.Test

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
