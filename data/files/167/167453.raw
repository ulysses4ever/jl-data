#
# 1D bound state energies for a QM particle in an infinite well and potential V(x) 
#

## Definition of the orthonormal basis states 
@everywhere function φ(i) return  function (x) sin(π*i*x) end end

## Coupling strength
@everywhere λ = 1.0*π^2/4.0

## Definition of the centered harmonic potential V(x)
@everywhere function V(x) return λ*(x-0.5)^2 end 

## Multiply a potential to calculate <φ1|V|φ2> 
@everywhere function Vφ(i) return  function (x) sin(π*i*x)*V(x) end end

## Definition of the inner product <φ1|φ2> 
@everywhere function ∫(φ1::Function,φ2::Function)
    ψ(x)=φ1(x)*φ2(x)::Float64
    return 2*quadgk(ψ,0,1,abstol=1e-8)[1]::Float64
end

##  Infinite well energies 
@everywhere function ɛ(i::Int,j::Int)
    return  i == j ? i^2 : 0
end 

# The numerical Hamiltonian 
function hamiltonian(n::Int)
  h = SharedArray(Float64,n^2)
  @sync for j=1:n
    @parallel for i=j:n
      h[i+(j-1)*n] = ɛ(i,j) + ∫(φ(i),Vφ(j))::Float64 
     end
  end;
  H = reshape(h,n,n)
  return H+transpose(H-triu(H))
end

# The exact Hamiltonian 
function hamiltonian_exact(n::Int)
  return Float64[ i==j? i^2 + (1/12)*λ*(1-6/(i*π)^2) : 0.25*(1+(-1)^(i+j))*(1/(i-j)^2-1/(i+j)^2) for i=1:n,j=1:n ]
end

## Checking orthonomality 
function orthonormal(n::Int)
    v = SharedArray(Float64,n^2)
    @sync for j=1:n
        @parallel for i=j:n
            v[i+(j-1)*n] = ∫(φ(i),φ(j))::Float64
        end
    end; 
    m = reshape(v,n,n)
    return m+transpose(m-triu(m))
end

function main(n::Int) 
   @time println("norm of difference = ", norm(eigvals(hamiltonian(n))-eigvals(hamiltonian_exact(n))))
end

main(400)


