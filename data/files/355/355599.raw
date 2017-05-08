include ("SR.jl")

function SRA (f,a,b,tol,N)

Va=fill(1.0,2N); Vb=fill(1.0,2N);

i=1; approx=0; Va[i]=a; Vb[i]=b;

while i>0

  atemp= Va[i]; btemp= Vb[i]; htemp=(btemp-atemp)/2;
  S1=SR(f,atemp,btemp,2); S2=SR(f,atemp,btemp,4);

  toltemp=15tol/((b-a)/(btemp-atemp))
  i-=1
  if abs(S1-S2)<toltemp
    approx+=S2
  else
    if ((b-a)/(btemp-atemp)>N)
      println ("Limite de subintervalos excedido.")
      return 0
    else
      i+=1
      Va[i]=btemp-htemp; Vb[i]=btemp;
      i+=1
      Va[i]=atemp; Vb[i]=btemp-htemp;
    end
  end
end
return approx
end