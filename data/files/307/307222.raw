require("argparse")
using ArgParse

include("load.jl")

function parseTest()
        s = ArgParseSettings()
        @add_arg_table s begin
                "init"
                        help = "init file"
                        required = false
                "test"
                        help = "train file"
                        required = false
                "output"
                        help = "output file"
                        required = false
        end

        return parse_args(s)
end

function promptTest()
        parsedArgs=parseTest()

        if parsedArgs["init"] == nothing
                println("File containing neural network initialization:")
                initName = readline(STDIN)[1:end-1]
        else
                initName = parsedArgs["init"]
        end

        if parsedArgs["test"] == nothing
                println("File containing test set:")
                testName = readline(STDIN)[1:end-1]
        else
                testName = parsedArgs["test"]
        end

        if parsedArgs["output"] == nothing
                println("Name of output file:")
                outputName = readline(STDIN)[1:end-1]
        else
                outputName = parsedArgs["output"]
        end

        init = open(initName)
        test = open(testName)
        output = open(outputName, "w")

        return init, test, output, nepochs, alpha
end

stod(str::String) = convert(Float64,parse(str))::Float64

line2Arr(str::String) = [stod(x) for x in split(str::String)]::Array{Float64}
