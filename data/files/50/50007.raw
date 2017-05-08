using Lazy

import Base: in, show, getindex

# Basic Structures

immutable TagOr
  a
  b
end

immutable TagAnd
  a
  b
end

or(x) = x
and(x) = x
or(a, b) = TagOr(a, b)
and(a, b) = TagAnd(a, b)
or(xs...)  =  reduce(or, xs)
and(xs...) = reduce(and, xs)

matches(tag, tags) = tag in tags
matches(tag::Type{Any}, tags) = true
matches(tag::TagOr,  tags) = matches(tag.a, tags) || matches(tag.b, tags)
matches(tag::TagAnd, tags) = matches(tag.a, tags) && matches(tag.b, tags)

# Tag Parsing & Printing

parsetag(tag::Symbol) = tag

parsetag(tag::QuoteNode) = tag.value

parsetag(tag::Expr) =
  isexpr(tag, :quote) ? tag.args[1] :
  isexpr(tag, :tuple) ?  or(map(parsetag, tag.args)...) :
  isexpr(tag, :.)     ? and(map(parsetag, tag.args)...) :
  error("Unsupported tag expression $tag of type $(tag.head)")

parsetag(tag::Tuple) = TagOr(map(parsetag, tag)...)

tag(x) = parsetag(x)

macro tag_str(s)
  t = parsetag(parse(s))
  isa(t, Symbol) ? Expr(:quote, t) : t
end

macro tag_ (s)
  t = parsetag(s)
  isa(t, Symbol) ? Expr(:quote, t) : t
end

showtag(x) = x
showor(x) = showtag(x)
showor(t::TagOr) = "$(showor(t.a)), $(showor(t.b))"
showtag(t::TagOr)  = "($(showor(t.a)), $(showor(t.b)))"
showtag(t::TagAnd) = "$(showtag(t.a)).$(showtag(t.b))"
show(io::IO, t::Union(TagOr, TagAnd)) = print(io, "tag\"", showor(t), "\"")

# Decomposition

mapcat(f, xs) = vcat(map(f, xs)...)

mapcart(f, xs, ys) = mapcat(x -> map(y -> f(x, y), ys), xs)

splithairs(x) = {{x}}
splithairs(o::TagOr) = vcat(splithairs(o.a), splithairs(o.b))
splithairs(a::TagAnd) = mapcart(vcat, splithairs(a.a), splithairs(a.b))

decompose(x) = map(xs -> unique(sort(xs)), splithairs(x))

==(a::Union(TagOr, TagAnd), b::Union(TagOr, TagAnd)) =
  decompose(a) == decompose(b)

# The Tag Tree
# TODO: Don't use sets for this
# perhaps split child nodes and data

type TagTree
  tag
  parent::TagTree
  children::Set{Any}

  TagTree(tag, parent::TagTree, children = Set()) = new(tag, parent, children)

  function TagTree(tag = Any, children = Set())
    tr = new()
    tr.tag, tr.parent, tr.children = tag, tr, children
    return tr
  end
end

==(a::TagTree, b::TagTree) = a.tag == b.tag && a.children == b.children
Base.hash(t::TagTree, h::Uint) = h $ hash(t.tag) $ hash(t.children)
Base.push!(t::TagTree, x) = push!(children(t), x)
Base.delete!(t::TagTree, x) = (delete!(children(t), x); trim!(t))

function trim!(tr::TagTree)
  if isempty(tr.children) && tr.parent != tr
    delete!(tr.parent, tr)
    trim!(tr.parent)
  end
  return
end

children(tr) = tr.children

function show(io::IO, tree::TagTree)
  print(io, "{", tree.tag, ": ")
  print_joined(io, tree.children, ", ")
  print(io, "}")
end

function getindex(tr::TagTree, ta)
  tr.tag == ta && return tr
  for c in children(tr)
    isa(c, TagTree) && c.tag == ta && return c
  end
  tree = TagTree(ta, tr)
  push!(tr, tree)
  return tree
end

nodes!(tr::TagTree, ta) = map(branch -> foldl(getindex, tr, branch), decompose(ta))

function assoc!(tree::TagTree, tag, x)
  for node in nodes!(tree, tag)
    push!(node, x)
  end
  refreshtag!(tag)
end

function dissoc!(tree::TagTree, tag, x)
  for node in nodes!(tree, tag)
    delete!(node, x)
  end
  refreshtag!(tag)
end

# Tag/Implementation interface

const tagtree = TagTree()

current_tag = nothing
current_tag!(t) = (global current_tag = t)

macro tag (t)
  :(current_tag!(@tag_ $(esc((t)))))
end

macro + (x)
  :(assoc!(tagtree, current_tag, $(esc(x))))
end

macro - (x)
  :(dissoc!(tagtree, current_tag, $(esc(x))))
end
