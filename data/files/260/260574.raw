facts("PivotMetadata") do
  colNames = [:age, :sex]
  rowNames = [:height]
  colLevels = Vector{Symbol}[[:LT15, :GT15][:M, :F]]
  rowLevels = Vector{Symbol}[[:short, :tall]]
  statisticNames = [:mean, :sd]
  statisticInCols = true

  pm = PivotMetadata(rowNames, colNames,
                     rowLevels, colLevels,
                     statisticNames, statisticInCols)
end
