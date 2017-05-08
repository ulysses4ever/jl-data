immutable Icntl
    Fout::Cint                          # Fortran stdout output stream number
    Ferr::Cint                          # Fortran stderr output stream number
    FDout::Cint                         # Fortran distributed stdout
    Verb::Cint                          # Verbosity level
    MElm::Cint                          # Matrix in Assembled (0) or Elemental (1) format
    PermScal::Cint                      # Permutation and Scaling method
    Ordm::Cint                          # Ordering method 0 - AMD, 1 input, 2 AMF, 3 SCOTCH, 4 PORD, 5 Metis, 6 QAMD, 7 auto
    Scal::Cint                          # Scaling strategy
    Trans::Cint                         # Solve transposed system
    Irfn::Cint                          # Max # of iterative refinement steps
    Stat::Cint                          # Return error analysis on solve step in rinfog
    Gensym::Cint                        # ordering choices for general symmetric
    ScalLA::Cint                        # use ScalLAPACK on root frontal matrix
    PcntIn::Cint                        # percentage increase in working space allowed
    d15::Cint                           # d15-d17 not used
    d16::Cint
    d17::Cint
    Dist::Cint                          # Distributed input matrix
    Schur::Cint                         # Return the Schur complement matrix
    RHSsp::Cint                         # RHS is sparse
    dSol::Cint                          # Solution kept distributed
    OOC::Cint                           # Out-of-core
    MaxWM::Cint                         # Maximum working memory (in MB)
    NullPiv::Cint                       # NULL pivot rows check
    NullSp::Cint                        # Create a null-space basis
    SchRHS::Cint                        # Options for Schur RHS
    BlkRHS::Cint                        # Blocking size for multiple RHS
    ParOrd::Cint                        # Should parallel ordering be used
    POMeth::Cint                        # Parallel ordering method (PT-SCOTCH or ParMetis)
    Inv::Cint                           # Determine specified elements of inverse
    DrpFac::Cint                        # Drop the factorization components (only stats returned)
    d32::Cint                           # Not used
    Det::Cint                           # Compute determinant
    d34::Cint                           # d34-d40 not used
    d35::Cint
    d36::Cint
    d37::Cint
    d38::Cint
    d39::Cint
    d40::Cint
end
immutable Rcntl
    Numpiv::Cdouble                     # relative threshold for numeric pivoting
    ItRef::Cdouble                      # stopping criterion for iterative refinement
    NullPiv::Cdouble                    # Null pivot detection threshold
    StatPiv::Cdouble                    # Static pivoting threshold
    NPfix::Cdouble                      # Fixation for null pivots
    d6::Cdouble                         # d6-d15 not used
    d7::Cdouble
    d8::Cdouble
    d9::Cdouble
    d10::Cdouble
    d11::Cdouble
    d12::Cdouble
    d13::Cdouble
    d14::Cdouble
    d15::Cdouble
end
immutable Info
    Info::Cint  # 0 for success, neg for error, pos for warning
    Proc::Cint  # processor number on which error or warning occurred
    fSiz::Cint  # Estimated size of real/complex space to store factor
    iSiz::Cint  # Estimated integer size for factors
    frSiz::Cint # Estimated maximum front size
    Nodes::Cint # Number of nodes in the complete tree
    mIWSiz::Cint                        # Minimum internal integer storage
    mRWSiz::Cint                        # Minimum interanl float storage
    FSiz::Cint                          # Actual real storage for factor
    ISiz::Cint                          # Actual integer storage for factor
    FrOrd::Cint                         # Order of largest frontal matrix
    NegPiv::Cint                        # Number of negative pivots
    PostElim::Cint                      # Number of postponed eliminations
    MemComp::Cint                       # Number of memory compresses
    memSiz::Cint                        # Estimated memory size (MB) for factor/solve
    MemSiz::Cint                        # Actual memory size (MB) for factorization
    memSizOOC::Cint                     # Estimated memory size for OOC factorization
    NNull::Cint                         # Number of null pivots
    iSizOOC::Cint                       # Estimated size of integer work for OOC
    rSizOOC::Cint                       # Estimated size of real work for OOC
    EffSiz::Cint                        # Effective space used
    EffSzMB::Cint                       # Effective space in MB
    PivElim::Cint                       # Total number of pivots eliminated
    fEnt::Cint                          # Estimated number of entries in factors
    PivTiny::Cint                       # Number of tiny pivots
    SolSiz::Cint                        # Effective size of memory to run solution (MB)
    FEnt::Cint                          # Effective number of entries in factors
    d28::Cint                           # d28-d40 not used
    d29::Cint
    d30::Cint
    d31::Cint
    d32::Cint
    d33::Cint
    d34::Cint
    d35::Cint
    d36::Cint
    d37::Cint
    d38::Cint
    d39::Cint
    d40::Cint
end
immutable Rinfo
    eFPelim::Cdouble                     # Estimated FLOPS for elimination
    FPassm::Cdouble                      # FLOPS for assembly
    FPelim::Cdouble                      # FLOPS for elimination
    d4::Cdouble                          # d4-d40 not used
    d5::Cdouble
    d6::Cdouble
    d7::Cdouble
    d8::Cdouble
    d9::Cdouble
    d10::Cdouble
    d11::Cdouble
    d12::Cdouble
    d13::Cdouble
    d14::Cdouble
    d15::Cdouble
    d16::Cdouble
    d17::Cdouble
    d18::Cdouble
    d19::Cdouble
    d20::Cdouble
    d21::Cdouble
    d22::Cdouble
    d23::Cdouble
    d24::Cdouble
    d25::Cdouble
    d26::Cdouble
    d27::Cdouble
    d28::Cdouble
    d29::Cdouble
    d30::Cdouble
    d31::Cdouble
    d32::Cdouble
    d33::Cdouble
    d34::Cdouble
    d35::Cdouble
    d36::Cdouble
    d37::Cdouble
    d38::Cdouble
    d39::Cdouble
    d40::Cdouble
end
immutable Array_16_Uint8
    d1::Uint8
    d2::Uint8
    d3::Uint8
    d4::Uint8
    d5::Uint8
    d6::Uint8
    d7::Uint8
    d8::Uint8
    d9::Uint8
    d10::Uint8
    d11::Uint8
    d12::Uint8
    d13::Uint8
    d14::Uint8
    d15::Uint8
    d16::Uint8
end
immutable Array_256_Uint8
    d1::Uint8
    d2::Uint8
    d3::Uint8
    d4::Uint8
    d5::Uint8
    d6::Uint8
    d7::Uint8
    d8::Uint8
    d9::Uint8
    d10::Uint8
    d11::Uint8
    d12::Uint8
    d13::Uint8
    d14::Uint8
    d15::Uint8
    d16::Uint8
    d17::Uint8
    d18::Uint8
    d19::Uint8
    d20::Uint8
    d21::Uint8
    d22::Uint8
    d23::Uint8
    d24::Uint8
    d25::Uint8
    d26::Uint8
    d27::Uint8
    d28::Uint8
    d29::Uint8
    d30::Uint8
    d31::Uint8
    d32::Uint8
    d33::Uint8
    d34::Uint8
    d35::Uint8
    d36::Uint8
    d37::Uint8
    d38::Uint8
    d39::Uint8
    d40::Uint8
    d41::Uint8
    d42::Uint8
    d43::Uint8
    d44::Uint8
    d45::Uint8
    d46::Uint8
    d47::Uint8
    d48::Uint8
    d49::Uint8
    d50::Uint8
    d51::Uint8
    d52::Uint8
    d53::Uint8
    d54::Uint8
    d55::Uint8
    d56::Uint8
    d57::Uint8
    d58::Uint8
    d59::Uint8
    d60::Uint8
    d61::Uint8
    d62::Uint8
    d63::Uint8
    d64::Uint8
    d65::Uint8
    d66::Uint8
    d67::Uint8
    d68::Uint8
    d69::Uint8
    d70::Uint8
    d71::Uint8
    d72::Uint8
    d73::Uint8
    d74::Uint8
    d75::Uint8
    d76::Uint8
    d77::Uint8
    d78::Uint8
    d79::Uint8
    d80::Uint8
    d81::Uint8
    d82::Uint8
    d83::Uint8
    d84::Uint8
    d85::Uint8
    d86::Uint8
    d87::Uint8
    d88::Uint8
    d89::Uint8
    d90::Uint8
    d91::Uint8
    d92::Uint8
    d93::Uint8
    d94::Uint8
    d95::Uint8
    d96::Uint8
    d97::Uint8
    d98::Uint8
    d99::Uint8
    d100::Uint8
    d101::Uint8
    d102::Uint8
    d103::Uint8
    d104::Uint8
    d105::Uint8
    d106::Uint8
    d107::Uint8
    d108::Uint8
    d109::Uint8
    d110::Uint8
    d111::Uint8
    d112::Uint8
    d113::Uint8
    d114::Uint8
    d115::Uint8
    d116::Uint8
    d117::Uint8
    d118::Uint8
    d119::Uint8
    d120::Uint8
    d121::Uint8
    d122::Uint8
    d123::Uint8
    d124::Uint8
    d125::Uint8
    d126::Uint8
    d127::Uint8
    d128::Uint8
    d129::Uint8
    d130::Uint8
    d131::Uint8
    d132::Uint8
    d133::Uint8
    d134::Uint8
    d135::Uint8
    d136::Uint8
    d137::Uint8
    d138::Uint8
    d139::Uint8
    d140::Uint8
    d141::Uint8
    d142::Uint8
    d143::Uint8
    d144::Uint8
    d145::Uint8
    d146::Uint8
    d147::Uint8
    d148::Uint8
    d149::Uint8
    d150::Uint8
    d151::Uint8
    d152::Uint8
    d153::Uint8
    d154::Uint8
    d155::Uint8
    d156::Uint8
    d157::Uint8
    d158::Uint8
    d159::Uint8
    d160::Uint8
    d161::Uint8
    d162::Uint8
    d163::Uint8
    d164::Uint8
    d165::Uint8
    d166::Uint8
    d167::Uint8
    d168::Uint8
    d169::Uint8
    d170::Uint8
    d171::Uint8
    d172::Uint8
    d173::Uint8
    d174::Uint8
    d175::Uint8
    d176::Uint8
    d177::Uint8
    d178::Uint8
    d179::Uint8
    d180::Uint8
    d181::Uint8
    d182::Uint8
    d183::Uint8
    d184::Uint8
    d185::Uint8
    d186::Uint8
    d187::Uint8
    d188::Uint8
    d189::Uint8
    d190::Uint8
    d191::Uint8
    d192::Uint8
    d193::Uint8
    d194::Uint8
    d195::Uint8
    d196::Uint8
    d197::Uint8
    d198::Uint8
    d199::Uint8
    d200::Uint8
    d201::Uint8
    d202::Uint8
    d203::Uint8
    d204::Uint8
    d205::Uint8
    d206::Uint8
    d207::Uint8
    d208::Uint8
    d209::Uint8
    d210::Uint8
    d211::Uint8
    d212::Uint8
    d213::Uint8
    d214::Uint8
    d215::Uint8
    d216::Uint8
    d217::Uint8
    d218::Uint8
    d219::Uint8
    d220::Uint8
    d221::Uint8
    d222::Uint8
    d223::Uint8
    d224::Uint8
    d225::Uint8
    d226::Uint8
    d227::Uint8
    d228::Uint8
    d229::Uint8
    d230::Uint8
    d231::Uint8
    d232::Uint8
    d233::Uint8
    d234::Uint8
    d235::Uint8
    d236::Uint8
    d237::Uint8
    d238::Uint8
    d239::Uint8
    d240::Uint8
    d241::Uint8
    d242::Uint8
    d243::Uint8
    d244::Uint8
    d245::Uint8
    d246::Uint8
    d247::Uint8
    d248::Uint8
    d249::Uint8
    d250::Uint8
    d251::Uint8
    d252::Uint8
    d253::Uint8
    d254::Uint8
    d255::Uint8
    d256::Uint8
end
immutable Array_64_Uint8
    d1::Uint8
    d2::Uint8
    d3::Uint8
    d4::Uint8
    d5::Uint8
    d6::Uint8
    d7::Uint8
    d8::Uint8
    d9::Uint8
    d10::Uint8
    d11::Uint8
    d12::Uint8
    d13::Uint8
    d14::Uint8
    d15::Uint8
    d16::Uint8
    d17::Uint8
    d18::Uint8
    d19::Uint8
    d20::Uint8
    d21::Uint8
    d22::Uint8
    d23::Uint8
    d24::Uint8
    d25::Uint8
    d26::Uint8
    d27::Uint8
    d28::Uint8
    d29::Uint8
    d30::Uint8
    d31::Uint8
    d32::Uint8
    d33::Uint8
    d34::Uint8
    d35::Uint8
    d36::Uint8
    d37::Uint8
    d38::Uint8
    d39::Uint8
    d40::Uint8
    d41::Uint8
    d42::Uint8
    d43::Uint8
    d44::Uint8
    d45::Uint8
    d46::Uint8
    d47::Uint8
    d48::Uint8
    d49::Uint8
    d50::Uint8
    d51::Uint8
    d52::Uint8
    d53::Uint8
    d54::Uint8
    d55::Uint8
    d56::Uint8
    d57::Uint8
    d58::Uint8
    d59::Uint8
    d60::Uint8
    d61::Uint8
    d62::Uint8
    d63::Uint8
    d64::Uint8
end
type DMumps
    sym::Cint
    par::Cint
    job::Cint
    comm_fortran::Cint
    icntl::Icntl
    cntl::Rcntl
    n::Cint
    nz_alloc::Cint
    nz::Cint
    irn::Ptr{Cint}
    jcn::Ptr{Cint}
    a::Ptr{Cdouble}
    nz_loc::Cint
    irn_loc::Ptr{Cint}
    jcn_loc::Ptr{Cint}
    a_loc::Ptr{Cdouble}
    nelt::Cint
    eltptr::Ptr{Cint}
    eltvar::Ptr{Cint}
    a_elt::Ptr{Cdouble}
    perm_in::Ptr{Cint}
    sym_perm::Ptr{Cint}
    uns_perm::Ptr{Cint}
    colsca::Ptr{Cdouble}
    rowsca::Ptr{Cdouble}
    rhs::Ptr{Cdouble}
    redrhs::Ptr{Cdouble}
    rhs_sparse::Ptr{Cdouble}
    sol_loc::Ptr{Cdouble}
    irhs_sparse::Ptr{Cint}
    irhs_ptr::Ptr{Cint}
    isol_loc::Ptr{Cint}
    nrhs::Cint
    lrhs::Cint
    lredrhs::Cint
    nz_rhs::Cint
    lsol_loc::Cint
    schur_mloc::Cint
    schur_nloc::Cint
    schur_lld::Cint
    mblock::Cint
    nblock::Cint
    nprow::Cint
    npcol::Cint
    info::Info
    infog::Info
    rinfo::Rinfo
    rinfog::Rinfo
    deficiency::Cint
    pivnul_list::Ptr{Cint}
    mapping::Ptr{Cint}
    size_schur::Cint
    listvar_schur::Ptr{Cint}
    schur::Ptr{Cdouble}
    instance_number::Cint
    wk_user::Ptr{Cdouble}
    version_number::Array_16_Uint8
    ooc_tmpdir::Array_256_Uint8
    ooc_prefix::Array_64_Uint8
    write_problem::Array_256_Uint8
    lwk_user::Cint
end

import Base: zero, string

for T in (:Icntl, :Rcntl, :Info, :Rinfo, :Array_16_Uint8, :Array_64_Uint8, :Array_256_Uint8)
    @eval begin
        zero(::Type{$T}) = apply($T, map(zero, $T.types))
    end
end

function DMumps()
    res = apply(DMumps, map(zero, DMumps.types)) # fill type with zeros
    res.par = 1
    res.job = -1
    ccall((:dmumps_c, dmumps), Void, (Ptr{DMumps},), &res)
    res
end

function string{T<:Union{Array_16_Uint8,Array_64_Uint8,Array_256_Uint8})(a::T)
    bytestring(pointer([getfield(a,nm)::Uint8 for nm in names(a)]))
end
