#!usr/bin/env julia

packages = ["IJulia", "BackpropNeuralNet", "Bokeh", "Boltzmann", "Calculus", "Clustering",
            "Convex", "Cpp", "DataArrays", "DataFrames", "DataFramesMeta", "DataStructures",
            "DecisionTree", "Distances", "Distributions", "DSP", "FunctionalCollections",
            "Gadfly", "GeneticAlgorithms", "GLM", "GLMNet", "Graphs", "HDF5", "HypothesisTests",
            "Images", "IJulia", "JuMP", "MachineLearning", "Mamba", "Markdown", "Match",
            "MixedModels", "MLBase", "MultivariateStats", "NLopt", "Optim", "Orchestra", "PGM",
            "PyCall", "RCall", "RDatasets", "Regression", "StatsBase", "StreamStats", 
            "TimeSeries", "Winston"]

println("Updating metadata repo...")
try
    Pkg.update()
catch e
    println("Updating the metadata repo failed. This install run may possibly install out-of-date versions of the packages.")
end

installed = 0
for package in packages    
    println("Installing $package...")
    try
        Pkg.add(package)
    catch e
        println("The installation of $package encountered an error: $e")
    end
    installed += 1
    println("Installation of $package successful. $(100*installed/length(packages)) complete.")
end
