cd(Pkg.dir("BasicSpace", "deps"))
pic = @windows ? "" : "-fPIC"
src = "basicspace.f90"
so = "basicspace.so"
run(`gfortran -ffloat-store $pic -shared -O2 -llapack -lblas $src -o $so`)
