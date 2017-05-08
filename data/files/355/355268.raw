module COPL
export solve, call_test
#c_callable_interior_point_algorithm(int m, int n, int k,\
#						 double* Gp, int* Gj, int* Gi, double* h,\
#						 double* c,\
#						 double* Ap, int* Aj, int* Ai, double* b,\
#						 double* x, double* y, double* s, double* z, double* tau, double* kappa,\
#						 int max_iter, double linear_feas_tol, double comp_tol){
#include("/Users/tiago/COPL.jl/src/COPL.jl")

function solve_low(m::Int, n::Int, p::Int,
               Gp::Vector{Float64}, Gi::Vector{Int}, Gj::Vector{Int},
               Ap::Vector{Float64}, Ai::Vector{Int}, Aj::Vector{Int},
               c::Vector{Float64}, h::Vector{Float64}, b::Vector{Float64},
       	       max_iter::Int, linear_feas_tol::Float64, comp_tol::Float64)

   #Allocate the return variables
	x = zeros(n);
	y = zeros(p);
	s = zeros(m);
	z = zeros(m);
	tau = Array(Float64,1)
	kappa = Array(Float64,1)

    # Convert to canonical forms
    ccall((:c_callable_interior_point_algorithm, "/Users/tiago/mpc_lp_cpp/lib/copl_sovler.dylib"), Cdouble,
        (Clong, Cint, Cint, 
         Ptr{Cdouble}, Ptr{Cint}, Ptr{Cint}, Ptr{Cdouble},
	 Ptr{Cdouble},
         Ptr{Cdouble}, Ptr{Cint}, Ptr{Cint}, Ptr{Cdouble},
         Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble},
	 Clong,Cdouble,Cdouble),
         m, n, p,
         Gp, int32(Gi)-1, int32(Gj)-1, h,
	 c,
         Ap, int32(Ai)-1, int32(Aj)-1, b,
	 x,y,s,z,tau,kappa,
	 max_iter, linear_feas_tol, comp_tol)
	(x,y,s,z,tau[1],kappa[1])
end

function call_test(A::Array{Float64})
	ccall((:c_callable_test,"/Users/tiago/mpc_lp_cpp/lib/copl_sovler.dylib"),Cdouble,(Clong,Ptr{Cdouble}),size(A)[1],A)
end

#High level solve call
function solve(A::SparseMatrixCSC{Float64}, b::Array{Float64}, c::Array{Float64}, G::SparseMatrixCSC{Float64}, h::Array{Float64})
	(p,nA) = size(A)
	(m,nG) = size(G)
	n = nA
	if(nA!=nG)        throw("A and G are not compatible") end
	if(size(b)[1]!=p) throw("A and b are not compatible") end
	if(size(c)[1]!=n) throw("A and c are not compatible") end 
	if(size(h)[1]!=m) throw("G and h are not compatible") end
	max_iter = 30;
	lin_feas_tol = 1.e-7;
	comp_tol = 1.e-7;
	Ai = A.rowval;
	Aj = A.colptr;
	Ap = A.nzval;
	Gi = G.rowval;
	Gj = G.colptr;
	Gp = G.nzval;
	solve_low(m,n,p,Gp,Gi,Gj,Ap,Ai,Aj,c,h,b,max_iter,lin_feas_tol,comp_tol)
end

#Rand problem 
function rand_prob()
	p = 100;
	n = 1000;
	m = 200;
	A = sprand(p,n,0.9);
	G = sprand(m,n,0.9);
	x0 = randn(n);
	y0 = randn(p);
	z0 = rand(m);
	s0 = rand(m);
	b = A*x0;
	c = -A'*y0-G'*z0;
	h = G*x0+s0;
	(x,y,s,z,t,k) = solve(A,b,c,G,h)
	#Evaluate the soultion
	r1 = norm(A*x-t*b)
	r2 = norm(G*x+s-t*h)
	r3 = norm(A'*y+G'*z+t*c)
	gap = s'*z;
	print(r1)
	print(r2)
	print(r3)
	print(gap)
	
end
end
