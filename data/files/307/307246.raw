include("loadNN.jl")
include("mathNN.jl")
include("saveNN.jl")

( init, train, output, nepochs, alpha ) = promptUser()
(ni, nh, no, Theta1, Theta2) = loadInit(init)
( X, y) = loadTrain(train)

while nepochs
        (Theta1, Theta2) = gradientDescent(costFunction, Theta1, Theta2, X, y, alpha)
        nepochs -= 1
end
