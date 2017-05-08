#!/usr/bin/env julia
#
# Random sampler. Usage: reservoir_sampler.jl <n> where n is the number of lines
# from standard input you want to sample [and print to standard output]

type ReservoirSampler{T}
  values::Array{Union(Nothing, T)}
  num_added::Int64
end

new(T, sz) = ReservoirSampler{T}(
    fill!(Array(Union(Nothing, T), sz), nothing),
    0
)

randint(n) = rem1(rand(Uint), n)

update(sampler, x) =
    let sz = length(sampler.values), n = (sampler.num_added += 1)
        index = (n <= sz ? n : randint(n))
        if index <= sz
            sampler.values[index] = x
        end
    end

nonnil_values(sampler) = sampler.values[1:min(sampler.num_added, length(sampler.values))]

sampler = new(Union(ASCIIString, UTF8String), int(ARGS[1]))
for line in eachline(STDIN)
    update(sampler, line)
end
for line in shuffle(nonnil_values(sampler))
    write(STDOUT, line)
end
