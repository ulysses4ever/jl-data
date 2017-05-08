module DriveShare
export get_dataset

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

function get_dataset(version)
	if version == :trace
		save(get("http://driveshare.me/anonUTM"), "anonUTM.json")
		return JSON.parsefile("anonUTM.json", dicttype=Dict, use_mmap=true)
	elseif version == :highlevel
		save(get("http://driveshare.me/highlevel"), "highlevel.csv")
		return readtable("highlevel.csv")
	end
end

end