require("argparse")
using ArgParse

function parseArgs()
        s = ArgParseSettings()
        @add_arg_table s begin
                "init"
                        help = "init file"
                        required = false
                "train"
                        help = "train file"
                        required = false
                "output"
                        help = "output file"
                        required = false
                "-e"
                        help = "number of epochs"
                        arg_type=Int
                "-a"
                        help = "learning rate"
                        arg_type=Float64
        end

        return parse_args(s)
end

function promptUser()
        parsedArgs=parseArgs()

        if parsedArgs["init"] == nothing
                println("File containing neural network initialization:")
                initName = readline(STDIN)[1:end-1]
        else
                initName = parsedArgs["init"]
        end

        if parsedArgs["train"] == nothing
                println("File containing training set:")
                trainName = readline(STDIN)[1:end-1]
        else
                trainName = parsedArgs["train"]
        end

        if parsedArgs["output"] == nothing
                println("Name of output file:")
                outputName = readline(STDIN)[1:end-1]
        else
                outputName = parsedArgs["output"]
        end

        if parsedArgs["e"] == nothing
                println("Number of epochs:")
                nepochs = int(readline(STDIN))
        else
                nepochs = parsedArgs["e"]
        end

        if parsedArgs["a"] == nothing
                println("Learning rate, alpha:")
                alpha = double(readline(STDIN))
        else
                alpha = parsedArgs["a"]
        end

        init = open(initName)
        train = open(trainName)
        output = open(outputName, "w")

        return init, train, output, nepochs, alpha
end

stod(str::String) = convert(Float64,parse(str))

line2Arr(str::String) = [stod(x) for x in split(str)]

function loadInit(init)
        initLines=readlines(init)
        (ni, nh, no) = int(split(initLines[1]))
        Theta1 = zeros(nh,ni+1)
        for i=1:nh
                Theta1[i,:] = line2Arr(initLines[1+i])
        end
        Theta2 = zeros(no, nh+1)
        for i=1:no
                Theta2[i,:] = line2Arr(initLines[1+nh+i])
        end

        return ni, nh, no, Theta1, Theta2
end

function loadTrain(train)
        trainlines=readlines(train)
        (m, ni, no) = int(split(trainLines[1]))
        X = zeros(m, ni)
        y = zeros(m, no)
        for i=1:m
               X[i,:] = split(trainLines[1+i])[1:ni]
               y[i,:] = split(trainLines[1+i])[ni+1:end]
        end
        return X, y
end
