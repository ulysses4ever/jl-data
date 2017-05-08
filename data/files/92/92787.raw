include("gp.jl")

function fn(x)
    sin(x[1]) * cos(x[2])
end

xs = shuffle([[i,j] for i=0.0:0.5:5.0, j=0.0:0.5:5.0][:])
ts = map(fn, xs)

Vals = repmat(Observation[Val()], length(xs))
Nsparse = 30
gp = SparseGP(Nsparse, squared_exp, 1e-4, [2.0, 2.0], xs, ts, Vals)

Xout = [[i,j] for i=0.0:0.1:5.0, j=0.0:0.1:5.0]

a = [gp_predict(gp, x) for x in Xout[:]]
a=reshape(a,size(Xout))

result = zeros(size(Xout,1), 3, size(Xout,2))
for i=1:size(Xout,1)
    for j=1:size(Xout,2)
        result[i,1,j] = Xout[i,j][1]
        result[i,2,j] = Xout[i,j][2]
        result[i,3,j] = a[i,j][1]
    end
end

writedlm(result, "predicted-value2")

