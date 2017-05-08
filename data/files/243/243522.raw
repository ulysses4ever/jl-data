module SimPEG

# using BigLib: thing1, thing2

import Mesh

export Mesh

type MyType
    x
end

bar(x) = 2x
foo(a::MyType) = bar(a.x) + 1

show(io, a::MyType) = print(io, "MyType $(a.x)")
end
