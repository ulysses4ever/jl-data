module XmlToDict

using LightXML
using DataStructures

export xmlparse_string, @x2d_str, XmlDictAccessor, getindex

function handle_node(xelem:: XMLElement; strip_text=true, wrapper_text=false)
    
    elem = OrderedDict{String,Any}()
    for a in attributes(xelem) 
        elem["@"*name(a)] = value(a)
    end
    
    has_element_children = false
    for item in child_elements(xelem)
        cname = "$(name(item))"
        celem = handle_node(item)
        
        if cname in keys(elem)
            curr = elem[cname]
            if isa(curr, Array)
                push!(elem[cname],celem)
            else
                elem[cname] = [curr, celem]
            end
        else
            elem[cname] = celem
        end
        has_element_children = true
    end

    text = ""
    for item in child_nodes(xelem) |> xs->filter(is_textnode, xs) 
        ctext = content(item)
        ctext_stripped = strip(ctext)
        text *= (strip_text || (!wrapper_text&&has_element_children)) ? ctext_stripped : ctext
    end
    # println("text: $text")
    
    if !has_element_children || (has_element_children && !wrapper_text && !isempty(text) )
        elem["#text"] = text
    end
    
    return elem
end

function xmlparse_string(xml_input)
    
    xdoc = parse_string(xml_input)
    xroot = root(xdoc)

    elem = OrderedDict{String,Any}()
    elem[name(xroot)] = handle_node(xroot)
    return elem
end

type XmlDictAccessor
    value::String
end

macro x2d_str(str)
    return :( XmlDictAccessor($str) )
end

function getindex(od::OrderedDict, name::XmlDictAccessor) 
    if endswith(name.value, "+")
		rname = rstrip(name.value, '+')
        rvalue = od[rname]
		return isa(rvalue, Array) ? rvalue : [ rvalue ]
    elseif endswith(name.value, "*")
		rname = rstrip(name.value, '*')
		if rname in keys(od)
	        rvalue = od[rname]
			return isa(rvalue, Array) ? rvalue : [ rvalue ]
		else
			return []
		end
    else
        return od[name.value]
    end
end

end # module
