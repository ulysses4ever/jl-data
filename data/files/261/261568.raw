srand(43);

function log_normal_pdf(z::Float64, y::Float64, sigma::Float64)
        return -0.5*((y-z)/sigma)^2 - log(sqrt(2*pi)*sigma);
end

function log_likelihood(y::Array, sigma::Array, z::Array)
   n = length(y);
   sum = zero(y[1]);
   for i in 1:n
    sum = sum + log_normal_pdf(y[i],z[i],sigma[i]);
   end;
   return sum;
end     

Nobs = 1000000;
z = zeros(Nobs);
sigma = 2. * ones(Nobs);
y = z + sigma .* randn(Nobs);

log_likelihood(y,sigma,z);
#Profile.clear()
#@profile log_likelihood(y,z,sigma);
#@time log_likelihood(y,z,sigma);
#Profile.print();
