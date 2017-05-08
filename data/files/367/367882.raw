Pkg.add("FastaIO")
Pkg.update()
Pkg.status()
pwd()
# Windows / Linux
# cd("C:\\Users\\Nico\\Documents\\UFQ-FIL\\CompositionalAnalysis.jl\\src\\RelativeAbundance")
cd("//home//npalopoli//CompositionalAnalysis.jl//src//RelativeAbundance")

using FastaIO

function nucfreq(seq::ASCIIString,k::Int)
  N = length(seq) - k + 1
  countdinuc = Dict{ASCIIString, Float64}()
  for i in 1:N
    dinuc = seq[i:i+k-1]
    countdinuc[dinuc] = get(countdinuc, dinuc, 0.0) + 1/N
  end
  countdinuc
end

function nucfreqfromfile(file::ASCIIString)
  listnuc = Dict{ASCIIString, Dict{ASCIIString, Float64}}()
  FastaReader(file) do fr
    for (id, seq) in fr
      listnuc[id] = nucfreq(seq,1)
      for i in [2:4]
        merge!(listnuc[id],nucfreq(seq,i))
      end
      for key in collect(keys(listdinuc[id]))
#        a = haskey(listdinuc[id],key)
        println(key)
      end
    end
  end
  listnuc
end

listdinuc = nucfreqfromfile("test.fasta")

keys(listdinuc)
collect(keys(listdinuc))
haskey(listdinuc,collect(keys(listdinuc)))
keys(collect(keys(listdinuc)))
haskey(listdinuc[collect(keys(listdinuc))],"AT")
keys(listdinuc)



# fib(n) = n < 2 ? n : fib(n - 1) + fib(n - 2)
# fib(6)


# using Base.Test

# for freq in values(test)
#   @test_approx_eq sum(values(freq)) 1.0
# end

# Pkg.add("BioSeq")

# using BioSeq

# ntr"ACN"

# nt"ACN"

# macro nico_str(str)
#   println("Nico dice: $str")
# end

# nico"Hola"
# @nico_str "hola"
