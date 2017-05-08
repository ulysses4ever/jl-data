# test.jl - toy Eulerian assembler in Julia
# Copyright 2014 - Humberto Ortiz-Zuazaga <humberto.ortiz@upr.edu>
# Distributed under the GNU General Public Licence v3. See LICENSE

# Function to make a random nucleotide sequence of length N
function randseq(n)
  a = rand(1:4, n)
  map((i) -> "acgt"[i], a)
end

# Main function

# Initialize the random number generator to always make the same sequence
srand(0)

println(randseq(100))
