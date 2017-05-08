include("gp.jl")

function fn(x)
    cos(x)^2 + cos(0.2x)^2
end

function Dfn(x)
    -2.0*cos(x)*sin(x) - 0.4*cos(0.2x)*sin(0.2x)
end

xs = [0.0, 40.0, 40.0*rand(1000)]
ts  = map(fn, xs)
dts = map(Dfn, xs)

Vals = repmat(Observation[Val()], length(xs))
Derivs = repmat(Observation[Deriv{1}()], length(xs))

nsparse = 50
gp = SparseGP(nsparse, squared_exp, 1e-4, [1.3], [xs, xs], [ts, dts], [Vals, Derivs])
@time log_lik_optim!(gp, [1e-5, 0.1], [10.0, 100.0], iterations=100, ftol_rel=1e-5)

Xout = -10.0:0.05:50.0

tic()
a = [gp_predict(gp, x) for x in Xout]
da = [gp_predict(gp, x, Deriv{1}()) for x in Xout]
toc()

writedlm("predicted-value", hcat(Xout, map(first,a), map(last,a)))
writedlm("predicted-deriv", hcat(Xout, map(first,da), map(last,da)))
writedlm("training-data", hcat(xs, ts))
writedlm("active-set", hcat(xs[1:nsparse], ts[1:nsparse]))
