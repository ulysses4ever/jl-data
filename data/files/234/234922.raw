lap = PowerLAPACK.LAPACK

println("Test stev!")

function test_stev(N::Integer, nt::Integer)
    dv = -2ones(N)
    ev = ones(N-1)
    dv_w = copy(dv)
    ev_w = copy(ev)

    println("$(N)×$(N) symmetric tridiagonal matrix, $nt iterations")

    println("eigfact:")
    T = SymTridiagonal(copy(dv), copy(ev))
    ee = 1
    function highlevel(nn)
        for i = 1:nn
            TT = copy(T) # Ugly, I know
            ee = Base.Eigen(Base.LAPACK.stev!('V', TT.dv, TT.ev)...)
        end
    end
    highlevel(1)
    @time highlevel(nt)

    println("stev! w/ prealloc'd work, passed as splat array:")
    s_work = lap.stev!('V', dv, ev, true)
    function lowlevel_compound(nn)
        for i = 1:nn
            dv_w[:] = dv
            ev_w[:] = ev
            lap.stev!('V', dv_w, ev_w, s_work...)
        end
    end
    lowlevel_compound(1)
    @time lowlevel_compound(nt)
    @test sumabs2(ee[:values]-dv_w) == 0
    @test sumabs2(ee[:vectors]-s_work[1]) == 0

    println("stev! w/ prealloc'd work, passed separately:")
    Zmat,work,info = lap.stev!('V', dv, ev, true)
    function lowlevel_separate(nn)
        for i = 1:nn
            dv_w[:] = dv
            ev_w[:] = ev
            lap.stev!('V', dv_w, ev_w, Zmat, work, info)
        end
    end
    lowlevel_separate(1)
    @time lowlevel_separate(nt)
    @test sumabs2(ee[:values]-dv_w) == 0
    @test sumabs2(ee[:vectors]-Zmat) == 0
end

function test_stev_subspace(N,M)
    dv = -2ones(N)
    ev = ones(N-1)

    println("$(N)×$(N) symmetric tridiagonal matrix, $(M)×$(M) subspace")

    T = SymTridiagonal(copy(dv[1:M]), copy(ev[1:M-1]))
    ee = Base.Eigen(Base.LAPACK.stev!('V', T.dv, T.ev)...)

    Zmat,work,info = lap.stev!('V', dv, ev, true)
    @time lap.stev!('V', sub(dv, 1:M), sub(ev, 1:M), sub(Zmat, 1:M, 1:M), work, info)
    dv = -2ones(N)
    ev = ones(N-1)
    @time lap.stev!('V', sub(dv, 1:M), sub(ev, 1:M), sub(Zmat, 1:M, 1:M), work, info)

    @test sumabs2(ee[:values]-dv[1:M]) == 0
    @test sumabs2(ee[:vectors]-Zmat[1:M,1:M]) == 0
end

test_stev(500,10)
test_stev_subspace(20,10)

println()
