const c=299792458.

function IC(l,p,h,X,Y,Z,tilt,azimut,phase,amplitude,order,lx,ly,lz)
  const Rx=vcat([-1 0 0],[0 1 0],[0 0 1])
  const Ry=vcat([1 0 0],[0 -1 0],[0 0 1])
  const Rz=vcat([1 0 0],[0 1 0],[0 0 -1])
  const i0=amplitude*[sin(tilt).*cos(azimut), sin(tilt).*sin(azimut), cos(tilt)]
  crit=0.01
  orderx=minimum([order,int(log(crit)/log(lx))])
  ordery=minimum([order,int(log(crit)/log(ly))])
  orderz=minimum([order,int(log(crit)/log(lz))])
  POS=zeros((orderx+1)*(ordery+1)*(orderz+1)*8,7)#[0 0 0 0 0 0 0]
  count=1
  for i=0:orderx
    perc=round(i/orderx*1000)/10
    println("$perc %")
    for j=0:ordery
      for k=0:orderz
        n = int(i+j+k);
	#if n<order
        ip = (-Rx)^i*(-Ry)^j*(-Rz)^k*i0;
        losses=lx^i*ly^j*lz^k
        losses1=lx^i*ly^j*lz^(k+1)
        losses2=lx^i*ly^(j+1)*lz^k
        losses3=lx^i*ly^(j+1)*lz^(k+1)
        losses4=lx^(i+1)*ly^j*lz^k
	      losses5=lx^(i+1)*ly^j*lz^(k+1)
        losses6=lx^(i+1)*ly^(j+1)*lz^k
        losses7=lx^(i+1)*ly^(j+1)*lz^(k+1)
        x = (i+mod(i,2))*l+(-1)^i*X;
        y = (j+mod(j,2))*p+(-1)^j*Y;
        z = (k+mod(k,2))*h+(-1)^k*Z;
        POS[count,:]=[ip'*losses x  y  z n ]
        POS[count+1,:]=[(-Rz*ip)'*losses1 x  y  -z n+1 ]
        POS[count+2,:]=[(-Ry*ip)'*losses2 x  -y  z n+1 ]
        POS[count+3,:]=[(-Ry*-Rz*ip)'*losses3 x  -y  -z n+2 ]
        POS[count+4,:]=[(-Rx*ip)'*losses4 -x  y  z n+1 ]
        POS[count+5,:]=[(-Rx*-Rz*ip)'*losses5 -x  y  -z n+2 ]
        POS[count+6,:]=[(-Rx*-Ry*ip)'*losses6 -x  -y  z n+2 ]
        POS[count+7,:]=[(-Rx*-Ry*-Rz*ip)'*losses7 -x  -y  -z n+3 ]
	      count+=8
	#end
      end
    end
  end
  perm=sortperm(POS[:,7])
  return POS[perm,:]
end







