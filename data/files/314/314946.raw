# Julia wrapper for header: /opt/local/include/gdal_priv.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function GDALGetDataTypeSize(arg1::GDALDataType)
    ccall((:GDALGetDataTypeSize,libgdal),Cint,(GDALDataType,),arg1)
end

function GDALDataTypeIsComplex(arg1::GDALDataType)
    ccall((:GDALDataTypeIsComplex,libgdal),Cint,(GDALDataType,),arg1)
end

function GDALGetDataTypeName(arg1::GDALDataType)
    ccall((:GDALGetDataTypeName,libgdal),Ptr{Uint8},(GDALDataType,),arg1)
end

function GDALGetDataTypeByName(arg1::Ptr{Uint8})
    ccall((:GDALGetDataTypeByName,libgdal),GDALDataType,(Ptr{Uint8},),arg1)
end

function GDALDataTypeUnion(arg1::GDALDataType,arg2::GDALDataType)
    ccall((:GDALDataTypeUnion,libgdal),GDALDataType,(GDALDataType,GDALDataType),arg1,arg2)
end

function GDALGetAsyncStatusTypeName(arg1::GDALAsyncStatusType)
    ccall((:GDALGetAsyncStatusTypeName,libgdal),Ptr{Uint8},(GDALAsyncStatusType,),arg1)
end

function GDALGetAsyncStatusTypeByName(arg1::Ptr{Uint8})
    ccall((:GDALGetAsyncStatusTypeByName,libgdal),GDALAsyncStatusType,(Ptr{Uint8},),arg1)
end

function GDALGetColorInterpretationName(arg1::GDALColorInterp)
    ccall((:GDALGetColorInterpretationName,libgdal),Ptr{Uint8},(GDALColorInterp,),arg1)
end

function GDALGetColorInterpretationByName(pszName::Ptr{Uint8})
    ccall((:GDALGetColorInterpretationByName,libgdal),GDALColorInterp,(Ptr{Uint8},),pszName)
end

function GDALGetPaletteInterpretationName(arg1::GDALPaletteInterp)
    ccall((:GDALGetPaletteInterpretationName,libgdal),Ptr{Uint8},(GDALPaletteInterp,),arg1)
end

function GDALAllRegister()
    ccall((:GDALAllRegister,libgdal),Void,())
end

function GDALCreate(hDriver::GDALDriverH,arg1::Ptr{Uint8},arg2::Cint,arg3::Cint,arg4::Cint,arg5::GDALDataType,arg6::Ptr{Ptr{Uint8}})
    ccall((:GDALCreate,libgdal),GDALDatasetH,(GDALDriverH,Ptr{Uint8},Cint,Cint,Cint,GDALDataType,Ptr{Ptr{Uint8}}),hDriver,arg1,arg2,arg3,arg4,arg5,arg6)
end

function GDALCreateCopy(arg1::GDALDriverH,arg2::Ptr{Uint8},arg3::GDALDatasetH,arg4::Cint,arg5::Ptr{Ptr{Uint8}},arg6::GDALProgressFunc,arg7::Ptr{Void})
    ccall((:GDALCreateCopy,libgdal),GDALDatasetH,(GDALDriverH,Ptr{Uint8},GDALDatasetH,Cint,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6,arg7)
end

function GDALIdentifyDriver(pszFilename::Ptr{Uint8},papszFileList::Ptr{Ptr{Uint8}})
    ccall((:GDALIdentifyDriver,libgdal),GDALDriverH,(Ptr{Uint8},Ptr{Ptr{Uint8}}),pszFilename,papszFileList)
end

function GDALOpen(pszFilename::Ptr{Uint8},eAccess::GDALAccess)
    ccall((:GDALOpen,libgdal),GDALDatasetH,(Ptr{Uint8},GDALAccess),pszFilename,eAccess)
end

function GDALOpenShared(arg1::Ptr{Uint8},arg2::GDALAccess)
    ccall((:GDALOpenShared,libgdal),GDALDatasetH,(Ptr{Uint8},GDALAccess),arg1,arg2)
end

function GDALDumpOpenDatasets(arg1::Ptr{FILE})
    ccall((:GDALDumpOpenDatasets,libgdal),Cint,(Ptr{FILE},),arg1)
end

function GDALGetDriverByName(arg1::Ptr{Uint8})
    ccall((:GDALGetDriverByName,libgdal),GDALDriverH,(Ptr{Uint8},),arg1)
end

function GDALGetDriverCount()
    ccall((:GDALGetDriverCount,libgdal),Cint,())
end

function GDALGetDriver(arg1::Cint)
    ccall((:GDALGetDriver,libgdal),GDALDriverH,(Cint,),arg1)
end

function GDALDestroyDriver(arg1::GDALDriverH)
    ccall((:GDALDestroyDriver,libgdal),Void,(GDALDriverH,),arg1)
end

function GDALRegisterDriver(arg1::GDALDriverH)
    ccall((:GDALRegisterDriver,libgdal),Cint,(GDALDriverH,),arg1)
end

function GDALDeregisterDriver(arg1::GDALDriverH)
    ccall((:GDALDeregisterDriver,libgdal),Void,(GDALDriverH,),arg1)
end

function GDALDestroyDriverManager()
    ccall((:GDALDestroyDriverManager,libgdal),Void,())
end

function GDALDeleteDataset(arg1::GDALDriverH,arg2::Ptr{Uint8})
    ccall((:GDALDeleteDataset,libgdal),CPLErr,(GDALDriverH,Ptr{Uint8}),arg1,arg2)
end

function GDALRenameDataset(arg1::GDALDriverH,pszNewName::Ptr{Uint8},pszOldName::Ptr{Uint8})
    ccall((:GDALRenameDataset,libgdal),CPLErr,(GDALDriverH,Ptr{Uint8},Ptr{Uint8}),arg1,pszNewName,pszOldName)
end

function GDALCopyDatasetFiles(arg1::GDALDriverH,pszNewName::Ptr{Uint8},pszOldName::Ptr{Uint8})
    ccall((:GDALCopyDatasetFiles,libgdal),CPLErr,(GDALDriverH,Ptr{Uint8},Ptr{Uint8}),arg1,pszNewName,pszOldName)
end

function GDALValidateCreationOptions(arg1::GDALDriverH,papszCreationOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALValidateCreationOptions,libgdal),Cint,(GDALDriverH,Ptr{Ptr{Uint8}}),arg1,papszCreationOptions)
end

function GDALGetDriverShortName(arg1::GDALDriverH)
    ccall((:GDALGetDriverShortName,libgdal),Ptr{Uint8},(GDALDriverH,),arg1)
end

function GDALGetDriverLongName(arg1::GDALDriverH)
    ccall((:GDALGetDriverLongName,libgdal),Ptr{Uint8},(GDALDriverH,),arg1)
end

function GDALGetDriverHelpTopic(arg1::GDALDriverH)
    ccall((:GDALGetDriverHelpTopic,libgdal),Ptr{Uint8},(GDALDriverH,),arg1)
end

function GDALGetDriverCreationOptionList(arg1::GDALDriverH)
    ccall((:GDALGetDriverCreationOptionList,libgdal),Ptr{Uint8},(GDALDriverH,),arg1)
end

function GDALInitGCPs(arg1::Cint,arg2::Ptr{GDAL_GCP})
    ccall((:GDALInitGCPs,libgdal),Void,(Cint,Ptr{GDAL_GCP}),arg1,arg2)
end

function GDALDeinitGCPs(arg1::Cint,arg2::Ptr{GDAL_GCP})
    ccall((:GDALDeinitGCPs,libgdal),Void,(Cint,Ptr{GDAL_GCP}),arg1,arg2)
end

function GDALDuplicateGCPs(arg1::Cint,arg2::Ptr{GDAL_GCP})
    ccall((:GDALDuplicateGCPs,libgdal),Ptr{GDAL_GCP},(Cint,Ptr{GDAL_GCP}),arg1,arg2)
end

function GDALGCPsToGeoTransform(nGCPCount::Cint,pasGCPs::Ptr{GDAL_GCP},padfGeoTransform::Ptr{Cdouble},bApproxOK::Cint)
    ccall((:GDALGCPsToGeoTransform,libgdal),Cint,(Cint,Ptr{GDAL_GCP},Ptr{Cdouble},Cint),nGCPCount,pasGCPs,padfGeoTransform,bApproxOK)
end

function GDALInvGeoTransform(padfGeoTransformIn::Ptr{Cdouble},padfInvGeoTransformOut::Ptr{Cdouble})
    ccall((:GDALInvGeoTransform,libgdal),Cint,(Ptr{Cdouble},Ptr{Cdouble}),padfGeoTransformIn,padfInvGeoTransformOut)
end

function GDALApplyGeoTransform(arg1::Ptr{Cdouble},arg2::Cdouble,arg3::Cdouble,arg4::Ptr{Cdouble},arg5::Ptr{Cdouble})
    ccall((:GDALApplyGeoTransform,libgdal),Void,(Ptr{Cdouble},Cdouble,Cdouble,Ptr{Cdouble},Ptr{Cdouble}),arg1,arg2,arg3,arg4,arg5)
end

function GDALComposeGeoTransforms(padfGeoTransform1::Ptr{Cdouble},padfGeoTransform2::Ptr{Cdouble},padfGeoTransformOut::Ptr{Cdouble})
    ccall((:GDALComposeGeoTransforms,libgdal),Void,(Ptr{Cdouble},Ptr{Cdouble},Ptr{Cdouble}),padfGeoTransform1,padfGeoTransform2,padfGeoTransformOut)
end

function GDALGetMetadataDomainList(hObject::GDALMajorObjectH)
    ccall((:GDALGetMetadataDomainList,libgdal),Ptr{Ptr{Uint8}},(GDALMajorObjectH,),hObject)
end

function GDALGetMetadata(arg1::GDALMajorObjectH,arg2::Ptr{Uint8})
    ccall((:GDALGetMetadata,libgdal),Ptr{Ptr{Uint8}},(GDALMajorObjectH,Ptr{Uint8}),arg1,arg2)
end

function GDALSetMetadata(arg1::GDALMajorObjectH,arg2::Ptr{Ptr{Uint8}},arg3::Ptr{Uint8})
    ccall((:GDALSetMetadata,libgdal),CPLErr,(GDALMajorObjectH,Ptr{Ptr{Uint8}},Ptr{Uint8}),arg1,arg2,arg3)
end

function GDALGetMetadataItem(arg1::GDALMajorObjectH,arg2::Ptr{Uint8},arg3::Ptr{Uint8})
    ccall((:GDALGetMetadataItem,libgdal),Ptr{Uint8},(GDALMajorObjectH,Ptr{Uint8},Ptr{Uint8}),arg1,arg2,arg3)
end

function GDALSetMetadataItem(arg1::GDALMajorObjectH,arg2::Ptr{Uint8},arg3::Ptr{Uint8},arg4::Ptr{Uint8})
    ccall((:GDALSetMetadataItem,libgdal),CPLErr,(GDALMajorObjectH,Ptr{Uint8},Ptr{Uint8},Ptr{Uint8}),arg1,arg2,arg3,arg4)
end

function GDALGetDescription(arg1::GDALMajorObjectH)
    ccall((:GDALGetDescription,libgdal),Ptr{Uint8},(GDALMajorObjectH,),arg1)
end

function GDALSetDescription(arg1::GDALMajorObjectH,arg2::Ptr{Uint8})
    ccall((:GDALSetDescription,libgdal),Void,(GDALMajorObjectH,Ptr{Uint8}),arg1,arg2)
end

function GDALGetDatasetDriver(arg1::GDALDatasetH)
    ccall((:GDALGetDatasetDriver,libgdal),GDALDriverH,(GDALDatasetH,),arg1)
end

function GDALGetFileList(arg1::GDALDatasetH)
    ccall((:GDALGetFileList,libgdal),Ptr{Ptr{Uint8}},(GDALDatasetH,),arg1)
end

function GDALClose(arg1::GDALDatasetH)
    ccall((:GDALClose,libgdal),Void,(GDALDatasetH,),arg1)
end

function GDALGetRasterXSize(arg1::GDALDatasetH)
    ccall((:GDALGetRasterXSize,libgdal),Cint,(GDALDatasetH,),arg1)
end

function GDALGetRasterYSize(arg1::GDALDatasetH)
    ccall((:GDALGetRasterYSize,libgdal),Cint,(GDALDatasetH,),arg1)
end

function GDALGetRasterCount(arg1::GDALDatasetH)
    ccall((:GDALGetRasterCount,libgdal),Cint,(GDALDatasetH,),arg1)
end

function GDALGetRasterBand(arg1::GDALDatasetH,arg2::Cint)
    ccall((:GDALGetRasterBand,libgdal),GDALRasterBandH,(GDALDatasetH,Cint),arg1,arg2)
end

function GDALAddBand(hDS::GDALDatasetH,eType::GDALDataType,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALAddBand,libgdal),CPLErr,(GDALDatasetH,GDALDataType,Ptr{Ptr{Uint8}}),hDS,eType,papszOptions)
end

function GDALBeginAsyncReader(hDS::GDALDatasetH,nXOff::Cint,nYOff::Cint,nXSize::Cint,nYSize::Cint,pBuf::Ptr{Void},nBufXSize::Cint,nBufYSize::Cint,eBufType::GDALDataType,nBandCount::Cint,panBandMap::Ptr{Cint},nPixelSpace::Cint,nLineSpace::Cint,nBandSpace::Cint,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALBeginAsyncReader,libgdal),GDALAsyncReaderH,(GDALDatasetH,Cint,Cint,Cint,Cint,Ptr{Void},Cint,Cint,GDALDataType,Cint,Ptr{Cint},Cint,Cint,Cint,Ptr{Ptr{Uint8}}),hDS,nXOff,nYOff,nXSize,nYSize,pBuf,nBufXSize,nBufYSize,eBufType,nBandCount,panBandMap,nPixelSpace,nLineSpace,nBandSpace,papszOptions)
end

function GDALEndAsyncReader(hDS::GDALDatasetH,hAsynchReaderH::GDALAsyncReaderH)
    ccall((:GDALEndAsyncReader,libgdal),Void,(GDALDatasetH,GDALAsyncReaderH),hDS,hAsynchReaderH)
end

function GDALDatasetRasterIO(hDS::GDALDatasetH,eRWFlag::GDALRWFlag,nDSXOff::Cint,nDSYOff::Cint,nDSXSize::Cint,nDSYSize::Cint,pBuffer::Ptr{Void},nBXSize::Cint,nBYSize::Cint,eBDataType::GDALDataType,nBandCount::Cint,panBandCount::Ptr{Cint},nPixelSpace::Cint,nLineSpace::Cint,nBandSpace::Cint)
    ccall((:GDALDatasetRasterIO,libgdal),CPLErr,(GDALDatasetH,GDALRWFlag,Cint,Cint,Cint,Cint,Ptr{Void},Cint,Cint,GDALDataType,Cint,Ptr{Cint},Cint,Cint,Cint),hDS,eRWFlag,nDSXOff,nDSYOff,nDSXSize,nDSYSize,pBuffer,nBXSize,nBYSize,eBDataType,nBandCount,panBandCount,nPixelSpace,nLineSpace,nBandSpace)
end

function GDALDatasetAdviseRead(hDS::GDALDatasetH,nDSXOff::Cint,nDSYOff::Cint,nDSXSize::Cint,nDSYSize::Cint,nBXSize::Cint,nBYSize::Cint,eBDataType::GDALDataType,nBandCount::Cint,panBandCount::Ptr{Cint},papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALDatasetAdviseRead,libgdal),CPLErr,(GDALDatasetH,Cint,Cint,Cint,Cint,Cint,Cint,GDALDataType,Cint,Ptr{Cint},Ptr{Ptr{Uint8}}),hDS,nDSXOff,nDSYOff,nDSXSize,nDSYSize,nBXSize,nBYSize,eBDataType,nBandCount,panBandCount,papszOptions)
end

function GDALGetProjectionRef(arg1::GDALDatasetH)
    ccall((:GDALGetProjectionRef,libgdal),Ptr{Uint8},(GDALDatasetH,),arg1)
end

function GDALSetProjection(arg1::GDALDatasetH,arg2::Ptr{Uint8})
    ccall((:GDALSetProjection,libgdal),CPLErr,(GDALDatasetH,Ptr{Uint8}),arg1,arg2)
end

function GDALGetGeoTransform(arg1::GDALDatasetH,arg2::Ptr{Cdouble})
    ccall((:GDALGetGeoTransform,libgdal),CPLErr,(GDALDatasetH,Ptr{Cdouble}),arg1,arg2)
end

function GDALSetGeoTransform(arg1::GDALDatasetH,arg2::Ptr{Cdouble})
    ccall((:GDALSetGeoTransform,libgdal),CPLErr,(GDALDatasetH,Ptr{Cdouble}),arg1,arg2)
end

function GDALGetGCPCount(arg1::GDALDatasetH)
    ccall((:GDALGetGCPCount,libgdal),Cint,(GDALDatasetH,),arg1)
end

function GDALGetGCPProjection(arg1::GDALDatasetH)
    ccall((:GDALGetGCPProjection,libgdal),Ptr{Uint8},(GDALDatasetH,),arg1)
end

function GDALGetGCPs(arg1::GDALDatasetH)
    ccall((:GDALGetGCPs,libgdal),Ptr{GDAL_GCP},(GDALDatasetH,),arg1)
end

function GDALSetGCPs(arg1::GDALDatasetH,arg2::Cint,arg3::Ptr{GDAL_GCP},arg4::Ptr{Uint8})
    ccall((:GDALSetGCPs,libgdal),CPLErr,(GDALDatasetH,Cint,Ptr{GDAL_GCP},Ptr{Uint8}),arg1,arg2,arg3,arg4)
end

function GDALGetInternalHandle(arg1::GDALDatasetH,arg2::Ptr{Uint8})
    ccall((:GDALGetInternalHandle,libgdal),Ptr{Void},(GDALDatasetH,Ptr{Uint8}),arg1,arg2)
end

function GDALReferenceDataset(arg1::GDALDatasetH)
    ccall((:GDALReferenceDataset,libgdal),Cint,(GDALDatasetH,),arg1)
end

function GDALDereferenceDataset(arg1::GDALDatasetH)
    ccall((:GDALDereferenceDataset,libgdal),Cint,(GDALDatasetH,),arg1)
end

function GDALBuildOverviews(arg1::GDALDatasetH,arg2::Ptr{Uint8},arg3::Cint,arg4::Ptr{Cint},arg5::Cint,arg6::Ptr{Cint},arg7::GDALProgressFunc,arg8::Ptr{Void})
    ccall((:GDALBuildOverviews,libgdal),CPLErr,(GDALDatasetH,Ptr{Uint8},Cint,Ptr{Cint},Cint,Ptr{Cint},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
end

function GDALGetOpenDatasets(hDS::Ptr{Ptr{GDALDatasetH}},pnCount::Ptr{Cint})
    ccall((:GDALGetOpenDatasets,libgdal),Void,(Ptr{Ptr{GDALDatasetH}},Ptr{Cint}),hDS,pnCount)
end

function GDALGetAccess(hDS::GDALDatasetH)
    ccall((:GDALGetAccess,libgdal),Cint,(GDALDatasetH,),hDS)
end

function GDALFlushCache(hDS::GDALDatasetH)
    ccall((:GDALFlushCache,libgdal),Void,(GDALDatasetH,),hDS)
end

function GDALCreateDatasetMaskBand(hDS::GDALDatasetH,nFlags::Cint)
    ccall((:GDALCreateDatasetMaskBand,libgdal),CPLErr,(GDALDatasetH,Cint),hDS,nFlags)
end

function GDALDatasetCopyWholeRaster(hSrcDS::GDALDatasetH,hDstDS::GDALDatasetH,papszOptions::Ptr{Ptr{Uint8}},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALDatasetCopyWholeRaster,libgdal),CPLErr,(GDALDatasetH,GDALDatasetH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),hSrcDS,hDstDS,papszOptions,pfnProgress,pProgressData)
end

function GDALRasterBandCopyWholeRaster(hSrcBand::GDALRasterBandH,hDstBand::GDALRasterBandH,papszOptions::Ptr{Ptr{Uint8}},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALRasterBandCopyWholeRaster,libgdal),CPLErr,(GDALRasterBandH,GDALRasterBandH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),hSrcBand,hDstBand,papszOptions,pfnProgress,pProgressData)
end

function GDALRegenerateOverviews(hSrcBand::GDALRasterBandH,nOverviewCount::Cint,pahOverviewBands::Ptr{GDALRasterBandH},pszResampling::Ptr{Uint8},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALRegenerateOverviews,libgdal),CPLErr,(GDALRasterBandH,Cint,Ptr{GDALRasterBandH},Ptr{Uint8},GDALProgressFunc,Ptr{Void}),hSrcBand,nOverviewCount,pahOverviewBands,pszResampling,pfnProgress,pProgressData)
end

function GDALGetRasterDataType(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterDataType,libgdal),GDALDataType,(GDALRasterBandH,),arg1)
end

function GDALGetBlockSize(arg1::GDALRasterBandH,pnXSize::Ptr{Cint},pnYSize::Ptr{Cint})
    ccall((:GDALGetBlockSize,libgdal),Void,(GDALRasterBandH,Ptr{Cint},Ptr{Cint}),arg1,pnXSize,pnYSize)
end

function GDALRasterAdviseRead(hRB::GDALRasterBandH,nDSXOff::Cint,nDSYOff::Cint,nDSXSize::Cint,nDSYSize::Cint,nBXSize::Cint,nBYSize::Cint,eBDataType::GDALDataType,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALRasterAdviseRead,libgdal),CPLErr,(GDALRasterBandH,Cint,Cint,Cint,Cint,Cint,Cint,GDALDataType,Ptr{Ptr{Uint8}}),hRB,nDSXOff,nDSYOff,nDSXSize,nDSYSize,nBXSize,nBYSize,eBDataType,papszOptions)
end

function GDALRasterIO(hRBand::GDALRasterBandH,eRWFlag::GDALRWFlag,nDSXOff::Cint,nDSYOff::Cint,nDSXSize::Cint,nDSYSize::Cint,pBuffer::Ptr{Void},nBXSize::Cint,nBYSize::Cint,eBDataType::GDALDataType,nPixelSpace::Cint,nLineSpace::Cint)
    ccall((:GDALRasterIO,libgdal),CPLErr,(GDALRasterBandH,GDALRWFlag,Cint,Cint,Cint,Cint,Ptr{Void},Cint,Cint,GDALDataType,Cint,Cint),hRBand,eRWFlag,nDSXOff,nDSYOff,nDSXSize,nDSYSize,pBuffer,nBXSize,nBYSize,eBDataType,nPixelSpace,nLineSpace)
end

function GDALReadBlock(arg1::GDALRasterBandH,arg2::Cint,arg3::Cint,arg4::Ptr{Void})
    ccall((:GDALReadBlock,libgdal),CPLErr,(GDALRasterBandH,Cint,Cint,Ptr{Void}),arg1,arg2,arg3,arg4)
end

function GDALWriteBlock(arg1::GDALRasterBandH,arg2::Cint,arg3::Cint,arg4::Ptr{Void})
    ccall((:GDALWriteBlock,libgdal),CPLErr,(GDALRasterBandH,Cint,Cint,Ptr{Void}),arg1,arg2,arg3,arg4)
end

function GDALGetRasterBandXSize(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterBandXSize,libgdal),Cint,(GDALRasterBandH,),arg1)
end

function GDALGetRasterBandYSize(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterBandYSize,libgdal),Cint,(GDALRasterBandH,),arg1)
end

function GDALGetRasterAccess(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterAccess,libgdal),GDALAccess,(GDALRasterBandH,),arg1)
end

function GDALGetBandNumber(arg1::GDALRasterBandH)
    ccall((:GDALGetBandNumber,libgdal),Cint,(GDALRasterBandH,),arg1)
end

function GDALGetBandDataset(arg1::GDALRasterBandH)
    ccall((:GDALGetBandDataset,libgdal),GDALDatasetH,(GDALRasterBandH,),arg1)
end

function GDALGetRasterColorInterpretation(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterColorInterpretation,libgdal),GDALColorInterp,(GDALRasterBandH,),arg1)
end

function GDALSetRasterColorInterpretation(arg1::GDALRasterBandH,arg2::GDALColorInterp)
    ccall((:GDALSetRasterColorInterpretation,libgdal),CPLErr,(GDALRasterBandH,GDALColorInterp),arg1,arg2)
end

function GDALGetRasterColorTable(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterColorTable,libgdal),GDALColorTableH,(GDALRasterBandH,),arg1)
end

function GDALSetRasterColorTable(arg1::GDALRasterBandH,arg2::GDALColorTableH)
    ccall((:GDALSetRasterColorTable,libgdal),CPLErr,(GDALRasterBandH,GDALColorTableH),arg1,arg2)
end

function GDALHasArbitraryOverviews(arg1::GDALRasterBandH)
    ccall((:GDALHasArbitraryOverviews,libgdal),Cint,(GDALRasterBandH,),arg1)
end

function GDALGetOverviewCount(arg1::GDALRasterBandH)
    ccall((:GDALGetOverviewCount,libgdal),Cint,(GDALRasterBandH,),arg1)
end

function GDALGetOverview(arg1::GDALRasterBandH,arg2::Cint)
    ccall((:GDALGetOverview,libgdal),GDALRasterBandH,(GDALRasterBandH,Cint),arg1,arg2)
end

function GDALGetRasterNoDataValue(arg1::GDALRasterBandH,arg2::Ptr{Cint})
    ccall((:GDALGetRasterNoDataValue,libgdal),Cdouble,(GDALRasterBandH,Ptr{Cint}),arg1,arg2)
end

function GDALSetRasterNoDataValue(arg1::GDALRasterBandH,arg2::Cdouble)
    ccall((:GDALSetRasterNoDataValue,libgdal),CPLErr,(GDALRasterBandH,Cdouble),arg1,arg2)
end

function GDALGetRasterCategoryNames(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterCategoryNames,libgdal),Ptr{Ptr{Uint8}},(GDALRasterBandH,),arg1)
end

function GDALSetRasterCategoryNames(arg1::GDALRasterBandH,arg2::Ptr{Ptr{Uint8}})
    ccall((:GDALSetRasterCategoryNames,libgdal),CPLErr,(GDALRasterBandH,Ptr{Ptr{Uint8}}),arg1,arg2)
end

function GDALGetRasterMinimum(arg1::GDALRasterBandH,pbSuccess::Ptr{Cint})
    ccall((:GDALGetRasterMinimum,libgdal),Cdouble,(GDALRasterBandH,Ptr{Cint}),arg1,pbSuccess)
end

function GDALGetRasterMaximum(arg1::GDALRasterBandH,pbSuccess::Ptr{Cint})
    ccall((:GDALGetRasterMaximum,libgdal),Cdouble,(GDALRasterBandH,Ptr{Cint}),arg1,pbSuccess)
end

function GDALGetRasterStatistics(arg1::GDALRasterBandH,bApproxOK::Cint,bForce::Cint,pdfMin::Ptr{Cdouble},pdfMax::Ptr{Cdouble},pdfMean::Ptr{Cdouble},pdfStdDev::Ptr{Cdouble})
    ccall((:GDALGetRasterStatistics,libgdal),CPLErr,(GDALRasterBandH,Cint,Cint,Ptr{Cdouble},Ptr{Cdouble},Ptr{Cdouble},Ptr{Cdouble}),arg1,bApproxOK,bForce,pdfMin,pdfMax,pdfMean,pdfStdDev)
end

function GDALComputeRasterStatistics(arg1::GDALRasterBandH,bApproxOK::Cint,pdfMin::Ptr{Cdouble},pdfMax::Ptr{Cdouble},pdfMean::Ptr{Cdouble},pdfStdDev::Ptr{Cdouble},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALComputeRasterStatistics,libgdal),CPLErr,(GDALRasterBandH,Cint,Ptr{Cdouble},Ptr{Cdouble},Ptr{Cdouble},Ptr{Cdouble},GDALProgressFunc,Ptr{Void}),arg1,bApproxOK,pdfMin,pdfMax,pdfMean,pdfStdDev,pfnProgress,pProgressData)
end

function GDALSetRasterStatistics(hBand::GDALRasterBandH,dfMin::Cdouble,dfMax::Cdouble,dfMean::Cdouble,dfStdDev::Cdouble)
    ccall((:GDALSetRasterStatistics,libgdal),CPLErr,(GDALRasterBandH,Cdouble,Cdouble,Cdouble,Cdouble),hBand,dfMin,dfMax,dfMean,dfStdDev)
end

function GDALGetRasterUnitType(arg1::GDALRasterBandH)
    ccall((:GDALGetRasterUnitType,libgdal),Ptr{Uint8},(GDALRasterBandH,),arg1)
end

function GDALSetRasterUnitType(hBand::GDALRasterBandH,pszNewValue::Ptr{Uint8})
    ccall((:GDALSetRasterUnitType,libgdal),CPLErr,(GDALRasterBandH,Ptr{Uint8}),hBand,pszNewValue)
end

function GDALGetRasterOffset(arg1::GDALRasterBandH,pbSuccess::Ptr{Cint})
    ccall((:GDALGetRasterOffset,libgdal),Cdouble,(GDALRasterBandH,Ptr{Cint}),arg1,pbSuccess)
end

function GDALSetRasterOffset(hBand::GDALRasterBandH,dfNewOffset::Cdouble)
    ccall((:GDALSetRasterOffset,libgdal),CPLErr,(GDALRasterBandH,Cdouble),hBand,dfNewOffset)
end

function GDALGetRasterScale(arg1::GDALRasterBandH,pbSuccess::Ptr{Cint})
    ccall((:GDALGetRasterScale,libgdal),Cdouble,(GDALRasterBandH,Ptr{Cint}),arg1,pbSuccess)
end

function GDALSetRasterScale(hBand::GDALRasterBandH,dfNewOffset::Cdouble)
    ccall((:GDALSetRasterScale,libgdal),CPLErr,(GDALRasterBandH,Cdouble),hBand,dfNewOffset)
end

function GDALComputeRasterMinMax(hBand::GDALRasterBandH,bApproxOK::Cint,adfMinMax::Ptr{Cdouble})
    ccall((:GDALComputeRasterMinMax,libgdal),Void,(GDALRasterBandH,Cint,Ptr{Cdouble}),hBand,bApproxOK,adfMinMax)
end

function GDALFlushRasterCache(hBand::GDALRasterBandH)
    ccall((:GDALFlushRasterCache,libgdal),CPLErr,(GDALRasterBandH,),hBand)
end

function GDALGetRasterHistogram(hBand::GDALRasterBandH,dfMin::Cdouble,dfMax::Cdouble,nBuckets::Cint,panHistogram::Ptr{Cint},bIncludeOutOfRange::Cint,bApproxOK::Cint,pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALGetRasterHistogram,libgdal),CPLErr,(GDALRasterBandH,Cdouble,Cdouble,Cint,Ptr{Cint},Cint,Cint,GDALProgressFunc,Ptr{Void}),hBand,dfMin,dfMax,nBuckets,panHistogram,bIncludeOutOfRange,bApproxOK,pfnProgress,pProgressData)
end

function GDALGetDefaultHistogram(hBand::GDALRasterBandH,pdfMin::Ptr{Cdouble},pdfMax::Ptr{Cdouble},pnBuckets::Ptr{Cint},ppanHistogram::Ptr{Ptr{Cint}},bForce::Cint,pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALGetDefaultHistogram,libgdal),CPLErr,(GDALRasterBandH,Ptr{Cdouble},Ptr{Cdouble},Ptr{Cint},Ptr{Ptr{Cint}},Cint,GDALProgressFunc,Ptr{Void}),hBand,pdfMin,pdfMax,pnBuckets,ppanHistogram,bForce,pfnProgress,pProgressData)
end

function GDALSetDefaultHistogram(hBand::GDALRasterBandH,dfMin::Cdouble,dfMax::Cdouble,nBuckets::Cint,panHistogram::Ptr{Cint})
    ccall((:GDALSetDefaultHistogram,libgdal),CPLErr,(GDALRasterBandH,Cdouble,Cdouble,Cint,Ptr{Cint}),hBand,dfMin,dfMax,nBuckets,panHistogram)
end

function GDALGetRandomRasterSample(arg1::GDALRasterBandH,arg2::Cint,arg3::Ptr{Cfloat})
    ccall((:GDALGetRandomRasterSample,libgdal),Cint,(GDALRasterBandH,Cint,Ptr{Cfloat}),arg1,arg2,arg3)
end

function GDALGetRasterSampleOverview(arg1::GDALRasterBandH,arg2::Cint)
    ccall((:GDALGetRasterSampleOverview,libgdal),GDALRasterBandH,(GDALRasterBandH,Cint),arg1,arg2)
end

function GDALFillRaster(hBand::GDALRasterBandH,dfRealValue::Cdouble,dfImaginaryValue::Cdouble)
    ccall((:GDALFillRaster,libgdal),CPLErr,(GDALRasterBandH,Cdouble,Cdouble),hBand,dfRealValue,dfImaginaryValue)
end

function GDALComputeBandStats(hBand::GDALRasterBandH,nSampleStep::Cint,pdfMean::Ptr{Cdouble},pdfStdDev::Ptr{Cdouble},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALComputeBandStats,libgdal),CPLErr,(GDALRasterBandH,Cint,Ptr{Cdouble},Ptr{Cdouble},GDALProgressFunc,Ptr{Void}),hBand,nSampleStep,pdfMean,pdfStdDev,pfnProgress,pProgressData)
end

function GDALOverviewMagnitudeCorrection(hBaseBand::GDALRasterBandH,nOverviewCount::Cint,pahOverviews::Ptr{GDALRasterBandH},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALOverviewMagnitudeCorrection,libgdal),CPLErr,(GDALRasterBandH,Cint,Ptr{GDALRasterBandH},GDALProgressFunc,Ptr{Void}),hBaseBand,nOverviewCount,pahOverviews,pfnProgress,pProgressData)
end

function GDALGetDefaultRAT(hBand::GDALRasterBandH)
    ccall((:GDALGetDefaultRAT,libgdal),GDALRasterAttributeTableH,(GDALRasterBandH,),hBand)
end

function GDALSetDefaultRAT(arg1::GDALRasterBandH,arg2::GDALRasterAttributeTableH)
    ccall((:GDALSetDefaultRAT,libgdal),CPLErr,(GDALRasterBandH,GDALRasterAttributeTableH),arg1,arg2)
end

function GDALAddDerivedBandPixelFunc(pszName::Ptr{Uint8},pfnPixelFunc::GDALDerivedPixelFunc)
    ccall((:GDALAddDerivedBandPixelFunc,libgdal),CPLErr,(Ptr{Uint8},GDALDerivedPixelFunc),pszName,pfnPixelFunc)
end

function GDALGetMaskBand(hBand::GDALRasterBandH)
    ccall((:GDALGetMaskBand,libgdal),GDALRasterBandH,(GDALRasterBandH,),hBand)
end

function GDALGetMaskFlags(hBand::GDALRasterBandH)
    ccall((:GDALGetMaskFlags,libgdal),Cint,(GDALRasterBandH,),hBand)
end

function GDALCreateMaskBand(hBand::GDALRasterBandH,nFlags::Cint)
    ccall((:GDALCreateMaskBand,libgdal),CPLErr,(GDALRasterBandH,Cint),hBand,nFlags)
end

function GDALARGetNextUpdatedRegion(hARIO::GDALAsyncReaderH,dfTimeout::Cdouble,pnXBufOff::Ptr{Cint},pnYBufOff::Ptr{Cint},pnXBufSize::Ptr{Cint},pnYBufSize::Ptr{Cint})
    ccall((:GDALARGetNextUpdatedRegion,libgdal),GDALAsyncStatusType,(GDALAsyncReaderH,Cdouble,Ptr{Cint},Ptr{Cint},Ptr{Cint},Ptr{Cint}),hARIO,dfTimeout,pnXBufOff,pnYBufOff,pnXBufSize,pnYBufSize)
end

function GDALARLockBuffer(hARIO::GDALAsyncReaderH,dfTimeout::Cdouble)
    ccall((:GDALARLockBuffer,libgdal),Cint,(GDALAsyncReaderH,Cdouble),hARIO,dfTimeout)
end

function GDALARUnlockBuffer(hARIO::GDALAsyncReaderH)
    ccall((:GDALARUnlockBuffer,libgdal),Void,(GDALAsyncReaderH,),hARIO)
end

function GDALGeneralCmdLineProcessor(nArgc::Cint,ppapszArgv::Ptr{Ptr{Ptr{Uint8}}},nOptions::Cint)
    ccall((:GDALGeneralCmdLineProcessor,libgdal),Cint,(Cint,Ptr{Ptr{Ptr{Uint8}}},Cint),nArgc,ppapszArgv,nOptions)
end

function GDALSwapWords(pData::Ptr{Void},nWordSize::Cint,nWordCount::Cint,nWordSkip::Cint)
    ccall((:GDALSwapWords,libgdal),Void,(Ptr{Void},Cint,Cint,Cint),pData,nWordSize,nWordCount,nWordSkip)
end

function GDALCopyWords(pSrcData::Ptr{Void},eSrcType::GDALDataType,nSrcPixelOffset::Cint,pDstData::Ptr{Void},eDstType::GDALDataType,nDstPixelOffset::Cint,nWordCount::Cint)
    ccall((:GDALCopyWords,libgdal),Void,(Ptr{Void},GDALDataType,Cint,Ptr{Void},GDALDataType,Cint,Cint),pSrcData,eSrcType,nSrcPixelOffset,pDstData,eDstType,nDstPixelOffset,nWordCount)
end

function GDALCopyBits(pabySrcData::Ptr{GByte},nSrcOffset::Cint,nSrcStep::Cint,pabyDstData::Ptr{GByte},nDstOffset::Cint,nDstStep::Cint,nBitCount::Cint,nStepCount::Cint)
    ccall((:GDALCopyBits,libgdal),Void,(Ptr{GByte},Cint,Cint,Ptr{GByte},Cint,Cint,Cint,Cint),pabySrcData,nSrcOffset,nSrcStep,pabyDstData,nDstOffset,nDstStep,nBitCount,nStepCount)
end

function GDALLoadWorldFile(arg1::Ptr{Uint8},arg2::Ptr{Cdouble})
    ccall((:GDALLoadWorldFile,libgdal),Cint,(Ptr{Uint8},Ptr{Cdouble}),arg1,arg2)
end

function GDALReadWorldFile(arg1::Ptr{Uint8},arg2::Ptr{Uint8},arg3::Ptr{Cdouble})
    ccall((:GDALReadWorldFile,libgdal),Cint,(Ptr{Uint8},Ptr{Uint8},Ptr{Cdouble}),arg1,arg2,arg3)
end

function GDALWriteWorldFile(arg1::Ptr{Uint8},arg2::Ptr{Uint8},arg3::Ptr{Cdouble})
    ccall((:GDALWriteWorldFile,libgdal),Cint,(Ptr{Uint8},Ptr{Uint8},Ptr{Cdouble}),arg1,arg2,arg3)
end

function GDALLoadTabFile(arg1::Ptr{Uint8},arg2::Ptr{Cdouble},arg3::Ptr{Ptr{Uint8}},arg4::Ptr{Cint},arg5::Ptr{Ptr{GDAL_GCP}})
    ccall((:GDALLoadTabFile,libgdal),Cint,(Ptr{Uint8},Ptr{Cdouble},Ptr{Ptr{Uint8}},Ptr{Cint},Ptr{Ptr{GDAL_GCP}}),arg1,arg2,arg3,arg4,arg5)
end

function GDALReadTabFile(arg1::Ptr{Uint8},arg2::Ptr{Cdouble},arg3::Ptr{Ptr{Uint8}},arg4::Ptr{Cint},arg5::Ptr{Ptr{GDAL_GCP}})
    ccall((:GDALReadTabFile,libgdal),Cint,(Ptr{Uint8},Ptr{Cdouble},Ptr{Ptr{Uint8}},Ptr{Cint},Ptr{Ptr{GDAL_GCP}}),arg1,arg2,arg3,arg4,arg5)
end

function GDALLoadOziMapFile(arg1::Ptr{Uint8},arg2::Ptr{Cdouble},arg3::Ptr{Ptr{Uint8}},arg4::Ptr{Cint},arg5::Ptr{Ptr{GDAL_GCP}})
    ccall((:GDALLoadOziMapFile,libgdal),Cint,(Ptr{Uint8},Ptr{Cdouble},Ptr{Ptr{Uint8}},Ptr{Cint},Ptr{Ptr{GDAL_GCP}}),arg1,arg2,arg3,arg4,arg5)
end

function GDALReadOziMapFile(arg1::Ptr{Uint8},arg2::Ptr{Cdouble},arg3::Ptr{Ptr{Uint8}},arg4::Ptr{Cint},arg5::Ptr{Ptr{GDAL_GCP}})
    ccall((:GDALReadOziMapFile,libgdal),Cint,(Ptr{Uint8},Ptr{Cdouble},Ptr{Ptr{Uint8}},Ptr{Cint},Ptr{Ptr{GDAL_GCP}}),arg1,arg2,arg3,arg4,arg5)
end

function GDALLoadRPBFile(pszFilename::Ptr{Uint8},papszSiblingFiles::Ptr{Ptr{Uint8}})
    ccall((:GDALLoadRPBFile,libgdal),Ptr{Ptr{Uint8}},(Ptr{Uint8},Ptr{Ptr{Uint8}}),pszFilename,papszSiblingFiles)
end

function GDALLoadRPCFile(pszFilename::Ptr{Uint8},papszSiblingFiles::Ptr{Ptr{Uint8}})
    ccall((:GDALLoadRPCFile,libgdal),Ptr{Ptr{Uint8}},(Ptr{Uint8},Ptr{Ptr{Uint8}}),pszFilename,papszSiblingFiles)
end

function GDALWriteRPBFile(pszFilename::Ptr{Uint8},papszMD::Ptr{Ptr{Uint8}})
    ccall((:GDALWriteRPBFile,libgdal),CPLErr,(Ptr{Uint8},Ptr{Ptr{Uint8}}),pszFilename,papszMD)
end

function GDALLoadIMDFile(pszFilename::Ptr{Uint8},papszSiblingFiles::Ptr{Ptr{Uint8}})
    ccall((:GDALLoadIMDFile,libgdal),Ptr{Ptr{Uint8}},(Ptr{Uint8},Ptr{Ptr{Uint8}}),pszFilename,papszSiblingFiles)
end

function GDALWriteIMDFile(pszFilename::Ptr{Uint8},papszMD::Ptr{Ptr{Uint8}})
    ccall((:GDALWriteIMDFile,libgdal),CPLErr,(Ptr{Uint8},Ptr{Ptr{Uint8}}),pszFilename,papszMD)
end

function GDALDecToDMS(arg1::Cdouble,arg2::Ptr{Uint8},arg3::Cint)
    ccall((:GDALDecToDMS,libgdal),Ptr{Uint8},(Cdouble,Ptr{Uint8},Cint),arg1,arg2,arg3)
end

function GDALPackedDMSToDec(arg1::Cdouble)
    ccall((:GDALPackedDMSToDec,libgdal),Cdouble,(Cdouble,),arg1)
end

function GDALDecToPackedDMS(arg1::Cdouble)
    ccall((:GDALDecToPackedDMS,libgdal),Cdouble,(Cdouble,),arg1)
end

function GDALVersionInfo(arg1::Ptr{Uint8})
    ccall((:GDALVersionInfo,libgdal),Ptr{Uint8},(Ptr{Uint8},),arg1)
end

function GDALCheckVersion(nVersionMajor::Cint,nVersionMinor::Cint,pszCallingComponentName::Ptr{Uint8})
    ccall((:GDALCheckVersion,libgdal),Cint,(Cint,Cint,Ptr{Uint8}),nVersionMajor,nVersionMinor,pszCallingComponentName)
end

function GDALExtractRPCInfo(arg1::Ptr{Ptr{Uint8}},arg2::Ptr{GDALRPCInfo})
    ccall((:GDALExtractRPCInfo,libgdal),Cint,(Ptr{Ptr{Uint8}},Ptr{GDALRPCInfo}),arg1,arg2)
end

function GDALCreateColorTable(arg1::GDALPaletteInterp)
    ccall((:GDALCreateColorTable,libgdal),GDALColorTableH,(GDALPaletteInterp,),arg1)
end

function GDALDestroyColorTable(arg1::GDALColorTableH)
    ccall((:GDALDestroyColorTable,libgdal),Void,(GDALColorTableH,),arg1)
end

function GDALCloneColorTable(arg1::GDALColorTableH)
    ccall((:GDALCloneColorTable,libgdal),GDALColorTableH,(GDALColorTableH,),arg1)
end

function GDALGetPaletteInterpretation(arg1::GDALColorTableH)
    ccall((:GDALGetPaletteInterpretation,libgdal),GDALPaletteInterp,(GDALColorTableH,),arg1)
end

function GDALGetColorEntryCount(arg1::GDALColorTableH)
    ccall((:GDALGetColorEntryCount,libgdal),Cint,(GDALColorTableH,),arg1)
end

function GDALGetColorEntry(arg1::GDALColorTableH,arg2::Cint)
    ccall((:GDALGetColorEntry,libgdal),Ptr{GDALColorEntry},(GDALColorTableH,Cint),arg1,arg2)
end

function GDALGetColorEntryAsRGB(arg1::GDALColorTableH,arg2::Cint,arg3::Ptr{GDALColorEntry})
    ccall((:GDALGetColorEntryAsRGB,libgdal),Cint,(GDALColorTableH,Cint,Ptr{GDALColorEntry}),arg1,arg2,arg3)
end

function GDALSetColorEntry(arg1::GDALColorTableH,arg2::Cint,arg3::Ptr{GDALColorEntry})
    ccall((:GDALSetColorEntry,libgdal),Void,(GDALColorTableH,Cint,Ptr{GDALColorEntry}),arg1,arg2,arg3)
end

function GDALCreateColorRamp(hTable::GDALColorTableH,nStartIndex::Cint,psStartColor::Ptr{GDALColorEntry},nEndIndex::Cint,psEndColor::Ptr{GDALColorEntry})
    ccall((:GDALCreateColorRamp,libgdal),Void,(GDALColorTableH,Cint,Ptr{GDALColorEntry},Cint,Ptr{GDALColorEntry}),hTable,nStartIndex,psStartColor,nEndIndex,psEndColor)
end

function GDALCreateRasterAttributeTable()
    ccall((:GDALCreateRasterAttributeTable,libgdal),GDALRasterAttributeTableH,())
end

function GDALDestroyRasterAttributeTable(arg1::GDALRasterAttributeTableH)
    ccall((:GDALDestroyRasterAttributeTable,libgdal),Void,(GDALRasterAttributeTableH,),arg1)
end

function GDALRATGetColumnCount(arg1::GDALRasterAttributeTableH)
    ccall((:GDALRATGetColumnCount,libgdal),Cint,(GDALRasterAttributeTableH,),arg1)
end

function GDALRATGetNameOfCol(arg1::GDALRasterAttributeTableH,arg2::Cint)
    ccall((:GDALRATGetNameOfCol,libgdal),Ptr{Uint8},(GDALRasterAttributeTableH,Cint),arg1,arg2)
end

function GDALRATGetUsageOfCol(arg1::GDALRasterAttributeTableH,arg2::Cint)
    ccall((:GDALRATGetUsageOfCol,libgdal),GDALRATFieldUsage,(GDALRasterAttributeTableH,Cint),arg1,arg2)
end

function GDALRATGetTypeOfCol(arg1::GDALRasterAttributeTableH,arg2::Cint)
    ccall((:GDALRATGetTypeOfCol,libgdal),GDALRATFieldType,(GDALRasterAttributeTableH,Cint),arg1,arg2)
end

function GDALRATGetColOfUsage(arg1::GDALRasterAttributeTableH,arg2::GDALRATFieldUsage)
    ccall((:GDALRATGetColOfUsage,libgdal),Cint,(GDALRasterAttributeTableH,GDALRATFieldUsage),arg1,arg2)
end

function GDALRATGetRowCount(arg1::GDALRasterAttributeTableH)
    ccall((:GDALRATGetRowCount,libgdal),Cint,(GDALRasterAttributeTableH,),arg1)
end

function GDALRATGetValueAsString(arg1::GDALRasterAttributeTableH,arg2::Cint,arg3::Cint)
    ccall((:GDALRATGetValueAsString,libgdal),Ptr{Uint8},(GDALRasterAttributeTableH,Cint,Cint),arg1,arg2,arg3)
end

function GDALRATGetValueAsInt(arg1::GDALRasterAttributeTableH,arg2::Cint,arg3::Cint)
    ccall((:GDALRATGetValueAsInt,libgdal),Cint,(GDALRasterAttributeTableH,Cint,Cint),arg1,arg2,arg3)
end

function GDALRATGetValueAsDouble(arg1::GDALRasterAttributeTableH,arg2::Cint,arg3::Cint)
    ccall((:GDALRATGetValueAsDouble,libgdal),Cdouble,(GDALRasterAttributeTableH,Cint,Cint),arg1,arg2,arg3)
end

function GDALRATSetValueAsString(arg1::GDALRasterAttributeTableH,arg2::Cint,arg3::Cint,arg4::Ptr{Uint8})
    ccall((:GDALRATSetValueAsString,libgdal),Void,(GDALRasterAttributeTableH,Cint,Cint,Ptr{Uint8}),arg1,arg2,arg3,arg4)
end

function GDALRATSetValueAsInt(arg1::GDALRasterAttributeTableH,arg2::Cint,arg3::Cint,arg4::Cint)
    ccall((:GDALRATSetValueAsInt,libgdal),Void,(GDALRasterAttributeTableH,Cint,Cint,Cint),arg1,arg2,arg3,arg4)
end

function GDALRATSetValueAsDouble(arg1::GDALRasterAttributeTableH,arg2::Cint,arg3::Cint,arg4::Cdouble)
    ccall((:GDALRATSetValueAsDouble,libgdal),Void,(GDALRasterAttributeTableH,Cint,Cint,Cdouble),arg1,arg2,arg3,arg4)
end

function GDALRATChangesAreWrittenToFile(hRAT::GDALRasterAttributeTableH)
    ccall((:GDALRATChangesAreWrittenToFile,libgdal),Cint,(GDALRasterAttributeTableH,),hRAT)
end

function GDALRATValuesIOAsDouble(hRAT::GDALRasterAttributeTableH,eRWFlag::GDALRWFlag,iField::Cint,iStartRow::Cint,iLength::Cint,pdfData::Ptr{Cdouble})
    ccall((:GDALRATValuesIOAsDouble,libgdal),CPLErr,(GDALRasterAttributeTableH,GDALRWFlag,Cint,Cint,Cint,Ptr{Cdouble}),hRAT,eRWFlag,iField,iStartRow,iLength,pdfData)
end

function GDALRATValuesIOAsInteger(hRAT::GDALRasterAttributeTableH,eRWFlag::GDALRWFlag,iField::Cint,iStartRow::Cint,iLength::Cint,pnData::Ptr{Cint})
    ccall((:GDALRATValuesIOAsInteger,libgdal),CPLErr,(GDALRasterAttributeTableH,GDALRWFlag,Cint,Cint,Cint,Ptr{Cint}),hRAT,eRWFlag,iField,iStartRow,iLength,pnData)
end

function GDALRATValuesIOAsString(hRAT::GDALRasterAttributeTableH,eRWFlag::GDALRWFlag,iField::Cint,iStartRow::Cint,iLength::Cint,papszStrList::Ptr{Ptr{Uint8}})
    ccall((:GDALRATValuesIOAsString,libgdal),CPLErr,(GDALRasterAttributeTableH,GDALRWFlag,Cint,Cint,Cint,Ptr{Ptr{Uint8}}),hRAT,eRWFlag,iField,iStartRow,iLength,papszStrList)
end

function GDALRATSetRowCount(arg1::GDALRasterAttributeTableH,arg2::Cint)
    ccall((:GDALRATSetRowCount,libgdal),Void,(GDALRasterAttributeTableH,Cint),arg1,arg2)
end

function GDALRATCreateColumn(arg1::GDALRasterAttributeTableH,arg2::Ptr{Uint8},arg3::GDALRATFieldType,arg4::GDALRATFieldUsage)
    ccall((:GDALRATCreateColumn,libgdal),CPLErr,(GDALRasterAttributeTableH,Ptr{Uint8},GDALRATFieldType,GDALRATFieldUsage),arg1,arg2,arg3,arg4)
end

function GDALRATSetLinearBinning(arg1::GDALRasterAttributeTableH,arg2::Cdouble,arg3::Cdouble)
    ccall((:GDALRATSetLinearBinning,libgdal),CPLErr,(GDALRasterAttributeTableH,Cdouble,Cdouble),arg1,arg2,arg3)
end

function GDALRATGetLinearBinning(arg1::GDALRasterAttributeTableH,arg2::Ptr{Cdouble},arg3::Ptr{Cdouble})
    ccall((:GDALRATGetLinearBinning,libgdal),Cint,(GDALRasterAttributeTableH,Ptr{Cdouble},Ptr{Cdouble}),arg1,arg2,arg3)
end

function GDALRATInitializeFromColorTable(arg1::GDALRasterAttributeTableH,arg2::GDALColorTableH)
    ccall((:GDALRATInitializeFromColorTable,libgdal),CPLErr,(GDALRasterAttributeTableH,GDALColorTableH),arg1,arg2)
end

function GDALRATTranslateToColorTable(arg1::GDALRasterAttributeTableH,nEntryCount::Cint)
    ccall((:GDALRATTranslateToColorTable,libgdal),GDALColorTableH,(GDALRasterAttributeTableH,Cint),arg1,nEntryCount)
end

function GDALRATDumpReadable(arg1::GDALRasterAttributeTableH,arg2::Ptr{FILE})
    ccall((:GDALRATDumpReadable,libgdal),Void,(GDALRasterAttributeTableH,Ptr{FILE}),arg1,arg2)
end

function GDALRATClone(arg1::GDALRasterAttributeTableH)
    ccall((:GDALRATClone,libgdal),GDALRasterAttributeTableH,(GDALRasterAttributeTableH,),arg1)
end

function GDALRATGetRowOfValue(arg1::GDALRasterAttributeTableH,arg2::Cdouble)
    ccall((:GDALRATGetRowOfValue,libgdal),Cint,(GDALRasterAttributeTableH,Cdouble),arg1,arg2)
end

function GDALSetCacheMax(nBytes::Cint)
    ccall((:GDALSetCacheMax,libgdal),Void,(Cint,),nBytes)
end

function GDALGetCacheMax()
    ccall((:GDALGetCacheMax,libgdal),Cint,())
end

function GDALGetCacheUsed()
    ccall((:GDALGetCacheUsed,libgdal),Cint,())
end

function GDALSetCacheMax64(nBytes::GIntBig)
    ccall((:GDALSetCacheMax64,libgdal),Void,(GIntBig,),nBytes)
end

function GDALGetCacheMax64()
    ccall((:GDALGetCacheMax64,libgdal),GIntBig,())
end

function GDALGetCacheUsed64()
    ccall((:GDALGetCacheUsed64,libgdal),GIntBig,())
end

function GDALFlushCacheBlock()
    ccall((:GDALFlushCacheBlock,libgdal),Cint,())
end

function GDALDatasetGetVirtualMem(hDS::GDALDatasetH,eRWFlag::GDALRWFlag,nXOff::Cint,nYOff::Cint,nXSize::Cint,nYSize::Cint,nBufXSize::Cint,nBufYSize::Cint,eBufType::GDALDataType,nBandCount::Cint,panBandMap::Ptr{Cint},nPixelSpace::Cint,nLineSpace::GIntBig,nBandSpace::GIntBig,nCacheSize::Csize_t,nPageSizeHint::Csize_t,bSingleThreadUsage::Cint,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALDatasetGetVirtualMem,libgdal),Ptr{CPLVirtualMem},(GDALDatasetH,GDALRWFlag,Cint,Cint,Cint,Cint,Cint,Cint,GDALDataType,Cint,Ptr{Cint},Cint,GIntBig,GIntBig,Csize_t,Csize_t,Cint,Ptr{Ptr{Uint8}}),hDS,eRWFlag,nXOff,nYOff,nXSize,nYSize,nBufXSize,nBufYSize,eBufType,nBandCount,panBandMap,nPixelSpace,nLineSpace,nBandSpace,nCacheSize,nPageSizeHint,bSingleThreadUsage,papszOptions)
end

function GDALRasterBandGetVirtualMem(hBand::GDALRasterBandH,eRWFlag::GDALRWFlag,nXOff::Cint,nYOff::Cint,nXSize::Cint,nYSize::Cint,nBufXSize::Cint,nBufYSize::Cint,eBufType::GDALDataType,nPixelSpace::Cint,nLineSpace::GIntBig,nCacheSize::Csize_t,nPageSizeHint::Csize_t,bSingleThreadUsage::Cint,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALRasterBandGetVirtualMem,libgdal),Ptr{CPLVirtualMem},(GDALRasterBandH,GDALRWFlag,Cint,Cint,Cint,Cint,Cint,Cint,GDALDataType,Cint,GIntBig,Csize_t,Csize_t,Cint,Ptr{Ptr{Uint8}}),hBand,eRWFlag,nXOff,nYOff,nXSize,nYSize,nBufXSize,nBufYSize,eBufType,nPixelSpace,nLineSpace,nCacheSize,nPageSizeHint,bSingleThreadUsage,papszOptions)
end

function GDALGetVirtualMemAuto(hBand::GDALRasterBandH,eRWFlag::GDALRWFlag,pnPixelSpace::Ptr{Cint},pnLineSpace::Ptr{GIntBig},papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALGetVirtualMemAuto,libgdal),Ptr{CPLVirtualMem},(GDALRasterBandH,GDALRWFlag,Ptr{Cint},Ptr{GIntBig},Ptr{Ptr{Uint8}}),hBand,eRWFlag,pnPixelSpace,pnLineSpace,papszOptions)
end

function GDALDatasetGetTiledVirtualMem(hDS::GDALDatasetH,eRWFlag::GDALRWFlag,nXOff::Cint,nYOff::Cint,nXSize::Cint,nYSize::Cint,nTileXSize::Cint,nTileYSize::Cint,eBufType::GDALDataType,nBandCount::Cint,panBandMap::Ptr{Cint},eTileOrganization::GDALTileOrganization,nCacheSize::Csize_t,bSingleThreadUsage::Cint,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALDatasetGetTiledVirtualMem,libgdal),Ptr{CPLVirtualMem},(GDALDatasetH,GDALRWFlag,Cint,Cint,Cint,Cint,Cint,Cint,GDALDataType,Cint,Ptr{Cint},GDALTileOrganization,Csize_t,Cint,Ptr{Ptr{Uint8}}),hDS,eRWFlag,nXOff,nYOff,nXSize,nYSize,nTileXSize,nTileYSize,eBufType,nBandCount,panBandMap,eTileOrganization,nCacheSize,bSingleThreadUsage,papszOptions)
end

function GDALRasterBandGetTiledVirtualMem(hBand::GDALRasterBandH,eRWFlag::GDALRWFlag,nXOff::Cint,nYOff::Cint,nXSize::Cint,nYSize::Cint,nTileXSize::Cint,nTileYSize::Cint,eBufType::GDALDataType,nCacheSize::Csize_t,bSingleThreadUsage::Cint,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:GDALRasterBandGetTiledVirtualMem,libgdal),Ptr{CPLVirtualMem},(GDALRasterBandH,GDALRWFlag,Cint,Cint,Cint,Cint,Cint,Cint,GDALDataType,Csize_t,Cint,Ptr{Ptr{Uint8}}),hBand,eRWFlag,nXOff,nYOff,nXSize,nYSize,nTileXSize,nTileYSize,eBufType,nCacheSize,bSingleThreadUsage,papszOptions)
end

function GDALRegister_GDB()
    ccall((:GDALRegister_GDB,libgdal),Void,())
end

function GDALRegister_GTiff()
    ccall((:GDALRegister_GTiff,libgdal),Void,())
end

function GDALRegister_GXF()
    ccall((:GDALRegister_GXF,libgdal),Void,())
end

function GDALRegister_OGDI()
    ccall((:GDALRegister_OGDI,libgdal),Void,())
end

function GDALRegister_HFA()
    ccall((:GDALRegister_HFA,libgdal),Void,())
end

function GDALRegister_AAIGrid()
    ccall((:GDALRegister_AAIGrid,libgdal),Void,())
end

function GDALRegister_GRASSASCIIGrid()
    ccall((:GDALRegister_GRASSASCIIGrid,libgdal),Void,())
end

function GDALRegister_AIGrid()
    ccall((:GDALRegister_AIGrid,libgdal),Void,())
end

function GDALRegister_AIGrid2()
    ccall((:GDALRegister_AIGrid2,libgdal),Void,())
end

function GDALRegister_CEOS()
    ccall((:GDALRegister_CEOS,libgdal),Void,())
end

function GDALRegister_SAR_CEOS()
    ccall((:GDALRegister_SAR_CEOS,libgdal),Void,())
end

function GDALRegister_SDTS()
    ccall((:GDALRegister_SDTS,libgdal),Void,())
end

function GDALRegister_ELAS()
    ccall((:GDALRegister_ELAS,libgdal),Void,())
end

function GDALRegister_EHdr()
    ccall((:GDALRegister_EHdr,libgdal),Void,())
end

function GDALRegister_GenBin()
    ccall((:GDALRegister_GenBin,libgdal),Void,())
end

function GDALRegister_PAux()
    ccall((:GDALRegister_PAux,libgdal),Void,())
end

function GDALRegister_ENVI()
    ccall((:GDALRegister_ENVI,libgdal),Void,())
end

function GDALRegister_DOQ1()
    ccall((:GDALRegister_DOQ1,libgdal),Void,())
end

function GDALRegister_DOQ2()
    ccall((:GDALRegister_DOQ2,libgdal),Void,())
end

function GDALRegister_DTED()
    ccall((:GDALRegister_DTED,libgdal),Void,())
end

function GDALRegister_MFF()
    ccall((:GDALRegister_MFF,libgdal),Void,())
end

function GDALRegister_HKV()
    ccall((:GDALRegister_HKV,libgdal),Void,())
end

function GDALRegister_PNG()
    ccall((:GDALRegister_PNG,libgdal),Void,())
end

function GDALRegister_DDS()
    ccall((:GDALRegister_DDS,libgdal),Void,())
end

function GDALRegister_GTA()
    ccall((:GDALRegister_GTA,libgdal),Void,())
end

function GDALRegister_JPEG()
    ccall((:GDALRegister_JPEG,libgdal),Void,())
end

function GDALRegister_JPEG2000()
    ccall((:GDALRegister_JPEG2000,libgdal),Void,())
end

function GDALRegister_JP2KAK()
    ccall((:GDALRegister_JP2KAK,libgdal),Void,())
end

function GDALRegister_JPIPKAK()
    ccall((:GDALRegister_JPIPKAK,libgdal),Void,())
end

function GDALRegister_MEM()
    ccall((:GDALRegister_MEM,libgdal),Void,())
end

function GDALRegister_JDEM()
    ccall((:GDALRegister_JDEM,libgdal),Void,())
end

function GDALRegister_RASDAMAN()
    ccall((:GDALRegister_RASDAMAN,libgdal),Void,())
end

function GDALRegister_GRASS()
    ccall((:GDALRegister_GRASS,libgdal),Void,())
end

function GDALRegister_PNM()
    ccall((:GDALRegister_PNM,libgdal),Void,())
end

function GDALRegister_GIF()
    ccall((:GDALRegister_GIF,libgdal),Void,())
end

function GDALRegister_BIGGIF()
    ccall((:GDALRegister_BIGGIF,libgdal),Void,())
end

function GDALRegister_Envisat()
    ccall((:GDALRegister_Envisat,libgdal),Void,())
end

function GDALRegister_FITS()
    ccall((:GDALRegister_FITS,libgdal),Void,())
end

function GDALRegister_ECW()
    ccall((:GDALRegister_ECW,libgdal),Void,())
end

function GDALRegister_JP2ECW()
    ccall((:GDALRegister_JP2ECW,libgdal),Void,())
end

function GDALRegister_ECW_JP2ECW()
    ccall((:GDALRegister_ECW_JP2ECW,libgdal),Void,())
end

function GDALRegister_FujiBAS()
    ccall((:GDALRegister_FujiBAS,libgdal),Void,())
end

function GDALRegister_FIT()
    ccall((:GDALRegister_FIT,libgdal),Void,())
end

function GDALRegister_VRT()
    ccall((:GDALRegister_VRT,libgdal),Void,())
end

function GDALRegister_USGSDEM()
    ccall((:GDALRegister_USGSDEM,libgdal),Void,())
end

function GDALRegister_FAST()
    ccall((:GDALRegister_FAST,libgdal),Void,())
end

function GDALRegister_HDF4()
    ccall((:GDALRegister_HDF4,libgdal),Void,())
end

function GDALRegister_HDF4Image()
    ccall((:GDALRegister_HDF4Image,libgdal),Void,())
end

function GDALRegister_L1B()
    ccall((:GDALRegister_L1B,libgdal),Void,())
end

function GDALRegister_LDF()
    ccall((:GDALRegister_LDF,libgdal),Void,())
end

function GDALRegister_BSB()
    ccall((:GDALRegister_BSB,libgdal),Void,())
end

function GDALRegister_XPM()
    ccall((:GDALRegister_XPM,libgdal),Void,())
end

function GDALRegister_BMP()
    ccall((:GDALRegister_BMP,libgdal),Void,())
end

function GDALRegister_GSC()
    ccall((:GDALRegister_GSC,libgdal),Void,())
end

function GDALRegister_NITF()
    ccall((:GDALRegister_NITF,libgdal),Void,())
end

function GDALRegister_RPFTOC()
    ccall((:GDALRegister_RPFTOC,libgdal),Void,())
end

function GDALRegister_ECRGTOC()
    ccall((:GDALRegister_ECRGTOC,libgdal),Void,())
end

function GDALRegister_MrSID()
    ccall((:GDALRegister_MrSID,libgdal),Void,())
end

function GDALRegister_MG4Lidar()
    ccall((:GDALRegister_MG4Lidar,libgdal),Void,())
end

function GDALRegister_PCIDSK()
    ccall((:GDALRegister_PCIDSK,libgdal),Void,())
end

function GDALRegister_BT()
    ccall((:GDALRegister_BT,libgdal),Void,())
end

function GDALRegister_DODS()
    ccall((:GDALRegister_DODS,libgdal),Void,())
end

function GDALRegister_GMT()
    ccall((:GDALRegister_GMT,libgdal),Void,())
end

function GDALRegister_netCDF()
    ccall((:GDALRegister_netCDF,libgdal),Void,())
end

function GDALRegister_LAN()
    ccall((:GDALRegister_LAN,libgdal),Void,())
end

function GDALRegister_CPG()
    ccall((:GDALRegister_CPG,libgdal),Void,())
end

function GDALRegister_AirSAR()
    ccall((:GDALRegister_AirSAR,libgdal),Void,())
end

function GDALRegister_RS2()
    ccall((:GDALRegister_RS2,libgdal),Void,())
end

function GDALRegister_ILWIS()
    ccall((:GDALRegister_ILWIS,libgdal),Void,())
end

function GDALRegister_PCRaster()
    ccall((:GDALRegister_PCRaster,libgdal),Void,())
end

function GDALRegister_IDA()
    ccall((:GDALRegister_IDA,libgdal),Void,())
end

function GDALRegister_NDF()
    ccall((:GDALRegister_NDF,libgdal),Void,())
end

function GDALRegister_RMF()
    ccall((:GDALRegister_RMF,libgdal),Void,())
end

function GDALRegister_BAG()
    ccall((:GDALRegister_BAG,libgdal),Void,())
end

function GDALRegister_HDF5()
    ccall((:GDALRegister_HDF5,libgdal),Void,())
end

function GDALRegister_HDF5Image()
    ccall((:GDALRegister_HDF5Image,libgdal),Void,())
end

function GDALRegister_MSGN()
    ccall((:GDALRegister_MSGN,libgdal),Void,())
end

function GDALRegister_MSG()
    ccall((:GDALRegister_MSG,libgdal),Void,())
end

function GDALRegister_RIK()
    ccall((:GDALRegister_RIK,libgdal),Void,())
end

function GDALRegister_Leveller()
    ccall((:GDALRegister_Leveller,libgdal),Void,())
end

function GDALRegister_SGI()
    ccall((:GDALRegister_SGI,libgdal),Void,())
end

function GDALRegister_SRTMHGT()
    ccall((:GDALRegister_SRTMHGT,libgdal),Void,())
end

function GDALRegister_DIPEx()
    ccall((:GDALRegister_DIPEx,libgdal),Void,())
end

function GDALRegister_ISIS3()
    ccall((:GDALRegister_ISIS3,libgdal),Void,())
end

function GDALRegister_ISIS2()
    ccall((:GDALRegister_ISIS2,libgdal),Void,())
end

function GDALRegister_PDS()
    ccall((:GDALRegister_PDS,libgdal),Void,())
end

function GDALRegister_IDRISI()
    ccall((:GDALRegister_IDRISI,libgdal),Void,())
end

function GDALRegister_Terragen()
    ccall((:GDALRegister_Terragen,libgdal),Void,())
end

function GDALRegister_WCS()
    ccall((:GDALRegister_WCS,libgdal),Void,())
end

function GDALRegister_WMS()
    ccall((:GDALRegister_WMS,libgdal),Void,())
end

function GDALRegister_HTTP()
    ccall((:GDALRegister_HTTP,libgdal),Void,())
end

function GDALRegister_SDE()
    ccall((:GDALRegister_SDE,libgdal),Void,())
end

function GDALRegister_GSAG()
    ccall((:GDALRegister_GSAG,libgdal),Void,())
end

function GDALRegister_GSBG()
    ccall((:GDALRegister_GSBG,libgdal),Void,())
end

function GDALRegister_GS7BG()
    ccall((:GDALRegister_GS7BG,libgdal),Void,())
end

function GDALRegister_GRIB()
    ccall((:GDALRegister_GRIB,libgdal),Void,())
end

function GDALRegister_INGR()
    ccall((:GDALRegister_INGR,libgdal),Void,())
end

function GDALRegister_ERS()
    ccall((:GDALRegister_ERS,libgdal),Void,())
end

function GDALRegister_PALSARJaxa()
    ccall((:GDALRegister_PALSARJaxa,libgdal),Void,())
end

function GDALRegister_DIMAP()
    ccall((:GDALRegister_DIMAP,libgdal),Void,())
end

function GDALRegister_GFF()
    ccall((:GDALRegister_GFF,libgdal),Void,())
end

function GDALRegister_COSAR()
    ccall((:GDALRegister_COSAR,libgdal),Void,())
end

function GDALRegister_TSX()
    ccall((:GDALRegister_TSX,libgdal),Void,())
end

function GDALRegister_ADRG()
    ccall((:GDALRegister_ADRG,libgdal),Void,())
end

function GDALRegister_SRP()
    ccall((:GDALRegister_SRP,libgdal),Void,())
end

function GDALRegister_COASP()
    ccall((:GDALRegister_COASP,libgdal),Void,())
end

function GDALRegister_BLX()
    ccall((:GDALRegister_BLX,libgdal),Void,())
end

function GDALRegister_LCP()
    ccall((:GDALRegister_LCP,libgdal),Void,())
end

function GDALRegister_PGCHIP()
    ccall((:GDALRegister_PGCHIP,libgdal),Void,())
end

function GDALRegister_TMS()
    ccall((:GDALRegister_TMS,libgdal),Void,())
end

function GDALRegister_EIR()
    ccall((:GDALRegister_EIR,libgdal),Void,())
end

function GDALRegister_GEOR()
    ccall((:GDALRegister_GEOR,libgdal),Void,())
end

function GDALRegister_TIL()
    ccall((:GDALRegister_TIL,libgdal),Void,())
end

function GDALRegister_R()
    ccall((:GDALRegister_R,libgdal),Void,())
end

function GDALRegister_Rasterlite()
    ccall((:GDALRegister_Rasterlite,libgdal),Void,())
end

function GDALRegister_EPSILON()
    ccall((:GDALRegister_EPSILON,libgdal),Void,())
end

function GDALRegister_PostGISRaster()
    ccall((:GDALRegister_PostGISRaster,libgdal),Void,())
end

function GDALRegister_NWT_GRD()
    ccall((:GDALRegister_NWT_GRD,libgdal),Void,())
end

function GDALRegister_NWT_GRC()
    ccall((:GDALRegister_NWT_GRC,libgdal),Void,())
end

function GDALRegister_SAGA()
    ccall((:GDALRegister_SAGA,libgdal),Void,())
end

function GDALRegister_KMLSUPEROVERLAY()
    ccall((:GDALRegister_KMLSUPEROVERLAY,libgdal),Void,())
end

function GDALRegister_GTX()
    ccall((:GDALRegister_GTX,libgdal),Void,())
end

function GDALRegister_LOSLAS()
    ccall((:GDALRegister_LOSLAS,libgdal),Void,())
end

function GDALRegister_Istar()
    ccall((:GDALRegister_Istar,libgdal),Void,())
end

function GDALRegister_NTv2()
    ccall((:GDALRegister_NTv2,libgdal),Void,())
end

function GDALRegister_CTable2()
    ccall((:GDALRegister_CTable2,libgdal),Void,())
end

function GDALRegister_JP2OpenJPEG()
    ccall((:GDALRegister_JP2OpenJPEG,libgdal),Void,())
end

function GDALRegister_XYZ()
    ccall((:GDALRegister_XYZ,libgdal),Void,())
end

function GDALRegister_HF2()
    ccall((:GDALRegister_HF2,libgdal),Void,())
end

function GDALRegister_PDF()
    ccall((:GDALRegister_PDF,libgdal),Void,())
end

function GDALRegister_JPEGLS()
    ccall((:GDALRegister_JPEGLS,libgdal),Void,())
end

function GDALRegister_MAP()
    ccall((:GDALRegister_MAP,libgdal),Void,())
end

function GDALRegister_OZI()
    ccall((:GDALRegister_OZI,libgdal),Void,())
end

function GDALRegister_ACE2()
    ccall((:GDALRegister_ACE2,libgdal),Void,())
end

function GDALRegister_CTG()
    ccall((:GDALRegister_CTG,libgdal),Void,())
end

function GDALRegister_E00GRID()
    ccall((:GDALRegister_E00GRID,libgdal),Void,())
end

function GDALRegister_SNODAS()
    ccall((:GDALRegister_SNODAS,libgdal),Void,())
end

function GDALRegister_WEBP()
    ccall((:GDALRegister_WEBP,libgdal),Void,())
end

function GDALRegister_ZMap()
    ccall((:GDALRegister_ZMap,libgdal),Void,())
end

function GDALRegister_NGSGEOID()
    ccall((:GDALRegister_NGSGEOID,libgdal),Void,())
end

function GDALRegister_MBTiles()
    ccall((:GDALRegister_MBTiles,libgdal),Void,())
end

function GDALRegister_ARG()
    ccall((:GDALRegister_ARG,libgdal),Void,())
end

function GDALRegister_IRIS()
    ccall((:GDALRegister_IRIS,libgdal),Void,())
end

function GDALRegister_KRO()
    ccall((:GDALRegister_KRO,libgdal),Void,())
end

function GDALOpenInternal(pszFilename::Ptr{Uint8},eAccess::GDALAccess,papszAllowedDrivers::Ptr{Ptr{Uint8}})
    ccall((:GDALOpenInternal,libgdal),GDALDatasetH,(Ptr{Uint8},GDALAccess,Ptr{Ptr{Uint8}}),pszFilename,eAccess,papszAllowedDrivers)
end

function GetGDALDriverManager()
    ccall((:GetGDALDriverManager,libgdal),Ptr{Cint},())
end

function GDALRegenerateOverviewsMultiBand(nBands::Cint,papoSrcBands::Ptr{Ptr{Cint}},nOverviews::Cint,papapoOverviewBands::Ptr{Ptr{Ptr{Cint}}},pszResampling::Ptr{Uint8},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALRegenerateOverviewsMultiBand,libgdal),CPLErr,(Cint,Ptr{Ptr{Cint}},Cint,Ptr{Ptr{Ptr{Cint}}},Ptr{Uint8},GDALProgressFunc,Ptr{Void}),nBands,papoSrcBands,nOverviews,papapoOverviewBands,pszResampling,pfnProgress,pProgressData)
end

function HFAAuxBuildOverviews(pszOvrFilename::Ptr{Uint8},poParentDS::Ptr{Cint},ppoDS::Ptr{Ptr{Cint}},nBands::Cint,panBandList::Ptr{Cint},nNewOverviews::Cint,panNewOverviewList::Ptr{Cint},pszResampling::Ptr{Uint8},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:HFAAuxBuildOverviews,libgdal),CPLErr,(Ptr{Uint8},Ptr{Cint},Ptr{Ptr{Cint}},Cint,Ptr{Cint},Cint,Ptr{Cint},Ptr{Uint8},GDALProgressFunc,Ptr{Void}),pszOvrFilename,poParentDS,ppoDS,nBands,panBandList,nNewOverviews,panNewOverviewList,pszResampling,pfnProgress,pProgressData)
end

function GTIFFBuildOverviews(pszFilename::Ptr{Uint8},nBands::Cint,papoBandList::Ptr{Ptr{Cint}},nOverviews::Cint,panOverviewList::Ptr{Cint},pszResampling::Ptr{Uint8},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GTIFFBuildOverviews,libgdal),CPLErr,(Ptr{Uint8},Cint,Ptr{Ptr{Cint}},Cint,Ptr{Cint},Ptr{Uint8},GDALProgressFunc,Ptr{Void}),pszFilename,nBands,papoBandList,nOverviews,panOverviewList,pszResampling,pfnProgress,pProgressData)
end

function GDALDefaultBuildOverviews(hSrcDS::Ptr{Cint},pszBasename::Ptr{Uint8},pszResampling::Ptr{Uint8},nOverviews::Cint,panOverviewList::Ptr{Cint},nBands::Cint,panBandList::Ptr{Cint},pfnProgress::GDALProgressFunc,pProgressData::Ptr{Void})
    ccall((:GDALDefaultBuildOverviews,libgdal),CPLErr,(Ptr{Cint},Ptr{Uint8},Ptr{Uint8},Cint,Ptr{Cint},Cint,Ptr{Cint},GDALProgressFunc,Ptr{Void}),hSrcDS,pszBasename,pszResampling,nOverviews,panOverviewList,nBands,panBandList,pfnProgress,pProgressData)
end

function GDALBandGetBestOverviewLevel(poBand::Ptr{Cint},arg1::Cint)
    ccall((:GDALBandGetBestOverviewLevel,libgdal),Cint,(Ptr{Cint},Cint),poBand,arg1)
end

function GDALOvLevelAdjust(nOvLevel::Cint,nXSize::Cint)
    ccall((:GDALOvLevelAdjust,libgdal),Cint,(Cint,Cint),nOvLevel,nXSize)
end

function GDALFindAssociatedAuxFile()
    ccall((:GDALFindAssociatedAuxFile,libgdal),Ptr{Cint},())
end

function GDALParseGMLCoverage(psTree::Ptr{CPLXMLNode},pnXSize::Ptr{Cint},pnYSize::Ptr{Cint},padfGeoTransform::Ptr{Cdouble},ppszProjection::Ptr{Ptr{Uint8}})
    ccall((:GDALParseGMLCoverage,libgdal),CPLErr,(Ptr{CPLXMLNode},Ptr{Cint},Ptr{Cint},Ptr{Cdouble},Ptr{Ptr{Uint8}}),psTree,pnXSize,pnYSize,padfGeoTransform,ppszProjection)
end

function GDALCheckDatasetDimensions(nXSize::Cint,nYSize::Cint)
    ccall((:GDALCheckDatasetDimensions,libgdal),Cint,(Cint,Cint),nXSize,nYSize)
end

function GDALCheckBandCount(nBands::Cint,bIsZeroAllowed::Cint)
    ccall((:GDALCheckBandCount,libgdal),Cint,(Cint,Cint),nBands,bIsZeroAllowed)
end

function GDALReadWorldFile2(pszBaseFilename::Ptr{Uint8},pszExtension::Ptr{Uint8},padfGeoTransform::Ptr{Cdouble},papszSiblingFiles::Ptr{Ptr{Uint8}},ppszWorldFileNameOut::Ptr{Ptr{Uint8}})
    ccall((:GDALReadWorldFile2,libgdal),Cint,(Ptr{Uint8},Ptr{Uint8},Ptr{Cdouble},Ptr{Ptr{Uint8}},Ptr{Ptr{Uint8}}),pszBaseFilename,pszExtension,padfGeoTransform,papszSiblingFiles,ppszWorldFileNameOut)
end

function GDALReadTabFile2(pszBaseFilename::Ptr{Uint8},padfGeoTransform::Ptr{Cdouble},ppszWKT::Ptr{Ptr{Uint8}},pnGCPCount::Ptr{Cint},ppasGCPs::Ptr{Ptr{GDAL_GCP}},papszSiblingFiles::Ptr{Ptr{Uint8}},ppszTabFileNameOut::Ptr{Ptr{Uint8}})
    ccall((:GDALReadTabFile2,libgdal),Cint,(Ptr{Uint8},Ptr{Cdouble},Ptr{Ptr{Uint8}},Ptr{Cint},Ptr{Ptr{GDAL_GCP}},Ptr{Ptr{Uint8}},Ptr{Ptr{Uint8}}),pszBaseFilename,padfGeoTransform,ppszWKT,pnGCPCount,ppasGCPs,papszSiblingFiles,ppszTabFileNameOut)
end

function GDALNullifyOpenDatasetsList()
    ccall((:GDALNullifyOpenDatasetsList,libgdal),Void,())
end

function GDALGetphDMMutex()
    ccall((:GDALGetphDMMutex,libgdal),Ptr{Ptr{Void}},())
end

function GDALGetphDLMutex()
    ccall((:GDALGetphDLMutex,libgdal),Ptr{Ptr{Void}},())
end

function GDALNullifyProxyPoolSingleton()
    ccall((:GDALNullifyProxyPoolSingleton,libgdal),Void,())
end

function GDALGetAPIPROXYDriver()
    ccall((:GDALGetAPIPROXYDriver,libgdal),Ptr{Cint},())
end

function GDALSetResponsiblePIDForCurrentThread(responsiblePID::GIntBig)
    ccall((:GDALSetResponsiblePIDForCurrentThread,libgdal),Void,(GIntBig,),responsiblePID)
end

function GDALGetResponsiblePIDForCurrentThread()
    ccall((:GDALGetResponsiblePIDForCurrentThread,libgdal),GIntBig,())
end

function GDALFindAssociatedFile()
    ccall((:GDALFindAssociatedFile,libgdal),Cint,())
end

function EXIFExtractMetadata(arg1::Ptr{Ptr{Uint8}})
    ccall((:EXIFExtractMetadata,libgdal),CPLErr,(Ptr{Ptr{Uint8}},),arg1)
end

function GDALSerializeGCPListToXML(psParentNode::Ptr{CPLXMLNode},pasGCPList::Ptr{GDAL_GCP},nGCPCount::Cint,pszGCPProjection::Ptr{Uint8})
    ccall((:GDALSerializeGCPListToXML,libgdal),Void,(Ptr{CPLXMLNode},Ptr{GDAL_GCP},Cint,Ptr{Uint8}),psParentNode,pasGCPList,nGCPCount,pszGCPProjection)
end

function GDALDeserializeGCPListFromXML(psGCPList::Ptr{CPLXMLNode},ppasGCPList::Ptr{Ptr{GDAL_GCP}},pnGCPCount::Ptr{Cint},ppszGCPProjection::Ptr{Ptr{Uint8}})
    ccall((:GDALDeserializeGCPListFromXML,libgdal),Void,(Ptr{CPLXMLNode},Ptr{Ptr{GDAL_GCP}},Ptr{Cint},Ptr{Ptr{Uint8}}),psGCPList,ppasGCPList,pnGCPCount,ppszGCPProjection)
end
