# Copyright (c) 2014 Eugene Wang
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

abstract Neuron

type LinNeuron <: Neuron
    zeroThreshold::Float64
    oneThreshold::Float64
    firingCoeffs::Array{Float64}
    inputOffset::Int
    currentState::Float64
    selfWeight::Float64
end

function setFire!(neuron::LinNeuron, inputs::Array{Float64})
    istate = fire(neuron)*neuron.selfWeight
    neuron.currentState = istate
    @simd for i = 1:length(neuron.firingCoeffs)
        @inbounds neuron.currentState += neuron.firingCoeffs[i]*inputs[i+neuron.inputOffset]
    end
end

function fire(neuron::LinNeuron)
    state = (neuron.currentState-neuron.zeroThreshold)/(neuron.oneThreshold-neuron.zeroThreshold)
    if state > 1
        return 1
    elseif state < 0
        return 0
    else
        return state
    end
end

type NeuralNet
    neuronOffset::Int
    neurons::Array{Neuron}
    outArray::Array{Float64}
    outputStart::Int
end

function netTick! (nn::NeuralNet, inputs::Array{Float64})
    for n in nn.neurons
        setFire!(n, nn.outArray);
    end
    outArray = [inputs, [fire(n) for n in nn.neurons]]
end

function getOutput (nn::NeuralNet)
    return @parallel (vcat) for i = nn.outputStart:length(nn.outArray)
        nn.outArray[i]
    end
end

# Genomes are pairs of boolean arrays used to initialize neural nets

type Genome
    s1::Array{Bool}
    s2::Array{Bool}
    Genome(s1, s2) = new(s1, s2)
end

function crossGenomes (g1::Genome, g2::Genome)
    r1 = randbool(length(g1.s1)) # Random bool array used to determine crossing over
    r2 = randbool(length(g2.s1))
    a1 = g1.s1 & r1 | g1.s2 & !r1
    a2 = g2.s1 & r2 | g2.s2 & !r2
    m1 = [rand(1:1000)==1?true:false for i = 1:length(g1.s1)]
    m2 = [rand(1:1000)==1?true:false for i = 1:length(g2.s1)]
    return Genome(r1$m1, r2$m2)
end

function createNextGen (genomeArray::Array{Genome}, fitnessArray::Array{Float64})
    for k in fitnessArray #Because NaN is not a good thing
        if isnan(k)
            k = -Inf
        end
    end
    fitnessOrder = sortperm(fitnessArray)
    crossingArray = []
    while length(crossingArray) < length(fitnessOrder)
        r = rand(1:length(genomeArray))
        if fitnessOrder[r] >= length(fitnessOrder)/2
            crossingArray = [crossingArray, fitnessOrder[r]]
        end
    end
    returnArray = []
    for i = 1:length(fitnessOrder)
        c1 = rand(1:length(fitnessOrder))
        c2 = rand(1:length(fitnessOrder))
        returnArray = [returnArray, crossGenomes(genomeArray[crossingArray[c1]], genomeArray[crossingArray[c2]])]
    end
    return returnArray
end

function createGenericGenome (numInputs::Int, numRing::Int, numCenter::Int, numOutputs::Int)
    # Creates a completely random genome of the apropriate size
    length = 
    (
      numRing*(5+numInputs+numCenter)+
      numCenter*(3+numRing)+
      numOutputs*(3+numRing)
    )*16
    a1 = randbool(length)
    a2 = randbool(length)
    return Genome(a1, a2)
end

function generateNeuralNet (genome::Genome, numInputs::Int, numRing::Int, numCenter::Int, numOutputs::Int)
    outputStart = numInputs + numRing + numCenter
    distA = distB = zeros (Int, length(genome.s1) >> 4)
    for i = length(distA), j = 1:16
        distA[i] += genome.s1[(i-1)*16+j]?1:0
    end
    for i = length(distB), j = 1:16
        distB[i] += genome.s2[(i-1)*16+j]?1:0
    end
    dg = (distA+distB)*.125 - 2
    ringpart = []
    for i = 1:numRing
        fa = (i-1)*(numInputs+numCenter+3);
        ca = [ringpart, LinNeuron(
            dg[fa+1],
            dg[fa+2],
            [[dg[fa+3+k] for k = 1:numInputs], [dg[fa+3+numInputs+k] for k = 1:numCenter]],
            0, 
            0.0,
            dg[fa+3]
        ) ]
        ringpart = ca
    end
    centerpart = []
    for i = 1:numCenter
        fb = (numRing)*(numInputs+numCenter+3) + (i-1)*(numRing+3);
        cb = [centerpart, LinNeuron(
            dg[fb+1],
            dg[fb+2],
            [dg[fb+3+k] for k = 1:numRing],
            numInputs+numCenter,
            0.0,
            dg[fb+3]
        ) ]
        centerpart = cb
    end
    outputpart = []
    for i = 1:numOutputs
        fc = (numRing)*(numInputs+numCenter+3) + (numCenter)*(numRing+3) + (i-1)*(numRing+3);
        cc = [outputpart, LinNeuron(
            dg[fc+1],
            dg[fc+2],
            [dg[fc+3+k] for k = 1:numRing],
            numInputs+numCenter,
            0.0,
            dg[fc+3]
        ) ]
        outputpart = cc
    end
    return NeuralNet(numInputs, [centerpart, ringpart, outputpart], zeros(numInputs+numCenter+numRing+numOutputs), outputStart)
end






        
