require("fsc_types.jl");
require("fsc_learning_multi.jl");
require("fsc_coding_fastmulti.jl");
require("fsc_fastmulti.jl");
require("normalize.jl");
require("helpers.jl");
require("lagrangian.jl");

d = zeros(Float64, 10, 10, 2);
d[1:3, 1:3, 1] = [1 2 3;2 3 1;3 2 1];
d[1:3, 1:3, 2] = rotr90([1 2 3;2 3 1;3 2 1]);
D = reshape(d, 100, 2);
DtD = D'*D;

X1 = [0 0 0 0 1 1 0 0 0 0;
      0 0 0 0 1 1 0 0 0 0;
      0 0 0 0 1 1 0 0 0 0;
      1 1 1 1 1 1 1 1 1 1;
      0 0 0 0 0 0 0 0 0 0;
      0 0 0 0 0 0 0 0 0 0;
      1 1 1 1 1 1 1 1 1 1;
      0 0 0 0 1 1 0 0 0 0;
      0 0 0 0 1 1 0 0 0 0;
      0 0 0 0 1 1 0 0 0 0];
X2 = eye(10)+rotr90(eye(10));
X1 = float64(X1); X2 = float64(X2);
x1 = X1[:]; x2 = X2[:];
D = [x1 x2]; DtD = D'*D;

Dtx1 = D'*x1; Dtx2 = D'*x2;
Dtx = [Dtx1 Dtx2];
data_bat = FastCodingData(Dtx, DtD);
opts_bat = FastCodingOpts(Float64); opts_bat.max_iter = 13; opts_bat.mu_t = 1;
@time (z_bat,) = fsc_coding_fastmulti(data_bat, opts_bat);



opts = FSCOpts(Float64); opts.max_iter = 20;
opts.DEBUG = true;
@time (s, z) = fsc_fastmulti([x1 x2], 2, opts);
