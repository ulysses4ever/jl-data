module LotkaVolterra

using Iterators
using ODE

import Base.show

export AbstractLotkaVolterra,
       LogisticGrowth,GeneralizedLotkaVolterra,
       rate,specificrate,jacobian,
       somefixedpoint,hasfixedpoint,fixedpoint,fixedpoints,
       isfeasible,isstable,feasibility,stability,viability,
       odeint

include("utils.jl")
include("abstract.jl")
include("logistic.jl")
include("general.jl")

end
