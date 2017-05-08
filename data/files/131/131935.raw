

type DirichiletLift

    N::Int
    nd::Int
    nv::Int
    idx::Array{Int,1}
    vidx::Array{Int,1}
    A::Array{Float64,2}
    function DirichiletLift(n, is_dirichilet)
        nd = 0
        for i = 1:n
            nd = is_dirichilet[i]?nd+1:nd
        end
        nv = n - nd
        idx = zeros(Int, nd)
        vidx = zeros(Int, n-nd)
        icnt = 1
        ivar = 1
        for i = 1:n
            if is_dirichilet[i]
                idx[icnt] = i
                icnt += 1
            else
                vidx[ivar] = i
                ivar += 1
            end
        end
        
        A = zeros(nd, nv)

        new(n, nd, nv, idx, vidx, A)
    end
    
end


function set_dirichilet_matrix(dlift::DirichiletLift, M)
    A = dlift.A
    N = dlift.N
    nd = dlift.nd
    nv = dlift.nv
    idx = dlift.idx
    vidx = dlift.vidx

    for i = 1:nv
        iv = vidx[i]
        for k = 1:nd
            A[k,i] = M[idx[k],iv]
        end
    end

end


function lift(dlift::DirichiletLift, f)

    idx = dlift.idx
    nv = dlift.nv
    nd = dlift.nd
    vidx = dlift.vidx
    A = dlift.A

    for i = 1:nv
        iv = vidx[i]
        b = f[iv]
        for k = 1:nd
            b -= A[k,i] * f[idx[k]]
        end
    end
end



    