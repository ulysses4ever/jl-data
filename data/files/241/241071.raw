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
    d1::Int128
end
immutable Array_256_Uint8
    d1::Int128
    d2::Int128
    d3::Int128
    d4::Int128
    d5::Int128
    d6::Int128
    d7::Int128
    d8::Int128
    d9::Int128
    d10::Int128
    d11::Int128
    d12::Int128
    d13::Int128
    d14::Int128
    d15::Int128
    d16::Int128
end
immutable Array_64_Uint8
    d1::Int128
    d2::Int128
    d3::Int128
    d4::Int128
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
