using UnionFind
using Base.Test

function create_singleton()
    uf = UnionFinder(1)
    cf = CompressedFinder(uf)

    return uf, cf
end

uf, cf = create_singleton()

@test nodes(uf) == 1
@test nodes(cf) == 1
@test find!(uf, 1) == 1
@test find(cf, 1) == 1
@test groups(cf) == 1
