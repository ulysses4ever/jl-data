using HDF5, JLD

const metadata = load(joinpath(dirname(@__FILE__), "xdata", "classifications.jld"))

flip(x) = (x[2], x[1])
function reverse_idx(vec)
    map(flip, collect(enumerate(vec))) |> Dict
end

const categories = metadata["categories"]
const category_idx = reverse_idx(categories)
const tickers = metadata["tickers"]
const ticker_idx = reverse_idx(tickers)
const matrix = metadata["matrix"]

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
