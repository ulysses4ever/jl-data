# Julia wrapper for header: /home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include/braid_defs.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0

# Julia wrapper for header: /home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include/_braid.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function _braid_AccessStatusInit(t::braid_Real,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int,wrapper_test::braid_Int,status::braid_AccessStatus)
    ccall((:_braid_AccessStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Int,braid_Int,braid_Int,braid_Int,braid_AccessStatus),t,rnorm,iter,level,done,wrapper_test,status)
end

function _braid_AccessStatusDestroy(status::braid_AccessStatus)
    ccall((:_braid_AccessStatusDestroy,libxbraid),braid_Int,(braid_AccessStatus,),status)
end

function braid_AccessStatusGetT(status::braid_AccessStatus,t_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetT,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,t_ptr)
end

function braid_AccessStatusGetResidual(status::braid_AccessStatus,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetResidual,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,rnorm_ptr)
end

function braid_AccessStatusGetIter(status::braid_AccessStatus,iter_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetIter,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,iter_ptr)
end

function braid_AccessStatusGetLevel(status::braid_AccessStatus,level_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetLevel,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,level_ptr)
end

function braid_AccessStatusGetDone(status::braid_AccessStatus,done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetDone,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,done_ptr)
end

function braid_AccessStatusGetWrapperTest(status::braid_AccessStatus,wtest_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetWrapperTest,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,wtest_ptr)
end

function braid_AccessStatusGetTILD(status::braid_AccessStatus,t_ptr::Ptr{braid_Real},iter_ptr::Ptr{braid_Int},level_ptr::Ptr{braid_Int},done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetTILD,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real},Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),status,t_ptr,iter_ptr,level_ptr,done_ptr)
end

function _braid_CoarsenRefStatusInit(tstart::braid_Real,f_tprior::braid_Real,f_tstop::braid_Real,c_tprior::braid_Real,c_tstop::braid_Real,status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_Real,braid_Real,braid_CoarsenRefStatus),tstart,f_tprior,f_tstop,c_tprior,c_tstop,status)
end

function _braid_CoarsenRefStatusDestroy(status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusDestroy,libxbraid),braid_Int,(braid_CoarsenRefStatus,),status)
end

function braid_CoarsenRefStatusGetTstart(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTstart,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_CoarsenRefStatusGetFTstop(status::braid_CoarsenRefStatus,f_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tstop_ptr)
end

function braid_CoarsenRefStatusGetFTprior(status::braid_CoarsenRefStatus,f_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tprior_ptr)
end

function braid_CoarsenRefStatusGetCTstop(status::braid_CoarsenRefStatus,c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tstop_ptr)
end

function braid_CoarsenRefStatusGetCTprior(status::braid_CoarsenRefStatus,c_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tprior_ptr)
end

function braid_CoarsenRefStatusGetTpriorTstop(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real},f_tprior_ptr::Ptr{braid_Real},f_tstop_ptr::Ptr{braid_Real},c_tprior_ptr::Ptr{braid_Real},c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTpriorTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,f_tprior_ptr,f_tstop_ptr,c_tprior_ptr,c_tstop_ptr)
end

function _braid_PhiStatusInit(tstart::braid_Real,tstop::braid_Real,accuracy::braid_Real,status::braid_PhiStatus)
    ccall((:_braid_PhiStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_PhiStatus),tstart,tstop,accuracy,status)
end

function _braid_PhiStatusDestroy(status::braid_PhiStatus)
    ccall((:_braid_PhiStatusDestroy,libxbraid),braid_Int,(braid_PhiStatus,),status)
end

function braid_PhiStatusGetTstart(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstart,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_PhiStatusGetTstop(status::braid_PhiStatus,tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstop_ptr)
end

function braid_PhiStatusGetAccuracy(status::braid_PhiStatus,accuracy_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetAccuracy,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,accuracy_ptr)
end

function braid_PhiStatusSetRFactor(status::braid_PhiStatus,rfactor::braid_Real)
    ccall((:braid_PhiStatusSetRFactor,libxbraid),braid_Int,(braid_PhiStatus,braid_Real),status,rfactor)
end

function braid_PhiStatusGetTstartTstop(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real},tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstartTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,tstop_ptr)
end

function braid_Init(comm_world::MPI_Comm,comm::MPI_Comm,tstart::braid_Real,tstop::braid_Real,ntime::braid_Int,app::braid_App,phi::braid_PtFcnPhi,init::braid_PtFcnInit,clone::braid_PtFcnClone,free::braid_PtFcnFree,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,access::braid_PtFcnAccess,bufsize::braid_PtFcnBufSize,bufpack::braid_PtFcnBufPack,bufunpack::braid_PtFcnBufUnpack,core_ptr::Ptr{braid_Core})
    ccall((:braid_Init,libxbraid),braid_Int,(MPI_Comm,MPI_Comm,braid_Real,braid_Real,braid_Int,braid_App,braid_PtFcnPhi,braid_PtFcnInit,braid_PtFcnClone,braid_PtFcnFree,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnAccess,braid_PtFcnBufSize,braid_PtFcnBufPack,braid_PtFcnBufUnpack,Ptr{braid_Core}),comm_world,comm,tstart,tstop,ntime,app,phi,init,clone,free,sum,spatialnorm,access,bufsize,bufpack,bufunpack,core_ptr)
end

function braid_Drive(core::braid_Core)
    ccall((:braid_Drive,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_Destroy(core::braid_Core)
    ccall((:braid_Destroy,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_PrintStats(core::braid_Core)
    ccall((:braid_PrintStats,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetLoosexTol(core::braid_Core,level::braid_Int,loose_tol::braid_Real)
    ccall((:braid_SetLoosexTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,loose_tol)
end

function braid_SetTightxTol(core::braid_Core,level::braid_Int,tight_tol::braid_Real)
    ccall((:braid_SetTightxTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,tight_tol)
end

function braid_SetMaxLevels(core::braid_Core,max_levels::braid_Int)
    ccall((:braid_SetMaxLevels,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_levels)
end

function braid_SetMinCoarse(core::braid_Core,min_coarse::braid_Int)
    ccall((:braid_SetMinCoarse,libxbraid),braid_Int,(braid_Core,braid_Int),core,min_coarse)
end

function braid_SetAbsTol(core::braid_Core,atol::braid_Real)
    ccall((:braid_SetAbsTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,atol)
end

function braid_SetRelTol(core::braid_Core,rtol::braid_Real)
    ccall((:braid_SetRelTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,rtol)
end

function braid_SetNRelax(core::braid_Core,level::braid_Int,nrelax::braid_Int)
    ccall((:braid_SetNRelax,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,nrelax)
end

function braid_SetCFactor(core::braid_Core,level::braid_Int,cfactor::braid_Int)
    ccall((:braid_SetCFactor,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,cfactor)
end

function braid_SetMaxIter(core::braid_Core,max_iter::braid_Int)
    ccall((:braid_SetMaxIter,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_iter)
end

function braid_SetFMG(core::braid_Core)
    ccall((:braid_SetFMG,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetTemporalNorm(core::braid_Core,tnorm::braid_Int)
    ccall((:braid_SetTemporalNorm,libxbraid),braid_Int,(braid_Core,braid_Int),core,tnorm)
end

function braid_SetNFMGVcyc(core::braid_Core,nfmg_Vcyc::braid_Int)
    ccall((:braid_SetNFMGVcyc,libxbraid),braid_Int,(braid_Core,braid_Int),core,nfmg_Vcyc)
end

function braid_SetSpatialCoarsen(core::braid_Core,coarsen::braid_PtFcnCoarsen)
    ccall((:braid_SetSpatialCoarsen,libxbraid),braid_Int,(braid_Core,braid_PtFcnCoarsen),core,coarsen)
end

function braid_SetSpatialRefine(core::braid_Core,refine::braid_PtFcnRefine)
    ccall((:braid_SetSpatialRefine,libxbraid),braid_Int,(braid_Core,braid_PtFcnRefine),core,refine)
end

function braid_SetPrintLevel(core::braid_Core,print_level::braid_Int)
    ccall((:braid_SetPrintLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,print_level)
end

function braid_SetPrintFile(core::braid_Core,printfile_name::Ptr{Uint8})
    ccall((:braid_SetPrintFile,libxbraid),braid_Int,(braid_Core,Ptr{Uint8}),core,printfile_name)
end

function braid_SetAccessLevel(core::braid_Core,access_level::braid_Int)
    ccall((:braid_SetAccessLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,access_level)
end

function braid_SplitCommworld(comm_world::Ptr{MPI_Comm},px::braid_Int,comm_x::Ptr{MPI_Comm},comm_t::Ptr{MPI_Comm})
    ccall((:braid_SplitCommworld,libxbraid),braid_Int,(Ptr{MPI_Comm},braid_Int,Ptr{MPI_Comm},Ptr{MPI_Comm}),comm_world,px,comm_x,comm_t)
end

function braid_GetNumIter(core::braid_Core,niter_ptr::Ptr{braid_Int})
    ccall((:braid_GetNumIter,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,niter_ptr)
end

function braid_GetRNorm(core::braid_Core,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_GetRNorm,libxbraid),braid_Int,(braid_Core,Ptr{braid_Real}),core,rnorm_ptr)
end

function _braid_GetDistribution(core::braid_Core,ilower_ptr::Ptr{braid_Int},iupper_ptr::Ptr{braid_Int})
    ccall((:_braid_GetDistribution,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int},Ptr{braid_Int}),core,ilower_ptr,iupper_ptr)
end

function _braid_GetProc(core::braid_Core,level::braid_Int,index::braid_Int,proc_ptr::Ptr{braid_Int})
    ccall((:_braid_GetProc,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Int}),core,level,index,proc_ptr)
end

function _braid_CommRecvInit(core::braid_Core,level::braid_Int,index::braid_Int,vector_ptr::Ptr{braid_Vector},handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommRecvInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector},Ptr{Ptr{_braid_CommHandle}}),core,level,index,vector_ptr,handle_ptr)
end

function _braid_CommSendInit(core::braid_Core,level::braid_Int,index::braid_Int,vector::braid_Vector,handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommSendInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector,Ptr{Ptr{_braid_CommHandle}}),core,level,index,vector,handle_ptr)
end

function _braid_CommWait(core::braid_Core,handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommWait,libxbraid),braid_Int,(braid_Core,Ptr{Ptr{_braid_CommHandle}}),core,handle_ptr)
end

function _braid_UCommInit(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommInit,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UCommInitF(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommInitF,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UCommWait(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommWait,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UGetInterval(core::braid_Core,level::braid_Int,interval_index::braid_Int,flo_ptr::Ptr{braid_Int},fhi_ptr::Ptr{braid_Int},ci_ptr::Ptr{braid_Int})
    ccall((:_braid_UGetInterval,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),core,level,interval_index,flo_ptr,fhi_ptr,ci_ptr)
end

function _braid_UGetVectorRef(core::braid_Core,level::braid_Int,index::braid_Int,u_ptr::Ptr{braid_Vector})
    ccall((:_braid_UGetVectorRef,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector}),core,level,index,u_ptr)
end

function _braid_USetVectorRef(core::braid_Core,level::braid_Int,index::braid_Int,u::braid_Vector)
    ccall((:_braid_USetVectorRef,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector),core,level,index,u)
end

function _braid_UGetVector(core::braid_Core,level::braid_Int,index::braid_Int,u_ptr::Ptr{braid_Vector})
    ccall((:_braid_UGetVector,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector}),core,level,index,u_ptr)
end

function _braid_USetVector(core::braid_Core,level::braid_Int,index::braid_Int,u::braid_Vector)
    ccall((:_braid_USetVector,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector),core,level,index,u)
end

function _braid_UAccessVector(core::braid_Core,status::braid_AccessStatus,u::braid_Vector)
    ccall((:_braid_UAccessVector,libxbraid),braid_Int,(braid_Core,braid_AccessStatus,braid_Vector),core,status,u)
end

function _braid_Phi(core::braid_Core,level::braid_Int,index::braid_Int,accuracy::braid_Real,u::braid_Vector,rfactor::Ptr{braid_Int})
    ccall((:_braid_Phi,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real,braid_Vector,Ptr{braid_Int}),core,level,index,accuracy,u,rfactor)
end

function _braid_Step(core::braid_Core,level::braid_Int,index::braid_Int,accuracy::braid_Real,u::braid_Vector)
    ccall((:_braid_Step,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real,braid_Vector),core,level,index,accuracy,u)
end

function _braid_Coarsen(core::braid_Core,level::braid_Int,f_index::braid_Int,c_index::braid_Int,fvector::braid_Vector,cvector::Ptr{braid_Vector})
    ccall((:_braid_Coarsen,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,braid_Vector,Ptr{braid_Vector}),core,level,f_index,c_index,fvector,cvector)
end

function _braid_Refine(core::braid_Core,level::braid_Int,f_index::braid_Int,c_index::braid_Int,cvector::braid_Vector,fvector::Ptr{braid_Vector})
    ccall((:_braid_Refine,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,braid_Vector,Ptr{braid_Vector}),core,level,f_index,c_index,cvector,fvector)
end

function _braid_GridInit(core::braid_Core,level::braid_Int,ilower::braid_Int,iupper::braid_Int,grid_ptr::Ptr{Ptr{_braid_Grid}})
    ccall((:_braid_GridInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,Ptr{Ptr{_braid_Grid}}),core,level,ilower,iupper,grid_ptr)
end

function _braid_GridDestroy(core::braid_Core,grid::Ptr{_braid_Grid})
    ccall((:_braid_GridDestroy,libxbraid),braid_Int,(braid_Core,Ptr{_braid_Grid}),core,grid)
end

function _braid_InitGuess(core::braid_Core,level::braid_Int)
    ccall((:_braid_InitGuess,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_FCRelax(core::braid_Core,level::braid_Int)
    ccall((:_braid_FCRelax,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_FRestrict(core::braid_Core,level::braid_Int,iter::braid_Int,rnorm_ptr::Ptr{braid_Real})
    ccall((:_braid_FRestrict,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Real}),core,level,iter,rnorm_ptr)
end

function _braid_FInterp(core::braid_Core,level::braid_Int,iter::braid_Int,rnorm::braid_Real)
    ccall((:_braid_FInterp,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real),core,level,iter,rnorm)
end

function _braid_FRefine(core::braid_Core,refined_ptr::Ptr{braid_Int})
    ccall((:_braid_FRefine,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,refined_ptr)
end

function _braid_FAccess(core::braid_Core,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int)
    ccall((:_braid_FAccess,libxbraid),braid_Int,(braid_Core,braid_Real,braid_Int,braid_Int,braid_Int),core,rnorm,iter,level,done)
end

function _braid_InitHierarchy(core::braid_Core,fine_grid::Ptr{_braid_Grid})
    ccall((:_braid_InitHierarchy,libxbraid),braid_Int,(braid_Core,Ptr{_braid_Grid}),core,fine_grid)
end
# Julia wrapper for header: /home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include/braid.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function _braid_AccessStatusInit(t::braid_Real,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int,wrapper_test::braid_Int,status::braid_AccessStatus)
    ccall((:_braid_AccessStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Int,braid_Int,braid_Int,braid_Int,braid_AccessStatus),t,rnorm,iter,level,done,wrapper_test,status)
end

function _braid_AccessStatusDestroy(status::braid_AccessStatus)
    ccall((:_braid_AccessStatusDestroy,libxbraid),braid_Int,(braid_AccessStatus,),status)
end

function braid_AccessStatusGetT(status::braid_AccessStatus,t_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetT,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,t_ptr)
end

function braid_AccessStatusGetResidual(status::braid_AccessStatus,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetResidual,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,rnorm_ptr)
end

function braid_AccessStatusGetIter(status::braid_AccessStatus,iter_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetIter,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,iter_ptr)
end

function braid_AccessStatusGetLevel(status::braid_AccessStatus,level_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetLevel,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,level_ptr)
end

function braid_AccessStatusGetDone(status::braid_AccessStatus,done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetDone,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,done_ptr)
end

function braid_AccessStatusGetWrapperTest(status::braid_AccessStatus,wtest_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetWrapperTest,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,wtest_ptr)
end

function braid_AccessStatusGetTILD(status::braid_AccessStatus,t_ptr::Ptr{braid_Real},iter_ptr::Ptr{braid_Int},level_ptr::Ptr{braid_Int},done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetTILD,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real},Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),status,t_ptr,iter_ptr,level_ptr,done_ptr)
end

function _braid_CoarsenRefStatusInit(tstart::braid_Real,f_tprior::braid_Real,f_tstop::braid_Real,c_tprior::braid_Real,c_tstop::braid_Real,status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_Real,braid_Real,braid_CoarsenRefStatus),tstart,f_tprior,f_tstop,c_tprior,c_tstop,status)
end

function _braid_CoarsenRefStatusDestroy(status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusDestroy,libxbraid),braid_Int,(braid_CoarsenRefStatus,),status)
end

function braid_CoarsenRefStatusGetTstart(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTstart,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_CoarsenRefStatusGetFTstop(status::braid_CoarsenRefStatus,f_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tstop_ptr)
end

function braid_CoarsenRefStatusGetFTprior(status::braid_CoarsenRefStatus,f_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tprior_ptr)
end

function braid_CoarsenRefStatusGetCTstop(status::braid_CoarsenRefStatus,c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tstop_ptr)
end

function braid_CoarsenRefStatusGetCTprior(status::braid_CoarsenRefStatus,c_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tprior_ptr)
end

function braid_CoarsenRefStatusGetTpriorTstop(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real},f_tprior_ptr::Ptr{braid_Real},f_tstop_ptr::Ptr{braid_Real},c_tprior_ptr::Ptr{braid_Real},c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTpriorTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,f_tprior_ptr,f_tstop_ptr,c_tprior_ptr,c_tstop_ptr)
end

function _braid_PhiStatusInit(tstart::braid_Real,tstop::braid_Real,accuracy::braid_Real,status::braid_PhiStatus)
    ccall((:_braid_PhiStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_PhiStatus),tstart,tstop,accuracy,status)
end

function _braid_PhiStatusDestroy(status::braid_PhiStatus)
    ccall((:_braid_PhiStatusDestroy,libxbraid),braid_Int,(braid_PhiStatus,),status)
end

function braid_PhiStatusGetTstart(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstart,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_PhiStatusGetTstop(status::braid_PhiStatus,tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstop_ptr)
end

function braid_PhiStatusGetAccuracy(status::braid_PhiStatus,accuracy_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetAccuracy,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,accuracy_ptr)
end

function braid_PhiStatusSetRFactor(status::braid_PhiStatus,rfactor::braid_Real)
    ccall((:braid_PhiStatusSetRFactor,libxbraid),braid_Int,(braid_PhiStatus,braid_Real),status,rfactor)
end

function braid_PhiStatusGetTstartTstop(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real},tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstartTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,tstop_ptr)
end

function braid_Init(comm_world::MPI_Comm,comm::MPI_Comm,tstart::braid_Real,tstop::braid_Real,ntime::braid_Int,app::braid_App,phi::braid_PtFcnPhi,init::braid_PtFcnInit,clone::braid_PtFcnClone,free::braid_PtFcnFree,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,access::braid_PtFcnAccess,bufsize::braid_PtFcnBufSize,bufpack::braid_PtFcnBufPack,bufunpack::braid_PtFcnBufUnpack,core_ptr::Ptr{braid_Core})
    ccall((:braid_Init,libxbraid),braid_Int,(MPI_Comm,MPI_Comm,braid_Real,braid_Real,braid_Int,braid_App,braid_PtFcnPhi,braid_PtFcnInit,braid_PtFcnClone,braid_PtFcnFree,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnAccess,braid_PtFcnBufSize,braid_PtFcnBufPack,braid_PtFcnBufUnpack,Ptr{braid_Core}),comm_world,comm,tstart,tstop,ntime,app,phi,init,clone,free,sum,spatialnorm,access,bufsize,bufpack,bufunpack,core_ptr)
end

function braid_Drive(core::braid_Core)
    ccall((:braid_Drive,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_Destroy(core::braid_Core)
    ccall((:braid_Destroy,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_PrintStats(core::braid_Core)
    ccall((:braid_PrintStats,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetLoosexTol(core::braid_Core,level::braid_Int,loose_tol::braid_Real)
    ccall((:braid_SetLoosexTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,loose_tol)
end

function braid_SetTightxTol(core::braid_Core,level::braid_Int,tight_tol::braid_Real)
    ccall((:braid_SetTightxTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,tight_tol)
end

function braid_SetMaxLevels(core::braid_Core,max_levels::braid_Int)
    ccall((:braid_SetMaxLevels,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_levels)
end

function braid_SetMinCoarse(core::braid_Core,min_coarse::braid_Int)
    ccall((:braid_SetMinCoarse,libxbraid),braid_Int,(braid_Core,braid_Int),core,min_coarse)
end

function braid_SetAbsTol(core::braid_Core,atol::braid_Real)
    ccall((:braid_SetAbsTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,atol)
end

function braid_SetRelTol(core::braid_Core,rtol::braid_Real)
    ccall((:braid_SetRelTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,rtol)
end

function braid_SetNRelax(core::braid_Core,level::braid_Int,nrelax::braid_Int)
    ccall((:braid_SetNRelax,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,nrelax)
end

function braid_SetCFactor(core::braid_Core,level::braid_Int,cfactor::braid_Int)
    ccall((:braid_SetCFactor,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,cfactor)
end

function braid_SetMaxIter(core::braid_Core,max_iter::braid_Int)
    ccall((:braid_SetMaxIter,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_iter)
end

function braid_SetFMG(core::braid_Core)
    ccall((:braid_SetFMG,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetTemporalNorm(core::braid_Core,tnorm::braid_Int)
    ccall((:braid_SetTemporalNorm,libxbraid),braid_Int,(braid_Core,braid_Int),core,tnorm)
end

function braid_SetNFMGVcyc(core::braid_Core,nfmg_Vcyc::braid_Int)
    ccall((:braid_SetNFMGVcyc,libxbraid),braid_Int,(braid_Core,braid_Int),core,nfmg_Vcyc)
end

function braid_SetSpatialCoarsen(core::braid_Core,coarsen::braid_PtFcnCoarsen)
    ccall((:braid_SetSpatialCoarsen,libxbraid),braid_Int,(braid_Core,braid_PtFcnCoarsen),core,coarsen)
end

function braid_SetSpatialRefine(core::braid_Core,refine::braid_PtFcnRefine)
    ccall((:braid_SetSpatialRefine,libxbraid),braid_Int,(braid_Core,braid_PtFcnRefine),core,refine)
end

function braid_SetPrintLevel(core::braid_Core,print_level::braid_Int)
    ccall((:braid_SetPrintLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,print_level)
end

function braid_SetPrintFile(core::braid_Core,printfile_name::Ptr{Uint8})
    ccall((:braid_SetPrintFile,libxbraid),braid_Int,(braid_Core,Ptr{Uint8}),core,printfile_name)
end

function braid_SetAccessLevel(core::braid_Core,access_level::braid_Int)
    ccall((:braid_SetAccessLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,access_level)
end

function braid_SplitCommworld(comm_world::Ptr{MPI_Comm},px::braid_Int,comm_x::Ptr{MPI_Comm},comm_t::Ptr{MPI_Comm})
    ccall((:braid_SplitCommworld,libxbraid),braid_Int,(Ptr{MPI_Comm},braid_Int,Ptr{MPI_Comm},Ptr{MPI_Comm}),comm_world,px,comm_x,comm_t)
end

function braid_GetNumIter(core::braid_Core,niter_ptr::Ptr{braid_Int})
    ccall((:braid_GetNumIter,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,niter_ptr)
end

function braid_GetRNorm(core::braid_Core,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_GetRNorm,libxbraid),braid_Int,(braid_Core,Ptr{braid_Real}),core,rnorm_ptr)
end
# Julia wrapper for header: /home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include/braid_status.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function _braid_AccessStatusInit(t::braid_Real,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int,wrapper_test::braid_Int,status::braid_AccessStatus)
    ccall((:_braid_AccessStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Int,braid_Int,braid_Int,braid_Int,braid_AccessStatus),t,rnorm,iter,level,done,wrapper_test,status)
end

function _braid_AccessStatusDestroy(status::braid_AccessStatus)
    ccall((:_braid_AccessStatusDestroy,libxbraid),braid_Int,(braid_AccessStatus,),status)
end

function braid_AccessStatusGetT(status::braid_AccessStatus,t_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetT,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,t_ptr)
end

function braid_AccessStatusGetResidual(status::braid_AccessStatus,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetResidual,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,rnorm_ptr)
end

function braid_AccessStatusGetIter(status::braid_AccessStatus,iter_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetIter,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,iter_ptr)
end

function braid_AccessStatusGetLevel(status::braid_AccessStatus,level_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetLevel,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,level_ptr)
end

function braid_AccessStatusGetDone(status::braid_AccessStatus,done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetDone,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,done_ptr)
end

function braid_AccessStatusGetWrapperTest(status::braid_AccessStatus,wtest_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetWrapperTest,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,wtest_ptr)
end

function braid_AccessStatusGetTILD(status::braid_AccessStatus,t_ptr::Ptr{braid_Real},iter_ptr::Ptr{braid_Int},level_ptr::Ptr{braid_Int},done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetTILD,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real},Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),status,t_ptr,iter_ptr,level_ptr,done_ptr)
end

function _braid_CoarsenRefStatusInit(tstart::braid_Real,f_tprior::braid_Real,f_tstop::braid_Real,c_tprior::braid_Real,c_tstop::braid_Real,status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_Real,braid_Real,braid_CoarsenRefStatus),tstart,f_tprior,f_tstop,c_tprior,c_tstop,status)
end

function _braid_CoarsenRefStatusDestroy(status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusDestroy,libxbraid),braid_Int,(braid_CoarsenRefStatus,),status)
end

function braid_CoarsenRefStatusGetTstart(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTstart,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_CoarsenRefStatusGetFTstop(status::braid_CoarsenRefStatus,f_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tstop_ptr)
end

function braid_CoarsenRefStatusGetFTprior(status::braid_CoarsenRefStatus,f_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tprior_ptr)
end

function braid_CoarsenRefStatusGetCTstop(status::braid_CoarsenRefStatus,c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tstop_ptr)
end

function braid_CoarsenRefStatusGetCTprior(status::braid_CoarsenRefStatus,c_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tprior_ptr)
end

function braid_CoarsenRefStatusGetTpriorTstop(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real},f_tprior_ptr::Ptr{braid_Real},f_tstop_ptr::Ptr{braid_Real},c_tprior_ptr::Ptr{braid_Real},c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTpriorTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,f_tprior_ptr,f_tstop_ptr,c_tprior_ptr,c_tstop_ptr)
end

function _braid_PhiStatusInit(tstart::braid_Real,tstop::braid_Real,accuracy::braid_Real,status::braid_PhiStatus)
    ccall((:_braid_PhiStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_PhiStatus),tstart,tstop,accuracy,status)
end

function _braid_PhiStatusDestroy(status::braid_PhiStatus)
    ccall((:_braid_PhiStatusDestroy,libxbraid),braid_Int,(braid_PhiStatus,),status)
end

function braid_PhiStatusGetTstart(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstart,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_PhiStatusGetTstop(status::braid_PhiStatus,tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstop_ptr)
end

function braid_PhiStatusGetAccuracy(status::braid_PhiStatus,accuracy_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetAccuracy,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,accuracy_ptr)
end

function braid_PhiStatusSetRFactor(status::braid_PhiStatus,rfactor::braid_Real)
    ccall((:braid_PhiStatusSetRFactor,libxbraid),braid_Int,(braid_PhiStatus,braid_Real),status,rfactor)
end

function braid_PhiStatusGetTstartTstop(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real},tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstartTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,tstop_ptr)
end
# Julia wrapper for header: /home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include/braid_test.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function _braid_AccessStatusInit(t::braid_Real,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int,wrapper_test::braid_Int,status::braid_AccessStatus)
    ccall((:_braid_AccessStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Int,braid_Int,braid_Int,braid_Int,braid_AccessStatus),t,rnorm,iter,level,done,wrapper_test,status)
end

function _braid_AccessStatusDestroy(status::braid_AccessStatus)
    ccall((:_braid_AccessStatusDestroy,libxbraid),braid_Int,(braid_AccessStatus,),status)
end

function braid_AccessStatusGetT(status::braid_AccessStatus,t_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetT,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,t_ptr)
end

function braid_AccessStatusGetResidual(status::braid_AccessStatus,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetResidual,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,rnorm_ptr)
end

function braid_AccessStatusGetIter(status::braid_AccessStatus,iter_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetIter,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,iter_ptr)
end

function braid_AccessStatusGetLevel(status::braid_AccessStatus,level_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetLevel,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,level_ptr)
end

function braid_AccessStatusGetDone(status::braid_AccessStatus,done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetDone,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,done_ptr)
end

function braid_AccessStatusGetWrapperTest(status::braid_AccessStatus,wtest_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetWrapperTest,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,wtest_ptr)
end

function braid_AccessStatusGetTILD(status::braid_AccessStatus,t_ptr::Ptr{braid_Real},iter_ptr::Ptr{braid_Int},level_ptr::Ptr{braid_Int},done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetTILD,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real},Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),status,t_ptr,iter_ptr,level_ptr,done_ptr)
end

function _braid_CoarsenRefStatusInit(tstart::braid_Real,f_tprior::braid_Real,f_tstop::braid_Real,c_tprior::braid_Real,c_tstop::braid_Real,status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_Real,braid_Real,braid_CoarsenRefStatus),tstart,f_tprior,f_tstop,c_tprior,c_tstop,status)
end

function _braid_CoarsenRefStatusDestroy(status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusDestroy,libxbraid),braid_Int,(braid_CoarsenRefStatus,),status)
end

function braid_CoarsenRefStatusGetTstart(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTstart,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_CoarsenRefStatusGetFTstop(status::braid_CoarsenRefStatus,f_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tstop_ptr)
end

function braid_CoarsenRefStatusGetFTprior(status::braid_CoarsenRefStatus,f_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tprior_ptr)
end

function braid_CoarsenRefStatusGetCTstop(status::braid_CoarsenRefStatus,c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tstop_ptr)
end

function braid_CoarsenRefStatusGetCTprior(status::braid_CoarsenRefStatus,c_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tprior_ptr)
end

function braid_CoarsenRefStatusGetTpriorTstop(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real},f_tprior_ptr::Ptr{braid_Real},f_tstop_ptr::Ptr{braid_Real},c_tprior_ptr::Ptr{braid_Real},c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTpriorTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,f_tprior_ptr,f_tstop_ptr,c_tprior_ptr,c_tstop_ptr)
end

function _braid_PhiStatusInit(tstart::braid_Real,tstop::braid_Real,accuracy::braid_Real,status::braid_PhiStatus)
    ccall((:_braid_PhiStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_PhiStatus),tstart,tstop,accuracy,status)
end

function _braid_PhiStatusDestroy(status::braid_PhiStatus)
    ccall((:_braid_PhiStatusDestroy,libxbraid),braid_Int,(braid_PhiStatus,),status)
end

function braid_PhiStatusGetTstart(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstart,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_PhiStatusGetTstop(status::braid_PhiStatus,tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstop_ptr)
end

function braid_PhiStatusGetAccuracy(status::braid_PhiStatus,accuracy_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetAccuracy,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,accuracy_ptr)
end

function braid_PhiStatusSetRFactor(status::braid_PhiStatus,rfactor::braid_Real)
    ccall((:braid_PhiStatusSetRFactor,libxbraid),braid_Int,(braid_PhiStatus,braid_Real),status,rfactor)
end

function braid_PhiStatusGetTstartTstop(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real},tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstartTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,tstop_ptr)
end

function braid_Init(comm_world::MPI_Comm,comm::MPI_Comm,tstart::braid_Real,tstop::braid_Real,ntime::braid_Int,app::braid_App,phi::braid_PtFcnPhi,init::braid_PtFcnInit,clone::braid_PtFcnClone,free::braid_PtFcnFree,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,access::braid_PtFcnAccess,bufsize::braid_PtFcnBufSize,bufpack::braid_PtFcnBufPack,bufunpack::braid_PtFcnBufUnpack,core_ptr::Ptr{braid_Core})
    ccall((:braid_Init,libxbraid),braid_Int,(MPI_Comm,MPI_Comm,braid_Real,braid_Real,braid_Int,braid_App,braid_PtFcnPhi,braid_PtFcnInit,braid_PtFcnClone,braid_PtFcnFree,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnAccess,braid_PtFcnBufSize,braid_PtFcnBufPack,braid_PtFcnBufUnpack,Ptr{braid_Core}),comm_world,comm,tstart,tstop,ntime,app,phi,init,clone,free,sum,spatialnorm,access,bufsize,bufpack,bufunpack,core_ptr)
end

function braid_Drive(core::braid_Core)
    ccall((:braid_Drive,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_Destroy(core::braid_Core)
    ccall((:braid_Destroy,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_PrintStats(core::braid_Core)
    ccall((:braid_PrintStats,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetLoosexTol(core::braid_Core,level::braid_Int,loose_tol::braid_Real)
    ccall((:braid_SetLoosexTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,loose_tol)
end

function braid_SetTightxTol(core::braid_Core,level::braid_Int,tight_tol::braid_Real)
    ccall((:braid_SetTightxTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,tight_tol)
end

function braid_SetMaxLevels(core::braid_Core,max_levels::braid_Int)
    ccall((:braid_SetMaxLevels,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_levels)
end

function braid_SetMinCoarse(core::braid_Core,min_coarse::braid_Int)
    ccall((:braid_SetMinCoarse,libxbraid),braid_Int,(braid_Core,braid_Int),core,min_coarse)
end

function braid_SetAbsTol(core::braid_Core,atol::braid_Real)
    ccall((:braid_SetAbsTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,atol)
end

function braid_SetRelTol(core::braid_Core,rtol::braid_Real)
    ccall((:braid_SetRelTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,rtol)
end

function braid_SetNRelax(core::braid_Core,level::braid_Int,nrelax::braid_Int)
    ccall((:braid_SetNRelax,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,nrelax)
end

function braid_SetCFactor(core::braid_Core,level::braid_Int,cfactor::braid_Int)
    ccall((:braid_SetCFactor,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,cfactor)
end

function braid_SetMaxIter(core::braid_Core,max_iter::braid_Int)
    ccall((:braid_SetMaxIter,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_iter)
end

function braid_SetFMG(core::braid_Core)
    ccall((:braid_SetFMG,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetTemporalNorm(core::braid_Core,tnorm::braid_Int)
    ccall((:braid_SetTemporalNorm,libxbraid),braid_Int,(braid_Core,braid_Int),core,tnorm)
end

function braid_SetNFMGVcyc(core::braid_Core,nfmg_Vcyc::braid_Int)
    ccall((:braid_SetNFMGVcyc,libxbraid),braid_Int,(braid_Core,braid_Int),core,nfmg_Vcyc)
end

function braid_SetSpatialCoarsen(core::braid_Core,coarsen::braid_PtFcnCoarsen)
    ccall((:braid_SetSpatialCoarsen,libxbraid),braid_Int,(braid_Core,braid_PtFcnCoarsen),core,coarsen)
end

function braid_SetSpatialRefine(core::braid_Core,refine::braid_PtFcnRefine)
    ccall((:braid_SetSpatialRefine,libxbraid),braid_Int,(braid_Core,braid_PtFcnRefine),core,refine)
end

function braid_SetPrintLevel(core::braid_Core,print_level::braid_Int)
    ccall((:braid_SetPrintLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,print_level)
end

function braid_SetPrintFile(core::braid_Core,printfile_name::Ptr{Uint8})
    ccall((:braid_SetPrintFile,libxbraid),braid_Int,(braid_Core,Ptr{Uint8}),core,printfile_name)
end

function braid_SetAccessLevel(core::braid_Core,access_level::braid_Int)
    ccall((:braid_SetAccessLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,access_level)
end

function braid_SplitCommworld(comm_world::Ptr{MPI_Comm},px::braid_Int,comm_x::Ptr{MPI_Comm},comm_t::Ptr{MPI_Comm})
    ccall((:braid_SplitCommworld,libxbraid),braid_Int,(Ptr{MPI_Comm},braid_Int,Ptr{MPI_Comm},Ptr{MPI_Comm}),comm_world,px,comm_x,comm_t)
end

function braid_GetNumIter(core::braid_Core,niter_ptr::Ptr{braid_Int})
    ccall((:braid_GetNumIter,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,niter_ptr)
end

function braid_GetRNorm(core::braid_Core,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_GetRNorm,libxbraid),braid_Int,(braid_Core,Ptr{braid_Real}),core,rnorm_ptr)
end

function _braid_GetDistribution(core::braid_Core,ilower_ptr::Ptr{braid_Int},iupper_ptr::Ptr{braid_Int})
    ccall((:_braid_GetDistribution,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int},Ptr{braid_Int}),core,ilower_ptr,iupper_ptr)
end

function _braid_GetProc(core::braid_Core,level::braid_Int,index::braid_Int,proc_ptr::Ptr{braid_Int})
    ccall((:_braid_GetProc,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Int}),core,level,index,proc_ptr)
end

function _braid_CommRecvInit(core::braid_Core,level::braid_Int,index::braid_Int,vector_ptr::Ptr{braid_Vector},handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommRecvInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector},Ptr{Ptr{_braid_CommHandle}}),core,level,index,vector_ptr,handle_ptr)
end

function _braid_CommSendInit(core::braid_Core,level::braid_Int,index::braid_Int,vector::braid_Vector,handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommSendInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector,Ptr{Ptr{_braid_CommHandle}}),core,level,index,vector,handle_ptr)
end

function _braid_CommWait(core::braid_Core,handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommWait,libxbraid),braid_Int,(braid_Core,Ptr{Ptr{_braid_CommHandle}}),core,handle_ptr)
end

function _braid_UCommInit(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommInit,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UCommInitF(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommInitF,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UCommWait(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommWait,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UGetInterval(core::braid_Core,level::braid_Int,interval_index::braid_Int,flo_ptr::Ptr{braid_Int},fhi_ptr::Ptr{braid_Int},ci_ptr::Ptr{braid_Int})
    ccall((:_braid_UGetInterval,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),core,level,interval_index,flo_ptr,fhi_ptr,ci_ptr)
end

function _braid_UGetVectorRef(core::braid_Core,level::braid_Int,index::braid_Int,u_ptr::Ptr{braid_Vector})
    ccall((:_braid_UGetVectorRef,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector}),core,level,index,u_ptr)
end

function _braid_USetVectorRef(core::braid_Core,level::braid_Int,index::braid_Int,u::braid_Vector)
    ccall((:_braid_USetVectorRef,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector),core,level,index,u)
end

function _braid_UGetVector(core::braid_Core,level::braid_Int,index::braid_Int,u_ptr::Ptr{braid_Vector})
    ccall((:_braid_UGetVector,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector}),core,level,index,u_ptr)
end

function _braid_USetVector(core::braid_Core,level::braid_Int,index::braid_Int,u::braid_Vector)
    ccall((:_braid_USetVector,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector),core,level,index,u)
end

function _braid_UAccessVector(core::braid_Core,status::braid_AccessStatus,u::braid_Vector)
    ccall((:_braid_UAccessVector,libxbraid),braid_Int,(braid_Core,braid_AccessStatus,braid_Vector),core,status,u)
end

function _braid_Phi(core::braid_Core,level::braid_Int,index::braid_Int,accuracy::braid_Real,u::braid_Vector,rfactor::Ptr{braid_Int})
    ccall((:_braid_Phi,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real,braid_Vector,Ptr{braid_Int}),core,level,index,accuracy,u,rfactor)
end

function _braid_Step(core::braid_Core,level::braid_Int,index::braid_Int,accuracy::braid_Real,u::braid_Vector)
    ccall((:_braid_Step,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real,braid_Vector),core,level,index,accuracy,u)
end

function _braid_Coarsen(core::braid_Core,level::braid_Int,f_index::braid_Int,c_index::braid_Int,fvector::braid_Vector,cvector::Ptr{braid_Vector})
    ccall((:_braid_Coarsen,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,braid_Vector,Ptr{braid_Vector}),core,level,f_index,c_index,fvector,cvector)
end

function _braid_Refine(core::braid_Core,level::braid_Int,f_index::braid_Int,c_index::braid_Int,cvector::braid_Vector,fvector::Ptr{braid_Vector})
    ccall((:_braid_Refine,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,braid_Vector,Ptr{braid_Vector}),core,level,f_index,c_index,cvector,fvector)
end

function _braid_GridInit(core::braid_Core,level::braid_Int,ilower::braid_Int,iupper::braid_Int,grid_ptr::Ptr{Ptr{_braid_Grid}})
    ccall((:_braid_GridInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,Ptr{Ptr{_braid_Grid}}),core,level,ilower,iupper,grid_ptr)
end

function _braid_GridDestroy(core::braid_Core,grid::Ptr{_braid_Grid})
    ccall((:_braid_GridDestroy,libxbraid),braid_Int,(braid_Core,Ptr{_braid_Grid}),core,grid)
end

function _braid_InitGuess(core::braid_Core,level::braid_Int)
    ccall((:_braid_InitGuess,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_FCRelax(core::braid_Core,level::braid_Int)
    ccall((:_braid_FCRelax,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_FRestrict(core::braid_Core,level::braid_Int,iter::braid_Int,rnorm_ptr::Ptr{braid_Real})
    ccall((:_braid_FRestrict,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Real}),core,level,iter,rnorm_ptr)
end

function _braid_FInterp(core::braid_Core,level::braid_Int,iter::braid_Int,rnorm::braid_Real)
    ccall((:_braid_FInterp,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real),core,level,iter,rnorm)
end

function _braid_FRefine(core::braid_Core,refined_ptr::Ptr{braid_Int})
    ccall((:_braid_FRefine,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,refined_ptr)
end

function _braid_FAccess(core::braid_Core,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int)
    ccall((:_braid_FAccess,libxbraid),braid_Int,(braid_Core,braid_Real,braid_Int,braid_Int,braid_Int),core,rnorm,iter,level,done)
end

function _braid_InitHierarchy(core::braid_Core,fine_grid::Ptr{_braid_Grid})
    ccall((:_braid_InitHierarchy,libxbraid),braid_Int,(braid_Core,Ptr{_braid_Grid}),core,fine_grid)
end

function braid_TestInitAccess(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,init::braid_PtFcnInit,access::braid_PtFcnAccess,free::braid_PtFcnFree)
    ccall((:braid_TestInitAccess,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_PtFcnInit,braid_PtFcnAccess,braid_PtFcnFree),app,comm_x,fp,t,init,access,free)
end

function braid_TestClone(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,init::braid_PtFcnInit,access::braid_PtFcnAccess,free::braid_PtFcnFree,clone::braid_PtFcnClone)
    ccall((:braid_TestClone,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_PtFcnInit,braid_PtFcnAccess,braid_PtFcnFree,braid_PtFcnClone),app,comm_x,fp,t,init,access,free,clone)
end

function braid_TestSum(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,init::braid_PtFcnInit,access::braid_PtFcnAccess,free::braid_PtFcnFree,clone::braid_PtFcnClone,sum::braid_PtFcnSum)
    ccall((:braid_TestSum,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_PtFcnInit,braid_PtFcnAccess,braid_PtFcnFree,braid_PtFcnClone,braid_PtFcnSum),app,comm_x,fp,t,init,access,free,clone,sum)
end

function braid_TestSpatialNorm(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,init::braid_PtFcnInit,free::braid_PtFcnFree,clone::braid_PtFcnClone,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm)
    ccall((:braid_TestSpatialNorm,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_PtFcnInit,braid_PtFcnFree,braid_PtFcnClone,braid_PtFcnSum,braid_PtFcnSpatialNorm),app,comm_x,fp,t,init,free,clone,sum,spatialnorm)
end

function braid_TestBuf(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,init::braid_PtFcnInit,free::braid_PtFcnFree,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,bufsize::braid_PtFcnBufSize,bufpack::braid_PtFcnBufPack,bufunpack::braid_PtFcnBufUnpack)
    ccall((:braid_TestBuf,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_PtFcnInit,braid_PtFcnFree,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnBufSize,braid_PtFcnBufPack,braid_PtFcnBufUnpack),app,comm_x,fp,t,init,free,sum,spatialnorm,bufsize,bufpack,bufunpack)
end

function braid_TestCoarsenRefine(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,fdt::braid_Real,cdt::braid_Real,init::braid_PtFcnInit,access::braid_PtFcnAccess,free::braid_PtFcnFree,clone::braid_PtFcnClone,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,coarsen::braid_PtFcnCoarsen,refine::braid_PtFcnRefine)
    ccall((:braid_TestCoarsenRefine,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_Real,braid_Real,braid_PtFcnInit,braid_PtFcnAccess,braid_PtFcnFree,braid_PtFcnClone,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnCoarsen,braid_PtFcnRefine),app,comm_x,fp,t,fdt,cdt,init,access,free,clone,sum,spatialnorm,coarsen,refine)
end

function braid_TestAll(app::braid_App,comm_x::MPI_Comm,fp::Ptr{FILE},t::braid_Real,fdt::braid_Real,cdt::braid_Real,init::braid_PtFcnInit,free::braid_PtFcnFree,clone::braid_PtFcnClone,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,bufsize::braid_PtFcnBufSize,bufpack::braid_PtFcnBufPack,bufunpack::braid_PtFcnBufUnpack,coarsen::braid_PtFcnCoarsen,refine::braid_PtFcnRefine)
    ccall((:braid_TestAll,libxbraid),braid_Int,(braid_App,MPI_Comm,Ptr{FILE},braid_Real,braid_Real,braid_Real,braid_PtFcnInit,braid_PtFcnFree,braid_PtFcnClone,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnBufSize,braid_PtFcnBufPack,braid_PtFcnBufUnpack,braid_PtFcnCoarsen,braid_PtFcnRefine),app,comm_x,fp,t,fdt,cdt,init,free,clone,sum,spatialnorm,bufsize,bufpack,bufunpack,coarsen,refine)
end
# Julia wrapper for header: /home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include/util.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function _braid_AccessStatusInit(t::braid_Real,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int,wrapper_test::braid_Int,status::braid_AccessStatus)
    ccall((:_braid_AccessStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Int,braid_Int,braid_Int,braid_Int,braid_AccessStatus),t,rnorm,iter,level,done,wrapper_test,status)
end

function _braid_AccessStatusDestroy(status::braid_AccessStatus)
    ccall((:_braid_AccessStatusDestroy,libxbraid),braid_Int,(braid_AccessStatus,),status)
end

function braid_AccessStatusGetT(status::braid_AccessStatus,t_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetT,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,t_ptr)
end

function braid_AccessStatusGetResidual(status::braid_AccessStatus,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_AccessStatusGetResidual,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real}),status,rnorm_ptr)
end

function braid_AccessStatusGetIter(status::braid_AccessStatus,iter_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetIter,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,iter_ptr)
end

function braid_AccessStatusGetLevel(status::braid_AccessStatus,level_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetLevel,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,level_ptr)
end

function braid_AccessStatusGetDone(status::braid_AccessStatus,done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetDone,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,done_ptr)
end

function braid_AccessStatusGetWrapperTest(status::braid_AccessStatus,wtest_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetWrapperTest,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Int}),status,wtest_ptr)
end

function braid_AccessStatusGetTILD(status::braid_AccessStatus,t_ptr::Ptr{braid_Real},iter_ptr::Ptr{braid_Int},level_ptr::Ptr{braid_Int},done_ptr::Ptr{braid_Int})
    ccall((:braid_AccessStatusGetTILD,libxbraid),braid_Int,(braid_AccessStatus,Ptr{braid_Real},Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),status,t_ptr,iter_ptr,level_ptr,done_ptr)
end

function _braid_CoarsenRefStatusInit(tstart::braid_Real,f_tprior::braid_Real,f_tstop::braid_Real,c_tprior::braid_Real,c_tstop::braid_Real,status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_Real,braid_Real,braid_CoarsenRefStatus),tstart,f_tprior,f_tstop,c_tprior,c_tstop,status)
end

function _braid_CoarsenRefStatusDestroy(status::braid_CoarsenRefStatus)
    ccall((:_braid_CoarsenRefStatusDestroy,libxbraid),braid_Int,(braid_CoarsenRefStatus,),status)
end

function braid_CoarsenRefStatusGetTstart(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTstart,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_CoarsenRefStatusGetFTstop(status::braid_CoarsenRefStatus,f_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tstop_ptr)
end

function braid_CoarsenRefStatusGetFTprior(status::braid_CoarsenRefStatus,f_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetFTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,f_tprior_ptr)
end

function braid_CoarsenRefStatusGetCTstop(status::braid_CoarsenRefStatus,c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tstop_ptr)
end

function braid_CoarsenRefStatusGetCTprior(status::braid_CoarsenRefStatus,c_tprior_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetCTprior,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real}),status,c_tprior_ptr)
end

function braid_CoarsenRefStatusGetTpriorTstop(status::braid_CoarsenRefStatus,tstart_ptr::Ptr{braid_Real},f_tprior_ptr::Ptr{braid_Real},f_tstop_ptr::Ptr{braid_Real},c_tprior_ptr::Ptr{braid_Real},c_tstop_ptr::Ptr{braid_Real})
    ccall((:braid_CoarsenRefStatusGetTpriorTstop,libxbraid),braid_Int,(braid_CoarsenRefStatus,Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,f_tprior_ptr,f_tstop_ptr,c_tprior_ptr,c_tstop_ptr)
end

function _braid_PhiStatusInit(tstart::braid_Real,tstop::braid_Real,accuracy::braid_Real,status::braid_PhiStatus)
    ccall((:_braid_PhiStatusInit,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_PhiStatus),tstart,tstop,accuracy,status)
end

function _braid_PhiStatusDestroy(status::braid_PhiStatus)
    ccall((:_braid_PhiStatusDestroy,libxbraid),braid_Int,(braid_PhiStatus,),status)
end

function braid_PhiStatusGetTstart(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstart,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstart_ptr)
end

function braid_PhiStatusGetTstop(status::braid_PhiStatus,tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,tstop_ptr)
end

function braid_PhiStatusGetAccuracy(status::braid_PhiStatus,accuracy_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetAccuracy,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real}),status,accuracy_ptr)
end

function braid_PhiStatusSetRFactor(status::braid_PhiStatus,rfactor::braid_Real)
    ccall((:braid_PhiStatusSetRFactor,libxbraid),braid_Int,(braid_PhiStatus,braid_Real),status,rfactor)
end

function braid_PhiStatusGetTstartTstop(status::braid_PhiStatus,tstart_ptr::Ptr{braid_Real},tstop_ptr::Ptr{braid_Real})
    ccall((:braid_PhiStatusGetTstartTstop,libxbraid),braid_Int,(braid_PhiStatus,Ptr{braid_Real},Ptr{braid_Real}),status,tstart_ptr,tstop_ptr)
end

function braid_Init(comm_world::MPI_Comm,comm::MPI_Comm,tstart::braid_Real,tstop::braid_Real,ntime::braid_Int,app::braid_App,phi::braid_PtFcnPhi,init::braid_PtFcnInit,clone::braid_PtFcnClone,free::braid_PtFcnFree,sum::braid_PtFcnSum,spatialnorm::braid_PtFcnSpatialNorm,access::braid_PtFcnAccess,bufsize::braid_PtFcnBufSize,bufpack::braid_PtFcnBufPack,bufunpack::braid_PtFcnBufUnpack,core_ptr::Ptr{braid_Core})
    ccall((:braid_Init,libxbraid),braid_Int,(MPI_Comm,MPI_Comm,braid_Real,braid_Real,braid_Int,braid_App,braid_PtFcnPhi,braid_PtFcnInit,braid_PtFcnClone,braid_PtFcnFree,braid_PtFcnSum,braid_PtFcnSpatialNorm,braid_PtFcnAccess,braid_PtFcnBufSize,braid_PtFcnBufPack,braid_PtFcnBufUnpack,Ptr{braid_Core}),comm_world,comm,tstart,tstop,ntime,app,phi,init,clone,free,sum,spatialnorm,access,bufsize,bufpack,bufunpack,core_ptr)
end

function braid_Drive(core::braid_Core)
    ccall((:braid_Drive,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_Destroy(core::braid_Core)
    ccall((:braid_Destroy,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_PrintStats(core::braid_Core)
    ccall((:braid_PrintStats,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetLoosexTol(core::braid_Core,level::braid_Int,loose_tol::braid_Real)
    ccall((:braid_SetLoosexTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,loose_tol)
end

function braid_SetTightxTol(core::braid_Core,level::braid_Int,tight_tol::braid_Real)
    ccall((:braid_SetTightxTol,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Real),core,level,tight_tol)
end

function braid_SetMaxLevels(core::braid_Core,max_levels::braid_Int)
    ccall((:braid_SetMaxLevels,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_levels)
end

function braid_SetMinCoarse(core::braid_Core,min_coarse::braid_Int)
    ccall((:braid_SetMinCoarse,libxbraid),braid_Int,(braid_Core,braid_Int),core,min_coarse)
end

function braid_SetAbsTol(core::braid_Core,atol::braid_Real)
    ccall((:braid_SetAbsTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,atol)
end

function braid_SetRelTol(core::braid_Core,rtol::braid_Real)
    ccall((:braid_SetRelTol,libxbraid),braid_Int,(braid_Core,braid_Real),core,rtol)
end

function braid_SetNRelax(core::braid_Core,level::braid_Int,nrelax::braid_Int)
    ccall((:braid_SetNRelax,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,nrelax)
end

function braid_SetCFactor(core::braid_Core,level::braid_Int,cfactor::braid_Int)
    ccall((:braid_SetCFactor,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int),core,level,cfactor)
end

function braid_SetMaxIter(core::braid_Core,max_iter::braid_Int)
    ccall((:braid_SetMaxIter,libxbraid),braid_Int,(braid_Core,braid_Int),core,max_iter)
end

function braid_SetFMG(core::braid_Core)
    ccall((:braid_SetFMG,libxbraid),braid_Int,(braid_Core,),core)
end

function braid_SetTemporalNorm(core::braid_Core,tnorm::braid_Int)
    ccall((:braid_SetTemporalNorm,libxbraid),braid_Int,(braid_Core,braid_Int),core,tnorm)
end

function braid_SetNFMGVcyc(core::braid_Core,nfmg_Vcyc::braid_Int)
    ccall((:braid_SetNFMGVcyc,libxbraid),braid_Int,(braid_Core,braid_Int),core,nfmg_Vcyc)
end

function braid_SetSpatialCoarsen(core::braid_Core,coarsen::braid_PtFcnCoarsen)
    ccall((:braid_SetSpatialCoarsen,libxbraid),braid_Int,(braid_Core,braid_PtFcnCoarsen),core,coarsen)
end

function braid_SetSpatialRefine(core::braid_Core,refine::braid_PtFcnRefine)
    ccall((:braid_SetSpatialRefine,libxbraid),braid_Int,(braid_Core,braid_PtFcnRefine),core,refine)
end

function braid_SetPrintLevel(core::braid_Core,print_level::braid_Int)
    ccall((:braid_SetPrintLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,print_level)
end

function braid_SetPrintFile(core::braid_Core,printfile_name::Ptr{Uint8})
    ccall((:braid_SetPrintFile,libxbraid),braid_Int,(braid_Core,Ptr{Uint8}),core,printfile_name)
end

function braid_SetAccessLevel(core::braid_Core,access_level::braid_Int)
    ccall((:braid_SetAccessLevel,libxbraid),braid_Int,(braid_Core,braid_Int),core,access_level)
end

function braid_SplitCommworld(comm_world::Ptr{MPI_Comm},px::braid_Int,comm_x::Ptr{MPI_Comm},comm_t::Ptr{MPI_Comm})
    ccall((:braid_SplitCommworld,libxbraid),braid_Int,(Ptr{MPI_Comm},braid_Int,Ptr{MPI_Comm},Ptr{MPI_Comm}),comm_world,px,comm_x,comm_t)
end

function braid_GetNumIter(core::braid_Core,niter_ptr::Ptr{braid_Int})
    ccall((:braid_GetNumIter,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,niter_ptr)
end

function braid_GetRNorm(core::braid_Core,rnorm_ptr::Ptr{braid_Real})
    ccall((:braid_GetRNorm,libxbraid),braid_Int,(braid_Core,Ptr{braid_Real}),core,rnorm_ptr)
end

function _braid_GetDistribution(core::braid_Core,ilower_ptr::Ptr{braid_Int},iupper_ptr::Ptr{braid_Int})
    ccall((:_braid_GetDistribution,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int},Ptr{braid_Int}),core,ilower_ptr,iupper_ptr)
end

function _braid_GetProc(core::braid_Core,level::braid_Int,index::braid_Int,proc_ptr::Ptr{braid_Int})
    ccall((:_braid_GetProc,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Int}),core,level,index,proc_ptr)
end

function _braid_CommRecvInit(core::braid_Core,level::braid_Int,index::braid_Int,vector_ptr::Ptr{braid_Vector},handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommRecvInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector},Ptr{Ptr{_braid_CommHandle}}),core,level,index,vector_ptr,handle_ptr)
end

function _braid_CommSendInit(core::braid_Core,level::braid_Int,index::braid_Int,vector::braid_Vector,handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommSendInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector,Ptr{Ptr{_braid_CommHandle}}),core,level,index,vector,handle_ptr)
end

function _braid_CommWait(core::braid_Core,handle_ptr::Ptr{Ptr{_braid_CommHandle}})
    ccall((:_braid_CommWait,libxbraid),braid_Int,(braid_Core,Ptr{Ptr{_braid_CommHandle}}),core,handle_ptr)
end

function _braid_UCommInit(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommInit,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UCommInitF(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommInitF,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UCommWait(core::braid_Core,level::braid_Int)
    ccall((:_braid_UCommWait,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_UGetInterval(core::braid_Core,level::braid_Int,interval_index::braid_Int,flo_ptr::Ptr{braid_Int},fhi_ptr::Ptr{braid_Int},ci_ptr::Ptr{braid_Int})
    ccall((:_braid_UGetInterval,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Int},Ptr{braid_Int},Ptr{braid_Int}),core,level,interval_index,flo_ptr,fhi_ptr,ci_ptr)
end

function _braid_UGetVectorRef(core::braid_Core,level::braid_Int,index::braid_Int,u_ptr::Ptr{braid_Vector})
    ccall((:_braid_UGetVectorRef,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector}),core,level,index,u_ptr)
end

function _braid_USetVectorRef(core::braid_Core,level::braid_Int,index::braid_Int,u::braid_Vector)
    ccall((:_braid_USetVectorRef,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector),core,level,index,u)
end

function _braid_UGetVector(core::braid_Core,level::braid_Int,index::braid_Int,u_ptr::Ptr{braid_Vector})
    ccall((:_braid_UGetVector,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Vector}),core,level,index,u_ptr)
end

function _braid_USetVector(core::braid_Core,level::braid_Int,index::braid_Int,u::braid_Vector)
    ccall((:_braid_USetVector,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Vector),core,level,index,u)
end

function _braid_UAccessVector(core::braid_Core,status::braid_AccessStatus,u::braid_Vector)
    ccall((:_braid_UAccessVector,libxbraid),braid_Int,(braid_Core,braid_AccessStatus,braid_Vector),core,status,u)
end

function _braid_Phi(core::braid_Core,level::braid_Int,index::braid_Int,accuracy::braid_Real,u::braid_Vector,rfactor::Ptr{braid_Int})
    ccall((:_braid_Phi,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real,braid_Vector,Ptr{braid_Int}),core,level,index,accuracy,u,rfactor)
end

function _braid_Step(core::braid_Core,level::braid_Int,index::braid_Int,accuracy::braid_Real,u::braid_Vector)
    ccall((:_braid_Step,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real,braid_Vector),core,level,index,accuracy,u)
end

function _braid_Coarsen(core::braid_Core,level::braid_Int,f_index::braid_Int,c_index::braid_Int,fvector::braid_Vector,cvector::Ptr{braid_Vector})
    ccall((:_braid_Coarsen,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,braid_Vector,Ptr{braid_Vector}),core,level,f_index,c_index,fvector,cvector)
end

function _braid_Refine(core::braid_Core,level::braid_Int,f_index::braid_Int,c_index::braid_Int,cvector::braid_Vector,fvector::Ptr{braid_Vector})
    ccall((:_braid_Refine,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,braid_Vector,Ptr{braid_Vector}),core,level,f_index,c_index,cvector,fvector)
end

function _braid_GridInit(core::braid_Core,level::braid_Int,ilower::braid_Int,iupper::braid_Int,grid_ptr::Ptr{Ptr{_braid_Grid}})
    ccall((:_braid_GridInit,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Int,Ptr{Ptr{_braid_Grid}}),core,level,ilower,iupper,grid_ptr)
end

function _braid_GridDestroy(core::braid_Core,grid::Ptr{_braid_Grid})
    ccall((:_braid_GridDestroy,libxbraid),braid_Int,(braid_Core,Ptr{_braid_Grid}),core,grid)
end

function _braid_InitGuess(core::braid_Core,level::braid_Int)
    ccall((:_braid_InitGuess,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_FCRelax(core::braid_Core,level::braid_Int)
    ccall((:_braid_FCRelax,libxbraid),braid_Int,(braid_Core,braid_Int),core,level)
end

function _braid_FRestrict(core::braid_Core,level::braid_Int,iter::braid_Int,rnorm_ptr::Ptr{braid_Real})
    ccall((:_braid_FRestrict,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,Ptr{braid_Real}),core,level,iter,rnorm_ptr)
end

function _braid_FInterp(core::braid_Core,level::braid_Int,iter::braid_Int,rnorm::braid_Real)
    ccall((:_braid_FInterp,libxbraid),braid_Int,(braid_Core,braid_Int,braid_Int,braid_Real),core,level,iter,rnorm)
end

function _braid_FRefine(core::braid_Core,refined_ptr::Ptr{braid_Int})
    ccall((:_braid_FRefine,libxbraid),braid_Int,(braid_Core,Ptr{braid_Int}),core,refined_ptr)
end

function _braid_FAccess(core::braid_Core,rnorm::braid_Real,iter::braid_Int,level::braid_Int,done::braid_Int)
    ccall((:_braid_FAccess,libxbraid),braid_Int,(braid_Core,braid_Real,braid_Int,braid_Int,braid_Int),core,rnorm,iter,level,done)
end

function _braid_InitHierarchy(core::braid_Core,fine_grid::Ptr{_braid_Grid})
    ccall((:_braid_InitHierarchy,libxbraid),braid_Int,(braid_Core,Ptr{_braid_Grid}),core,fine_grid)
end

function _braid_ProjectInterval(ilower::braid_Int,iupper::braid_Int,index::braid_Int,stride::braid_Int,pilower::Ptr{braid_Int},piupper::Ptr{braid_Int})
    ccall((:_braid_ProjectInterval,libxbraid),braid_Int,(braid_Int,braid_Int,braid_Int,braid_Int,Ptr{braid_Int},Ptr{braid_Int}),ilower,iupper,index,stride,pilower,piupper)
end

function _braid_SetAccuracy(rnorm::braid_Real,loose_tol::braid_Real,tight_tol::braid_Real,oldAccuracy::braid_Real,tol::braid_Real,paccuracy::Ptr{braid_Real})
    ccall((:_braid_SetAccuracy,libxbraid),braid_Int,(braid_Real,braid_Real,braid_Real,braid_Real,braid_Real,Ptr{braid_Real}),rnorm,loose_tol,tight_tol,oldAccuracy,tol,paccuracy)
end

function _braid_Max(array::Ptr{braid_Real},size::braid_Int,max_val::Ptr{braid_Real})
    ccall((:_braid_Max,libxbraid),braid_Int,(Ptr{braid_Real},braid_Int,Ptr{braid_Real}),array,size,max_val)
end
