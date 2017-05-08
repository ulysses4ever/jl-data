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

# make an k-mer graph from the reads
using Graphs

# see https://stackoverflow.com/questions/24578430/changing-vertices-value-with-graphs-jl
# for example julia Graphs with non integer vertices.
function empty_graph()
  va::Array{Graphs.ExVertex,1} = {}
  ea::Array{Graphs.ExEdge{Graphs.ExVertex},1} = {}
  G = Graphs.graph(va,ea)
end

function add_label!(G,s::ASCIIString)
  v = Graphs.ExVertex(Graphs.num_vertices(G) + 1,s)
  Graphs.add_vertex!(G,v)
  v
end

function add_connection!(G,from::Int,to::Int)
  va = Graphs.vertices(G)
  e = Graphs.ExEdge(Graphs.num_edges(G) + 1,va[from],va[to])
  Graphs.add_edge!(G,e)
  e
end

function kmergraph(reads)
  g = empty_graph()
  k = 9
  for read in reads
    for i in 1:length(read)-k
      kmer_a = read[i:i+k-1]
      kmer_b = read[i+1:i+k]
    end
  end
  g
end

# Main function

# Initialize the random number generator to always make the same sequence
srand(0)

myseq = randseq(1000)
#printseq(myseq, "myseq")

readcount = 500
readlen = 15
reads = makereads(myseq, readlen, readcount)

# insert some errors into some of the reads
percenterror = 3  # error rate as an integer percentage
errorcount = div(percenterror * readcount,  100)

for i in readcount-errorcount:readcount
  reads[i][div(readlen, 2)] = 'x'
end

#map((seq) -> begin printseq(seq); println() end, reads[1:10])

map((seq) -> begin printseq(seq); println() end, reads[end-20:end])

g = kmergraph(reads)

add_label!(g, "tagttgxg")
g
