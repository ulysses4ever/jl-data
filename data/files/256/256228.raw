export register,
    protocol,
    protocol!,
    PROTOCOLS,
    key

immutable type Protocol{SCK<:Number,SCV<:String}
    name::String
    version::String
    status_codes::Associative{SCK, SCV}
    status_wo_msg::Array{SCK}
    supports::Array{String}
    prepare_res_headers::Function
    default_status::Integer
    header_msg_chunk::(String, String)
    header_msg_size::String
    req_post_init::Function
    res_post_init::Function
end

key(p::Protocol) = (p.name, p.version)

immutable type Protocols
    data::Associative{(String,String), Protocol}
end

Protocols() = Protocols(Dict{(String,String), Protocol}())

const PROTOCOLS = Protocols()

protocol(d::Protocols, name_version::(String,String)) = d.data[name_version]
protocol(name_version::(String,String)) = protocol(PROTOCOLS, name_version)

protocol!(d::Protocols, p::Protocol) = (d.data[(p.name, p.version)] = p)
protocol!(p::Protocol) = protocol!(PROTOCOLS, p)

protocol!(d::Protocols, name_version::(String,String), p::Protocol) = (d.data[name_version] = p)
protocol!(name_version::(String,String), p::Protocol) = protocol!(PROTOCOLS, name_version, p)

