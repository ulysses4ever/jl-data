module ice

# package code goes here
using Logging
#include("pdf.jl")
using icepdf.pdf


# type IcePdf # move me to ice module
#     a::Float64
#     b::Float64
#     c::Float64
# end

type IcePdf # move me to ice module
    controlPoints::Array{Float64,1}
    logarithmOfDensity::Array{Float64,1}
    curvatures::Array{Float64,1}
    hasLeftTail::Bool
    hasRightTail::Bool
end

function normalise(icepdf::IcePdf)
    #assertNonEmpty();
    la=log(area(icepdf));
    for (unsigned i=0;i<myLogarithmOfDensity.size();++i)
        myLogarithmOfDensity[i]-=la;
    end
end

function area(icepdf::IcePdf)
    #assertNonEmpty();
    r = 0.0;
    #alpha = 0.0;
    for j = [1:1:length(curvatures)] # (unsigned j=0;j<myCurvatures.size();++j)
        alpha = (myControlPoints[j+1]-myControlPoints[j])/2;
        r += A(j)*alpha;
    end
    return r;
end



    double IcePDF::A(const size_t i) const
    {
        assertNonEmpty();
        double a=(myLogarithmOfDensity[i]+myLogarithmOfDensity[i+1])/2;
        double b=(myLogarithmOfDensity[i+1]-myLogarithmOfDensity[i])/2;
        if (i==0 and i==myCurvatures.size()-1 and myHasLeftTail and myHasRightTail)
        {
            return I(inf,a,b,myCurvatures[i])-I(-inf,a,b,myCurvatures[i]);
        }
        if (i==0 and myHasLeftTail)
        {
            return I(1,a,b,myCurvatures[i])-I(-inf,a,b,myCurvatures[i]);
        }
        if (i==myCurvatures.size()-1 and myHasRightTail)
        {
            return I(inf,a,b,myCurvatures[i])-I(-1,a,b,myCurvatures[i]);
        }
        return I(1,a,b,myCurvatures[i])-I(-1,a,b,myCurvatures[i]);
    }



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

function C(b::Number, c::Number)
    if (abs(b*b/c)>30)
        return 0.0;
    end
    return c;
end

function I(z::Number,
           a::Number,
           b::Number,
           c::Number)
    if (c==0)
        if (b==0)
            @assert(isfinite(z), "z infinite, c=b=0");
            return (z*exp(a));
        end
        @assert(isInf(z)*b <= 0, "z infinite, z*b>0");
        return (exp(a+b*z)/b);
    end

    if (isinf(z))
        @assert(c > 0, "z infinite, c<=0");
        return exp(b*b/4/c+a+c)*sqrt(pi)*isinf(z)/2/sqrt(c);
    end

    @assert(isfinite(z), "z still infinite");
    if (c > 0)
        return exp(b*b/4/c+a+c)*sqrt(pi)*erf((2*c*z-b)/2/sqrt(c))/2/sqrt(c);
    end

    @assert(c < 0, "c should be less than 0");
        
    return exp(b*b/4/c+a+c)*sqrt(pi)*erfi((b-2*c*z)/2/sqrt(-c))/2/sqrt(-c);
end


function findC( x1::Float64, y1::Float64,
                x2::Float64, y2::Float64,
                A::Float64)

    a=(y1+y2)/2;
    b=(y2-y1)/2;
    l=-1;
    r=1;
    m = 0;
    localA = A/(x2-x1)*2;
    debug("I(1,a,b,C(b,l))-I(-1,a,b,C(b,l)) ", I(1,a,b,C(b,l))-I(-1,a,b,C(b,l)))
    while I(1,a,b,C(b,l))-I(-1,a,b,C(b,l)) > localA
        if l < -100.0
            return C(b,-100);
        end
        l *= 2
    end

    while (I(1,a,b,C(b,r)) - I(-1,a,b,C(b,r)) < localA)
        if (r > 100)
            return C(b,100);
        end
        r*=2;
    end

    for i = [1:1:64] #(int i=0; i<64; ++i)
        m=(l+r)/2;
        if (I(1,a,b,C(b,m))-I(-1,a,b,C(b,m)) < localA)
            l = m
        else
            r=m;
        end
    end
    return C(b,m);
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
    debug("size(controlPoints) $size(controlPoints)")
    
    for i = [2:1:length(controlPoints)]
        lod = log(evaluate(pdf, controlPoints[1]));
        if lod < -20
            lod = -20;
        end
        push!(logarithmOfDensity, lod)
        debug("lod $lod")

        println(i)
        println(length(controlPoints))
        println(controlPoints[i-1])
        println(controlPoints[i])
        println(logarithmOfDensity[i])

        push!(curvatures, 
	      findC(
		    controlPoints[i-1],
		    logarithmOfDensity[i-1],
		    controlPoints[i],
		    logarithmOfDensity[i],
		    cumulative(pdf, controlPoints[i])
		    -cumulative(pdf, controlPoints[i-1])
		    )
	      )
        
        hasLeftTail = curvatures[1] > 0;
        if (hasLeftTail) 
            alpha=(controlPoints[2]-controlPoints[1])/2;
            beta=(controlPoints[1]+controlPoints[2])/2;
            b=(logarithmOfDensity[2]-logarithmOfDensity[1])/2;
            hasLeftTail = (controlPoints[1] <= b/2/curvatures[1]*alpha+beta);
        end
        if (hasLeftTail)
            hasLeftTail = leftTail;
            debug("hasLeftTail $hasLeftTail")
        end

        hasRightTail = curvatures[length(curvatures)] > 0;
        if (hasRightTail) 
            k = length(curvatures)
            alpha = (controlPoints[k+1]-controlPoints[k])/2;
            beta = (controlPoints[k]+controlPoints[k+1])/2;
            b= (logarithmOfDensity[k+1]-logarithmOfDensity[k])/2;
            hasRightTail = (controlPoints[k+1] >= b/2/curvatures[k]*alpha+beta);
        end
        if (hasRightTail)
            hasRightTail = rightTail;
            debug("hasRightTail $hasRightTail")
        end

        r = IcePdf(controlPoints,
                   logarithmOfDensity,
                   curvatures,
                   hasLeftTail,
                   hasRightTail);
        

        # r.normalise();

        return r;

    end
end


[close() for i = [1:10]]


n = GaussianPdf(0,1,1)
nice = fromPdf(n)
cps = [-3:0.5:3]
nice = fromPdfControlPoints(n, cps, true, true)
println("nice $nice")
info("nice $nice")



end # module
