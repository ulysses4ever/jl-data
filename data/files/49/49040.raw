module
immutable type PhasePoint4
  x::Float64
  y::Float64
  vx::Float64
  vy::Float64
end

function f_ell(ni::Float64,p::PhasePoint4)
  # FIXME (mu, e) dovrebbero essere inseriti da utente; il problema è che non funziona l'integratore
  const mu=9.537e-4; # FIXME
  const e=0.04839; # FIXME
  const K=1+e*cos(ni);
  x_prime=p.vx;
  y_prime=p.vy;
  wx_prime=2*p.vy+(p.x-((1-mu)*(p.x+mu))/(((p.x+mu)^2+p.y^2)^(1.5))-(mu*(p.x-1+mu))/(((p.x-1+mu)^2+p.y^2)^(1.5)))/K;
  wy_prime=-2*p.vx+(p.y-(1-mu)*p.y/(((p.x+mu)^2+p.y^2)^(1.5))-(mu*p.y)/(((p.x-1+mu)^2+p.y^2)^(1.5)))/K;
  x_out=[x_prime, y_prime, wx_prime, wy_prime]
  return x_out
end
end #module

function f_ell(ni::Float64,x::Array{Float64}) # FIXME mu, e da includere da utente
  const mu=9.537e-4; # FIXME
  const e=0.04839; # FIXME
  const K=1+e*cos(ni);
  x_prime=x[3];
  y_prime=x[4];
  wx_prime=2*x[4]+(x[1]-((1-mu).*(x[1]+mu))./(((x[1]+mu).^2+x[2].^2).^(1.5))-(mu.*(x[1]-1+mu))./(((x[1]-1+mu).^2+x[2].^2).^(1.5)))/K;
  wy_prime=-2*x[3]+(x[2]-(1-mu).*x[2]./(((x[1]+mu).^2+x[2].^2).^(1.5))-(mu*x[2])./(((x[1]-1+mu).^2+x[2].^2).^(1.5)))/K;
  x_out=[x_prime, y_prime, wx_prime, wy_prime]
  return x_out
end

function nu2xy(nu,R )
  x=R.*cos(nu)
  y=R.*sin(nu)
  return x,y
end

## DATA ##
const mu=9.537e-4;
const ecc=0.04839;
const T=2;

const dist_Sun_Jup = 778547200;   # km
const r_earth_orbit = 149600000;  # km
const R = r_earth_orbit/dist_Sun_Jup;

const dx=0.1
const dy=0.1
const dvx=0.2
const dvy=0.2