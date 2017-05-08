module QuantumComputing
import Base: convert, show, kron, replace, length, sub, split

export N,E,Id,X,Y,Z,H,CNOT,SWAP,Q
export Ket,Bra
export GGate,GCNot,CNot,Not,Swap,Hadamard,VentureMartinez,M
export append,appendhead,extract

# |0> NULL
# |1> EINS
const N = sparse(complex([1.0,0.0]))
const E = sparse(complex([0.0,1.0]))

# Unit 
const Id = complex(speye(2))

# Pauli matrices
const X = sparse(complex([0.0 1.0;1.0 0.0]))
const Y = sparse([0.0 -im; im 0.0])
const Z = sparse(complex([1.0 0.0; 0.0 -1.0]))

# Hadamard matrix
const H = sparse(1.0/sqrt(2)*complex([1.0 1.0; 1.0 -1.0]))

# 2 q-bits operator
const CNOT = blkdiag(Id,X)
const SWAP = hcat(kron(N,N),kron(E,N),kron(N,E),kron(E,E))

const Q = H*N

const sbra = "\u27E8" # <
const svbar = "\u007C" # |
const sket = "\u27E9" # >

abstract QGate

# 0->N, 1->E
function parse01(x)
    if x==0
       return N 
    elseif x == 1
       return E 
    else
       return x
    end
end

immutable Ket 
    v::SparseMatrixCSC
    function Ket(x...)
        v = map(parse01, x)
        new(kron(v...))
    end
    function Ket(v::SparseMatrixCSC)
        new(v)
    end
end

immutable GGate <: QGate
    v::SparseMatrixCSC
    function GGate(v)
        new(v)
    end
end

immutable CNot <: QGate
    v::SparseMatrixCSC
    t::Integer
    c::Integer
    function CNot(n,t,c)
        M1 = Swap(n,1,c).v
        M2 = Swap(n,2,t==1?2:t).v
        v = M1*M2*kron(CNOT,[Id for i=1:n-2]...)*M2*M1
        new(v,t,c)
    end
end

immutable GCNot <: QGate
    v::SparseMatrixCSC
    t::Integer
    c
    function GCNot(n,t,c...)
        nc = length(c)
        v = blkdiag([Id for i=1:2^nc]...)
        v[end-1:end,end-1:end] = X

        Mf = SparseMatrixCSC[]
        c = sort([c...])
        idx=1
        tp = t
        for i in filter(x->x>nc,c)
            while (idx in c)
                idx+=1
                @assert(idx<=nc)
            end
            push!(Mf,Swap(n,idx,i).v)
            if idx==t
                tp = i
            end
            idx+=1
        end
        push!(Mf,Swap(n,nc+1,tp).v)
        v = reduce(*,Mf)*kron(v,[Id for i=1:n-nc-1]...)*reduce(*,reverse(Mf))

        new(v,t,c)
    end
end

immutable Not <: QGate
    v::SparseMatrixCSC
    t::Integer
    function Not(n,t)
        v = [Id for i=1:n]
        v[t] = X
        new(kron(v...),t)
    end
end

immutable Swap <: QGate
    v::SparseMatrixCSC
    t1::Integer
    t2::Integer
    function Swap(n,t1,t2)
        mint = min(t1,t2)
        maxt = max(t1,t2)
        v = kron([Id for i=1:n]...)
        for t=mint:maxt-1
            tv = kron([Id for i=1:t-1]...,SWAP,[Id for i=t+1:n-1]...)
            v *= tv
        end
        for t=maxt-2:-1:mint
            tv = kron([Id for i=1:t-1]...,SWAP,[Id for i=t+1:n-1]...)
            v *= tv
        end
        new(v,t1,t2)
    end
end

immutable Hadamard <: QGate
    v::SparseMatrixCSC
    t::Integer
    function Hadamard(n,t)
        v = [Id for i=1:n]
        v[t] = H
        new(kron(v...),t)
    end
end

immutable VentureMartinez <: QGate
    v::SparseMatrixCSC
    t::Integer
    c::Integer
    j::Integer
    s::Integer
    function VentureMartinez(n,t,c,j,s=-1)
        S = complex(blkdiag(
        speye(2),
        sparse(
        [sqrt((j-1.0)/j) -s/sqrt(j);s/sqrt(j) sqrt((j-1.0)/j)])
        ))
        M1 = Swap(n,1,c).v
        M2 = Swap(n,2,t==1?2:t).v
        v = M1*M2*kron(S, [Id for i=1:n-2]...)*M2*M1
        new(v,t,c,j,s)
    end
end

immutable M <: QGate
    v::SparseMatrixCSC
    m::Complex
    function M(n,m)
        v = complex(spzeros(2^n,2^n))
        v[1,1] = zero(eltype(v))
        for i=2:2^n
            v[i,i] = sqrt(1/(1-m))
        end
        new(v,m)
    end
end

kron(ket1::Ket, ket2::Ket) = Ket(kron(ket1.v, ket2.v))
kron(v) = v
length(ket::Ket) = int(log(size(ket.v,1))/log(2))
show(io::IO, ket::Ket) = print(io,convert(String,ket))

*(val::Number, ket::Ket) = Ket(ket.v*val)
*(ket::Ket, val::Number) = val*ket.v
*(op1::QGate, op2::QGate) = GGate(op1.v*op2.v)
*(ket::Ket, op::QGate) = op*ket
*(op::QGate, ket::Ket) = Ket(op.v*ket.v)
==(ket1::Ket, ket2::Ket) = ket1.v==ket2.v
+(ket1::Ket, ket2::Ket) = Ket(ket1.v+ket2.v)

function convert(::Type{String}, ket::Ket)
    vp = prob(ket.v)
    str=map(find(vp)) do x
        string(@sprintf("%1.13f",vp[x]),"\t", svbar,bin(x-1,length(ket)),sket," \n")
    end
    join(sort(str))
end

function prob(v::SparseMatrixCSC)
    prob(x) = real(x*x)
    map(prob,v)
end

# (|0000>,3) -> |000>
function sub(ket::Ket,n)
    nk = length(ket)
    @assert(n<=nk)
    v = prob(ket.v)
    for i=1:nk-n
        v = reshape(v,2,length(v)>>1)'
        v = v[:,1] + v[:,2]
    end
    kets=map(find(v)) do x
        sqrt(v[x]) * Ket(map(parseint,split(bin(x-1,n),""))...)
    end
    reduce(+,kets)
end

# (|abcd>,3) -> |c>
function extract(ket::Ket,n)
    sub(Swap(length(ket),1,n)*ket,1)
end

#  (|0000>,a,b,c) -> |0000abc>
function append(ket::Ket, x...)
    av = map(parse01, x)
    Ket(kron(ket.v, av...))
end

#  (|0000>,a,b,c) -> |abc0000>
function appendhead(ket::Ket, x...)
    nk = length(ket)
    nx = length(x)
    av = map(parse01, x)

    v = ket.v
    for i=1:nx
        v = kron(v, av[i])
        nk = nk+1
        v = Swap(nk,i,nk).v*v
        v = reduce(*, [Swap(nk,j,j+1).v for j=i+1:nk-1])*v
    end

    Ket(v)
end

end # module

