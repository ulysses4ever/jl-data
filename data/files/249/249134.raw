# Checking the sampler tables

module TablesTest  # separate namespace

using Base.Test

include("../src/randtn_zigtables.jl")

# basic properties
@test all(tnzig_yl .<= tnzig_yu)
@test all(diff(tnzig_x) .== tnzig_d)

# ncell index into x
n = length(tnzig_x)
xsimn = 10^6
for i = 1:xsimn
    x = tnzig_xmin + (tnzig_xmax - tnzig_xmin) * rand()
    i = tnzig_i0 + ifloor(x * tnzig_invh)
    # array boundaries
    @test i >= 1
    @test i <= length(tnzig_ncell)
    j = tnzig_ncell[i]
    @test j >= 1
    @test j <= n - 1
    # x[j] <= x < x[j+2] (or x[j+1] for j = n-1)
    @test tnzig_x[j] <= x
    @test tnzig_x[min(n, j+2)] > x
end

end