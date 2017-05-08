Pkg.add("FastaIO")
Pkg.update()
Pkg.status()
pwd()
cd("C:\\Users\\Nico\\Documents\\UFQ-FIL\\CompositionalAnalysis.jl\\src\\RelativeAbundance")

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
#      listnuc[id] = nucfreq(seq,2)
      for i in [1,2]
        listnuc[id] = nucfreq(seq,i)
#        listdinuc[id] = push!(get(listdinuc, id, 0),nucfreq(seq,i))
#        listnuc[id] = nucfreq(seq,i)
      end
#      listnuc[id] = map(nucfreq,(seq,(1:2)))
#      listnuc[id] = map(2) do x; nucfreq(seq,x); end
#      listnuc[id] = x -> nucfreq(seq,x), [1,2,3,4]
    end
  end
  listnuc
end

listdinuc = nucfreqfromfile("test.fasta")


map([A, B, C]) do x
    if x < 0 && iseven(x)
        return 0
    elseif x == 0
        return 1
    else
        return x
    end
end


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
