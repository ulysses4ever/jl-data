function createdataranges(start::Point{Int}, data, incols::Bool=true)
    tbldata = Matrix[]
    tblrngs = CellRange{Int}[]
    nelements = incols ? size(data[1],2) : size(data[1],1)
    kd = length(data)

    if incols
        numRows = size(data[1],1)
        for col=1:nelements
            for k=1:kd
                el = data[k]
                j = (col-1)*kd + k
                statrow = CellRange(
                    Box{Int}(Point(start.x + j - 1, start.y),
                             Point(start.x + j, start.y + numRows)),
                j+5,k+5)
                push!(tblrngs, statrow)
                push!(tbldata, reshape(el[:, col], numRows, 1))
            end
        end
    else
        numCols = size(data[1],2)
        for row=1:nelements
            for k=1:kd
                el = data[k]
                i = (row-1)*kd + k
                statrow = CellRange(
                    Box{Int}(Point(start.x, start.y + i - 1),
                             Point(start.x + numCols, start.y + i)),
                    i+5,k+5)
                push!(tblrngs, statrow)
                push!(tbldata, el[row,:])
            end
        end
    end
    return tbldata, tblrngs
end

const EMPTY = 1
const COLNAME = 2
const ROWNAME = 3
const COLLEVELS = 4
const ROWLEVELS = 5

checkstylelen(styles, p::Pivot) = (length(p.data) + 5 == length(styles)) ||
  error("length of data + 3 != length of styles")

function checkdatasize(p::Pivot)
    res = [size(el) for el in p.data]
    n = length(res)
    if n > 0
        el = res[1]
        for i=2:n
            if el != res[i]
                error("data sizes are not all the same\n$res")
            end
        end
    end
    return true
end

function totable(p::Pivot)
    styles = pivotstyles(p)
    checkstylelen(styles, p)
    checkdatasize(p)

    pm = p.metadata
    collevels = CartesianDataElement(colLevels(pm), true)
    rowlevels = CartesianDataElement(rowLevels(pm), false)
    rownames = rowNames(pm)
    rownames = reshape(rownames, 1, length(rownames))
    colnames = colNames(pm)

    # figure out where to place the tables
    rowRibbonHeight, rowRibbonWidth  = size(rowlevels)
    colRibbonHeight, colRibbonWidth = size(collevels)
    numCols = rowRibbonWidth + colRibbonWidth
    numRows = rowRibbonHeight + colRibbonHeight + 1

    emptydata = ExpandDataElement("", colRibbonHeight, rowRibbonWidth)
    colnames =  ExpandDataElement(join(colnames, " / "), 1, colRibbonWidth)

    emptyrng = CellRange(
        Box{Int}(Point(0,0), Point(rowRibbonWidth, colRibbonHeight)),
        EMPTY,EMPTY)
    colnamerng = CellRange(
        Box{Int}(Point(rowRibbonWidth, 0), Point(numCols, 1)),
        COLNAME,COLNAME)
    rownamerng = CellRange(
        Box{Int}(Point(0, colRibbonHeight), Point(rowRibbonWidth, colRibbonHeight + 1)),
        ROWNAME,ROWNAME)
    collevelrng = CellRange(
        Box{Int}(Point(rowRibbonWidth, 1), Point(numCols, 1+colRibbonHeight)),
        COLLEVELS,COLLEVELS)
    rowlevelrng = CellRange(
        Box{Int}(Point(0, 1+colRibbonHeight), Point(rowRibbonWidth, numRows)),
        ROWLEVELS,ROWLEVELS)

    data = Any[emptydata, colnames, rownames, collevels, rowlevels]
    rngs = CellRange{Int}[emptyrng; colnamerng; rownamerng; collevelrng; rowlevelrng]

    ndata, nrngs = createdataranges(Point(rowRibbonWidth, colRibbonHeight + 1),
                                    p.data, incols(p.metadata))
    append!(data, ndata)
    append!(rngs, nrngs)

    return Table(data, Layout(rngs), styles)
end

function strings(xs)
    n = length(xs)
    res = fill(String[], n)
    for i=1:n
        res[i] = map(string, xs[i])
    end
    return res
end

function levellength(xs)
    if length(xs) > 0
        return prod([length(x) for x in xs])
    else
        return 1
    end
end

@doc """
Args:
  df:           DataFrame to summarize
  rowvars:      row variables in table
  colvars:      column variables in table
  stats:        aggregate statistics to decribe each combination
                of row and column variables
  statnames:    statistic names used for table
  varorders:    makes the levels of the row and column variables
                follow the order given
  stat_in_cols: if true then the statistics are considered column
                levels of the "stats" variable. Otherwise they are
                row levels.

Usage:

```
using RDatasets
using Pivots
using Tables.HTMLFormat
const tb = Tables.HTMLFormat

house = RDatasets.dataset("Ecdat", "Housing")
p = summarize(
    house,
    rowvars      = [:Bedrooms],
    colvars      = Symbol[],
    statnames    = String["mean(price)", "std(price)", "count"],
    stats        = [df->mean(df[:Price]), df->std(df[:Price]), df->length(df[:Price])],
    varorders    = [:Bedrooms => Int32[1:6], :Driveway => ["no", "yes"]],
    stat_in_cols = true)

tbl = totable(p)
tb.HTML(tbl)
```
""" ->
function summarize{T <: String}(
    df::AbstractDataFrame;
    rowvars::Vector{Symbol} = Symbol[],
    colvars::Vector{Symbol} = Symbol[],
    stats::Vector{Function} = Function[],
    statnames::Vector{T} = fill("", length(stats)),
    varorders=Dict{Symbol,Any}(),
    stat_in_cols=true)

    @assert length(statnames) == length(stats)

    levels_of_rowvars = [haskey(varorders, rowvar) ? varorders[rowvar] :
                           unique(df[rowvar]) for rowvar in rowvars]
    levels_of_colvars = [haskey(varorders, colvar) ? varorders[colvar] :
                           unique(df[colvar]) for colvar in colvars]

    rownames = String[string(rowvar) for rowvar in rowvars]
    colnames = String[string(colvar) for colvar in colvars]

    pm = PivotMetadata(rownames, colnames,
                       strings(levels_of_rowvars),
                       strings(levels_of_colvars), statnames, stat_in_cols)

    statlen = length(stats)

    # determine how big the statistic matrices are
    n = levellength(levels_of_rowvars)
    m = levellength(levels_of_colvars)

    # create the global statistics
    frsts = [stat(df[1,:]) for stat in stats]
    types = [typeof(frst) for frst in frsts]

    # make the statistic matrices
    results = [fill(Nullable{tp}(), n, m) for tp in types]

    allvars = [colvars; rowvars]
    if length(allvars) > 0
        for (i,grp) in groupby(df, allvars, varorders)
            for k=1:statlen
                results[k][i] = Nullable{types[k]}(stats[k](grp))
            end
        end
    else
        for k=1:length(types)
            results[k][1,1] = Nullable{types[k]}(statistics[k](df))
        end
    end

    p = Pivot(results, pm)

    return p
end
