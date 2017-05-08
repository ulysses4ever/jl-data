
using Winston
#define TDMA input coe table
type TheCoeTabOfTDMA
     a::Vector{Float64}
     b::Vector{Float64}
     c::Vector{Float64}
     r::Vector{Float64}
     TheCoeTabOfTDMA(Num)=new(Array(Float64,Num),Array(Float64,Num),
                              Array(Float64,Num),Array(Float64,Num));
end
#define Naturl Cubic spline  coe stored table
type TheCoeTabOfNCS
     a::Vector{Any}
     b::Vector{Any}
     c::Vector{Any}
     d::Vector{Any}
     TheCoeTabOfNCS(Num)=new(Array(Any,Num),Array(Any,Num),
                              Array(Any,Num),Array(Any,Num));
end

#Tridiagonal Matrix Inversion Algorithms
function TDMA(T::TheCoeTabOfTDMA,size_N)

  T.c[1]=T.c[1]/T.b[1];
  T.r[1]=T.r[1]/T.b[1];

  for n in 2:1:size_N
      m=1.0/(T.b[n]-T.a[n]*T.c[n-1]);
      T.c[n]=T.c[n]*m;
      T.r[n]=(T.r[n]-T.a[n]*T.r[n-1])*m;
  end

  for m in (size_N-1):-1:1
    T.r[m]=T.r[m] - T.c[m] * T.r[m+1];
  end
  return T
end

function TheCoeOfNCS(T::TheCoeTabOfNCS,TheValue,TheCoeCofNCS,h,N)
  h1=1/h;
  for TheCurCou in 1:1:N-1
      T.a[TheCurCou]=TheValue[TheCurCou];
      T.b[TheCurCou]=(TheValue[TheCurCou+1]-TheValue[TheCurCou])*h1-
      (TheCoeCofNCS[TheCurCou+1]+2*TheCoeCofNCS[TheCurCou])*h/3;
      T.c[TheCurCou]=TheCoeCofNCS[TheCurCou];
      T.d[TheCurCou]=(TheCoeCofNCS[TheCurCou+1]-TheCoeCofNCS[TheCurCou])*h1/3;
  end
      T.a[N]=T.a[N-1];
      T.b[N]=T.b[N-1];
      T.c[N]=T.c[N-1];
      T.d[N]=T.d[N-1];
  return T
end

function natural_spline(f,a,b,N)
    N=N+1;#include 0
    #
    x=linspace(a,b,N);
    h=(b-a)/(N-1);##interval h

    TheValue=Array(Float64,N);
    TheValue=[f(i) for i in a:h:b];#The value of f(x)
    #return TheValue

    #solve tridiagonal matrix inversion
    table=TheCoeTabOfTDMA(N-2);
    table.r=[3*(TheValue[i+2]-2*TheValue[i+1]+TheValue[i])/h for i in 1:1:N-2];
    table.a=[h for TheCurNum in 1:1:N-2];
    table.b=[4*h for TheCurNum in 1:1:N-2];
    table.c=[h for TheCurNum in 1:1:N-2];
    #return table
    table=TDMA(table,N-2);
    #return table

    c=Array(Any,N);
    c=[0,table.r,0];#add c0=0 and cn=0

    #The coe of NCS calculate (ai,bi,ci and di,i=1....N)
    TheTableOfNCS=TheCoeTabOfNCS(N);
    TheTableOfNCS=TheCoeOfNCS(TheTableOfNCS,TheValue,c,h,N);
    #return TheTableOfNCS

    #output NCS
    s(z)=TheTableOfNCS.a[floor((z-a)/h)+1]+TheTableOfNCS.b[floor((z-a)/h)+1]*(z-x[floor((z-a)/h)+1])+TheTableOfNCS.c[floor((z-a)/h)+1]*(z-x[floor((z-a)/h)+1])^2+TheTableOfNCS.d[floor((z-a)/h)+1]*(z-x[floor((z-a)/h)+1])^3;
    return s
end

function plot1(f,g,r)
  N=200;
  x=linspace(r[1],r[2],N);
  window=FramedPlot(
                    title="Compare",
                    xlabel="x",
                    ylabel="y",
                    );

  y1=Array(Any,N);
  y2=Array(Any,N);
  for i=1:N
    y1[i]=f(x[i]);
    y2[i]=g(x[i]);
  end
  Cur1=Curve(x,y1,color="red");
  Cur2=Curve(x,y2,color="blue");
  add(window,Cur2);
  add(window,Cur1);
end
