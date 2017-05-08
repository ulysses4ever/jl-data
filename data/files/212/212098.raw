type HODClient
    url                 ::ASCIIString
    root                ::ASCIIString
    version             ::VersionNumber
    api_default_version ::VersionNumber
    api_key             ::ASCIIString
    proxy               ::Dict
end

abstract HODResponse

for T in (:HODSyncResponse, :HODAsyncResponse)
    @eval type $T <: HODResponse
        response
        client
    end
end

type HODIndex
    documents::Vector{UTF8String}
    client::HODClient
    name::UTF8String

    function HODIndex(client::HODClient, name::UTF8String)
        new(Vector{UTF8String}[], client, name)
    end
end

type HODException <: Exception
    message::ASCIIString
    json_response
    code_code

    function HODException(rjson, code)

        new(message, json_response, error_code)
    end
end

type DocumentException <: Exception end
