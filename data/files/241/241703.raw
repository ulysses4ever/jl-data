#!/usr/bin/env julia

module Jld2Mat

include("Params.jl")
include("Util.jl")

using .Util

printlog("Loading modules")
printlog("HDF5...")
using HDF5
printlog("JLD...")
using JLD
printlog("MAT...")
using MAT

function main()
    if length(ARGS) == 0
        println("Usage: jld2mat file1.jld [file2.jld ...]")
    end
    for file in ARGS
        if ! isfile(file)
            error("'$file' is not a file")
        end
    end

    for file in ARGS
        outfile = "$file.mat"
        if endswith(".jld", lowercase(file))
            outfile = string(file[1:end-4], ".mat")
        end
        printlog("Opening $file")
        f = jldopen(file, "r")
        printlog("Extracting variables from $file")
        vars = read(f)
        printlog("Writing to $outfile")
        matwrite(outfile, vars)
    end
end

printlog("Running main()")

main()

end # module
