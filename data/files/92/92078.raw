include("lib/data.jl")
include("lib/functions.jl")
include("lib/util.jl")
include("lib/pyfilters.jl")

using DataFrames
using Gadfly
using Compose

# Load seizures
sz = seizures()

# Length of seizures column
sz[:length] = new_col(Int, (b, a) -> b - a,
                      sz[:, [:offset, :onset]])

# Range of samples to take out (equal before, during and after)
sz[:range] = new_col(Range1{Int64}, (a, b, l) -> (a-l):(b+l),
                     sz[:, [:onset, :offset, :length]])

# Subset of seizures considered
good_szs = [(2,15),(2,18),(2,21),(3,105),(3,125),(3,127),(3,174),(4,207),(4,304),(4,323),(4,328),(6,11),(6,23),(6,30),(7,346),(7,372),(8,46),(10,137),(10,166),(10,200),(12,5),(12,15),(12,17),(12,19),(13,1),(13,40),(14,7),(14,15),(14,17),(14,19),(15,6),(15,9),(15,41),(15,88),(16,8),(16,27),(16,41),(16,83),(17,99),(17,110),(17,115),(17,123),(17,132),(20,13),(20,25),(20,55),(20,82),(20,94)]


#good_recs = [2, 17, 16,3, 13, 15, 12, 4, 6, 7, 8, 20, 10, 14]
sz = sz[rowindices(x -> ((x[:patient], x[:hour]) in good_szs), sz), :]

# Bins to put the entire data in (3 x parts per region)
const BINS = 6

# Find the total number of simultaneous peaks and troughs
# In each seizure
function peaks_and_troughs(X)
    P  = each_col(C -> extrema(C, :peaks), X1)
    T  = each_col(C -> extrema(C, :troughs), X1)

    P  = (P[1].data & P[2].data & P[3].data)
    T  = (T[1].data & T[2].data & T[3].data)

    P, T
end

# Find power spectrum density, sum them in two parts over 6 regions
function power_change(X)
    P, T = peaks_and_troughs(X)
    P_vals = X[1].data .* P
    P_vals
end

function magnitude(X)
    bin_sum(X, BINS) / length(X)
end

filters = {"x8_42"    => loadfilter("filt0842")}
           #    "x8_16.5"  => loadfilter("filt8-16.5"),
           #    "x16.5_25" => loadfilter("filt16.5-25"),
           #    "x25_33.5" => loadfilter("filt25-33.5"),

           #    "x33.5_42" => loadfilter("filt33.5-42")}
          

# Find peaks and troughs in each band
results = Vector{Union(NAtype, Int)}[]
powerspec = Array{Union{NAtype, Float64),2}[]
for s in eachrow(sz)
    try
        X  = get_samples(s[:patient],
                         s[:patient_id],
                         s[:hour], 1:3,
                         s[:range])
        X1 = each_col(C -> filtfilt(filters["x8_42"], C), X)
        P, T = peaks_and_troughs(X1)
        push!(results, [bin_sum(P, BINS), bin_sum(T, BINS)])

        push!(powerspec, )
    catch e
        push!(results, [NA, NA, NA, NA, NA, NA,
                        NA, NA, NA, NA, NA, NA])
        println("There was an error analyzing $(s[:patient]), hour $(s[:hour]): $(e)")
    end
end

function frame(res)
    columns = [[r[i] for r in res] for i in 1:length(res[1])]
    df = DataFrame()
    [df[i] = columns[i] for i in 1:length(columns)]
    return df
end

res = frame(results)
writetable("results/pandt.csv", hcat(sz, res))

diffs = DataFrame()
diffs[:P] = new_col(Float64, (b1,b2,a1,a2) -> (b1+b2 - (a1+a2)) / +(b1,b2,a1,a2),
                    res[:, [5, 6, 4, 3]])
diffs[:T] = new_col(Float64, (b1,b2,a1,a2) -> (b1+b2 - (a1+a2)) / +(b1,b2,a1,a2),
                    res[:, [11, 12, 10, 9]])

# Histograms
include("histograms.jl")
