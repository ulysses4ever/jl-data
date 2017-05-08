


# julia main function
# execute this function

cd("/Users/florianoswald/git/RBC_codes/julia")

include("RBCmodule.jl")

# build model
m = RBCmod.Model();
show(m)

# force compilation
RBCmod.compute(m)

# reset
RBCmod.resetV!(m);

# time
withTypes = @elapsed RBCmod.compute(m)


# compare that with Jesus' version
include("RBC_Julia.jl")
noTypes = @elapsed main()
# do it twice to be fair to the JIT
noTypes = @elapsed main()

print((withTypes - noTypes) / noTypes)


# why is this still not faster?
RBCmod.resetV!(m);
@profile RBCmod.compute(m);
Profile.print()

# spend a lot of time in (1-m.bbeta)*log(consumption)+m.bbeta*m.expectedValueFunction[nCapitalNextPeriod,nProductivity]

# 1) get rid of multidim array access
# 2) take out (1-m.bbeta)


RBCmod.resetV!(m);
RBCmod.computeTuned(m)
RBCmod.resetV!(m);
Tuned = @elapsed RBCmod.computeTuned(m)


println("% time difference typed vs Jesus: $((withTypes - noTypes) / noTypes)")
println("% time difference tuned vs Jesus: $((Tuned - noTypes) / noTypes)")
