#==============================================================================#
# AWSSDB.jl
#
# SDB API. See http://aws.amazon.com/documentation/simpledb/
#
# Copyright Sam O'Connor 2016 - All rights reserved
#==============================================================================#


__precompile__()


module AWSSDB


export sdb_list_domains, sdb_create_domain, sdb_delete_domain,
       sdb_delete_item, sdb_put, sdb_get, sdb_select,
       SimpleDB


using AWSCore
using XMLDict
using SymDict

using Compat
import Compat: String



# Associative get/setindex! interface...

type SimpleDB <:Associative{AbstractString,AbstractString}
    aws
    domain
end


function Base.get(db::SimpleDB, key::AbstractString, default)
    r = sdb_get(db, key)
    return r == nothing ? default : r
end

Base.setindex!(db::SimpleDB, v, key::AbstractString) = sdb_put(db, key, v)



# SDB API Interface...

function sdb(aws::AWSConfig, action, query::Dict)
    query["Action"] = action
    do_request(post_request(aws, "sdb", "2009-04-15", query))
end

sdb(aws::AWSConfig, action, query::SymbolDict) = sdb(aws, action, StringDict(query))

sdb(aws::AWSConfig, action; args...) = sdb(aws, action, StringDict(args))


function sdb_list_domains(aws::AWSConfig)
    r = sdb(aws, "ListDomains")["ListDomainsResult"]
    list = String[]
    if r != ""
        r = r["DomainName"]
        for d in (isa(r, Vector) ? r : [r])
            push!(list, d)
        end
    end
    return list
end


function sdb_create_domain(aws::AWSConfig, name)
    sdb(aws, "CreateDomain", DomainName = name)
end


function sdb_delete_domain(aws::AWSConfig, name)
    sdb(aws, "DeleteDomain", DomainName = name)
end


function sdb_delete_item(aws::AWSConfig, DomainName, ItemName)
    sdb(aws, "DeleteAttributes", @SymDict(DomainName, ItemName))
end


function sdb_put(aws::AWSConfig, DomainName, ItemName, dict; replace=true)

    attrs = StringDict()
    i = 1
    for (a, v) in dict
        if !isa(v, Vector)
            v = [v]
        end
        for v in v
            attrs["Attribute.$i.Name"] = a
            attrs["Attribute.$i.Value"] = v
            attrs["Attribute.$i.Replace"] = string(replace)
            i += 1
        end
    end

    sdb(aws, "PutAttributes", @SymDict(DomainName, ItemName, attrs...))
end

sdb_put(db::SimpleDB, ItemName, dict) = sdb_put(db.aws, db.domain, ItemName, dict)

typealias SDBStr Compat.UTF8String
typealias SDBAttribute Pair{SDBStr,Union{SDBStr,Vector{SDBStr}}}
typealias SDBItem Union{SDBStr,Pair{SDBStr,Vector{SDBAttribute}}}


# Convert XML attribute vector "v" to Vector{Pair}...

function sdb_attributes(v, order=nothing)

    v = isa(v, Vector) ? v : [v]

    # Build dict of attribute values...
    d = Dict{SDBStr,Union{SDBStr,Vector{SDBStr}}}()
    for i in v

        # Get Attribute name and value...
        attribute = SDBStr(i["Name"])
        value = i["Value"]

        # Decode base64 values...
        if isa(value, XMLDict.XMLDictElement)
            if get(value, :encoding, nothing) == "base64"
                value = base64decode(value[""])
            end
        end
        value = SDBStr(value)

        # Build vector for multi-valued attributes...
        if haskey(d, attribute)
            if isa(d[attribute], Vector{SDBStr})
                push!(d[attribute], value)
            else
                d[attribute] = SDBStr[d[attribute], value]
            end
        else
            d[attribute] = value
        end
    end

    if order == nothing
        return [SDBAttribute(k, v) for (k,v) in d]
    else
        # Return ordered Vector of Pairs...
        return [SDBAttribute(a, get(d, a, SDBStr(""))) for a in order]
    end
end


function sdb_get(aws::AWSConfig, DomainName, ItemName; attribute="")

    query = @SymDict(DomainName, ItemName)

    if attribute != ""
        query[:AttributeName] = attribute
    end

    r = sdb(aws, "GetAttributes", query)
    r = r["GetAttributesResult"]
    if r == ""
        return nothing
    end
    r = r["Attribute"]

    return sdb_attributes(r)
end

sdb_get(db::SimpleDB, ItemName) = sdb_get(db.aws, db.domain, ItemName)


type SDBSelectItr
    aws
    SelectExpression
    attributes
    NextToken::String
    result
end


function sdb_select(aws::AWSConfig, SelectExpression; NextToken="")
    return SDBSelectItr(aws, SelectExpression, nothing, NextToken, nothing)
end


function sdb_select(aws::AWSConfig, domain::AbstractString,
                                    attributes::Vector,
                                    condition::AbstractString="";
                                    NextToken="")

    SelectExpression = """
                       select $(join(["`$a`" for a in attributes], ", "))
                       from `$domain`
                       $condition
                       """

    return SDBSelectItr(aws, SelectExpression, attributes, NextToken, nothing)
end


# Iterator interface...

Base.eltype(::Type{SDBSelectItr}) = SDBItem
if VERSION > v"0.5.0-dev+4340"
Base.iteratorsize(::Type{SDBSelectItr}) = Base.SizeUnknown()
end



function Base.start(itr::SDBSelectItr)

    itr.result, itr.NextToken = _sdb_select(itr.aws,
                                            itr.SelectExpression,
                                            itr.attributes)
    return start(itr.result)
end


function Base.next(itr::SDBSelectItr, state)

    if done(itr.result, state)

        itr.result, itr.NextToken =
            _sdb_select(itr.aws,
                        itr.SelectExpression,
                        itr.attributes,
                        itr.NextToken)
        state = start(itr.result)
    end

    return next(itr.result, state)
end


function Base.done(itr::SDBSelectItr, state)

    return done(itr.result, state) && itr.NextToken == ""
end


function _sdb_select(aws::AWSConfig, SelectExpression, attributes, NextToken="")

    query = @SymDict(SelectExpression)

    if NextToken != ""
        query[:NextToken] = NextToken
    end

    r = sdb(aws, "Select", query)
    r = r["SelectResult"]

    if r == ""
        return (SDBItem[], "")
    end

    NextToken = get(r, "NextToken", "")

    r = r["Item"]

    if !isa(r, Vector)
        r = [r]
    end

    if ismatch(r"select itemName()", SelectExpression)
        r = SDBItem[SDBStr(i["Name"]) for i in r]
    else
        r = SDBItem[SDBStr(i["Name"]) =>
                    sdb_attributes(get(i, "Attribute", []), attributes)
                    for i in r]
    end

    return (r, NextToken)
end



end # module AWSSDB



#==============================================================================#
# End of file.
#==============================================================================#
