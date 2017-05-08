#!usr/bin/env julia

module UsefulPackages

import Base.Pkg.add

export main, add


const packages = [ "a",
    "IJulia", "BackpropNeuralNet", "Bokeh", "Boltzmann", "Calculus",
    "Clustering", "Convex", "Cpp", "DataArrays", "DataFrames", "DataFramesMeta",
    "DataStructures", "DecisionTree", "Distances", "Distributions", "DSP",
    "FunctionalCollections", "Gadfly", "GeneticAlgorithms", "GLM", "GLMNet",
    "Graphs", "HDF5", "HypothesisTests", "Images", "JuMP", "MachineLearning",
    "Mamba", "Markdown", "Match", "MixedModels", "MLBase", "MultivariateStats",
    "NLopt", "Optim", "Orchestra", "PGM", "PyCall", "RCall", "RDatasets",
    "Regression", "StatsBase", "StreamStats", "TimeSeries", "Winston"
]


function add(packages...)
    try
        Pkg.update()
    catch
        warn("updating the metadata repo failed. This install run may ",
            "possibly install out-of-date versions of the packages.")
    end

    available = Pkg.available()
    installed = Pkg.installed()
    n = 0
    for package in packages
        if package ∈ available && package ∉ installed
            try
                Pkg.add(package)
                print_with_color(:cyan, STDERR,
                    @sprintf "INFO: %.2f%% complete.\n" 100n/length(packages)
                )
                n += 1
            catch e
                warn("the installation of $package encountered an error: $(e).")
            end
        else
            warn("package $package does not exist.")
        end
    end
end

main() = add(packages...)


end


using UsefulPackages; main()
