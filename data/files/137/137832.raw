
using Rmath

# Resevior sampling
# Given some sequence of unknown size, pick an entry uniformly
# at random ( so essentially 1/n when sequence length is n)

function ReseviorSample(sequence::Vector{Float64})
    choice = sequence[1]
    for i = 1:size(sequence)[1]
        if rand() < 1.0 / i
            choice = sequence[i]
        end
    end
    return choice
end


# trying to get some basic Gibbs sampling
function SimpleGibbs(N::Int, thin::Int)
    mat = Array(Float64, (N, 2))
    x = 0
    y = 0

    for i = 1:N
        for j = 1:thin
            # x = Rmath::rgamma(1, 3, (y*y + 4)::Int)[1]
            # y = Rmath::rnorm(1, 1/(x+1), 1/sqrt(2*(x+1)))[1]
        end

        mat[i, :] = [x, y]
    end

    mat
end

rs = ReseviorSample([1:500.])
# tm = SimpleGibbs(20000, 200)