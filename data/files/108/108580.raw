# Parse RSS documents
module RSS
import HTTPClient: get


type HTTPError <: Exception end
type NotImplementedError <: Exception end


function parse(url)
    #= Parse an RSS feed
      input:
        url: A URL to an RSS feed
    =#
    response = get(url)

    if response.http_code != 200
        info("Invalid status code $(response.http_code)")
        throw(HTTPError())
    end

    body = bytestring(response.body)

    info("TODO: parse '$body'")
    throw(NotImplementedError())
end

export parse, HTTPError, NotImplementedError
end
