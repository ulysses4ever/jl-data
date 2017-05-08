module Pivots
  using DataFrames
  using Docile
  import DataFrames: groupby
  using Tables
  import TableInterface:
    Nullable, get,
    Table, Point, Box, CellRange, Layout, AbstractStyleElement, AbstractPresentationStyleElement,
    CartesianStyleElement, ExpandStyleElement, UniformStyleElement,
    ExpandDataElement, CartesianDataElement
  import Iterators: product
  import Formatting: sprintf1, format

  export Pivot, PivotMetadata, totable, summarize

  include("group.jl")
  include("pivot.jl")
  include("table.jl")
end # module
