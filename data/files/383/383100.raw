function interpolate(x,px::Array{Float64,1},py::Array{Float64,1})
    # piecewise linear interpolation
    @assert length(px)==length(py)
    # assumes px and py are both sorted in ascending order
    iPxB=searchsortedlast(px,x)
    iPxE=searchsortedfirst(px,x)

    
    # interpolate by constant if out of range
    if iPxB<1
        return py[1]
    end
    if iPxE>length(px)
        return py[length(px)]
    end

    pxB=px[iPxB]
    pxE=px[iPxE]

    pyB=py[iPxB]
    pyE=py[iPxE]

    return pyB*(pxE-x)/(pxE-pxB) + pyE*(x-pxB)/(pxE-pxB)
end

