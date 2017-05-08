using Winston
  g=-9.8;
  H=19.6;
  v0=19.6*0.5;

  f1(t)=H+1/2*g*t^2;
  g1(t)=g*t;
  f2(t)=v0*(t-2)+1/2*g*(t-2)^2;
  g2(t)=v0+g*(t-2);

  N=200;
  x1=linspace(0,2,N);
  x2=linspace(2,4,N);

  window=FramedPlot(
                    title="h and v-t",
                    xlabel="t(s)",
                    ylabel="h(m) and v(m/s)",
                    );

  y1=Array(Float64,N);
  y2=Array(Float64,N);


  z1=Array(Float64,N);
  z2=Array(Float64,N);


  for i=1:1:N
    y1[i]=f1(x1[i]);
    y2[i]=f2(x2[i]);

    z1[i]=g1(x1[i]);
    z2[i]=g2(x2[i]);

  end
  Cur1_1=Curve(x1,y1,color="red");
  Cur2_1=Curve(x1,z1,color="blue");
  setattr(Cur1_1,label="Hei(m)");
  setattr(Cur2_1,label="Vel(m/s)");
  Cur1_2=Curve(x2,y2,color="red");
  Cur2_2=Curve(x2,z2,color="blue");

  I=Legend(.8,.9,[Cur1_1,Cur2_1]);

  add(window,Cur1_1,Cur1_2,Cur2_1,Cur2_2,I);



w(t)=track(statu,t,Ou).Vel;

f(x)=[w(x[2]);1];
xinit=[0;0];
pl1=RK45(f,xinit,t,hinit,TOL,ATOL)[1];
pl2=RK45(f,xinit,t,hinit,TOL,ATOL)[2];
PlotRK45([0 8],pl1,pl2);
