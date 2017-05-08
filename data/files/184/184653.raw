using NLopt, Distributions

module gjrGARCH

using NLopt, Distributions


export  GJRGARCHged,  GJRGARCHt,  dged, dstd 

type GarchFit
  data::Vector
  params::Vector
  llh::Float64
  status::Symbol
  converged::Bool
 sigma::Vector 
end




function Base.show(io::IO ,fit::GarchFit)
  @printf io "Fitted GJR Garch (1,1) model\n"
  @printf io "  Coefficient(s): \tmu \t\tomega \t\talpha \t\tbeta  \t\ttau\n"
  @printf io "  \t\t\t%f\t%f\t%f\t%f\t%f\n" fit.params[1] fit.params[2] fit.params[3] fit.params[4] fit.params[5]
  @printf io "  Shape of the Distribution: %f\n" fit.params[6]
  @printf io "  Log Likelihood: %f\n" fit.llh
  @printf io "  Half Life: %f\n" log(0.5) / log(  fit.params[4] + fit.params[3] + 0.5 * fit.params[5]  )
  @printf io "  Persistence: %f\n" fit.params[4] + fit.params[3] + 0.5 * fit.params[5] 
  @printf io "  Unconditional Volatility: %f\n"  sqrt(fit.params[2] / (1 - (  fit.params[4] + fit.params[3] + 0.5 * fit.params[5]   )))
end



#fit.params[4] + fit.params[3] + 0.5 * fit.params[5] 




function dged(mean::Real,sd::Real,nu::Real,x::Real)
    z = (x - mean)/sd
    lambda = sqrt ( 2^(-2/nu) * gamma(1/nu) / gamma(3/nu) )
    g  = nu / ( lambda * (2^(1+1/nu)) * gamma(1/nu) )
    result = g * exp (-0.5*(abs(z/lambda))^nu) / sd
end




function dstd(mean::Real,sd::Real,nu::Real,x::Real)
    s = sqrt(nu/(nu - 2))
    z = (x - mean)/sd
    result = pdf(TDist(nu),z * s) * s/sd
end






function GJRGARCHged(data::Vector)
  rets = data
  T = length(rets); 
  ht = zeros(T);
  ll = zeros(T-1);
  function garchLike(x::Vector, grad::Vector)
    mu,omega,alpha,beta,tau,shape = x;
    ht[1] = std(rets)^2;
    for i=2:T
      if rets[i-1] > 0 
        ht[i] = omega + alpha   * (rets[i-1]-mu)^2 + beta * ht[i-1] ;
      else
        ht[i] = omega + tau     * (rets[i-1]-mu)^2 + beta * ht[i-1] + alpha   * (rets[i-1]-mu)^2 ; 
      end
   ll[i-1] = -(log(dged(mu, sqrt(ht[i]), shape,rets[i])));
   end
   sum(ll)
  end  
  opt = Opt(:LN_SBPLX,6)
  lower_bounds!(opt,[-100, 1e-10, 0.0, 0.0, 0.0, 0.1])
  upper_bounds!(opt,[100; 1; 0.5; 0.99; 1; 10])
  min_objective!(opt, garchLike)
  (minf,minx,ret) = optimize(opt, [0, 1e-5, 0.05, 0.80, 0, 1])
  converged = minx[2]>0 && all(minx[3:4].>=0) && sum(minx[3:4])<1.0
  out = GarchFit(data, minx, minf, ret, converged,sqrt(ht))
end



function GJRGARCHt(data::Vector)
  rets = data
  T = length(rets); 
  ht = zeros(T);
  ll = zeros(T-1);
  function garchLike(x::Vector, grad::Vector)
    mu,omega,alpha,beta,tau,shape = x;
    ht[1] = std(rets)^2;
    for i=2:T
      if rets[i-1] > 0 
        ht[i] = omega + alpha   * (rets[i-1]-mu)^2 + beta * ht[i-1] ;
      else
        ht[i] = omega + tau     * (rets[i-1]-mu)^2 + beta * ht[i-1] + alpha   * (rets[i-1]-mu)^2 ; 
      end
	ll[i-1] = -(log(dstd(mu, sqrt(ht[i]), shape,rets[i])));
   end
   sum(ll)
  end  
  opt = Opt(:LN_SBPLX,6)
  lower_bounds!(opt,[-100, 1e-10, 0.0, 0.0, 0.0,2.1])
  upper_bounds!(opt,[100; 1; 0.5; 0.99; 0.5; 1000])
  min_objective!(opt, garchLike)
  (minf,minx,ret) = optimize(opt, [0, 1e-5, 0.05, 0.80, 0, 2.1])
  converged = minx[2]>0 && all(minx[3:4].>=0) && sum(minx[3:4])<1.0
  out = GarchFit(data, minx, minf, ret, converged,sqrt(ht))
  
end



end  #module

