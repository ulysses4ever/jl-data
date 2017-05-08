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
       sdb_delete_item, sdb_put, sdb_get, sdb_select



using AWSCore
using SymDict



function sdb(aws, action, query=StringDict())
    query["Action"] = action 
    do_request(post_request(aws, "sdb", "2009-04-15", query))
end

sdb(aws, action, args::SymbolDict) = sdb(aws, action, StringDict(args))

sdb(aws, action; args...) = sdb(aws, action, StringDict(args))


function sdb_list_domains(aws)
    sdb(aws, "ListDomains")["ListDomainsResult"]["DomainName"]
end


function sdb_create_domain(aws, name)
    sdb(aws, "CreateDomain", DomainName = name)
end


function sdb_delete_domain(aws, name)
    sdb(aws, "DeleteDomain", DomainName = name)
end


function sdb_delete_item(aws, DomainName, ItemName)
    sdb(aws, "DeleteAttributes", @SymDict(DomainName, ItemName))
end


function sdb_put(aws, DomainName, ItemName, dict; replace=true)

    attrs = StringDict()
    for (i, (a, v)) in enumerate(dict)
        attrs["Attribute.$i.Name"] = a
        attrs["Attribute.$i.Value"] = v
        attrs["Attribute.$i.Replace"] = string(replace)
    end

    sdb(aws, "PutAttributes", @SymDict(DomainName, ItemName, attrs...))
end

function sdb_attributes(r)
    return Pair[i["Name"] => i["Value"] for i in (isa(r, Vector) ? r : [r])]
end


function sdb_get(aws, DomainName, ItemName; attribute="")

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


type SDBSelectItr
    aws
    SelectExpression
    NextToken::ASCIIString
    result
end


function sdb_select(aws, SelectExpression; NextToken="")
    return SDBSelectItr(aws, SelectExpression, NextToken, nothing)
end


function Base.start(itr::SDBSelectItr)

    itr.result, itr.NextToken = sdb_select_token(itr.aws, itr.SelectExpression)
    return start(itr.result)
end


function Base.next(itr::SDBSelectItr, state)

    if done(itr.result, state)

        itr.result, itr.NextToken =
            sdb_select_token(itr.aws, itr.SelectExpression, itr.NextToken)
        state = start(itr.result)
    end

    return next(itr.result, state)
end


function Base.done(itr::SDBSelectItr, state)

    return done(itr.result, state) && itr.NextToken == ""
end


function sdb_select_token(aws, SelectExpression, NextToken="")

    query = @SymDict(SelectExpression) 
    
    if NextToken != ""
        query[:NextToken] = NextToken
    end

    r = sdb(aws, "Select", query)
    r = r["SelectResult"]
    NextToken = get(r, "NextToken", "")

    if r == ""
        return ([], NextToken)
    end

    r = r["Item"]

    if !isa(r, Vector)
        r = [r]
    end

    if ismatch(r"select itemName()", SelectExpression)
        r = [i["Name"] for i in r]
    else
        r = Pair[i["Name"] => sdb_attributes(get(i, "Attribute", [])) for i in r]
    end

    return (r, NextToken)
end



end # module AWSSDB



#==============================================================================#
# End of file.
#==============================================================================#
