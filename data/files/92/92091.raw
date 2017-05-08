using DataFrames

import Base.map
function each_col(f :: Function, df :: AbstractDataFrame, withNA=false)
    # A functor on seizure data
    res = DataFrame()
    for c in names(df)
        res[c] = f(withNA ? df[c] : df[c].data)
    end
    return res
end

function each_sz(f :: Function, args :: Tuple,
             df :: AbstractDataFrame, colname=nothing)
    res = DataFrame()
    take_args(row) = [row[sym][1] for sym in args]
    g(row) = f(take_args(row)...)
    res[colname == nothing ? 1 : colname] =
        Base.map(g, [df[i, :] for i = 1:size(df, 1)])
    return res
end

addcol(f :: Function, args :: Tuple, df :: DataFrame, colname=nothing) =
    hcat(df, each_sz(f, args, df, colname))
