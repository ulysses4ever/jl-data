module PkgVerifierServerPrototype

import HttpCommon
import Mux
import PkgVerifierPrototype
import JSON

export serve

repo = ""
certificates = Dict{ASCIIString,AbstractString}()

function get_certificate(req)
    package = req[:params][:package]
    cert = ""
    try 
        cert = certificates[package]
    catch error
        return "\"FAILURE\""
    end

    return cert
end

function put_certificate(req)
    package = req[:params][:package]
    
    cert = ASCIIString(req[:data])

    try
        PkgVerifierPrototype.open_data_certificate(repo, cert)
    catch error
        return string(error)
    end

    certificates[package] = cert

    return "\"SUCCESS\""
end

@Mux.app verifier_server_app = (
    Mux.defaults,
    Mux.page("/cert/:package", get_certificate),
    Mux.page("/push/:package", put_certificate),
    Mux.notfound())

function serve(local_repo::AbstractString)
    global repo = local_repo
    Mux.serve(verifier_server_app)
end

end # module
