include("lib/data.jl")
include("lib/functions.jl")
include("lib/util.jl")
include("lib/pyfilters.jl")
using DataFrames
using PyPlot

sz = seizures()

sz[:length] = new_col(Int, (b, a) -> b - a,
                      sz[:, [:offset, :onset]])


sz[:range] = new_col(Range1{Int64}, (a, b, l) -> (a-l):(b+l),
                     sz[:, [:onset, :offset, :length]])

good_recs = [2, 17, 16,3, 13, 15, 12, 4, 6, 7, 8, 20, 10, 14]
sz = sz[rowindices(x -> (x[:patient] in good_recs), sz), :]

coeffs = loadfilter("filt0842")
function analyze(patient, patient_id, hour, range)
    X  = get_samples(patient, patient_id, hour, 1:3, range)
    X1 = each_col(C -> filtfilt(coeffs, C), X)
    P  = each_col(extrema, X1)
    S  = P[1].data & P[2].data & P[3].data
    bins =  bin_sum(S, 6)
end

if ~isdefined(:redo) || ~redo
    results = Vector{Int}[]

    for s in eachrow(sz)
        println(s[:patient], " ", s[:hour])
        try
            bins = analyze([s[i] for i in
                            [:patient, :patient_id, :hour, :range]]...)
            push!(results, bins)
            plt.bar([1:length(bins)],
                    bins, color="green",
                    alpha = 1 / length(sz))
        catch
            println("There was an error analyzing $(s[:patient]), hour $(s[:hour])")
        end
    end
end

