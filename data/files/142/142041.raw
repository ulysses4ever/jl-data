using Base.Test

a = IndependentBelief(Normal(0,3), Gamma(1,2))
b = IndependentBelief(Normal(3,1), Gamma(3,4))
s = Socket([a,b],NO_BELIEF)

@test s.belief == NO_BELIEF
mix!(s)
@test s.belief != NO_BELIEF

clear_basin!(s)
@test isempty(s.basin)

clear_belief!(s)
@test s.belief == NO_BELIEF
