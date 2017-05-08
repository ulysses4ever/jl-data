lap = PowerLAPACK.LAPACK

function test_stegr(N::Integer, nt::Integer)
    dv = -2ones(N)
    ev = ones(N-1)
    eev = [ev; zero(eltype(ev))]
    dv_w = copy(dv)
    eev_w = copy(eev)

    println("$(N)×$(N) symmetric tridiagonal matrix, $nt iterations")

    println("eigfact:")
    T = SymTridiagonal(copy(dv), copy(ev))
    ee = 1
    function highlevel(nn)
        for i = 1:nn
            ee = eigfact(T)
        end
    end
    highlevel(1)
    @time highlevel(nt)

    println("stegr! w/ prealloc'd work, passed as splat array:")
    s_work = lap.stegr_work('V', 'A', dv, eev, 0.0, 0.0, 0, 0)
    function lowlevel_compound(nn)
        for i = 1:nn
            dv_w[:] = dv
            eev_w[:] = eev
            lap.stegr!('V', 'A', dv_w, eev_w, 0.0, 0.0, 0, 0, s_work...)
        end
    end
    lowlevel_compound(1)
    @time lowlevel_compound(nt)
    @test sumabs2(ee[:values]-s_work[3]) == 0
    @test sumabs2(ee[:vectors]-s_work[4]) == 0

    println("stegr! w/ prealloc'd work, passed separately:")
    abstol,m,w,Z,isuppz,work,lwork,iwork,liwork,info = lap.stegr_work('V', 'A', dv, eev, 0.0, 0.0, 0, 0)
    function lowlevel_separate(nn)
        for i = 1:nn
            dv_w[:] = dv
            eev_w[:] = eev
            lap.stegr!('V', 'A', dv_w, eev_w, 0.0, 0.0, 0, 0, abstol,m,w,Z,isuppz,work,lwork,iwork,liwork,info)
        end
    end
    lowlevel_separate(1)
    @time lowlevel_separate(nt)
    @test sumabs2(ee[:values]-w) == 0
    @test sumabs2(ee[:vectors]-Z) == 0
end

test_stegr(2000,100)
