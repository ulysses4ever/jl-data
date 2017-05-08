#! /usr/bin/julia

# Rosetta Code, Order disjoint list items

function order_disjoint{T<:AbstractArray}(m::T, n::T)
    rlen = length(n)
    rdis = zeros(Int, rlen)
    for (i, e) in enumerate(n)
        j = findfirst(m, e)
        while j in rdis && j != 0
            j = findnext(m, e, j+1)
        end
        rdis[i] = j
    end
    if 0 in rdis
        throw(DomainError())
    end
    sort!(rdis)
    p = copy(m)
    p[rdis] = n
    return p
end

testm = {["the", "cat", "sat", "on", "the", "mat"],
         ["the", "cat", "sat", "on", "the", "mat"],
         ["A", "B", "C", "A", "B", "C", "A", "B", "C"],
         ["A", "B", "C", "A", "B", "D", "A", "B", "E"],
         ["A", "B"],
         ["A", "B"],
         ["A", "B", "B", "A"],
         }

testn = {["mat", "cat"],
         ["cat", "mat"],
         ["C", "A", "C", "A"],
         ["E", "A", "D", "A"],
         ["B"],
         ["B", "A"],
         ["B", "A"],
         }

for i in 1:length(testm)
    m = join(testm[i], " ")
    n = join(testn[i], " ")
    p = join(order_disjoint(testm[i], testn[i]), " ")
    println("    (", m, ", ", n, ") => ", p)
end
