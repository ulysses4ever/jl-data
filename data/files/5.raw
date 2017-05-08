type ParseState
    secstack::Vector{UTF8String}
end

childtext(ele::HTMLElement) = join([gettext(e) for e in children(ele)])

gettext(ele::HTMLText) = replace(ele.text, r"\s+", " ")
gettext(ele::HTMLElement{:q}) = "``$(childtext(ele))''"
gettext(ele::HTMLElement) = childtext(ele)

function detailperson!(r, ele::HTMLElement)
    for e in postorder(ele)
        if isa(e, HTMLElement)
            attr = attrs(e)
            if haskey(attr, "property")
                prop = getattr(e, "property")
                if prop == "name"
                    r.name = strip(gettext(e))
                elseif prop == "telephone"
                    r.phone = strip(gettext(e))
                elseif prop == "email"
                    r.email = strip(gettext(e))
                elseif prop == "affiliated"
                    r.organization = Organization(strip(gettext(e)))
                end
            end
        end
    end
end

function detailwork!(sect, r, ele::HTMLElement)
    at = nothing
    time = ""
    role = ""
    descs = UTF8String[]
    for e in postorder(ele)
        if isa(e, HTMLElement{:address})
            at = Organization(strip(gettext(e)))
        elseif isa(e, HTMLElement{:time})
            time = strip(gettext(e))
        elseif isa(e, HTMLElement{:li})
            push!(descs, strip(gettext(e)))
        elseif isa(e, HTMLElement{:h1})
            role = strip(gettext(e))
        end
    end
    if !haskey(r.experience, sect)
        r.experience[sect] = []
    end
    push!(r.experience[sect], Experience(role, at, time, descs))
end

function detailskills!(r, ele::HTMLElement)
    for e in postorder(ele)
        if isa(e, HTMLElement{:li})
            push!(r.skills, strip(gettext(e)))
        end
    end
end

function parse!(ctx, r, ele::HTMLText) end

function parse!(ctx, r, ele::HTMLElement{:body})
    for e in children(ele)
        parse!(ctx, r, e)
    end
end

function parse!(ctx, r, ele::HTMLElement{:section})
    sslen = length(ctx.secstack)
    attr = attrs(ele)
    if haskey(attr, "class")
        if attr["class"] == "skills-list"
            detailskills!(r, ele)
            return
        elseif attr["class"] == "work-experience"
            detailwork!(ctx.secstack[end], r, ele)
            return
        end
    end
    for e in children(ele)
        parse!(ctx, r, e)
    end
    ctx.secstack = ctx.secstack[1:sslen]
end

function parse!(ctx, r, ele::HTMLElement{:h1})
    push!(ctx.secstack, gettext(ele))
end

function parse!(ctx, r, ele::HTMLElement)
    attr = attrs(ele)
    if haskey(attr, "typeof") && getattr(ele, "typeof") == "Person"
        detailperson!(r, ele)
    else
        for e in children(ele)
            parse!(ctx, r, e)
        end
    end
end

function parse!(ctx, r, ele::HTMLElement{:head}) end
