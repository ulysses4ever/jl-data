module DynamicAnalysis

using SQLite
using DataFrames
using Lens
using Dates

import DataFrames.groupby

VERSION < v"0.4.0-dev" && using Docile

export
  Problem,
  Algorithm,
  record,
  benchmark,
  KL,
  KLsafe,

  # db
  groupby,
  where,
  all_records,
  all_done,
  collate

include("common.jl")
include("db.jl")
include("run.jl")
include("analysis.jl")

# include("figure.jl")

end