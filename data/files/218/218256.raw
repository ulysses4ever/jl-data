module SolveBio
using Requests

include("utils.jl")

API_HOST = get(ENV, "SOLVEBIO_API_HOST", "https://api.solvebio.com/")
API_KEY = get(ENV, "SOLVEBIO_API_KEY", "")
PKG_VERSION = v"0.0.1"

function login(api_key=API_KEY, api_host=API_HOST)
    # TODO: log in manually with username and password
    try
        res = request("GET", "v1/user")
        println("Logged in to $api_host as $(res["email"]).")
        return res
    catch e
        println("Login failed: $e")
    end
end

function request(method, path, query=Dict(), body=Dict(), args...)
    headers = {
        "Accept" => "application/json",
        "Content-Type" => "application/json",
    }

    if API_KEY != ""
        headers["Authorization"] = "Token $API_KEY"
    end

    # Slice of beginning slash
    if path[1] == '/'
        path = path[2:end]
    end

    useragent = "SolveBio Julia Client $PKG_VERSION [$VERSION $(Sys.MACHINE)]"
    headers["User-Agent"] = useragent

    uri = "$API_HOST$path"

    if method == "GET"
        res = get(uri; headers=headers, query=query, json=body)
    elseif method == "POST"
        res = post(uri; headers=headers, query=query, json=body)
    elseif method == "PUT"
        res = put(uri; headers=headers, query=query, json=body)
    elseif method == "PATCH"
        res = patch(uri; headers=headers, query=query, json=body)
    else
        error("Invalid request method: $method")
    end

    if (res.status < 200 || res.status >= 400)
        if res.status == 429
            error("API error: Too many requests, please retry in $(res.headers["retry-after"]) seconds")
        elseif res.status == 400
            content = formatSolveBioResponse(res, raw=false)
            error("API error: $(res.data)")
        else
            error("API error: $(res.status)")
        end
    end

    if (res.status == 204 || res.status == 301 || res.status == 302)
        return res
    end

    res = formatSolveBioResponse(res)
    return res
end

end
