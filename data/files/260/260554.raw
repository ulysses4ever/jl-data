type PivotMetadata
  rowNames::Vector{String}
  colNames::Vector{String}
  rowLevels::Vector{Vector{String}}
  colLevels::Vector{Vector{String}}
  statisticLevels::Vector
  statisticInCols::Bool

  function PivotMetadata(rowNames::Vector{String}, colNames::Vector{String},
                         rowLevels, colLevels, statisticNames, statisticInCols)
    nRowLevel, nColLevel = length(rowLevels), length(colLevels)
    nRows,     nCols     = length(rowNames),  length(colNames)

    nRowLevel == nRows ? nothing :
      error("dim mismatch. nrowLevels != nrows, $mRowLevel != $nRows")
    nColLevel == nCols ? nothing :
      error("dim mismatch. ncolLevels != ncols, $nColLevel != $mCols")

    return new(rowNames, colNames, rowLevels, colLevels, statisticNames, statisticInCols)
  end
end
incols(pm::PivotMetadata) = pm.statisticInCols
function rowNames(pm::PivotMetadata)
  if incols(pm)
    return pm.rowNames
  else
    res = copy(pm.rowNames)
    append!(res, ["stats"])
    return res
  end
end
function colNames(pm::PivotMetadata)
  if incols(pm)
    res = copy(pm.colNames)
    append!(res, ["stats"])
    return res
  else
    return pm.colNames
  end
end
function rowLevels(pm::PivotMetadata)
  if incols(pm)
    return pm.rowLevels
  else
    res = copy(pm.rowLevels)
    append!(res, Vector{String}[pm.statisticLevels])
    return res
  end
end
function colLevels(pm::PivotMetadata)
  if incols(pm)
    res = copy(pm.colLevels)
    append!(res, Vector{String}[pm.statisticLevels])
    return res
  else
    return pm.colLevels
  end
end

type Pivot
  data::Vector{Matrix}
  metadata::PivotMetadata


  function Pivot(data, metadata)
#     @assert size(data, 1) == size(metadata.rowLevels, 1)
#     @assert size(data, 2) == size(metadata.colLevels, 2)

    return new(data, metadata)
  end
end
metadata(p::Pivot) = p.metadata

function pivotstyles(p::Pivot)
  empty = [:html => [:class => "empty", :style => "border:0;"]]
  head = [:html => [:class => "head", :style => "text-align:center;"]]
  colhead = [:html => [:class => "subhead", :style => "text-align:center;"]]
  rowhead = [:html => [:class => "subhead", :style => "text-align:right;"]]
  datael = [:html => [:class => "datael", :style => "text-align:right;"]]

  n = length(p.data)
  styleelements = Array(AbstractPresentationStyleElement, n+5)
  styleelements[1:5] = [
    ExpandStyleElement(empty),
    ExpandStyleElement(head),
    UniformStyleElement(head),
    CartesianStyleElement(colhead),
    CartesianStyleElement(rowhead)
    ]
  for i=6:(n+5)
    styleelements[i] = UniformStyleElement(datael)
  end
  return styleelements
end
