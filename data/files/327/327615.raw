

function solve(f::Function,y::Float64,xb::Float64,xe::Float64)
    xb,xe=intervalSearch(f,y,xb,xe)
    return dichotomy(f,y,xb,xe)
end

function intervalSearch(f::Function,y::Float64,xb::Float64,xe::Float64)
    @assert xb<xe
    yb=f(xb)
    ye=f(xe)
    m=(xb+xe)/2
    d=(xe-xb)
    while !(yb<y && y<ye)
        xb=m-d
        xe=m+d
        d=d*2
        yb=f(xb)
        ye=f(xe)
    end
    return (xb,xe)
end


function dichotomy(f::Function,y::Float64,xb::Float64,xe::Float64)
    # assumes f is increasing
    @assert xe>xb
    xm=(xb+xe)/2
    if xe-xb<eps(Float64)
        return xm
    end
    if f(xm)==y
        return xm
    elseif f(xm)>y
        return dichotomy(f,y,xb,xm)
    else
        return dichotomy(f,y,xm,xe)
    end
end


function testSolve()
    function f(x::Float64)
        return 2*x
    end

    println(solve(f,20.0,0.0,1.0))
end
