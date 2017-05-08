module Dataset
using SolveBio

function list()
    return SolveBio.request("GET", "v1/datasets")
end

function get(id)
    path = "v1/datasets/$id"
    return SolveBio.request("GET", path)
end

function search(id)
    path = "v1/datasets/$id/data"
    return SolveBio.request("POST", path)
end

end
