module DriveShare
export get_dataset

using Requests: get, save
using DataFrames
import JSON

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