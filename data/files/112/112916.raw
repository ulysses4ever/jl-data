include("neuralnet.jl")

function test(numRing::Int, numCenter::Int, genomes::Array{Genome}, generations::Int)

    newGenomes=genomes
    nets = [generateNeuralNet(genomes[j], 1, numRing, numCenter, 2) for j=1:length(genomes)]

    for gens = 1:generations

        fitness = [0.0 for i=1:length(genomes)]

        for tests = 1:5

            hiddenMean = randn()
            hiddenSD = randn()^2

            fitchange = @parallel (vcat) for nn in 1:length(nets)
                fit = 0;

                for trials = 1:200
                    netTick!(nets[nn], [randn()*hiddenSD+hiddenMean])
                end;

                output = getOutput(nets[nn]);
                fit -= ((output[1]*16-8)-hiddenMean)^2;
                fit -= ((output[2]*16-8)-hiddenSD)^2;

                fit

            end

            fitness += fitchange;

        end

        println("Median fitness for generation $gens was $(median(fitness))")

        ng = createNextGen(newGenomes, fitness)
        newGenomes = ng
        nets = [generateNeuralNet(newGenomes[k], 1, numRing, numCenter, 2) for k=1:length(newGenomes)]

    end

    return newGenomes

end
