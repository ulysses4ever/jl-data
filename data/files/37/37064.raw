#################################################
#  This test is for Natural spline Polynomials
#  Author: wangjiechao
#  Date: 2016.1.13
#  Version: 1.0
#################################################

include("Natural_Spline.jl")

function plot_1(f,g,r)
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

f(x)=1/(1+x*x);
s=natural_spline(f,[-5 5],100);

plot_1(f,s,[-5,5]);
plot(x->s(x),-5,5);
plot(x->f(x),-5,5);
