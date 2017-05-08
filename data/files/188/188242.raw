module DynamicAnalysis

#using SQLite*
using DataFrames
using Lens

import DataFrames:groupby, DataFrame, SubDataFrame

export
  Problem,
  Algorithm,
  record,
  benchmark,

  # Statistics
  KL,
  KLsafe,

  # db
  groupby,
  where,
  all_records,
  all_done,
  collate

include("common.jl")
# include("db.jl")
include("run.jl")
include("analysis.jl")
# include("figure.jl")

"""
A module to benchmark and compare algorithms.

DynamicAnalysis exports two important types `Problem` and `Algorithm` and two
important functions `benchmark` and `record`.

- DynamicAnalsis is for benchmarking (a variety of) algorithms against problems.
- By benchmarking, we meen analysis of any quantity which emerges when an algorithm
  is solving a problem: e.g., runtime, memory used, optimal value (e.g. in optimisation)

API Overview
- common.jl defines main abstract types `Problem` and `Algorithm`.
  User will subtype both , e.g. `SortingProblem <: Problem`, `BubbleSort <: Algorithm`
  Only constraint (by convention) is that subtypes have `capture::Vector{Symbol}`
  capture is a vector of Lens names to be captured by DynamicAnalsis during benchmarking

- run.jl defines interface function `benchmark(::Algorithm, ::Problem)`
  User should implement this for her algorithm and problem
- run.jl defines - run(algos::Vector{A},problems::Vector{B};...)
  This is where dynamicanalysis are created.
  It runs a set of problems vs a set of algorithms, captures the statistics exported
  by the Len's and captured by captures.  And records results into a database or file.

- analysis.jl - contains a suite of (typically statistical) methods for data analysis
- figure.jl - Plotting
"""
DynamicAnalysis

end
