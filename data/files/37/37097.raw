include("RK45.jl")
using Winston

function PlotRK45(t,p1,p2)
  N=200;
  x=linspace(t[1],t[2],N);
  window=FramedPlot(
                    title="RK45",
                    xlabel="t",
                    ylabel="x",
                    );

  y1=Array(Float64,N);
  y2=Array(Float64,N);
  for i=1:1:N
    y1[i]=p1(x[i]);
    y2[i]=p2(x[i]);
  end
  Cur1=Curve(x,y1,color="red");
  setattr(Cur1,label="x[2]");

  Cur2=Curve(x,y2,color="blue");
  setattr(Cur2,label="x[1]");

  I=Legend(.1,.9,[Cur1,Cur2]);

  add(window,Cur1,Cur2,I);
end

T=1;
TOL1=0.000001;
TOL2=0.0000001;
TOL3=0.00000001;
ATOL1=0.0000001;
ATOL2=0.0000001;
hinit=0.01;

##########################EXE1###############################
w(x)=[x[2]^(3)+sin(x[2]),1];
xinit=[0;0];

ET1=RK45(w,xinit,T,hinit,TOL1,ATOL1);
###############################################################


############################EXE2############################
g(x)=[0 1 0 0 0;0 0 1 0 0;0 0 0 1 0;0 0 0 0 1;0 0 0 0 0]*x;
x01=[0;0;0;0;1];

T1=RK45(g,x01,T,hinit,TOL1,ATOL1);
T2=RK45(g,x01,T,hinit,TOL1,ATOL2);
T3=RK45(g,x01,T,hinit,TOL2,ATOL1);
T4=RK45(g,x01,T,hinit,TOL3,ATOL1);
TT=[T1 T2 T3 T4];
###############################################################
##############################EXE3############################
k1=3;
k2=0.002;
k3=0.0006;
k4=0.5;
f(x)=[k1*x[1]-k2*x[1]*x[2];k3*x[1]*x[2]-k4*x[2]];
x0=[1000;500];

pl1(t)=RK45(f,x0,t,hinit,TOL1,ATOL1)[1];
pl2(t)=RK45(f,x0,t,hinit,TOL1,ATOL1)[2];
PlotRK45([0 4],pl1,pl2);
