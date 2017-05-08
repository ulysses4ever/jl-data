module COPL
export solve
#c_callable_interior_point_algorithm(int m, int n, int k,\
#						 double* Gp, int* Gj, int* Gi, double* h,\
#						 double* c,\
#						 double* Ap, int* Aj, int* Ai, double* b,\
#						 double* x, double* y, double* s, double* z, double* tau, double* kappa,\
#						 int max_iter, double linear_feas_tol, double comp_tol){
#include("/Users/tiago/COPL.jl/src/COPL.jl")

function solve(n::Int, m::Int, p::Int,
               Gpr::Vector{Float64}, Gjc::Vector{Int}, Gir::Vector{Int},
               Apr::Vector{Float64}, Ajc::Vector{Int}, Air::Vector{Int},
               c::Vector{Float64}, h::Vector{Float64}, b::Vector{Float64},
	       max_iter::Int, linear_feas_tol::Float64, comp_tol::Float64)
    
    # Convert to canonical forms
    Apr = (Apr == nothing) ? convert(Ptr{Cdouble}, C_NULL) : Apr
    Ajc = (Ajc == nothing) ? convert(Ptr{Cdouble}, C_NULL) : convert(Vector{Clong},Ajc)
    Air = (Air == nothing) ? convert(Ptr{Cdouble}, C_NULL) : convert(Vector{Clong},Air)
    b = (b == nothing) ? convert(Ptr{Cdouble}, C_NULL) : b
    ccall((:c_callable_interior_point_algorithm, "copl_solver.dylib"), Cdouble,
        (Clong, Clong, Clong, 
         Ptr{Cdouble}, Ptr{Clong}, Ptr{Clong}, Ptr{Cdouble},
	 Ptr{Cdouble},
         Ptr{Cdouble}, Ptr{Clong}, Ptr{Clong}, Ptr{Cdouble},
         Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble},
	 Clong,Cdouble,Cdouble),
        m, n, p,
        Gpr, Gjc, Gir, h,
	c,
        Apr, Ajc, Air, b,
	x,y,s,z,tau,kappa,
	max_iter, linear_feas_tol, comp_tol)

end

function solve_test()

end
end
