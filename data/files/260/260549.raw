type GroupedDataFrameCode
  parent::AbstractDataFrame
  cols::Vector           # columns used for sorting
  idx::Vector{Int}       # indexing vector when sorted by the given columns
  starts::Vector{Int}    # starts of groups
  ends::Vector{Int}      # ends of groups
  levelidx::Vector{Int}  # integer coded groups
end

function _markuniqueofsorted(x)
  n = length(x)
  res = ones(Bool, n)

  xprev = x[1]
  for i=1:(n-1)
    res[i] = x[i+1] != x[i]
  end
  return res
end

pda(da::DataArray, order) = PooledDataArray(da.data, order, da.na, Int)
pda(pda::PooledDataArray, order) = pda

@doc """
taken from the DataFrames package and modified to ensure that groups are encoded in an
order given by the `colorders` argument.
""" ->
function groupby{T}(df::AbstractDataFrame, cols::Vector{T}, colorders::Dict{T,Any})
  ## a subset of Wes McKinney's algorithm here:
  ##     http://wesmckinney.com/blog/?p=489

  ncols = length(cols)
  # use the pool trick to get a set of integer references for each unique item
  da = df[cols[ncols]]

  if haskey(colorders, cols[ncols])
    order = colorders[cols[ncols]]
    dv = pda(da, order)
  else
    dv = PooledDataArray(da)
  end
  # if there are NAs, add 1 to the refs to avoid underflows in x later
  dv_has_nas = (findfirst(dv.refs, 0) > 0 ? 1 : 0)
  x = copy(dv.refs) .+ dv_has_nas
  # also compute the number of groups, which is the product of the set lengths
  ngroups = length(dv.pool) + dv_has_nas
  # if there's more than 1 column, do roughly the same thing repeatedly
  for j = (ncols - 1):-1:1
    da = df[cols[j]]
    if haskey(colorders, cols[j])
      order = colorders[cols[j]]
      dv = pda(da, order)
    else
      dv = PooledDataArray(da)
    end
    dv_has_nas = (findfirst(dv.refs, 0) > 0 ? 1 : 0)
    for i = 1:nrow(df)
      x[i] += (dv.refs[i] + dv_has_nas- 1) * ngroups
    end
    ngroups = ngroups * (length(dv.pool) + dv_has_nas)
    # TODO if ngroups is really big, shrink it
  end
  (idx, starts) = DataArrays.groupsort_indexer(x, ngroups)
  # Remove zero-length groupings
  nonzerogroupings = _markuniqueofsorted(starts)
  starts = starts[nonzerogroupings]

  ends = [starts[2:end] .- 1] # change
  levelidx = Int[x[idx[endi]] for endi in ends]
#   println("idx:\n$idx\nends:\n$ends\nlevelidx:\n$levelidx")
  GroupedDataFrameCode(df, cols, idx, starts[1:end-1], ends, levelidx)
end

Base.start(gd::GroupedDataFrameCode) = 1
Base.next(gd::GroupedDataFrameCode, state::Int) =
    ((gd.levelidx[state], sub(gd.parent, gd.idx[gd.starts[state]:gd.ends[state]])),
     state + 1)
Base.done(gd::GroupedDataFrameCode, state::Int) = state > length(gd.starts)
Base.length(gd::GroupedDataFrameCode) = length(gd.starts)
Base.endof(gd::GroupedDataFrameCode) = length(gd.starts)
Base.first(gd::GroupedDataFrameCode) = gd[1]
Base.last(gd::GroupedDataFrameCode) = gd[end]
