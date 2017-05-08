module ice

# package code goes here
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


n = GaussianPdf(0,1,1)
nice = fromPdf(n)
println("nice $nice")
info("nice $nice")

    

end # module
