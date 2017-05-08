module DriveShare
export get_anonymized_paths, get_highlevel_info

using Requests: get, save
using DataFrames
import JSON

#=
function getSegment(name::AbstractString)
	json = get("http://driveshare.me/juliasegs/$name")
	save(json, "$name.json")
	JSON.parsefile("$name.json", dicttype=Dict, use_mmap=true)
end

function getAllSegments()
	json = get("http://driveshare.me/juliasegs/allthesegs")
	save(json, "allsegs.json")
	JSON.parsefile("allsegs.json", dicttype=Dict, use_mmap=true)
end

function getSegmentSummary()
	json = get("http://driveshare.me/segs")
	save(json, "segsummary.json")
	JSON.parsefile("segsummary.json", dicttype=Dict, use_mmap=true)
end
=#

function get_anonymized_paths()
	save(get("http://driveshare.me/anonUTM"), "anonUTM.json")
	JSON.parsefile("anonUTM.json", dicttype=Dict, use_mmap=true)
end

function get_highlevel_info()
	save(get("http://driveshare.me/highlevel"), "highlevel.csv")
	readtable("highlevel.csv")
end


function decodePolyline(str::AbstractString)
	# returns a list of (lat, lon) Float64 pts
	# reference: https://github.com/mapbox/polyline/blob/master/src/polyline.js

	retval = Tuple{Float64, Float64}[]

	lat, lon = 0.0, 0.0
	mult_factor = 1e5

	index = 0
	while index < length(str)

		byte = convert(UInt8, 0x20)
		shift = 0
		result = 0

		while byte ≥ 0x20
			byte = convert(UInt8, str[index+=1] - 63)
			result |= convert(Int, byte & 0x1f) << shift
			shift += 5
		end

		latitude_change = ((result & 1) > 0 ? ~(result >> 1) : (result >> 1))

		byte = convert(UInt8, 0x20)
		shift = result = 0;

		while byte ≥ 0x20
			byte = convert(UInt8, str[index+=1] - 63)
			result |= convert(Int, byte & 0x1f) << shift
			shift += 5
		end

		longitude_change = ((result & 1) > 0 ? ~(result >> 1) : (result >> 1))

		lat += latitude_change
        lon += longitude_change

        push!(retval, (lat/mult_factor, lon/mult_factor))
	end

	retval
end

end