include("libxbraid_xtra_h.jl")

typealias braid_Int Cint
typealias braid_Real Cdouble

type _braid_AccessStatus_struct
    t::braid_Real
    iter::braid_Int
    level::braid_Int
    rnorm::braid_Real
    done::braid_Int
    wrapper_test::braid_Int
end

typealias braid_AccessStatus Ptr{_braid_AccessStatus_struct}

type _braid_AccessStatus
    t::braid_Real
    iter::braid_Int
    level::braid_Int
    rnorm::braid_Real
    done::braid_Int
    wrapper_test::braid_Int
end

type _braid_CoarsenRefStatus_struct
    tstart::braid_Real
    f_tprior::braid_Real
    f_tstop::braid_Real
    c_tprior::braid_Real
    c_tstop::braid_Real
end

typealias braid_CoarsenRefStatus Ptr{_braid_CoarsenRefStatus_struct}

type _braid_CoarsenRefStatus
    tstart::braid_Real
    f_tprior::braid_Real
    f_tstop::braid_Real
    c_tprior::braid_Real
    c_tstop::braid_Real
end

type _braid_PhiStatus_struct
    tstart::braid_Real
    tstop::braid_Real
    accuracy::braid_Real
    rfactor::braid_Int
end

typealias braid_PhiStatus Ptr{_braid_PhiStatus_struct}

type _braid_PhiStatus
    tstart::braid_Real
    tstop::braid_Real
    accuracy::braid_Real
    rfactor::braid_Int
end

type _braid_App_struct
end

typealias braid_App Ptr{_braid_App_struct}

type _braid_Vector_struct
end

typealias braid_Vector Ptr{_braid_Vector_struct}
typealias braid_PtFcnPhi Ptr{Void}
typealias braid_PtFcnInit Ptr{Void}
typealias braid_PtFcnClone Ptr{Void}
typealias braid_PtFcnFree Ptr{Void}
typealias braid_PtFcnSum Ptr{Void}
typealias braid_PtFcnSpatialNorm Ptr{Void}
typealias braid_PtFcnAccess Ptr{Void}
typealias braid_PtFcnBufSize Ptr{Void}
typealias braid_PtFcnBufPack Ptr{Void}
typealias braid_PtFcnBufUnpack Ptr{Void}
typealias braid_PtFcnCoarsen Ptr{Void}
typealias braid_PtFcnRefine Ptr{Void}

type _braid_AccuracyHandle
    matchF::braid_Int
    value::braid_Real
    old_value::braid_Real
    loose::braid_Real
    tight::braid_Real
    tight_used::braid_Int
end

type _braid_CommHandle
    request_type::braid_Int
    num_requests::braid_Int
    requests::Ptr{MPI_Request}
    status::Ptr{MPI_Status}
    buffer::Ptr{Void}
    vector_ptr::Ptr{braid_Vector}
end

type _braid_Grid
    level::braid_Int
    ilower::braid_Int
    iupper::braid_Int
    clower::braid_Int
    cupper::braid_Int
    gupper::braid_Int
    cfactor::braid_Int
    ncpoints::braid_Int
    ua::Ptr{braid_Vector}
    ta::Ptr{braid_Real}
    va::Ptr{braid_Vector}
    wa::Ptr{braid_Vector}
    recv_index::braid_Int
    send_index::braid_Int
    recv_handle::Ptr{_braid_CommHandle}
    send_handle::Ptr{_braid_CommHandle}
    ua_alloc::Ptr{braid_Vector}
    ta_alloc::Ptr{braid_Real}
    va_alloc::Ptr{braid_Vector}
    wa_alloc::Ptr{braid_Vector}
end

type _braid_Core_struct
    comm_world::MPI_Comm
    comm::MPI_Comm
    tstart::braid_Real
    tstop::braid_Real
    ntime::braid_Int
    app::braid_App
    phi::braid_PtFcnPhi
    init::braid_PtFcnInit
    clone::braid_PtFcnClone
    free::braid_PtFcnFree
    sum::braid_PtFcnSum
    spatialnorm::braid_PtFcnSpatialNorm
    access::braid_PtFcnAccess
    bufsize::braid_PtFcnBufSize
    bufpack::braid_PtFcnBufPack
    bufunpack::braid_PtFcnBufUnpack
    coarsen::braid_PtFcnCoarsen
    refine::braid_PtFcnRefine
    access_level::braid_Int
    print_level::braid_Int
    max_levels::braid_Int
    min_coarse::braid_Int
    tol::braid_Real
    rtol::braid_Int
    nrels::Ptr{braid_Int}
    nrdefault::braid_Int
    cfactors::Ptr{braid_Int}
    cfdefault::braid_Int
    max_iter::braid_Int
    niter::braid_Int
    rnorm::braid_Real
    fmg::braid_Int
    nfmg_Vcyc::braid_Int
    tnorm::braid_Int
    tnorm_a::Ptr{braid_Real}
    accuracy::Ptr{_braid_AccuracyHandle}
    astatus::braid_AccessStatus
    cstatus::braid_CoarsenRefStatus
    pstatus::braid_PhiStatus
    gupper::braid_Int
    rfactors::Ptr{braid_Int}
    nlevels::braid_Int
    grids::Ptr{Ptr{_braid_Grid}}
    localtime::braid_Real
    globaltime::braid_Real
end

typealias braid_Core Ptr{_braid_Core_struct}

type _braid_Core
    comm_world::MPI_Comm
    comm::MPI_Comm
    tstart::braid_Real
    tstop::braid_Real
    ntime::braid_Int
    app::braid_App
    phi::braid_PtFcnPhi
    init::braid_PtFcnInit
    clone::braid_PtFcnClone
    free::braid_PtFcnFree
    sum::braid_PtFcnSum
    spatialnorm::braid_PtFcnSpatialNorm
    access::braid_PtFcnAccess
    bufsize::braid_PtFcnBufSize
    bufpack::braid_PtFcnBufPack
    bufunpack::braid_PtFcnBufUnpack
    coarsen::braid_PtFcnCoarsen
    refine::braid_PtFcnRefine
    access_level::braid_Int
    print_level::braid_Int
    max_levels::braid_Int
    min_coarse::braid_Int
    tol::braid_Real
    rtol::braid_Int
    nrels::Ptr{braid_Int}
    nrdefault::braid_Int
    cfactors::Ptr{braid_Int}
    cfdefault::braid_Int
    max_iter::braid_Int
    niter::braid_Int
    rnorm::braid_Real
    fmg::braid_Int
    nfmg_Vcyc::braid_Int
    tnorm::braid_Int
    tnorm_a::Ptr{braid_Real}
    accuracy::Ptr{_braid_AccuracyHandle}
    astatus::braid_AccessStatus
    cstatus::braid_CoarsenRefStatus
    pstatus::braid_PhiStatus
    gupper::braid_Int
    rfactors::Ptr{braid_Int}
    nlevels::braid_Int
    grids::Ptr{Ptr{_braid_Grid}}
    localtime::braid_Real
    globaltime::braid_Real
end
