using HDF5, JLD

metadata = load(joinpath(pwd(), "xdata/classifications.jld"))

flip(x) = (x[2], x[1])
function reverse_idx(vec)
    map(flip, collect(enumerate(vec))) |> Dict
end

categories = metadata["categories"]
category_idx = reverse_idx(categories)
tickers = metadata["tickers"]
ticker_idx = reverse_idx(tickers)
matrix = metadata["matrix"]

function gettickers(categories)
    cats = matrix[:, map(c -> category_idx[c], categories)]
    if length(cats) < 1
        return []
    else
        idxs = find(reducedim(|, cats, [2], false))
        return tickers[idxs]
    end
end

function getcategories(ticker)
    categories[find(matrix[ticker_idx[ticker], :])]
end
