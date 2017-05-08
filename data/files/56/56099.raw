using Jig

foo = 0
include("foo.jl")
foo += fails
include("bar.jl")
foo += fails
 
foo > 0 ? error("There are $foo failing tests in this suite") : nothing
