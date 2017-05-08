# test.jl - toy Eulerian assembler in Julia
# Copyright 2014 - Humberto Ortiz-Zuazaga <humberto.ortiz@upr.edu>
# Distributed under the GNU General Public Licence v3. See LICENSE

# Function to make a random nucleotide sequence of length N
function randseq(n)
  a = rand(1:4, n)
  map((i) -> "acgt"[i], a)
end

# Print sequences (arrays of characters) nicely.
# If passed optional name, print a fasta format header.
function printseq(seq, name="")
  count = 0
  if ""!=name
    print(">")
    println(name)
  end
  for c in seq
    print(c)
    count = count + 1
    if count == 65
      println()
      count = 0
    end
  end
end

# make a set of random reads from a sequence
function makereads(seq, readlen, n)
  stop = length(seq) - readlen
  starts = rand(1:stop, n)
  map((i) -> seq[i:i+readlen-1], starts)
end

# Main function

# Initialize the random number generator to always make the same sequence
srand(0)

myseq = randseq(1000)
#printseq(myseq, "myseq")

reads = makereads(myseq, 15, 500)

map((seq) -> begin printseq(seq); println() end, reads[1:10])
