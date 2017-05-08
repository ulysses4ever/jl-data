module IntervalosAR
import Base.sin,Base.cos,Base.tan,Base.cot,Base.sec,Base.csc,Base.exp,Base.log,Base.asin,Base.acos,Base.atan,Base.acot,Base.asec,Base.acsc,Base.sinh,Base.cosh,Base.tanh,Base.coth,Base.sech,Base.csch
export Interval

type Interval
    lowbound
    upbound

	function Interval(a,b)
if a>b

    set_rounding(BigFloat,RoundDown)
		
		A=BigFloat("$b")
	
	   
	    set_rounding(BigFloat,RoundUp)
		
		B=BigFloat("$a")
       
       
        else
	    set_rounding(BigFloat,RoundDown)
		
		A=BigFloat("$a")
	    
	    
	     set_rounding(BigFloat,RoundUp)
		
		B=BigFloat("$b")
        
        
        end
	    

	    
	    return new(A,B)
	end

end

function +(f::Interval,g::Interval)
h=Array(BigFloat,4)
h[1]=f.lowbound+g.lowbound
h[2]=f.lowbound+g.upbound
h[3]=f.upbound+g.lowbound
h[4]=f.upbound+g.upbound
    result=Interval(minimum(h),maximum(h))
   
end

function +(f::Interval,a)
f+Interval(a,a)
end

function +(a,f::Interval)
f+Interval(a,a)
end


function -(f::Interval,g::Interval)
h=Array(BigFloat,4)
h[1]=f.lowbound-g.lowbound
h[2]=f.lowbound-g.upbound
h[3]=f.upbound-g.lowbound
h[4]=f.upbound-g.upbound
    result=Interval(minimum(h),maximum(h))
   
end

function -(f::Interval,a)
f-Interval(a,a)
end

function -(a,f::Interval)
Interval(a,a)-f
end

function *(f::Interval,g::Interval)
    h=Array(BigFloat,4)
h[1]=f.lowbound*g.lowbound
h[2]=f.lowbound*g.upbound
h[3]=f.upbound*g.lowbound
h[4]=f.upbound*g.upbound
    result=Interval(minimum(h),maximum(h))
end

function *(f::Interval,a)
f*Interval(a,a)
end

function *(a,f::Interval)
Interval(a,a)*f
end

function /(f::Interval,g::Interval)
h=Array(BigFloat,4)
h[1]=f.lowbound/g.lowbound
h[2]=f.lowbound/g.upbound
h[3]=f.upbound/g.lowbound
h[4]=f.upbound/g.upbound
    result=Interval(minimum(h),maximum(h))
end

function /(f::Interval,a)
f/Interval(a,a)
end

function /(a,f::Interval)
Interval(a,a)/f
end

function ==(f::Interval,g::Interval)
if f.lowbound==g.lowbound && f.upbound==g.upbound
return true
else
return false
end
end

function union(f::Interval,g::Interval)
h=Array(BigFloat,4)
h[1]=f.lowbound
h[2]=f.upbound
h[3]=g.lowbound
h[4]=g.upbound
    result=Interval(minimum(h),maximum(h))
end

function ^(f::Interval,b::Int)
step=(f.upbound-f.lowbound)/1000
a=Interval((f.lowbound)^b,(f.lowbound)^b)
for i=0:999
a=union(Interval((f.lowbound+(step*i))^b,(f.lowbound+(step*(i+1)))^b),a)
end
return a
end

function ^(f::Interval,b::Float64)
 if f.upbound<=0
res=Interval(0,0)

 elseif f.lowbound<0
step=(f.upbound)/1000
a=Interval(0^b,step^b)
for i=1:999
a=union(Interval(((step*i))^b,((step*(i+1)))^b),a)
end
return a

else
step=(f.upbound-f.lowbound)/1000
a=Interval((f.lowbound)^b,(f.lowbound)^b)
for i=0:999
a=union(Interval((f.lowbound+(step*i))^b,(f.lowbound+(step*(i+1)))^b),a)
end
return a
end
end

function sin(f::Interval)
step=(f.upbound-f.lowbound)/1000
a=Interval(sin(f.lowbound),sin(f.lowbound))
for i=0:999
a=union(Interval(sin(f.lowbound+(step*i)),sin(f.lowbound+(step*(i+1)))),a)
end
return a
end

function cos(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(cos(f.lowbound),cos(f.lowbound))
for i=0:99
a=union(Interval(cos(f.lowbound+(step*i)),cos(f.lowbound+(step*(i+1)))),a)
end
return a
end

function tan(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(tan(f.lowbound),tan(f.lowbound))
for i=0:99
a=union(Interval(tan(f.lowbound+(step*i)),tan(f.lowbound+(step*(i+1)))),a)
end
return a
end

function cot(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(cot(f.lowbound),cot(f.lowbound))
for i=0:99
a=union(Interval(cot(f.lowbound+(step*i)),cot(f.lowbound+(step*(i+1)))),a)
end
return a
end

function sec(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(sec(f.lowbound),sec(f.lowbound))
for i=0:99
a=union(Interval(sec(f.lowbound+(step*i)),sec(f.lowbound+(step*(i+1)))),a)
end
return a
end

function csc(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(csc(f.lowbound),csc(f.lowbound))
for i=0:99
a=union(Interval(csc(f.lowbound+(step*i)),csc(f.lowbound+(step*(i+1)))),a)
end
return a
end

function exp(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(exp(f.lowbound),exp(f.lowbound))
for i=0:99
a=union(Interval(exp(f.lowbound+(step*i)),exp(f.lowbound+(step*(i+1)))),a)
end
return a
end

function log(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(log(f.lowbound),log(f.lowbound))
for i=0:99
a=union(Interval(log(f.lowbound+(step*i)),log(f.lowbound+(step*(i+1)))),a)
end
return a
end

function asin(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(asin(f.lowbound),asin(f.lowbound))
for i=0:99
a=union(Interval(asin(f.lowbound+(step*i)),asin(f.lowbound+(step*(i+1)))),a)
end
return a
end

function acos(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(acos(f.lowbound),acos(f.lowbound))
for i=0:99
a=union(Interval(acos(f.lowbound+(step*i)),acos(f.lowbound+(step*(i+1)))),a)
end
return a
end

function atan(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(atan(f.lowbound),atan(f.lowbound))
for i=0:99
a=union(Interval(atan(f.lowbound+(step*i)),atan(f.lowbound+(step*(i+1)))),a)
end
return a
end

function acot(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(acot(f.lowbound),acot(f.lowbound))
for i=0:99
a=union(Interval(acot(f.lowbound+(step*i)),acot(f.lowbound+(step*(i+1)))),a)
end
return a
end

function asec(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(asec(f.lowbound),asec(f.lowbound))
for i=0:99
a=union(Interval(asec(f.lowbound+(step*i)),asec(f.lowbound+(step*(i+1)))),a)
end
return a
end

function acsc(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(acsc(f.lowbound),acsc(f.lowbound))
for i=0:99
a=union(Interval(acsc(f.lowbound+(step*i)),acsc(f.lowbound+(step*(i+1)))),a)
end
return a
end

function sinh(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(sinh(f.lowbound),sinh(f.lowbound))
for i=0:99
a=union(Interval(sinh(f.lowbound+(step*i)),sinh(f.lowbound+(step*(i+1)))),a)
end
return a
end

function cosh(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(cosh(f.lowbound),cosh(f.lowbound))
for i=0:99
a=union(Interval(cosh(f.lowbound+(step*i)),cosh(f.lowbound+(step*(i+1)))),a)
end
return a
end

function tanh(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(tanh(f.lowbound),tanh(f.lowbound))
for i=0:99
a=union(Interval(tanh(f.lowbound+(step*i)),tanh(f.lowbound+(step*(i+1)))),a)
end
return a
end

function coth(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(coth(f.lowbound),coth(f.lowbound))
for i=0:99
a=union(Interval(coth(f.lowbound+(step*i)),coth(f.lowbound+(step*(i+1)))),a)
end
return a
end

function sech(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(sech(f.lowbound),sech(f.lowbound))
for i=0:99
a=union(Interval(sech(f.lowbound+(step*i)),sech(f.lowbound+(step*(i+1)))),a)
end
return a
end

function csch(f::Interval)
step=(f.upbound-f.lowbound)/100
a=Interval(csch(f.lowbound),csch(f.lowbound))
for i=0:99
a=union(Interval(csch(f.lowbound+(step*i)),csch(f.lowbound+(step*(i+1)))),a)
end
return a
end

end
