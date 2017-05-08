type PivotMetadata
  rowNames::Vector{String}
  colNames::Vector{String}
  rowLevels::Vector{Vector{String}}
  colLevels::Vector{Vector{String}}
  statisticNames::Vector
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

function _sanitizelabels(labels::Vector)
  if length(labels) == 0
    return String[""]
  else
    return [string(lbl) for lbl in labels]
  end
end

function PivotMetadata(rowNames, colNames,
                       rowLevels, colLevels,
                       statisticNames, statisticInCols)
  rowNames = _sanitizelabels(rowNames)
  colNames = _sanitizelabels(colNames)
  return PivotMetadata(rowNames, colNames,
                       rowLevels, colLevels,
                       statisticNames, statisticInCols)
end

function ncols(pm::PivotMetadata)
  levels = copy(pm.colLevels)
  if pm.statisticInCols
    push!(levels, statisticNames)
  end
  return prod([length(level) for level in levels])
end

function nrows(pm::PivotMetadata)
  levels = copy(pm.rowLevels)
  if !pm.statisticInCols
    push!(levels, statisticNames)
  end
  return prod([length(level) for level in levels])
end
