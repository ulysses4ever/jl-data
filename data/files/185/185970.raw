module icalparser

function parse(filename)
    icalstream = open(filename)
    mydict = parse_stream(icalstream)
    close(icalstream)
    return mydict
end
export parse

function parse_stream(icalstream)
    icalcontainer = []
    if eof(icalstream)
        return icalcontainer
    else
        parsedict = parse_event(icalstream)
        ##println(parsedict)
        icalcontainer = [icalcontainer;parsedict]
        return parse_stream(icalstream,icalcontainer)
    end
end

function parse_stream(icalstream,icalcontainer)
    ## println(icalcontainer," this is in parse_stream")
    if eof(icalstream)
        return icalcontainer
    else
        parsedict = parse_event(icalstream)
        ##println(parsedict)
        ##prinln(parsedict)
        ## println(parsedict)
        if parsedict == Dict()
            return icalcontainer
        end
        icalcontainer = [icalcontainer;parsedict]
        parse_stream(icalstream,icalcontainer)
    end
end

function parse_event(icalstream)
    
    dict = Dict()
    line = readline(icalstream)
    (key,value) = parse_line(line)
    #println("$key,$value")
    if key == "BEGIN"
       scope = key
       return  {value => parse_event(icalstream,dict,scope)}
    elseif key == "END" 
        return dict
    else
        dict = merge(dict,{key => value})
        println(dict)
        if eof(icalstream)
            return dict
        else
           parse_event(icalstream,dict) 
        end
    end
end

function parse_event(icalstream,dict,scope)
    line = readline(icalstream)
    (key,value) = parse_line(line)
    if key == "BEGIN"
        new_scope = key
        return {value => parse_event(icalstream,dict,scope,new_scope)}
    elseif key == "END" && value == convert(ASCIIString,scope)
        return dict
    else
        dict = merge(dict,{key=>value})
        if eof(icalstream)
            return dict
        else
            parse_event(icalstream,dict,scope)
        end
    end
end
        

function parse_event(icalstream,dict,scope,new_scope)
    line = readline(icalstream)
    (key,value) = parse_line(line)
    if key == "BEGIN"
        new_scope = key
        return {value => parse_event(icalstream,dict,scope,new_scope)}
    elseif key == "END" && value == convert(ASCIIString,new_scope)
        return dict
    elseif key == "END" && value == convert(ASCIIString,scope)
        return dict
    else
        dict = merge(dict,{key=>value})
        if eof(icalstream)
            return dict
        else
            parse_event(icalstream,dict,scope,new_scope)
        end
    end
end


              
        
                             
function parse_line(icalstring)
    key = get_key(icalstring)
    value = get_value(icalstring)
    return (key,value)
end

function get_key(string)
    return match(r".*(?=:)",string).match
end

function get_value(string)
    after_colon = match(r"(?<=:).*",string).match
    return remove_backslash = match(r"\w*",after_colon).match
end

end
        
