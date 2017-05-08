#-----------------------------
# Defining common variables used for
# unit testing, and including the functions
# used
#-----------------------------
using Base.Test
srand(42);
Nobs = 1024;
y = randn(Nobs);
include("rw_arr.jl")
include("rw_arrbin.jl")
include("rw_arrhdf5.jl")
#----------------------------

#------------------------------
# TEST 1: Test Read and Write for ASCII:
#------------------------------
write_arr(y, "randn.txt")
y2_ascii = read_arr("randn.txt")
#y2[1,1] = 100
@test_approx_eq_eps(y,y2_ascii,0.001)
println("ASCII rw passed test")
#------------------------------


#------------------------------
# TEST 2: Test Read and Write for Binary:
#------------------------------
write_arrbin(y, "randn_bin.txt")
y2_binary = read_arrbin("randn_bin.txt",Nobs)
#y2[1,1] = 100
@test_approx_eq_eps(y,y2_binary,0.001)
println("Binary rw passed test")
#------------------------------


#------------------------------
# TEST 3: Test Read and Write for HDF5:
#------------------------------
write_arrhdf5(y,"randn_hdf5.dat","y")
y2_binary = read_arrhdf5("randn_hdf5.dat","y")
#y2[1,1] = 100
@test_approx_eq_eps(y,y2_binary,0.001)
println("HDF5 rw passed test")
#------------------------------






#------------------------------
# Test Read and Write for Binary write:
#------------------------------




