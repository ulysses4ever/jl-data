#################################################
#  This test is for Newton_Polynomials
#  Author: wangjiechao
#  Date: 2016.1.13
#  Version: 1.0
#################################################


include("Newton_Polynomial.jl");

#function_name:plot2
#function_describe:plot interpolate and
#input:T::r ,f1 and f2
#output:none
function plot2(r,f1,f2)
  N=200;
  x=linspace(r[1],r[2],N);
  ylim(-4,4);
  window=FramedPlot(
                    title="Compare Interpolation with Primitive",
                    xlabel="x",
                    ylabel="y",
                    xrange=(-8,8),
                    yrange=(-2,2)
                    );

  y1=Array(Any,N);
  y2=Array(Any,N);
  for i=1:N
    y1[i]=f1(x[i]);
    y2[i]=f2(x[i]);
  end
  Cur1=Curve(x,y1,color="red");
  Cur2=Curve(x,y2,color="blue");
  add(window,Cur2);
  add(window,Cur1);
end

f(x)=1/(1+x^2);
range=[-5:1:5];
w=Newtoninter(range,f);
plot2([-5,5],f,w);


