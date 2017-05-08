module MetropolisUpdater

using Distributions
importall DataTransformations

export
  # types
    # metropolis
    ParameterType,
    MetropolisParameter,
    MetropolisVector,
    MetropolisMatrix,
    # calculated
    CalculatedValues,
    CalculatedValuesVector,
    CalculatedValuesMatrix,

  # constructors
    # metropolis
    createmetropolis,       # create Metropolis Vector or Matrix
    createcalculatedvalues,  # create CalculateValues Vector or Matrix

  # methods
    # metropolis
    fillcan!,          # fill candidate with values
    fillcur!,          # fill current with values
    updatestepsize!,   # update step size for cand distribution (adaptive MH)
    updatemh!,         # update the MH parameter
    # both
    activevalue        # select the candidate or current value based on whether
                       # or not object is involved in the update step

# source files
include("MCMCCalculated.jl")
include("MHParameters.jl")

end # module
