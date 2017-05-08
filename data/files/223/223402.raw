using GNSS
using Base.Test
using Lint

# code cleanliness
@test isempty(lintpkg("GNSS", returnMsgs=true))

# try to load type-b file
@test_throws ErrorException readsp3(joinpath(dirname(@__FILE__), "data/igs11720.sp3"))

# load type-c file
@test size(readsp3(joinpath(dirname(@__FILE__), "data/igs18000.sp3"))) == (96, 10, 32)
