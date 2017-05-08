module LotkaVolterra

using Iterators
using Match
using ODE

import Base.show

export AbstractLotkaVolterra,
      LogisticGrowth,PredatorPrey,GeneralizedLotkaVolterra,
      communitymatrix,intrinsicrate,
      issector,sectors,
      rate,specificrate,jacobian,
      somefixedpoint,isfixedpoint,fixedpoint,fixedpoints,
      somefeasible,isfeasible,feasibility,
      somestable,isstable,stability,
      someviable,isviable,viability,
      odeint

include("utils.jl")
include("abstract.jl")
include("logistic.jl")
include("predatorprey.jl")
include("general.jl")

end
