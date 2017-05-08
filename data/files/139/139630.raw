function compute_lagrangian(data::Dict)
  x        = data["x"];
  d        = data["d"];
  s        = data["s"];
  lambda_s = data["lambda_s"];
  mu_s     = data["mu_s"];
  z        = data["z"];
  t        = data["t"];
  lambda_t = data["lambda_t"];
  mu_t     = data["mu_t"];
  beta     = data["beta"];

  numPatches = size(x, 2);
  dictSize = size(d, 1);

  loss = 0.5*vecnorm( x-d'*z ) ^2;
  spar = beta*vecnorm(t, 1);
  cons = mu_t*0.5*vecnorm( z-t )^2 + [lambda_t[:]'*( z[:]-t[:] )][1];
  cons += mu_s*0.5*vecnorm( d-s )^2 + [lambda_s[:]'*( d[:]-s[:] )][1];
  obj = loss + spar + cons;

  return (obj, loss, spar);
end
