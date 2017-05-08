# Triggers define the methods the implementation responds to

triggers(x) = []

# Relating implementations/tags

function collectimps(tree::TagTree, tags; imps = Set{Any}())
  matches(tree.tag, tags) || return imps
  for c in children(tree)
    isa(c, TagTree) ?
      collectimps(c, tags; imps = imps) :
      push!(imps, c)
  end
  return imps
end

collectimps(tags) = collectimps(tagtree, tags)

# And turning them into method sets

typealias Methods Dict{Any, Set{Any}}

function collectmethods(imps; methods = Methods())
  for imp in imps
    for method in triggers(imp)
      push!(get!(methods, method, Set{Any}()), imp)
    end
  end
  return methods
end

methodset(tree::TagTree, tags) = collectmethods(collectimps(tree, tags))

methodset(tags) = methodset(tagtree, tags)

# Functions are implementations

name(f::Function) = f.env.name
triggers(f::Function) = Set([name(f)])
