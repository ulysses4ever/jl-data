include("lib/data.jl")
include("lib/functions.jl")
include("lib/util.jl")
include("lib/pyfilters.jl")
using DataFrames
using PyPlot

function peak_count(samples)
   sum(extrema(samples))
end

sz = seizures()

sz = addcol((b, a) -> b - a,
            (:offset, :onset),
            sz, :length)
sz = addcol((a, b, l) -> (a-l):(b+l),
            (:onset, :offset, :length),
            sz, :range)
print(sz)
good_sz = []
sz = sz[5:7, :] # Only patient 2

b = loadfilter("filt0842")
filtr(x) = filtfilt(b, x)
isdefined(:dat) ||
@time (dat = addcol((a,b,c,d) -> each_col(filtr,
                                    get_samples(a, b, c, 1:3, d)),
                              (:patient, :patient_id, :hour, :range),
                              sz, :data))
#########
# STEPS #
#########

# Find peaks & troughs
peaks = each_sz(samples -> each_col(extrema, samples),
                (:data,), dat, :peaks)

# Find simultaneous peaks
find_simul(p) =
    p[1].data & p[2].data & p[3].data

simul = each_sz(find_simul, (:peaks,), peaks, :simul)
println(simul)

# Bin peaks into 6 bins
counts = each_sz(p -> sum_bin(p, 6),
             (:simul,), simul, :counts)

