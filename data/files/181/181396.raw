type ArtificalNeuron
    weights::Vector{Float64}
    bias::Float64
    activation_func::Function
end

function activate(an::ArtificalNeuron, x::Vector{Float64})
    # sum of weights times input, then add bias
    pre_activation = an.weights' * x + an.bias
    an.activation_func(pre_activation)
end
