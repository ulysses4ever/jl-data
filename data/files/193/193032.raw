export Soln, SolvData, ExData

##
# Types for Examples
##

type ExData
  a::Function
  b::Function
  c::Function

  f::Function
  chi::Function
  g::Function
  phi::Function

  s::Function

  u::Function
  ux::Function
  ut::Function
  sp::Function

  γ::Function

  function ExData(a::Function, b::Function, c::Function, s::Function, u::Function, ux::Function, ut::Function, sp::Function, γf::Function)

    aux{T<:Real}(x::T, t::T)=a(x,t)*ux(x,t)
    auxx{T<:Real}(x::T, t::T)=(aux(x+gPDEDiffEst,t)-aux(x,t))/gPDEDiffEst

    f{T<:Real}(x::T, t::T)=-(auxx(x,t)+b(x,t)*ux(x,t)+c(x,t)*u(x,t)-ut(x,t))

    g{T<:Real}(t::T)=aux(zero(T), t)

    phi{T<:Real}(x::T)=u(x, zero(T))

    chi{T<:Real}(x::T, t::T)=a(x, t)*ux(x, t)+γf(x, t)*sp(t)

    return new(a,b,c,f,chi,g,phi,s,u,ux,ut,sp,γf)
  end
end

##
# Types for PDE Solver Routine
##
@lintpragma("Info me PDEtypes: Consider removing dx information from SolnA.")
type SolnA{T<:Real, T1<:Real}
  xgrid::Vector{T}
  tgrid::Vector{T}
  dx::Vector{T} # TODO: Consider removing dx information
  tau::T
  xbdy::Vector{T}
  soln::Matrix{T1}
end

SolnA(nSlice::Int, s::Function)=SolnA(linspace(0,1), linspace(0,1), linspace(0,1), 0.1, linspace(0,1), [one(Float) for x in linspace(0,1), t in linspace(0,1)])
typealias Soln SolnA

type SolvData
  verbose::Bool
  a::Function
  b::Function
  c::Function
  f::Function
  rhs::Function
  g::Function
  phi::Function
  s::Function
  grid::SolnA
  SolvData(verbose::Bool, a::Function, b::Function, c::Function, f::Function, rhs::Function, g::Function, phi::Function, s::Function, nSlice::Int) = new(verbose, a, b, c, f, rhs, g, phi, s, SolnA(nSlice, s))
end
SolvData(a::Function, b::Function, c::Function, f::Function, rhs::Function, g::Function, phi::Function, s::Function, nSlice::Int) = SolvData(gSetVerbose, a, b, c, f, rhs, g, phi, s, nSlice)

function SolvData(exin::ExData, nSlice::Int)
  rhs{T<:Real}(t::T) = exin.chi(exin.s(t), t) - exin.γ(exin.s(t), t) * exin.sp(t)
  return SolvData(gSetVerbose, exin.a, exin.b, exin.c, exin.f, rhs, exin.g, exin.phi, exin.s, nSlice)
end

# include("PDESolvDataHelpers.jl")
