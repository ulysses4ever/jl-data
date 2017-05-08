###########################################
#  This mudule is for 4/5Runge Kutta Method
#  Author: Marvin
#  Date: 2015.10.30
#  Version: 1.0


type OdeCoef
a::Array
b::Array
bs::Array
c::Array
OdeCoef(a,b,bs,c)=new(a,b,bs,c)
end

const RunKuDP45 = OdeCoef(
		[0 0 0 0 0 0 0
		1/5 0 0 0 0 0 0
		3/40 9/40 0 0 0 0 0
		44/45 -56/15 32/9 0 0 0 0
		19372/6561 -25360/2187 64448/6561 -212/729 0 0 0
		9017/3168 -355/33 46732/5247 49/176 -5103/18656 0 0
		35/384 0 500/1113 125/192 -2187/6784 11/84 0],
		[35/384 0 500/1113 125/192 -2187/6784 11/84 0],
		[5179/57600 0 7571/16695 393/640 -92097/339200 187/2100 1/40],
		[0 1/5 3/10 4/5 8/9 1 1]
		)

###########################################
#  This function is for calculate k
#  k is a n by 7 matrix
#  Date: 2015.10.30
#  Version: 1.0
function Slope(f::Function,N::Integer,h::Number,y::Array)
k=Array(Number,N,7);
k=zeros(k)
for i=1:7
	for j=1:i
		k[:,i]=f(y+k*(RunKuDP45.a[i,:])'*h)
	end
end
return k;
end

###########################################
#  This function is for calculate norm e
#  e is a vector with n elements
#  Date: 2015.10.30
#  Version: 1.0
function StepSize(yn::Array,zn::Array,N::Integer,TOL::Number, ATOL::Number,y::Array)
e=Array(Number,7);
e=zeros(e);
for i=1:N
	e[i]=abs(yn[i]-zn[i])/(TOL*y[i]+ATOL)
end
norme=norm(e)
return norme=norm(e)
end

###########################################
#  This function is for calculate the T current y(T)
#  return y which is a vector
#  Date: 2015.10.30
#  Version: 1.0
function RK451(f::Function, x0::Array, T::Number, hinit::Number, TOL::Number, ATOL::Number)
n = length(x0);
h=hinit;
y=x0;
yn=y;
#Y=Array(Number,0);
t=0
while 1==1
	t=t+h
	if t>= T
		h=T-t+h
	end
	while 1==1
		k=Slope(f,n,h,y);
		yn=k*(RunKuDP45.b)'*h+y;
		zn=k*(RunKuDP45.bs)'*h+y;
		norme=StepSize(yn,zn,n,TOL,ATOL,y)

		if norme <= 1
			break;
		end
		h=0.9*h/norme^(1/5)
	end
	y=yn;
	if t>=T
		break
	end
	#Y=[Y;y]
end
return y;
end

range=[9.8 10.3];

f(x)=[real_vel(x[2]);1];
xinit=[500;0];

pl_trace(t)=real_heiorbit(t);
pl_RK45(t)=RK45(f,xinit,t,hinit,TOL,ATOL)[1];
pl_OURRK45(t)=OURRK45(f,xinit,t,hinit,TOL,ATOL)[1];

PlotCom(range,pl_trace,pl_RK45,pl_OURRK45);
