#
# Correctness Tests
#

using Base.Test
using MixtureModels

my_tests = ["test/gmm.jl"]

@printf "Running tests:\n"

for my_test in my_tests
    @printf " * %s\n" my_test
    include(my_test)
end
