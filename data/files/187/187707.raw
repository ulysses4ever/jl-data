#
#
#
#
type Permutation
  order :: Array
  function Permutation ()
    new([])
  end
  function Permutation (array::Array)
    
    domain = map(_ -> _, 1:length(array))
    out = array
    order = array

    if sort(out) != domain
      throw("??")
    end

    new(array)
  end
end

function * (lhs::Permutation, rhs::Permutation)
  if len(lhs) != len(rhs)
    throw("")
  end
  return Permutation(map(x -> at(lhs, x), rhs.order))
end

function len(perm::Permutation)
  return length(perm.order)
end

# Evaluate permutation 
function at (perm::Permutation, i::Integer)
  return perm.order[i]
end

#
#
#
p = Permutation([ 1, 2, 3, 5, 4 ])
q = Permutation([ 5, 4, 3, 2, 1 ])

# println(len(p))
println(p*p*p)
# x = 1:5
# println(map(l -> l, x))