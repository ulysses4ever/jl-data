inpath = "/Users/Andre/Projects/Futures Data/Kospi/csv by contract/Front month/"
projectPath = "/Users/Andre/Projects/Futures_Pre-process/"
outpath = joinpath(projectPath,"output/")

include(joinpath(projectPath,"util.jl"))

files = Process.getCsvFiles(inpath)
f, m, d = Process.parseFileName(files[1])
df = Process.getData(inpath,f)
df[250000,1]

function parseDate(dt::String)
    y  = int(dt[1:4])
    m  = int(dt[6:7])
    d  = int(dt[9:10])
    h  = int(dt[12:13])
    mn = int(dt[15:16])
    s  = int(dt[18:19])
    ms = int(dt[21:23])
    ns = int(dt[24:26])

    return y,m,d,h,mn,s,ms,ns
end

parseDate(df[250000,1])
prices = Process.parsedaily(df)

ks = sort(collect(keys(prices)))
ks[end]-ks[1]

prices[ks[10]]
# # Actions taken
# Sell 100 -> Ask 100
# Buy 5 -> Ask 95, Trade 5
# Sell Cancel 15 -> Ask 80
# Sell 5 -> Ask 85
# Buy 90 -> Bid 0, Trade 80

# # Trade tick 1st
# S +100:  Ask 100  <- Sell 100
# TB  +5:  Trade 5  <- Buy 5
# B   -5:   ''
# TS  -5:   ''
# S   -5:  Ask 95   <-  Sell Reduce 5 (trade or cancel)

# # Quote tick 1st
# S +100:  Ask 100  <- Sell 100
# S   -5:  Ask 95   <- Sell Reduce 5 (trade or cancel)
# TB  +5:  Trade 5  <- Buy 5
# B   -5:   ''
# TS  -5:   ''
