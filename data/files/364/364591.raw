include("loadTrain.jl")
include("mathNN.jl")
include("saveNN.jl")

( init, train, output, nepochs, alpha ) = promptTrain()
(ni, nh, no, Theta1, Theta2) = loadInit(init)
( X, y) = loadTrainData(train)

while nepochs>0
        (Theta1, Theta2) = gradientDescent(costFunction, Theta1, Theta2, X, y, alpha)
        nepochs -= 1
end

write(output, "$ni $nh $no\n")
writeThetas(output, Theta1, Theta2)
close(output)
