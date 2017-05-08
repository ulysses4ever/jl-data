###########################################
#  This mudule is for plot
#  Author: wangjiechao and hanpeiqin
#  Date: 2015.12.21
#  Version: 1.0

function PlotCom(range,p1,y3,x3)
  N1=1000;
  x1=linspace(range[1],range[2],N1);
  window=FramedPlot(
                    title="h-t",
                    xlabel="t(s)",
                    ylabel="h(m)",
                    xrange=(8,12),
                    yrange=(-1,100),
                    );

    y1=Array(Float64,N1);
    y2=Array(Float64,N1);
    for i=1:1:N1
        y1[i]=p1(x1[i]);
        y2[i]=0;
    end

  Cur1=Curve(x1,y1,color="red");
  setattr(Cur1,label="real orbit");
  Cur2=Curve(x1,y2,color="blue");
  setattr(Cur2,label="zero line");
  Point1=Points(x3,y3,kind="fill circle");
  setattr(Point1,label="RK45");
#  Point2=Points(x4,y4,kind="circle");
#  setattr(Point2,label="OURRK45");
  I=Legend(.75,.2,[Cur1,Cur2,Point1]);

  add(window,Cur1,Cur2,Point1,I);

end
