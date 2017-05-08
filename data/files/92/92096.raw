using DataFrames

import Base.map

function _apply(f :: Function, df :: DataFrame)
    args = {df[name][1] for name in names(df)}
    if any(isna, args) return NA end
    #println(f(2))
    #println(args, f(args...))
    #println("ARGS ", length(args))
    return f(args...)
end

function new_col(T, f :: Function, df :: DataFrame)
    col = DataArray(T, nrow(df))
    for i = 1:nrow(df)
        try
            #println("Applying $(f) to $(df[i, :])")
            col[i] = _apply(f, df[i, :])
        catch
            #println("ERROR while applying $(f) to $(df[i, :])")
            rethrow()
        end
    end
    return col
end

function rowindices(pred :: Function, df :: DataFrame)
    rows = Int[]
    i=1
    for r in eachrow(df)
        if pred(r)
            push!(rows, i)
        end
        i += 1
    end
    return rows
end

function each_col(f :: Function, df :: AbstractDataFrame, withNA=false)
    # A functor on seizure data
    res = DataFrame()
    for c in names(df)
        res[c] = f(withNA ? df[c] : df[c].data)
    end
    return res
end
