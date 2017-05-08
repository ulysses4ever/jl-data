Pkg.add("FastaIO")

using FastaIO

function dinuc_freq(seq::ASCIIString)
  N = length(seq) - 1
  counter = Dict{ASCIIString, Float64}()
  for i in 1:N
    dinuc = seq[i:i+1]
    counter[dinuc] = get(counter, dinuc, 0.0) + 1/N
  end
  counter
end

function dinucfreqfromfile(file::ASCIIString)
  list = Dict{ASCIIString, Dict{ASCIIString, Float64}}()
  FastaReader(file) do fr
    for (id, seq) in fr
      list[id] = dinuc_freq(seq)
    end
  end
  list
end

test = dinucfreqfromfile("test.fasta")

using Base.Test

for freq in values(test)
  @test_approx_eq sum(values(freq)) 1.0
end

Pkg.add("BioSeq")

using BioSeq

ntr"ACN"

nt"ACN"

macro nico_str(str)
  println("Nico dice: $str")
end

nico"Hola"
@nico_str "hola"
