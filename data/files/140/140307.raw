module JsonIO
using JSON

export loadDataset, saveDataset

function loadDataset(jsonFile::String)
    # Load a json dset
    f = open(jsonFile)
    dset = JSON.parse(f)
    close(f)
    return dset
end

function saveDataset(dset::Dict, jsonFile::String)
    # Save a Dict as json file
    f = open(jsonFile, "w")
    write(f, JSON.json(dset))
    close(f)
end

end#module
