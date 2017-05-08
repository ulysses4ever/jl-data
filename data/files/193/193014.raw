
cd(joinpath(dirname(@__FILE__), "src"))
include(joinpath(dirname(@__FILE__), "src", "ISP.jl"))

function doISP()
  include(joinpath(dirname(@__FILE__), "ex3.jl"))

  ed=ISP.ExData(a,b,c,s,u,ux,ut,sp,γf)
  sd=ISP.SolvData(ed,10)

  const tgrid = sd.grid.tgrid

  v_actual = convert(Vector{Float64}, [sd.grid.xbdy, [sd.g(t) for t in tgrid]])
  v0 = copy(v_actual)
  len = length(v0)
  v0[1:(len/2)] = mean(v0[1:(len/2)])
  v0[(len/2+1):len] = mean(v0[(len/2+1):len])

  mu_actual = Float64[u(s(t), t) for t in tgrid]
  nu_actual = Float64[u(zero(t), t) for t in tgrid]

  delta = 0.5
  l = 5.0
  R = 20.0

  func=ISP.SimpleTest(sd, mu_actual, nu_actual, v0, delta, l, R)

end
doISP()
