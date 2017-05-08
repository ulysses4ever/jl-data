###########################################
#  This mudule is for 4/5Runge Kutta Method
#  Author: wangjiechao and hanpeiqin
#  Date: 2015.12.21
#  Version: 1.0

#################Coefficence############################
  A    =[0             0             0             0             0             0            0;
         1/5           0             0             0             0             0            0;
         3/40          9/40          0             0             0             0            0;
         44/45         -56/15        32/9          0             0             0            0;
         19372/6561    -25360/2187   64448/6561    -212/729      0             0            0;
         9017/3168     -355/33       46732/5247    49/176        -5103/18656   0            0;
         35/384        0             500/1113      125/192       -2187/6784    11/84        0];
  b_hat=[5179/57600    0             7571/16695    393/640       -92097/339200 187/2100     1/40];


###########################################
#  This function is for erro_contral
#  enorm is erro 2 norm
#  Date: 2015.12.21
#  Version: 1.0
function erro_contral(n,h,ynew,znew,yi,TOL,ATOL)
#################error contral#########################
           e=zeros(Float64,n,1);
           for j in 1:1:n
              e[j]=abs(ynew[j]-znew[j])/(TOL*abs(yi[j])+ATOL);
           end#####cal e[j]
           enorm=norm(e);
           return enorm;
end

###########################################
#  This function is for processing dicontinuous change
#  Date: 2015.12.21
#  Version: 1.0
function RK2A4(f,yi,ti,y,t)
    EPS=eps(Float64);

    hc=20*EPS;
    ti=ti+hc;
    k0=f(yi);
    k1=f(yi+hc/2*k0);
    ynew=yi+(k1+k0)*hc/2;
    yi=ynew;
    y=[y;ynew[1]];
    t=[t;ynew[2]];

    hc=60*EPS;
    ti=ti+hc;
    k0=f(yi);
    k1=f(yi+[hc/2*k0[1];hc/2]);
    k2=f(yi+[hc/2*k1[1];hc/2]);
    k3=f(yi+[hc*k2[1];hc]);
    ynew=yi+1/6*(k0+2*k1+2*k2+k3)*hc;

    y=[y;ynew[1]];
    t=[t;ynew[2]];
    return ynew,y,t;
end

###########################################
#  This function is our RK45 about the model
#  Date: 2015.12.21
#  Version: 1.0
function OURRK45(f,x0,T,hinit::Float64,TOL,ATOL)

  y=[0];
  t=[0];
  ################init
  n=length(x0);
  h=hinit;#初始的步长
  ti=0;#出事的时间点
  temph=h;
  EPS=eps(Float64);
  ynew=x0;#初始的出发点
  yi=ynew;
  y=[y;ynew[1]];
  t=[t;ynew[2]];

  while(ti<T)
        ti=ti+h;
            if(ti>=T)
              h=T-ti+h;
            end####ti>=T
  ############while################
        while 1==1
            hA=A*h;
            hb_hat=h*b_hat;#
            ki=zeros(Float64,7,n);
            for i in 1:1:6
                ki[i,:]=f(yi+(hA[i,:]*ki)');
            end#cal k1，k2，k3，k4，k5，k6
           ynew=yi+(hA[7,:]*ki)';#cal 5 order
           ki[7,:]=f(ynew);
           znew=yi+(hb_hat*ki)';#cal 4 order
  #################error contral#########################
           enorm=erro_contral(n,h,ynew,znew,yi,TOL,ATOL);
              if(enorm<=1)
                 break;#####accept h
              end#enorm
  ######################################################
           h=0.9*h/(enorm^(1/5));#reject h and dertemine a new h
        end##end while
   ###################################
        ####determination of change time####
        if f(yi)[1]<=0 && f(ynew)[1]>0
                   h=h/2;
                   ti=ti-temph;
                   temph=h;

                           if h<10*EPS #change happen between ti-h and ti+h
                               #only once
                               hc=90*EPS;
                               val=RK2A4(f,yi,ti,y,t)
                               ynew=val[1];
                               yi=ynew;
                               y=val[2];
                               t=val[3];
                               ti=ti+hc;
                               h=hinit;
                           end
        else
                   yi=ynew;
                   y=[y;ynew[1]];
                   t=[t;ynew[2]];
        end
    end####ti<T
   return y,t;
end
###########################################
#  This function is for debug
#  Date: 2015.12.21
#  Version: 1.0
function Myprint(ynew,yi,ti,h)
     println("ynew's ti:$(ynew[2])");
     println("yi's   ti:$(yi[2])");
     println("now    ti:$(ti)");
     println("h        :$(h)");
     println("H        :$(ynew[2]-yi[2])");
     println("\n");
     println("ynew's height:$(ynew[1])");
     println("yi's   height:$(yi[1])");
     println("\n");
end
