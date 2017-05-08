
using JSON
using SunlightAPIs
using MapLight

keys = readcsv("api-keys.csv")

for i in 1:first(size(keys))
    keyname = strip(keys[i, 1])
    key = strip(keys[i, 2])

    keyname == "maplight" && (global maplight_key = key)
    keyname == "sunlight" && (global sunlight_key = key)
end

(!isdefined(:sunlight_key) || !isdefined(:maplight_key)) && error("api-keys.csv must provide sunlight and maplight keys!")

att_sunlight_id = "d473e580c5684a658b754eb97566cb05"

att_bills = bills(sunlight_key, att_sunlight_id; cycle = 2012)

positions_on_att_bills = [ bill_positions(maplight_key, "us", bill["congress_no"], bill["bill_type"], bill["bill_no"]) for bill in att_bills ]

