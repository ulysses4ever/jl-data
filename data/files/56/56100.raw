using Jig

tally = 0
include("foo.jl")
tally += fails
include("bar.jl")
tally += fails
 
tally > 0 ? error("There are $tally failing tests in this suite") : nothing
