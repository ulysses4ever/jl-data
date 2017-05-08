module IntervalosAR
 
export Interval 

type Interval
    lowbound
    upbound

	function Interval(a,b)
if a>b
set_rounding(Float64,RoundDown)
		A=BigFloat("$b")
	    set_rounding(Float64,RoundUp)
		B=BigFloat("$a")
        else
	    set_rounding(Float64,RoundDown)
		A=BigFloat("$a")
	    set_rounding(Float64,RoundUp)
		B=BigFloat("$b")
        end
	    set_rounding(Float64,RoundNearest)

	    
	    return new(A,B)
	end

end

function +(f::Interval,g::Interval)
h=Array(Float64,4)
h[1]=f.lowbound+g.lowbound
h[2]=f.lowbound+g.upbound
h[3]=f.upbound+g.lowbound
h[4]=f.upbound+g.upbound
    result=Interval(minimum(h),maximum(h))
   
end

function -(f::Interval,g::Interval)
h=Array(Float64,4)
h[1]=f.lowbound-g.lowbound
h[2]=f.lowbound-g.upbound
h[3]=f.upbound-g.lowbound
h[4]=f.upbound-g.upbound
    result=Interval(minimum(h),maximum(h))
   
end

function *(f::Interval,g::Interval)
    h=Array(Float64,4)
h[1]=f.lowbound*g.lowbound
h[2]=f.lowbound*g.upbound
h[3]=f.upbound*g.lowbound
h[4]=f.upbound*g.upbound
    result=Interval(minimum(h),maximum(h))
end

function /(f::Interval,g::Interval)
h=Array(Float64,4)
h[1]=f.lowbound/g.lowbound
h[2]=f.lowbound/g.upbound
h[3]=f.upbound/g.lowbound
h[4]=f.upbound/g.upbound
    result=Interval(minimum(h),maximum(h))
end

function ==(f::Interval,g::Interval)
if f.lowbound==g.lowbound && f.upbound==g.upbound
return true
else
return false
end
end

end
