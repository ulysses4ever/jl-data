using HDF5, JLD

# preprocess stock ticker classification files

lines = open("classifications.txt") do txt
    readlines(txt)
end

function getcategories(str)
    if strip(str) == "???" || str == ""
        return []
    else
        try
            tuple = [eval(parse(str))...]
        catch
            println(str)
        end
    end
end

function splitup(str)
    k, v = split(str, ',', 2)
    (k, getcategories(v))
end

dict = Dict(map(splitup, lines))
ntickers = length(dict)

categories = [Set(reduce(vcat, values(dict)))...] |> sort
ncats = length(categories)

flip(x) = (x[2], x[1])
category_idx = map(flip, collect(enumerate(categories))) |> Dict

tickers = sort(collect(keys(dict)))
ticker_idx = map(flip, collect(enumerate(tickers))) |> Dict

matrix = zeros(Bool, ntickers, ncats)
for (sym, rowid) in ticker_idx
    for cat in dict[sym]
        colid = category_idx[cat]
        matrix[rowid, colid] = true
    end
end

# Write out preprocessed data

jldopen("classifications.jld", "w") do f
    @write f tickers
    @write f categories
    @write f matrix
end
