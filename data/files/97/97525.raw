module ice

# package code goes here
using Logging
#include("pdf.jl")
using icepdf.pdf


type Ice # move me to ice module
    a::Float64
    b::Float64
    c::Float64
end

# does fromPDFControlPoints use InverseCumulative() much?
# if so this is bad

function fromPdf(pdf::SimplePdf)
    println("From SimplePdf")
end

function fromPdf(pdf::GaussianPdf)
    l = cumulative(pdf, 0.25)
    r = cumulative(pdf, 0.75)
    x=0
end

function fromPdf(pdf::BoundedGaussianPdf)
    println("Not implemented")
    #raise/throw error
end



function fromPdfControlPoints(pdf::GaussianPdf, 
                              controlPoints::Array{Float64,1},
                              leftTail::Bool,
                              rightTail::Bool)
    logarithmOfDensity = Float64[]
    curvatures = Float64[]
    lod = log(evaluate(pdf, controlPoints[1]));
    if lod < -20
        lod = -20;
    end
       push!(logarithmOfDensity, lod)
    debug("lod $lod")
end


[close() for i = [1:10]]


n = GaussianPdf(0,1,1)
nice = fromPdf(n)
cps = [-3:0.5:3]
nice = fromPdfControlPoints(n, cps, true, true)
println("nice $nice")
info("nice $nice")



end # module
