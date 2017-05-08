include("gp.jl")

function fn(x)
    sin(x[1]) * cos(x[2])
end

xs = shuffle([[i,j] for i=0.0:0.5:5.0, j=0.0:0.5:5.0][:])
ts = map(fn, xs)

Vals = repmat(Observation[Val()], length(xs))
Nsparse = 40
gp = SparseGP(Nsparse, squared_exp, 1e-4, [2.0, 2.0], xs, ts, Vals)

Xout = [[i,j] for i=0.0:0.05:5.0, j=0.0:0.05:5.0]

print("timing $(length(Xout)) predictions...")
tic()
a = [gp_predict(gp, x) for x in Xout[:]]
toc()
a=reshape(a,size(Xout))

result = zeros(size(Xout,1), 3, size(Xout,2))
for i=1:size(Xout,1)
    for j=1:size(Xout,2)
        result[i,1,j] = Xout[i,j][1]
        result[i,2,j] = Xout[i,j][2]
        result[i,3,j] = a[i,j][1]
    end
end

sparse_pts = zeros(Nsparse, 3)
for i=1:Nsparse
    sparse_pts[i,1:2] = xs[i][:]
    sparse_pts[i,3] = ts[i]
end


writedlm("predicted-value2", result)
writedlm("sparse-pts2", sparse_pts)

