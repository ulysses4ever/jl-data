include("newtMin.jl")
function simpleProblem(x)
  # evaluate the function f(x)=‖x-y_0‖^4, the gradient 2x, and the Hessian 2*Id
  y0 = [-1 100 3];
  f = norm(x-y0, 2)^4;
  g = 4*norm(x-y0, 2)^2*(x-y0);
  H = 8*(x-y0)*(x-y0)';
  return (f, g, H);
end

newtmin(simpleProblem, [-1,136, 161])