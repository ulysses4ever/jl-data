function Log_NumErr(x,h)
   NumErr=f_d(x,h)-g(x);
   if NumErr<0
    PoNumErr=-NumErr;
  else
    PoNumErr=NumErr;
   end
   if PoNumErr==0
     PoNumErr=10;
  end
   LNumErr=log10(PoNumErr);
   return LNumErr
end


function f_d(x,h)
  Der_1=(f(x+h)-f(x-h))/2/h;
  return Der_1
end

function fs_d(x,h)
  Der=(f(x+h)-f(x))/h;
  return Der
end

function g(x)
  a=x*x;
  b=2*x;
  c=b-b*sin(a);
  return c
end

function f(x)
  a=x*x;
  b=cos(a);
  c=a+b;
  return c;
end
