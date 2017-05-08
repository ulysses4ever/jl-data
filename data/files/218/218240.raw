module Depository
using SolveBio

function list()
    return SolveBio.request("GET", "v1/depositories")
end

function get(id)
    path = "v1/depositories/$id"
    return SolveBio.request("GET", path)
end

function versions(id)
    path = "v1/depositories/$id/versions"
    return SolveBio.request("GET", path)
end

end
