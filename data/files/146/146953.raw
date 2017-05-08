using DictUtils

x = ["bar"=>0.0,"baz"=>1.0]
y = ["foo"=>1.0,"bar"=>1.0,"baz"=>1.0]
u = ["foo"=>1.0,"bar"=>2.0,"baz"=>3.0]
v = ["foo"=>1.0,"bar"=>2.0,"baz"=>3.0]

@assert coalesce(1,null,2) == 1
@assert coalesce(null,1,2) == 1
@assert coalesce(null,null,2) == 2

addDicts!(x, y, 1.0)
@assert x == ["foo"=>1,"bar"=>1,"baz"=>2]

normalizeDict!(x)
@assert x == ["foo"=>0.25,"bar"=>0.25,"baz"=>0.5]

sortedHead!(u, 4)
@assert u == ["foo"=>1,"bar"=>2,"baz"=>3]
sortedHead!(u, 2)
@assert u == ["foo"=>1,"bar"=>2]

sortedTail!(v, 4)
@assert v == ["foo"=>1,"bar"=>2,"baz"=>3]
sortedTail!(v, 2)
@assert v == ["bar"=>2,"baz"=>3]

@assert showCompact(v) == "bar:2.0,baz:3.0"
@assert parsePrimitive(String, "3") == "3"
@assert parsePrimitive(Float64, "3") == 3.0
@assert parsePrimitive(Int64, "3") == 3
@assert parseCompact("bar:2,baz:3", String, Float64) == v
