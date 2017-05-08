function variance(y::Array)
   n = length(y);
   var = zero(y[1]);
   mean = zero(y[1]);
   for i = 1:n
       if !isfinite(y[i])
               error("the ",i,"th element is Inf or -Inf");
       try
               mean += y[i];
               var += y[i].^2;
       catch y
               if isa(y,error)
                       break
       end
   end
   mean /= n;
   var -= n*mean.^2;
   return var/(n-1);
end

variance([1,4,10,100]);
