module DriveShare
export get_dataset

using Requests: get, save
using DataFrames
import JSON

function get_dataset(version)

    dirprefix = Pkg.dir("DriveShare", "data")
    if !isdir(dirprefix)
        mkdir(dirprefix)
    end

    if version == :trace
        url = "http://driveshare.me/anonUTM"
        filepath = joinpath(dirprefix, "anonUTM.json")
        success(`wget --continue --timestamping --output-document=$filepath $url`)
        sleep(0.1)
        return JSON.parsefile(filepath, dicttype=Dict, use_mmap=true)
    elseif version == :highlevel
        url = "http://driveshare.me/highlevel"
        filepath = joinpath(dirprefix, "highlevel.csv")
        success(`wget --continue --timestamping --output-document=$filepath $url`)
        sleep(0.1)
        return readtable(filepath)
    end

	# if version == :trace
	# 	save(get("http://driveshare.me/anonUTM"), "anonUTM.json")
	# 	return JSON.parsefile("anonUTM.json", dicttype=Dict, use_mmap=true)
	# elseif version == :highlevel
	# 	save(get("http://driveshare.me/highlevel"), "highlevel.csv")
	# 	return readtable("highlevel.csv")
	# end
end

end