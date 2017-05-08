export register,
    protocol,
    protocol!,
    PROTOCOLS,
    key,
    as_tuple

immutable type Protocol{SCK<:Number,SCV<:STR_TYPE}
    name::STR_TYPE
    version::STR_TYPE
    status_codes::Associative{SCK, SCV}
    status_wo_msg::Array{SCK}
    supports::Array{STR_TYPE}
    prepare_res_headers::Function
    default_status::Integer
    header_msg_chunk::(STR_TYPE, STR_TYPE)
    header_msg_type::STR_TYPE
    header_msg_size::STR_TYPE
    req_post_init::Function
    res_post_init::Function
end

key(p::Protocol) = (p.name, p.version)

immutable type Protocols
    data::Associative{(STR_TYPE,STR_TYPE), Protocol}
end

Protocols() = Protocols(Dict{(STR_TYPE,STR_TYPE), Protocol}())

const PROTOCOLS = Protocols()

status{K<:Integer, V<:STR_TYPE}(args::(K, V)...) = Dict{Integer, STR_TYPE}(args)
status{K<:Integer, V<:STR_TYPE}(d::Dict{K, V}) = convert(Dict{Integer, STR_TYPE}, d)

as_tuple(p::Protocol) = (p.name, p.version)

protocol(d::Protocols, name_version::(STR_TYPE,STR_TYPE)) = d.data[name_version]
protocol(name_version::(STR_TYPE,STR_TYPE)) = protocol(PROTOCOLS, name_version)

protocol!(d::Protocols, p::Protocol) = (d.data[(p.name, p.version)] = p)
protocol!(p::Protocol) = protocol!(PROTOCOLS, p)

protocol!(d::Protocols, name_version::(STR_TYPE,STR_TYPE), p::Protocol) = (d.data[name_version] = p)
protocol!(name_version::(STR_TYPE,STR_TYPE), p::Protocol) = protocol!(PROTOCOLS, name_version, p)