include("DataDictionary.jl")
include("SolveBalances.jl")
include("PlotSingle.jl")

# Setup the timescale -
TSTART = 0.0
TSTOP = 3.0
Ts = 0.01

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)

data_dictionary["INITIAL_CONDITION_ARRAY"][[24,26:28]] /= 5

Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)

PlotSingle(Tsim,X,data_dictionary)
