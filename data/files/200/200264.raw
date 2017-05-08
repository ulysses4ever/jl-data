# this need to be included
include(joinpath(Pkg.dir(),"JulieTest/src/watch.jl"))

# the directory to watch (will be recursive)
watch = ["src","test"]

# currently only `spec` and `dot` is available
reporter = "spec"

# the interval of each test, default is int 0.25 second
interval = 0.25

# this will start JulieTest
julieTest()
