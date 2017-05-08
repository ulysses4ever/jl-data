## Creation of the DMumps structure

const ZI40 = zeros(Cint,40)
const RCV = zeros(Cdouble,15)
const IIN = zeros(Cint,40)
const RIN = zeros(Cdouble,40)

init(::Type{Icntl}) = Icntl(ZI40...)
init(::Type{Rcntl}) = Rcntl(RCV...)
init(::Type{Info}) = Info(ZI40...)
init(::Type{Rinfo}) = Rinfo(RIN...)
for T in (Cint,Cdouble,Ptr{Cint},Ptr{Cdouble})
    @eval init(::Type{$T}) = zero($T)
end
init(::Type{Array_16_Uint8}) = Array_16_Uint8(zero(Int128))
init(::Type{Array_64_Uint8}) = Array_64_Uint8(zeros(Int128,4)...)
init(::Type{Array_256_Uint8}) = Array_256_Uint8(zeros(Int128,16)...)

function DMumps()
    res = DMumps(map(init, DMumps.types)...) # fill type with zeros
    res.par = 1
    res.job = -1
    ccall((:dmumps_c, dmumps), Void, (Ptr{DMumps},), &res)
    res
end

type DMumpssv
    dm::DMumps
    irn::Vector{Cint}
    jcn::Vector{Cint}
    a::Vector{Cdouble}
end

function Base.string{T<:Union(Array_16_Uint8,Array_64_Uint8,Array_256_Uint8)}(a::T)
    bytestring(convert(Ptr{Uint8},pointer(Int128[getfield(a,nm) for nm in names(a)])))
end

const jobs = ["initialize","","analyze","factorize","solve",
              "analyze/factorize","factorize/solve","analyze/factorize/solve"]
const symmetry = ["unsymmetric","positive definite","general symmetric"]                  

function Base.show(io::IO, dm::DMumps)
    j = dm.job
    println("MUMPS version ", string(dm.version_number), " interface")
    println("job: ", jobs[dm.job+2]," on a ",symmetry[dm.sym + 1]," matrix")
end

function DMumpssv(A::SparseMatrixCSC,determinant::Bool)
    dm = DMumps()
    iv = [getfield(dm.icntl,nm)::Int32 for nm in Icntl.names]
    iv[1] = iv[2] = iv[3] = -1
    iv[4] = 0                      # suppress output from within MUMPS
    iv[33] = determinant           # compute determinant
    dm.icntl = Icntl(iv...)
    dm.sym = issym(A)              # attempt pos. def. before general symmetric
    dm.job = 4
    dm.n = A.n
    dm.nz = nfilled(A)
    tt = findnz(A)
    irn = tt[1]
    eltype(irn) == Cint || (irn = int32(irn)) 
    dm.irn = pointer(irn)
    jcn = tt[2]
    eltype(jcn) == Cint || (jcn = int32(jcn)) 
    dm.jcn = pointer(jcn)
    a = tt[3]
    eltype(a) == Cdouble || (a =float64(a))
    dm.a = pointer(a)
    ccall((:dmumps_c,dmumps),Void,(Ptr{DMumps},),&dm)
    dm.info.Info == 0 || error("dmumps_c returned error code $(dm.info.Info)")
    res = DMumpssv(dm,irn,jcn,a)
    finalizer(res, dmumpssv_free)
    res
end

dmumpssv_free(dms::DMumpssv) = dmumps_free(dms.dm)
dmumps_free(dm::DMumps) = (dm.job = -2; ccall((:dmumps_c,dmumps),Void,(Ptr{DMumps},),&dm))

DMumpssv(A::SparseMatrixCSC) = DMumpssv(A,false)

function Base.A_ldiv_B!(A::SparseMatrixCSC{Float64},B::Vector{Float64})
    n = A.n
    A.m == n == length(B) || error("Dimension mismatch")
    dm = DMumps()
    iv = [getfield(dm.icntl,nm)::Int32 for nm in Icntl.names]
    iv[1] = iv[2] = iv[3] = -1
    iv[4] = 0                      # suppress output from within MUMPS
    dm.icntl = Icntl(iv...)
    dm.sym = issym(A)              # attempt pos. def. before general symmetric
    dm.job = 6
    dm.n = n
    dm.nz = nfilled(A)
    tt = findnz(A)
    irn = tt[1]
    eltype(irn) == Cint || (irn = int32(irn)) 
    dm.irn = pointer(irn)
    jcn = tt[2]
    eltype(jcn) == Cint || (jcn = int32(jcn)) 
    dm.jcn = pointer(jcn)
    a = tt[3]
#    eltype(a) == Cdouble || (a =float64(a))
    dm.a = pointer(a)
#    bcp = copy(b)
    dm.rhs = pointer(B)
    dm.nrhs = 1
    dm.lrhs = n
    ccall((:dmumps_c,dmumps),Void,(Ptr{DMumps},),&dm)
    dm.info.Info == 0 || error("dmumps_c returned error code $(dm.info.Info)")
    dm.job = -2
    ccall((:dmumps_c,dmumps),Void,(Ptr{DMumps},),&dm)
    B
end

function dinflate(A::SparseMatrixCSC, v::Real) # inflate the diagonal of A by v
    v = convert(eltype(A),v)
    colpt = A.colptr
    rv = A.rowval
    nz = A.nzval
    for j in 1:A.n, k in colpt[j]:(colpt[j+1] - 1)
        j == rv[k] && (nz[k] += v)
    end
    A
end

dinflate(A::SparseMatrixCSC) = dinflate(A,one(eltype(A)))

