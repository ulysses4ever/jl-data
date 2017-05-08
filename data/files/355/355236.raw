using StochJuMP, PIPS

MPI.Init()

numScen = 2
m = StochasticModel(numScen)

@defVar(m, 0 <= x <= 1)
@defVar(m, 0 <= y <= 1)

@addConstraint(m, x + y == 1)
setObjective(m, :Min, x*x + y)

for i in 1:numScen
    bl = StochasticBlock(m)
    @defVar(bl, w >= 0)
    @addConstraint(bl, w - x - y <= 1)
    setObjective(bl, :Min, w*w + w)
end

PIPS.pips_solve(m)
