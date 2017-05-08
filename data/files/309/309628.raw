module Process

using DataFrames, Datetime, DataStructures

getCsvFiles(path) = sort(filter(f -> contains(f,".csv"), readdir(path)))

parsedate(s::String) = date(int64(s[1:4]), int64(s[5:6]), int64(s[7:8]) )
parseFileName(s::String) = s, split(s, "_")[2], parsedate(split(split(s, "_")[3],".")[1])
getData(inpath::String,fileName::String) = readtable(joinpath(inpath,fileName))

type Price
    price::Real
    bid::Int
    ask::Int
    last::Real
    lastSz::Int64
    updated::DateTime
end

# function parsedaily(df::DataFrame)

#     tkSz = mode(df[:,:ask1] - df[:,:ask]) # get the tick size
#     prices = OrderedDict{Float64,DataFrame}()

# #     bids  = array(df[:,[15:-2:7]])
# #     bidSz = array(df[:,[14:-2:6]])
# #     asks  = array(df[:,[17:2:25]])
# #     askSz = array(df[:,[16:2:24]])

#     pricecol = vcat([15:-2:7],[17:2:25])
#     sizecol  = vcat([14:-2:6],[16:2:24])
#     tradecol = [4,5]
#     for i = 1:size(df,1)
# #     for i = 45:50 #size(df,1)
#         for cID in pricecol
#             p = df[i,cID]
#             sz = p + 1
# #             println("$cID, $p")
#             if !haskey(prices,p) && p != 0.
#                prices[p] = DataFrame()
# #                 println("Added $p")
#             end

#         end
#     end
#     return prices
# end
immutable csvEvent
    dt::Int32 # date
#     tm::MsTime # time of day
    isExec::Int32
    bid::Float32
    ask::Float32
    lastAmt::Int32
    BS::Int32
    OC::Int32
    CP::Int32
    oType::Int32
    AcctID::Int32
end

function parseDate(d::String)
    y  = int(d[1:4])
    m  = int(d[6:7])
    d  = int(d[9:10])
    h  = int(d[12:13])
#     mn = int(d[15:16])
#     s  = int(d[18:19])

    return y,m,d,h#,mn,s
end



# function parseLine(v::Array)
#     acct = 0
#     try acct = int32(v[31]) catch acct = 0 end
#     return csvEvent(
#             int32(v[1]), # date
# #             MsTime(v[2]), # time of day
#             int32(v[3]), #isExec
#             float32(v[9]), # bid
#             float32(v[10]), #ask
#             int32(v[26]), # last amount
#             int32(v[27]), # BS
#             int32(v[28]), # OC
#             int32(parseCP(v[29])), # CP
#             int32(oTypes[string(v[30])]), # order type
#             acct) # AcctID
# end

# function parsedaily(inpath::String, fileName::String)


# # #     bids  = array(df[:,[15:-2:7]])
# # #     bidSz = array(df[:,[14:-2:6]])
# # #     asks  = array(df[:,[17:2:25]])
# # #     askSz = array(df[:,[16:2:24]])

#     f = open(joinpath(inpath,fileName),"r")
#     o = open(outPath,"w")
#     cnt = 0
#     while !eof(f)
#         l = readline(f)[1:end-2]
#         cnt += 1
#         if cnt > 1
#             e = parseLine(split(l,","))
# #             writeBinaryEvent(o,e) # All data
#         end
# #         if cnt > 50  break end
#     end
#     close(f)
#     close(o)
#     println("line count = $cnt")
# end


end

