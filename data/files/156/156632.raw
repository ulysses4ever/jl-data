module GTD

using DataFrames

############
# Utilities
############

include("this.jl")
include("that.jl")

export @listable

macro listable(f)
  if typeof(f) == Expr && f.head == :tuple
    return Expr(:block, [:(@listable $f) for f in f.args]...)
  end
  f = esc(f)
  :($f(ls::List...) = map($f, ls...))
end
