
using DataFrames
# need y is coming out as a 2dim array so this is hack to get it to 1dim so can be a df
df = DataFrame(TIME = time, CONC = conc)

using Gadfly

plot(df, x = "TIME", y = "CONC", Geom.line)
