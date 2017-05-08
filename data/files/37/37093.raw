using Winston


p1(x)=1/3+3/5*x;
p2(x)=3/14+3/5*x+5/14*x^2;
p3(x)=3/14+5/6*x+5/14*x^2-7/18*x^3;
f(x)=sqrt(x);

plot1(f,p1,p2,p3,[0,1])


function plot1(f,p1,p2,p3,r)
  N=200;
  x=linspace(r[1],r[2],N);
  window=FramedPlot(
                    title="Solve the Gauss approximation problem",
                    xlabel="x",
                    ylabel="y",
                    );

  y1=Array(Float64,N);
  y2=Array(Float64,N);
  y3=Array(Float64,N);
  y4=Array(Float64,N);
  for i=1:N
    y1[i]=f(x[i]);
    y2[i]=p1(x[i]);
    y3[i]=p2(x[i]);
    y4[i]=p3(x[i]);
  end
  Cur1=Curve(x,y1,color="red");
  setattr(Cur1,label="f(x)");

  Cur2=Curve(x,y2,color="blue");
  setattr(Cur2,label="n=1");

  Cur3=Curve(x,y3,color="black");
  setattr(Cur3,label="n=2");

  Cur4=Curve(x,y4,color="pink");
  setattr(Cur4,label="n=3");

  I=Legend(.1,.9,[Cur1,Cur2,Cur3,Cur4]);

  add(window,Cur1,Cur2,Cur3,Cur4,I);
end
