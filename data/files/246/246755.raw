Pkg.clone()
using Toms566

include("newtMin.jl")
include("gradientDescent.jl")

for i=1:18
  p = Problem(i)
  (i, minn, path, err) = newtMin(LogRegress,[.5 .5 .5]')
  (▽minn,▽path,▽err) = gradientDescent(LogRegressNoHess,[.5 .5 .5]')
  # Graph the path of the parameters
  plot(path[1,:]',path[2,:]',color=(1, 0,.5),label="Newton's Method")
  grad = plot(▽path[1,:]',▽path[2,:]',color=(0,0,1),label="Gradient Descent")
  legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=17,ncol=1, mode="expand", borderaxespad=0.)
  title("Admissions Path")
  ylabel("GPA");
  xlabel("GRE");
  PyPlot.show()

  # Graph the size of the error
  plot(log(err[2:]),color=(1, 0,.5),label="Newton's Method")
  grad = plot(log(▽err[2:200]),color=(0,0,1),label="Gradient Descent")
  legend()
  title(string("Log error for ", "Admissions"))
  ylabel("log(error)");
  xlabel("step");
  PyPlot.show()
end
