include("../src/ASF.jl")

using ASF, Base.Test, Requests

a = ASFRequest(ALOS,RelativeOrbit(124),Frame(840),ASF.CSV)
res = get(a)
@test statuscode(res) != 400
print_with_color(:green,"Request Status: $(statuscode(res))\n")

