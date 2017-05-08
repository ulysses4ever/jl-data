using StatsBase

module GeoLM

    using StatsBase
    export                              # types
        MinLmfit,

                                        # functions
        minlmfit,       # a minimal linear model fit
        coef,           # extract estimated regression coefficients
        resid,          # extract residuals
        residuals,      # extract residuals
        corr            # extract unscaled vcov for coef

    abstract MinLmfit                  # Minimal linear model

    include("minlmfit.jl")

end # module
