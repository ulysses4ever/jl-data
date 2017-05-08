#=
Parse an RSS feed
=#
module RSS
import HTTPClient: get
import LibExpat: xp_parse, find


type Feed
    attributes :: Dict
    items :: Array{Dict}
end


# Exceptions
type FeedError <: Exception end
type HTTPError <: Exception end
type NotImplementedError <: Exception end


# Maybe
abstract Option

type Nothing <: Option
    reason :: String
    exception :: Exception
end

type Something <: Option
    value
end

function pipeline(fn)
    #=
    A function for handling multiple layers of failable operations.
    =#
    return (maybe :: Option) -> (
        if isa(maybe, Nothing)
            maybe
        else
            fn(maybe.value)
        end
    )
end

function resolver(maybe :: Option)
    #=
    Either bet the value from Something, or raise the error contained
    in a Nothing.
    =#
    if isa(maybe, Nothing)
        info(maybe.reason)
        throw(maybe.exception)
    else
        maybe.value
    end
end


# Parsing
function parse(url)
    #=
    Parse an RSS feed.

    input:
        url: A URL to an RSS feed.
    output:
        Feed
    =#
    response = get(url)

    # feed not found
    if response.http_code != 200
        info("Invalid status code $(response.http_code)")
        throw(HTTPError())
    end

    parse_feed(bytestring(response.body))
end


function parse_feed(xml_string)
    #=
    Parse an XML document containing an RSS feed.

    input:
        xml_string: A string containing an XML document.
    output:
        Feed
    =#
    root = null

    try
        root = xp_parse(xml_string)
    catch
        info("Invalid XML file")
        throw(FeedError())
    end

    channel = (
        if root.name == "rss"
            Something(root)
        else
            Nothing("Invalid feed type: $(root.name)", FeedError())
        end
    ) |> pipeline((root) -> (
        version = get(root.attr, "version", "");

        if version == "2.0"
            Something(root)
        else
            Nothing("Unknown RSS version: $version", FeedError())
        end
    )) |> pipeline((root) -> (
        channels = find(root, "channel");

        if length(channels) < 1
            Nothing("Feed missing its channel", FeedError())
        else
            Something(channels[1])
        end
    )) |> resolver

    attributes = Dict()
    items = Dict[]

    for element in channel.elements
        if element.name == "item"
            # Story
            item = Dict()

            for item_element in element.elements
                item[item_element.name] = item_element.elements[1]
            end

            push!(items, item)
        else
            attributes[element.name] = element.elements[1]
        end
    end

    return Feed(attributes, items)
end

export parse, FeedError, HTTPError, NotImplementedError
end
