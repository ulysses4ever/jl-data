module EiSCor

    using Base.LinAlg: Eigen, chksquare, chkstride1
    import Base: copy
    import Base.LinAlg: eig, eigfact!, eigvals

    const libeiscor = joinpath(Pkg.dir("EiSCor"), "deps", "libeiscor")

    type UnitaryHessenbergMatrix{T} <: AbstractMatrix{T}
        data::Matrix{T}
    end
    copy(UH::UnitaryHessenbergMatrix) = UnitaryHessenbergMatrix(copy(UH.data))

    function ohfqr!(compz::Char, H::Matrix{Float64})
        # Check
        chkstride1(H)
        n = chksquare(H)
        compz in ('N', 'I', 'V') || throw(ArgumentError("argument compz must be either be either 'N', 'I', or 'V'"))

        # Allocate
        work = Array(Float64, 4n)
        Z = compz == 'N' ? Array(Float64, 0, 0) : Array(Float64, n, n)
        its = Array(Int32, n - 1)
        info = Array(Int32, 1)

        ccall((:dohfqr_, libeiscor), Void,
            (Ptr{Uint8}, Ptr{Int32}, Ptr{Float64}, Ptr{Float64},
             Ptr{Int32}, Ptr{Float64}, Ptr{Int32}),
             &compz, &n, H, Z,
             its, work, info)

        if info[1] != 0
            info[1] == 2 && error("DOFFQR failed")
            info[1] == 1 && error("DOHRFF failed")
        end
        H, Z, its
    end

    function uhfqr!(compz::Char, H::Matrix{Complex{Float64}})
        # Check
        chkstride1(H)
        n = chksquare(H)
        compz in ('N', 'I', 'V') || throw(ArgumentError("argument compz must be either be either 'N', 'I', or 'V'"))

        # Allocate
        work = Array(Complex{Float64}, 5n)
        Z = compz == 'N' ? Array(Complex{Float64}, 0, 0) : Array(Complex{Float64}, n, n)
        its = Array(Int32, n - 1)
        info = Array(Int32, 1)

        ccall((:zuhfqr_, libeiscor), Void,
            (Ptr{Uint8}, Ptr{Int32}, Ptr{Complex{Float64}}, Ptr{Complex{Float64}},
             Ptr{Int32}, Ptr{Complex{Float64}}, Ptr{Int32}),
             &compz, &n, H, Z,
             its, work, info)

        if info[1] != 0
            info[1] == 2 && error("ZUFFQR failed")
            info[1] == 1 && error("ZUHRFF failed")
        end
        H, Z, its
    end

    function eigvals(UH::UnitaryHessenbergMatrix{Float64})
        H, Z, its = ohfqr!('N', copy(UH.data))
        n = size(H, 1)
        v = zeros(Complex{Float64}, n)
        i = 1
        while i < n
            if H[i + 1, i] == 0
                v[i] = H[i,i]
                i += 1
            else
                v[i]    = complex(H[i,i], H[i,i+1])
                v[i+1]  = complex(H[i,i], H[i+1,i])
                i += 2
            end
        end
        i == n && (v[n] = H[n,n])
        return v
    end
    eigvals(UH::UnitaryHessenbergMatrix{Complex{Float64}}) = diag(uhfqr!('N', copy(UH.data))[1])

    function eigfact!(UH::UnitaryHessenbergMatrix{Float64})
        H, Z, its = ohfqr!('I', UH.data)
        n = size(H, 1)
        v = zeros(Complex{Float64}, n)
        i = 1
        while i < n
            if H[i + 1, i] == 0
                v[i] = H[i,i]
                i += 1
            else
                v[i]    = complex(H[i,i], H[i,i+1])
                v[i+1]  = complex(H[i,i], H[i+1,i])
                i += 2
            end
        end
        i == n && (v[n] = H[n,n])
        return Eigen(v, Z)
    end

    function eigfact!(UH::UnitaryHessenbergMatrix{Complex{Float64}})
        H, Z, its = uhfqr!('I', UH.data)
        return Eigen(diag(H), Z)
    end

end # module
