#
#
#
#
type Permutation
  order :: Array

  function Permutation (array)
    
    domain = map(_ -> _, 1:length(array))
    out = array
    order = array

    if sort(out) != domain
      throw("??")
    end

    new(array)

  end
end

#
#
#
function length (permutation::Permutation)
  return permutation.order
end

p = Permutation([ 1, 2, 3, 5, 4 ])

println(length(p))
# x = 1:5
# println(map(l -> l, x))