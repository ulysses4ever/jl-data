include("mesh2d.jl")

module Nektar
using Mesh2d

type NektarBndry <: Mesh2d.Bndry
    tag::Char
    elem::Int
    edge::Int
    params::Array{Float64,1}
    funs::Array{String, 1}
    NektarBndry(bt, el, ed, p, funs=Array(String,0)) = new(bt, el, ed, p, funs)
end

function section(flines, header)

    nl = length(flines)
    for i in 1:nl
        if length(search(flines[i], header)) > 0
            return i
        end
    end

    return -1
end

function element(rea, idx)
    if length(search(uppercase(rea[1]), "QUAD")) > 0
        el = Mesh2d.Quad()
    else
        el = Mesh2d.Tri()
    end
    el.id = idx
    el.verts[:,1] = [parsefloat(x) for x = split(strip(rea[2]))][1:nverts(el)]
    el.verts[:,2] = [parsefloat(x) for x = split(strip(rea[3]))][1:nverts(el)]
    return el
end
    
    
function mesh(rea)

    isec = section(rea, "MESH DATA") + 1
    nelem = parseint(split(strip(rea[isec]), " ")[1])
    elems = Array(Mesh2d.Element2d, nelem)
    isec += 1
    for e = 1:nelem
        elems[e] = element(rea[isec:(isec+2)], e)
        isec += 3
    end

    return elems
    
end
        

function bndry_sec(rea, isec, nterms=2)

    s = split(strip(rea[isec]))
    tag = strip(s[1])[1]
    nums = [parsefloat(strip(ss)) for ss in s[2:end]]
    el = convert(Int, round(nums[1]))
    ed = convert(Int, round(nums[2]))
    p = nums[3:]
    if islower(tag)
        funs = rea[(isec+1):(isec+nterms)]
        isec += nterms + 1
    else
        funs = Array(String, 0)
        isec += 1
    end
    return NektarBndry(tag, el, ed, p, funs), isec
end


    
    
function bndry_conds(rea, elems)
    isec = section(rea, "BOUNDARY CONDITIONS")+2
    bndrylst = Array(Mesh2d.Bndry, 0)
    for el in elems
        ne = Mesh2d.nedges(el)
        for edge = 1:ne
            b, isec = bndry_sec(rea, isec)
            if b.tag == 'E' || b.tag == 'P'
                el.neigh[edge,1] = convert(Int, round(b.params[1]))
                el.neigh[edge,2] = convert(Int, round(b.params[2]))
            else
                push!(bndrylst, b)
                el.hasbc = true
            end
        end
        if ne == 3
            isec += 1
        end
    end
    nb = length(bndrylst)
    for i = 1:nb
        el = bndrylst[i].elem
        ed = bndrylst[i].edge
        elems[el].neigh[ed,2] = -i
    end
    return bndrylst
end
    

type NekCurve <: Mesh2d.Curve2d
    cname::String
    line::String
end

    
    
function curves(rea, elems)

    isec = section(rea, "CURVED SIDE DATA") + 1
    num = convert(Int, round(parsefloat(split(strip(rea[isec]))[1])))

    crv = Array(Mesh2d.Curve2d, num)
    if num == 0
        return crv
    end
    crvdict = Dict{String,Int}()
    isec += 1
    for i = 1:num
        ctype = lowercase(strip(rea[isec]))
        isec += 1
        if ctype == "circle"
            s = split(strip(rea[isec]))
            xc = parsefloat(s[1])
            yc = parsefloat(s[2])
            rad = parsefloat(s[3])
            inside = true
            if rad < 0
                rad = -rad
                inside = false
            end
            tag = strip(s[4])
            crvdict[tag] = i
            crv[i] = Mesh2d.Circle(xc, yc, rad, inside)
        elseif ctype=="str"
            crv[i] = Segment()
            tag = strip(rea[isec])
            crvdict[tag] = i
        elseif ctype=="fil"
            crv[i] = NekCurve(ctype, rea[isec])
            tag = strip(split(strip(rea[isec]))[2])
            crvdict[tag] = i
        else
            crv[i] = NekCurve(ctype, rea[isec])
        end
    end
    isec += 1
    num = convert(Int, round(parsefloat(split(strip(rea[isec]))[1])))
    isec += 1
    for i = 1:num
        s = split(strip(rea[isec]))
        iside = parseint(strip(s[1]))
        iel = parseint(strip(s[2]))
        tag = strip(s[3])
        elems[iel].curve[iside] = crvdict[tag]
        elems[iel].curved = true
        isec += 1
    end

    return crv
    
    
end 


function nektar(filename)
    fd = open(filename, "r")
    rea = readlines(fd)
    close(fd)
    elems = mesh(rea)
    crv = curves(rea, elems)
    bcs = bndry_conds(rea, elems)
    
    return Mesh2d.Mesh(elems, crv, bcs, rea)
end


end