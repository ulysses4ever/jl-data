module MUSIC
export readFile,writeFile,GridSearch,travtTable,getTravt,EigTaper,getNSS,MUSIC_GRID,opt,MCMC

function readFile(fileName,n1,n2)
f=open(fileName,"r");
data=reshape(readdlm(f),n1,n2);
return data
end

function writeFile(fileName,data)
f=open(fileName,"w");
writedlm(f,data);
end

function GridSearch(travtp,rlvt,fcnew,En)
nlat=size(travtp,2);
nlon=size(travtp,3);
nz=size(travtp,4);
omega=fcnew*2*pi;
P=Array(Float64,nlat,nlon);
temp1=zeros(1,size(En,2));temp2=temp1;
  for i=1:nlon
    for j=1:nlat
      @inbounds  delta=(travtp[:,j,i]-travtp[1,j,i]-rlvt)';
      #steer=complex(cos(delta*omega),sin(omega*delta));
      #temp=steer'*En;temp2=temp*temp';
      #P[j,i]=1.0/real(temp2[1,1]);
      temp1=cos(delta*omega)*real(En)-sin(delta*omega)*imag(En);temp2=cos(delta*omega)*imag(En)+sin(delta*omega)*real(En);
      Temp1=temp1*temp1';Temp2=temp2*temp2';
      P[j,i]=1.0/(Temp1[1,1]*Temp2[1,1]);
    end
  end
  P=P/maximum(P);
return P
end

function MUSIC_GRID(data,glat,glon,gz,grlvt,rcv,fc,fs,c1,c2,fileName)
  tic();  
  (tttbl,tdist,tdep)=travtTable(fileName);
  nz=length(gz);nlon=length(glon);nlat=length(glat);
  nsta=size(rcv,1);
  travtp=Array(Float64,nsta,nlat,nlon,nz);
  for i=1:nz
    for ii=1:nlon
      for iii=1:nlat
       @inbounds loc=[glat[iii],glon[ii],gz[i]];
       @inbounds travtp[:,iii,ii,i]=getTravt(loc,rcv,tttbl,tdist,tdep);
      end
    end
  end
  toc();
  rlvt=getTravt(grlvt,rcv,tttbl,tdist,tdep);
  nf=length(fc);
  P=Array(Float64,nlat,nlon,nf);
  tic()
  for i=1:nf
    @inbounds (En,fcnew)=getNSS(data,fs,fc[i],c1,c2);
    @inbounds P[:,:,i]=GridSearch(travtp,rlvt,fcnew,En);
  end
  toc();
  P=P/maximum(P);
  return P
end


function travtTable(fileName)
  f=open(fileName,"r");
  temp=readdlm(f);
  tttbl=temp[4:101,2:21];
  dist=temp[4:101,1];
  depth=temp[3,2:21];
  depth[20]=900.0;
  return tttbl,dist,depth
end

function getTravt(loc,rcv,tttbl,tdist,tdep) 
  lat=loc[1];lon=loc[2];
  dist=acos(cos(lat/180*pi)*cos(rcv[:,1]/180*pi).*cos((lon-rcv[:,2])/180*pi)+sin(lat/180*pi)*sin(rcv[:,1]/180*pi))*180/pi;
  dep=abs(loc[3]-rcv[:,3]);
  nrcv=size(rcv,1);
  travtp=Array(Float64,nrcv,1);
  for i=1:nrcv
    a=dep[i]-tdep;
    b=Array(Float64,size(a));
    for j=1:length(a)
      b[j]=abs(a[j]);
    end
    (minval,index1)=findmin(b,2);
    temp=minval[1]*1.0;index1=index1[1]*1;
    if dep[i]>tdep[index1]
      index2=index1-1;
    else
      index2=index1+1;
    end
    
    a=dist[i]-tdist;
    b=Array(Float64,size(a));
    for j=1:length(a)
      b[j]=abs(a[j]);
    end
    (minval,index3)=findmin(b,1);
    temp=minval[1]*1.0;index3=index3[1]*1;
    if dist[i]>tdist[index1]
      index4=index3-1;
    else
      index4=index3+1;
    end
    w1=abs(dep[i]-tdep[index1])/abs(tdep[index1]-tdep[index2]);w2=1-w1;
    w3=abs(dist[i]-tdist[index3])/abs(tdist[index3]-tdist[index4]);w4=1-w3;
    travtp[i]=60*(tttbl[index3,index1]*w1*w3+tttbl[index4,index1]*w1*w4+tttbl[index3,index2]*w2*w3+tttbl[index4,index2]*w2*w4);
  end
  return travtp
end

function EigTaper(N,a)
  # N is the length of the time serise and a is the criterior of the taper
  C=Array(Float64,N,N);
  freq=4/N;
  for j=1:N
    for i=1:N
      if i!=j
       @inbounds C[i,j]=sin(2*pi*freq*(i-j))/(pi*(i-j));
      else
       @inbounds C[i,j]=2*freq;
      end
    end
  end
  
  (D,V)=eig(C);
  index=find(D.>a);
  tempe=V[:,index];
  lambda=D[index];
  eigenvector=Array(Float64,size(tempe));
  for i=1:length(index)
    for j=1:N
     @inbounds eigenvector[j,i]=-tempe[N+1-j,i];
    end
  end
  return eigenvector,lambda
end

function getNSS(data,fs,fc,c1,c2)
  # get eigenvector of noise subspace,c1 and c2 are criterions
  (npt,nsta)=size(data);
  nfft=npt;
  df=fs/nfft;
  ff=[0:nfft/2]*df;
  II=(fc<=(fs/2));
  indexfc=round(fc[II]/df)+1;
  fcnew=ff[indexfc];
  println(fcnew);

  (EV,Lambda)=EigTaper(npt,c1);
  ntaper=length(Lambda);
  data_taped=Array(Float64,npt,nsta,ntaper);
  for i=1:ntaper
    for j=1:nsta
     @inbounds data_taped[:,j,i]=data[:,j].*EV[:,i];
    end
  end
  
  R=zeros(nsta,nsta);
  fseis=real(fft(data_taped,1));
  for i=1:ntaper
    temp=fseis[indexfc:indexfc,:,i];
    R+=temp'*temp*Lambda[i]/sum(Lambda);
  end
  R=R/ntaper;
  (D,V)=eig(R);
  D=D/maximum(D);
  npeak=sum(D.>c2);
  println(npeak);
  index=D.<=c2;
  En=V[:,index];
  return En,fcnew
end

function opt(travt,rlvt,fcnew,En)
  omega=fcnew*2*pi;
  delta=travt-rlvt;
  steer=complex(cos(delta*omega),sin(omega*delta));
  temp=steer'*En;temp2=temp*temp';
  f=1.0/real(temp2[1,1]);
  return f
end

function MCMC(data,fs,fc,c1,c2,grlvt,strp,Niter,xstep,xbnds,rcv,fileName)
  (tttbl,tdist,tdep)=travtTable(fileName);
 # z=rlvp[3];
  rlvt=getTravt(grlvt,rcv,tttbl,tdist,tdep);
  d=getTravt(strp,rcv,tttbl,tdist,tdep);
  (En,fcnew)=getNSS(data,fs,fc,c1,c2);
  L_keep=Array(Float64,1);x_keep=Array(Float64,3,1);
  L_keep[1]=opt(d,rlvt,fcnew,En);
  x_keep[:,1]=strp;
  ncount=1;
  for i=1:Niter-1
    xprop=x_keep[:,i]+xstep.*(2*rand(size(xstep))-1);
    x_keep=hcat(x_keep,x_keep[:,i]);
    L_keep=vcat(L_keep,L_keep[i]);
    if (((xprop.>xbnds[:,1])==[true,true,true]) & ((xprop.<xbnds[:,2])==[true,true,true]))
      dprop=getTravt(xprop,rcv,tttbl,tdist,tdep);
      lprop=opt(dprop,rlvt,fcnew,En);
      u=rand(1,1);
      if log(u[1,1]).<log(min(lprop./L_keep[i],1))
      @inbounds  x_keep[:,i+1]=xprop;
      @inbounds  L_keep[i+1]=lprop;
        ncount=ncount+1;
      end
    end
  end
  return x_keep,L_keep,ncount
end

end
