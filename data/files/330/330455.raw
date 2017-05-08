module APhill

import DataFrames
import Distributions
import Gadfly
import Graphs
import Stan
import Mamba
#import PyCall
#import PyPlot



include("functions.jl")
include("GenerateSimulatedData.jl")
include("graphModel.jl")
include("renameSimNames.jl")
include("sharedModel.jl")

#matplotlib import breaks without a backend
#PyCall.pygui(:qt)
#include("chains2Ani.jl")
#export chains2Ani

export GenerateSimulatedData
export unfold, calculateFDR, HPDinterval, intToHexavigesimal, combinePDFs
export makeGraph, summariseComponents, GenerateLocations
export renameSimNames
export sharedModel


end
