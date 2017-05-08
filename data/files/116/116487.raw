function variance(y::Array)
   n = length(y);
   var = zero(y[1]);
   mean = zero(y[1]);
   for i = 1:n
       if isnan(y[i])
               println("the ",i,"th element is NaN or -Nan");
               break;
       end
       if isinf(y[i])
               println("the ",i,"th element is Inf or -Inf");
               break;
       else
               mean += y[i];
               var += y[i].^2;
       end
   end
   mean /= n;
   var -= n*mean.^2;
   return var/(n-1);
end
