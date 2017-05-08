# Julia wrapper for header: /opt/local/include/ogr_api.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0


function GDALDummyProgress(arg1::Cdouble,arg2::Ptr{Uint8},arg3::Ptr{Void})
    ccall((:GDALDummyProgress,libogr),Cint,(Cdouble,Ptr{Uint8},Ptr{Void}),arg1,arg2,arg3)
end

function GDALTermProgress(arg1::Cdouble,arg2::Ptr{Uint8},arg3::Ptr{Void})
    ccall((:GDALTermProgress,libogr),Cint,(Cdouble,Ptr{Uint8},Ptr{Void}),arg1,arg2,arg3)
end

function GDALScaledProgress(arg1::Cdouble,arg2::Ptr{Uint8},arg3::Ptr{Void})
    ccall((:GDALScaledProgress,libogr),Cint,(Cdouble,Ptr{Uint8},Ptr{Void}),arg1,arg2,arg3)
end

function GDALCreateScaledProgress(arg1::Cdouble,arg2::Cdouble,arg3::GDALProgressFunc,arg4::Ptr{Void})
    ccall((:GDALCreateScaledProgress,libogr),Ptr{Void},(Cdouble,Cdouble,GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4)
end

function GDALDestroyScaledProgress(arg1::Ptr{Void})
    ccall((:GDALDestroyScaledProgress,libogr),Void,(Ptr{Void},),arg1)
end

function OGRMalloc(arg1::Csize_t)
    ccall((:OGRMalloc,libogr),Ptr{Void},(Csize_t,),arg1)
end

function OGRCalloc(arg1::Csize_t,arg2::Csize_t)
    ccall((:OGRCalloc,libogr),Ptr{Void},(Csize_t,Csize_t),arg1,arg2)
end

function OGRRealloc(arg1::Ptr{Void},arg2::Csize_t)
    ccall((:OGRRealloc,libogr),Ptr{Void},(Ptr{Void},Csize_t),arg1,arg2)
end

function OGRStrdup(arg1::Ptr{Uint8})
    ccall((:OGRStrdup,libogr),Ptr{Uint8},(Ptr{Uint8},),arg1)
end

function OGRFree(arg1::Ptr{Void})
    ccall((:OGRFree,libogr),Void,(Ptr{Void},),arg1)
end

function OGRGeometryTypeToName(eType::OGRwkbGeometryType)
    ccall((:OGRGeometryTypeToName,libogr),Ptr{Uint8},(OGRwkbGeometryType,),eType)
end

function OGRMergeGeometryTypes(eMain::OGRwkbGeometryType,eExtra::OGRwkbGeometryType)
    ccall((:OGRMergeGeometryTypes,libogr),OGRwkbGeometryType,(OGRwkbGeometryType,OGRwkbGeometryType),eMain,eExtra)
end

function OGRParseDate(pszInput::Ptr{Uint8},psOutput::Ptr{OGRField},nOptions::Cint)
    ccall((:OGRParseDate,libogr),Cint,(Ptr{Uint8},Ptr{OGRField},Cint),pszInput,psOutput,nOptions)
end

function GDALVersionInfo(arg1::Ptr{Uint8})
    ccall((:GDALVersionInfo,libogr),Ptr{Uint8},(Ptr{Uint8},),arg1)
end

function GDALCheckVersion(nVersionMajor::Cint,nVersionMinor::Cint,pszCallingComponentName::Ptr{Uint8})
    ccall((:GDALCheckVersion,libogr),Cint,(Cint,Cint,Ptr{Uint8}),nVersionMajor,nVersionMinor,pszCallingComponentName)
end

function OGR_G_CreateFromWkb(arg1::Ptr{Cuchar},arg2::OGRSpatialReferenceH,arg3::Ptr{OGRGeometryH},arg4::Cint)
    ccall((:OGR_G_CreateFromWkb,libogr),OGRErr,(Ptr{Cuchar},OGRSpatialReferenceH,Ptr{OGRGeometryH},Cint),arg1,arg2,arg3,arg4)
end

function OGR_G_CreateFromWkt(arg1::Ptr{Ptr{Uint8}},arg2::OGRSpatialReferenceH,arg3::Ptr{OGRGeometryH})
    ccall((:OGR_G_CreateFromWkt,libogr),OGRErr,(Ptr{Ptr{Uint8}},OGRSpatialReferenceH,Ptr{OGRGeometryH}),arg1,arg2,arg3)
end

function OGR_G_CreateFromFgf(arg1::Ptr{Cuchar},arg2::OGRSpatialReferenceH,arg3::Ptr{OGRGeometryH},arg4::Cint,arg5::Ptr{Cint})
    ccall((:OGR_G_CreateFromFgf,libogr),OGRErr,(Ptr{Cuchar},OGRSpatialReferenceH,Ptr{OGRGeometryH},Cint,Ptr{Cint}),arg1,arg2,arg3,arg4,arg5)
end

function OGR_G_DestroyGeometry(arg1::OGRGeometryH)
    ccall((:OGR_G_DestroyGeometry,libogr),Void,(OGRGeometryH,),arg1)
end

function OGR_G_CreateGeometry(arg1::OGRwkbGeometryType)
    ccall((:OGR_G_CreateGeometry,libogr),OGRGeometryH,(OGRwkbGeometryType,),arg1)
end

function OGR_G_ApproximateArcAngles(dfCenterX::Cdouble,dfCenterY::Cdouble,dfZ::Cdouble,dfPrimaryRadius::Cdouble,dfSecondaryAxis::Cdouble,dfRotation::Cdouble,dfStartAngle::Cdouble,dfEndAngle::Cdouble,dfMaxAngleStepSizeDegrees::Cdouble)
    ccall((:OGR_G_ApproximateArcAngles,libogr),OGRGeometryH,(Cdouble,Cdouble,Cdouble,Cdouble,Cdouble,Cdouble,Cdouble,Cdouble,Cdouble),dfCenterX,dfCenterY,dfZ,dfPrimaryRadius,dfSecondaryAxis,dfRotation,dfStartAngle,dfEndAngle,dfMaxAngleStepSizeDegrees)
end

function OGR_G_ForceToPolygon(arg1::OGRGeometryH)
    ccall((:OGR_G_ForceToPolygon,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_ForceToLineString(arg1::OGRGeometryH)
    ccall((:OGR_G_ForceToLineString,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_ForceToMultiPolygon(arg1::OGRGeometryH)
    ccall((:OGR_G_ForceToMultiPolygon,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_ForceToMultiPoint(arg1::OGRGeometryH)
    ccall((:OGR_G_ForceToMultiPoint,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_ForceToMultiLineString(arg1::OGRGeometryH)
    ccall((:OGR_G_ForceToMultiLineString,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_GetDimension(arg1::OGRGeometryH)
    ccall((:OGR_G_GetDimension,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_GetCoordinateDimension(arg1::OGRGeometryH)
    ccall((:OGR_G_GetCoordinateDimension,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_SetCoordinateDimension(arg1::OGRGeometryH,arg2::Cint)
    ccall((:OGR_G_SetCoordinateDimension,libogr),Void,(OGRGeometryH,Cint),arg1,arg2)
end

function OGR_G_Clone(arg1::OGRGeometryH)
    ccall((:OGR_G_Clone,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_GetEnvelope(arg1::OGRGeometryH,arg2::Ptr{OGREnvelope})
    ccall((:OGR_G_GetEnvelope,libogr),Void,(OGRGeometryH,Ptr{OGREnvelope}),arg1,arg2)
end

function OGR_G_GetEnvelope3D(arg1::OGRGeometryH,arg2::Ptr{OGREnvelope3D})
    ccall((:OGR_G_GetEnvelope3D,libogr),Void,(OGRGeometryH,Ptr{OGREnvelope3D}),arg1,arg2)
end

function OGR_G_ImportFromWkb(arg1::OGRGeometryH,arg2::Ptr{Cuchar},arg3::Cint)
    ccall((:OGR_G_ImportFromWkb,libogr),OGRErr,(OGRGeometryH,Ptr{Cuchar},Cint),arg1,arg2,arg3)
end

function OGR_G_ExportToWkb(arg1::OGRGeometryH,arg2::OGRwkbByteOrder,arg3::Ptr{Cuchar})
    ccall((:OGR_G_ExportToWkb,libogr),OGRErr,(OGRGeometryH,OGRwkbByteOrder,Ptr{Cuchar}),arg1,arg2,arg3)
end

function OGR_G_WkbSize(hGeom::OGRGeometryH)
    ccall((:OGR_G_WkbSize,libogr),Cint,(OGRGeometryH,),hGeom)
end

function OGR_G_ImportFromWkt(arg1::OGRGeometryH,arg2::Ptr{Ptr{Uint8}})
    ccall((:OGR_G_ImportFromWkt,libogr),OGRErr,(OGRGeometryH,Ptr{Ptr{Uint8}}),arg1,arg2)
end

function OGR_G_ExportToWkt(arg1::OGRGeometryH,arg2::Ptr{Ptr{Uint8}})
    ccall((:OGR_G_ExportToWkt,libogr),OGRErr,(OGRGeometryH,Ptr{Ptr{Uint8}}),arg1,arg2)
end

function OGR_G_GetGeometryType(arg1::OGRGeometryH)
    ccall((:OGR_G_GetGeometryType,libogr),OGRwkbGeometryType,(OGRGeometryH,),arg1)
end

function OGR_G_GetGeometryName(arg1::OGRGeometryH)
    ccall((:OGR_G_GetGeometryName,libogr),Ptr{Uint8},(OGRGeometryH,),arg1)
end

function OGR_G_DumpReadable(arg1::OGRGeometryH,arg2::Ptr{FILE},arg3::Ptr{Uint8})
    ccall((:OGR_G_DumpReadable,libogr),Void,(OGRGeometryH,Ptr{FILE},Ptr{Uint8}),arg1,arg2,arg3)
end

function OGR_G_FlattenTo2D(arg1::OGRGeometryH)
    ccall((:OGR_G_FlattenTo2D,libogr),Void,(OGRGeometryH,),arg1)
end

function OGR_G_CloseRings(arg1::OGRGeometryH)
    ccall((:OGR_G_CloseRings,libogr),Void,(OGRGeometryH,),arg1)
end

function OGR_G_CreateFromGML(arg1::Ptr{Uint8})
    ccall((:OGR_G_CreateFromGML,libogr),OGRGeometryH,(Ptr{Uint8},),arg1)
end

function OGR_G_ExportToGML(arg1::OGRGeometryH)
    ccall((:OGR_G_ExportToGML,libogr),Ptr{Uint8},(OGRGeometryH,),arg1)
end

function OGR_G_ExportToGMLEx(arg1::OGRGeometryH,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:OGR_G_ExportToGMLEx,libogr),Ptr{Uint8},(OGRGeometryH,Ptr{Ptr{Uint8}}),arg1,papszOptions)
end

function OGR_G_ExportToKML(arg1::OGRGeometryH,pszAltitudeMode::Ptr{Uint8})
    ccall((:OGR_G_ExportToKML,libogr),Ptr{Uint8},(OGRGeometryH,Ptr{Uint8}),arg1,pszAltitudeMode)
end

function OGR_G_ExportToJson(arg1::OGRGeometryH)
    ccall((:OGR_G_ExportToJson,libogr),Ptr{Uint8},(OGRGeometryH,),arg1)
end

function OGR_G_ExportToJsonEx(arg1::OGRGeometryH,papszOptions::Ptr{Ptr{Uint8}})
    ccall((:OGR_G_ExportToJsonEx,libogr),Ptr{Uint8},(OGRGeometryH,Ptr{Ptr{Uint8}}),arg1,papszOptions)
end

function OGR_G_CreateGeometryFromJson(arg1::Ptr{Uint8})
    ccall((:OGR_G_CreateGeometryFromJson,libogr),OGRGeometryH,(Ptr{Uint8},),arg1)
end

function OGR_G_AssignSpatialReference(arg1::OGRGeometryH,arg2::OGRSpatialReferenceH)
    ccall((:OGR_G_AssignSpatialReference,libogr),Void,(OGRGeometryH,OGRSpatialReferenceH),arg1,arg2)
end

function OGR_G_GetSpatialReference(arg1::OGRGeometryH)
    ccall((:OGR_G_GetSpatialReference,libogr),OGRSpatialReferenceH,(OGRGeometryH,),arg1)
end

function OGR_G_Transform(arg1::OGRGeometryH,arg2::OGRCoordinateTransformationH)
    ccall((:OGR_G_Transform,libogr),OGRErr,(OGRGeometryH,OGRCoordinateTransformationH),arg1,arg2)
end

function OGR_G_TransformTo(arg1::OGRGeometryH,arg2::OGRSpatialReferenceH)
    ccall((:OGR_G_TransformTo,libogr),OGRErr,(OGRGeometryH,OGRSpatialReferenceH),arg1,arg2)
end

function OGR_G_Simplify(hThis::OGRGeometryH,tolerance::Cdouble)
    ccall((:OGR_G_Simplify,libogr),OGRGeometryH,(OGRGeometryH,Cdouble),hThis,tolerance)
end

function OGR_G_SimplifyPreserveTopology(hThis::OGRGeometryH,tolerance::Cdouble)
    ccall((:OGR_G_SimplifyPreserveTopology,libogr),OGRGeometryH,(OGRGeometryH,Cdouble),hThis,tolerance)
end

function OGR_G_Segmentize(hGeom::OGRGeometryH,dfMaxLength::Cdouble)
    ccall((:OGR_G_Segmentize,libogr),Void,(OGRGeometryH,Cdouble),hGeom,dfMaxLength)
end

function OGR_G_Intersects(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Intersects,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Equals(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Equals,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Disjoint(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Disjoint,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Touches(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Touches,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Crosses(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Crosses,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Within(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Within,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Contains(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Contains,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Overlaps(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Overlaps,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Boundary(arg1::OGRGeometryH)
    ccall((:OGR_G_Boundary,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_ConvexHull(arg1::OGRGeometryH)
    ccall((:OGR_G_ConvexHull,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_Buffer(arg1::OGRGeometryH,arg2::Cdouble,arg3::Cint)
    ccall((:OGR_G_Buffer,libogr),OGRGeometryH,(OGRGeometryH,Cdouble,Cint),arg1,arg2,arg3)
end

function OGR_G_Intersection(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Intersection,libogr),OGRGeometryH,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Union(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Union,libogr),OGRGeometryH,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_UnionCascaded(arg1::OGRGeometryH)
    ccall((:OGR_G_UnionCascaded,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_PointOnSurface(arg1::OGRGeometryH)
    ccall((:OGR_G_PointOnSurface,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_Difference(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Difference,libogr),OGRGeometryH,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_SymDifference(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_SymDifference,libogr),OGRGeometryH,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Distance(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Distance,libogr),Cdouble,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Length(arg1::OGRGeometryH)
    ccall((:OGR_G_Length,libogr),Cdouble,(OGRGeometryH,),arg1)
end

function OGR_G_Area(arg1::OGRGeometryH)
    ccall((:OGR_G_Area,libogr),Cdouble,(OGRGeometryH,),arg1)
end

function OGR_G_Centroid(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Centroid,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Empty(arg1::OGRGeometryH)
    ccall((:OGR_G_Empty,libogr),Void,(OGRGeometryH,),arg1)
end

function OGR_G_IsEmpty(arg1::OGRGeometryH)
    ccall((:OGR_G_IsEmpty,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_IsValid(arg1::OGRGeometryH)
    ccall((:OGR_G_IsValid,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_IsSimple(arg1::OGRGeometryH)
    ccall((:OGR_G_IsSimple,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_IsRing(arg1::OGRGeometryH)
    ccall((:OGR_G_IsRing,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_Polygonize(arg1::OGRGeometryH)
    ccall((:OGR_G_Polygonize,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_Intersect(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Intersect,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_Equal(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_Equal,libogr),Cint,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_SymmetricDifference(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_SymmetricDifference,libogr),OGRGeometryH,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_GetArea(arg1::OGRGeometryH)
    ccall((:OGR_G_GetArea,libogr),Cdouble,(OGRGeometryH,),arg1)
end

function OGR_G_GetBoundary(arg1::OGRGeometryH)
    ccall((:OGR_G_GetBoundary,libogr),OGRGeometryH,(OGRGeometryH,),arg1)
end

function OGR_G_GetPointCount(arg1::OGRGeometryH)
    ccall((:OGR_G_GetPointCount,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_GetPoints(hGeom::OGRGeometryH,pabyX::Ptr{Void},nXStride::Cint,pabyY::Ptr{Void},nYStride::Cint,pabyZ::Ptr{Void},nZStride::Cint)
    ccall((:OGR_G_GetPoints,libogr),Cint,(OGRGeometryH,Ptr{Void},Cint,Ptr{Void},Cint,Ptr{Void},Cint),hGeom,pabyX,nXStride,pabyY,nYStride,pabyZ,nZStride)
end

function OGR_G_GetX(arg1::OGRGeometryH,arg2::Cint)
    ccall((:OGR_G_GetX,libogr),Cdouble,(OGRGeometryH,Cint),arg1,arg2)
end

function OGR_G_GetY(arg1::OGRGeometryH,arg2::Cint)
    ccall((:OGR_G_GetY,libogr),Cdouble,(OGRGeometryH,Cint),arg1,arg2)
end

function OGR_G_GetZ(arg1::OGRGeometryH,arg2::Cint)
    ccall((:OGR_G_GetZ,libogr),Cdouble,(OGRGeometryH,Cint),arg1,arg2)
end

function OGR_G_GetPoint(arg1::OGRGeometryH,iPoint::Cint,arg2::Ptr{Cdouble},arg3::Ptr{Cdouble},arg4::Ptr{Cdouble})
    ccall((:OGR_G_GetPoint,libogr),Void,(OGRGeometryH,Cint,Ptr{Cdouble},Ptr{Cdouble},Ptr{Cdouble}),arg1,iPoint,arg2,arg3,arg4)
end

function OGR_G_SetPointCount(hGeom::OGRGeometryH,nNewPointCount::Cint)
    ccall((:OGR_G_SetPointCount,libogr),Void,(OGRGeometryH,Cint),hGeom,nNewPointCount)
end

function OGR_G_SetPoint(arg1::OGRGeometryH,iPoint::Cint,arg2::Cdouble,arg3::Cdouble,arg4::Cdouble)
    ccall((:OGR_G_SetPoint,libogr),Void,(OGRGeometryH,Cint,Cdouble,Cdouble,Cdouble),arg1,iPoint,arg2,arg3,arg4)
end

function OGR_G_SetPoint_2D(arg1::OGRGeometryH,iPoint::Cint,arg2::Cdouble,arg3::Cdouble)
    ccall((:OGR_G_SetPoint_2D,libogr),Void,(OGRGeometryH,Cint,Cdouble,Cdouble),arg1,iPoint,arg2,arg3)
end

function OGR_G_AddPoint(arg1::OGRGeometryH,arg2::Cdouble,arg3::Cdouble,arg4::Cdouble)
    ccall((:OGR_G_AddPoint,libogr),Void,(OGRGeometryH,Cdouble,Cdouble,Cdouble),arg1,arg2,arg3,arg4)
end

function OGR_G_AddPoint_2D(arg1::OGRGeometryH,arg2::Cdouble,arg3::Cdouble)
    ccall((:OGR_G_AddPoint_2D,libogr),Void,(OGRGeometryH,Cdouble,Cdouble),arg1,arg2,arg3)
end

function OGR_G_SetPoints(hGeom::OGRGeometryH,nPointsIn::Cint,pabyX::Ptr{Void},nXStride::Cint,pabyY::Ptr{Void},nYStride::Cint,pabyZ::Ptr{Void},nZStride::Cint)
    ccall((:OGR_G_SetPoints,libogr),Void,(OGRGeometryH,Cint,Ptr{Void},Cint,Ptr{Void},Cint,Ptr{Void},Cint),hGeom,nPointsIn,pabyX,nXStride,pabyY,nYStride,pabyZ,nZStride)
end

function OGR_G_GetGeometryCount(arg1::OGRGeometryH)
    ccall((:OGR_G_GetGeometryCount,libogr),Cint,(OGRGeometryH,),arg1)
end

function OGR_G_GetGeometryRef(arg1::OGRGeometryH,arg2::Cint)
    ccall((:OGR_G_GetGeometryRef,libogr),OGRGeometryH,(OGRGeometryH,Cint),arg1,arg2)
end

function OGR_G_AddGeometry(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_AddGeometry,libogr),OGRErr,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_AddGeometryDirectly(arg1::OGRGeometryH,arg2::OGRGeometryH)
    ccall((:OGR_G_AddGeometryDirectly,libogr),OGRErr,(OGRGeometryH,OGRGeometryH),arg1,arg2)
end

function OGR_G_RemoveGeometry(arg1::OGRGeometryH,arg2::Cint,arg3::Cint)
    ccall((:OGR_G_RemoveGeometry,libogr),OGRErr,(OGRGeometryH,Cint,Cint),arg1,arg2,arg3)
end

function OGRBuildPolygonFromEdges(hLinesAsCollection::OGRGeometryH,bBestEffort::Cint,bAutoClose::Cint,dfTolerance::Cdouble,peErr::Ptr{OGRErr})
    ccall((:OGRBuildPolygonFromEdges,libogr),OGRGeometryH,(OGRGeometryH,Cint,Cint,Cdouble,Ptr{OGRErr}),hLinesAsCollection,bBestEffort,bAutoClose,dfTolerance,peErr)
end

function OGRSetGenerate_DB2_V72_BYTE_ORDER(bGenerate_DB2_V72_BYTE_ORDER::Cint)
    ccall((:OGRSetGenerate_DB2_V72_BYTE_ORDER,libogr),OGRErr,(Cint,),bGenerate_DB2_V72_BYTE_ORDER)
end

function OGRGetGenerate_DB2_V72_BYTE_ORDER()
    ccall((:OGRGetGenerate_DB2_V72_BYTE_ORDER,libogr),Cint,())
end

function OGR_Fld_Create(arg1::Ptr{Uint8},arg2::OGRFieldType)
    ccall((:OGR_Fld_Create,libogr),OGRFieldDefnH,(Ptr{Uint8},OGRFieldType),arg1,arg2)
end

function OGR_Fld_Destroy(arg1::OGRFieldDefnH)
    ccall((:OGR_Fld_Destroy,libogr),Void,(OGRFieldDefnH,),arg1)
end

function OGR_Fld_SetName(arg1::OGRFieldDefnH,arg2::Ptr{Uint8})
    ccall((:OGR_Fld_SetName,libogr),Void,(OGRFieldDefnH,Ptr{Uint8}),arg1,arg2)
end

function OGR_Fld_GetNameRef(arg1::OGRFieldDefnH)
    ccall((:OGR_Fld_GetNameRef,libogr),Ptr{Uint8},(OGRFieldDefnH,),arg1)
end

function OGR_Fld_GetType(arg1::OGRFieldDefnH)
    ccall((:OGR_Fld_GetType,libogr),OGRFieldType,(OGRFieldDefnH,),arg1)
end

function OGR_Fld_SetType(arg1::OGRFieldDefnH,arg2::OGRFieldType)
    ccall((:OGR_Fld_SetType,libogr),Void,(OGRFieldDefnH,OGRFieldType),arg1,arg2)
end

function OGR_Fld_GetJustify(arg1::OGRFieldDefnH)
    ccall((:OGR_Fld_GetJustify,libogr),OGRJustification,(OGRFieldDefnH,),arg1)
end

function OGR_Fld_SetJustify(arg1::OGRFieldDefnH,arg2::OGRJustification)
    ccall((:OGR_Fld_SetJustify,libogr),Void,(OGRFieldDefnH,OGRJustification),arg1,arg2)
end

function OGR_Fld_GetWidth(arg1::OGRFieldDefnH)
    ccall((:OGR_Fld_GetWidth,libogr),Cint,(OGRFieldDefnH,),arg1)
end

function OGR_Fld_SetWidth(arg1::OGRFieldDefnH,arg2::Cint)
    ccall((:OGR_Fld_SetWidth,libogr),Void,(OGRFieldDefnH,Cint),arg1,arg2)
end

function OGR_Fld_GetPrecision(arg1::OGRFieldDefnH)
    ccall((:OGR_Fld_GetPrecision,libogr),Cint,(OGRFieldDefnH,),arg1)
end

function OGR_Fld_SetPrecision(arg1::OGRFieldDefnH,arg2::Cint)
    ccall((:OGR_Fld_SetPrecision,libogr),Void,(OGRFieldDefnH,Cint),arg1,arg2)
end

function OGR_Fld_Set(arg1::OGRFieldDefnH,arg2::Ptr{Uint8},arg3::OGRFieldType,arg4::Cint,arg5::Cint,arg6::OGRJustification)
    ccall((:OGR_Fld_Set,libogr),Void,(OGRFieldDefnH,Ptr{Uint8},OGRFieldType,Cint,Cint,OGRJustification),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_Fld_IsIgnored(hDefn::OGRFieldDefnH)
    ccall((:OGR_Fld_IsIgnored,libogr),Cint,(OGRFieldDefnH,),hDefn)
end

function OGR_Fld_SetIgnored(hDefn::OGRFieldDefnH,arg1::Cint)
    ccall((:OGR_Fld_SetIgnored,libogr),Void,(OGRFieldDefnH,Cint),hDefn,arg1)
end

function OGR_GetFieldTypeName(arg1::OGRFieldType)
    ccall((:OGR_GetFieldTypeName,libogr),Ptr{Uint8},(OGRFieldType,),arg1)
end

function OGR_GFld_Create(arg1::Ptr{Uint8},arg2::OGRwkbGeometryType)
    ccall((:OGR_GFld_Create,libogr),OGRGeomFieldDefnH,(Ptr{Uint8},OGRwkbGeometryType),arg1,arg2)
end

function OGR_GFld_Destroy(arg1::OGRGeomFieldDefnH)
    ccall((:OGR_GFld_Destroy,libogr),Void,(OGRGeomFieldDefnH,),arg1)
end

function OGR_GFld_SetName(arg1::OGRGeomFieldDefnH,arg2::Ptr{Uint8})
    ccall((:OGR_GFld_SetName,libogr),Void,(OGRGeomFieldDefnH,Ptr{Uint8}),arg1,arg2)
end

function OGR_GFld_GetNameRef(arg1::OGRGeomFieldDefnH)
    ccall((:OGR_GFld_GetNameRef,libogr),Ptr{Uint8},(OGRGeomFieldDefnH,),arg1)
end

function OGR_GFld_GetType(arg1::OGRGeomFieldDefnH)
    ccall((:OGR_GFld_GetType,libogr),OGRwkbGeometryType,(OGRGeomFieldDefnH,),arg1)
end

function OGR_GFld_SetType(arg1::OGRGeomFieldDefnH,arg2::OGRwkbGeometryType)
    ccall((:OGR_GFld_SetType,libogr),Void,(OGRGeomFieldDefnH,OGRwkbGeometryType),arg1,arg2)
end

function OGR_GFld_GetSpatialRef(arg1::OGRGeomFieldDefnH)
    ccall((:OGR_GFld_GetSpatialRef,libogr),OGRSpatialReferenceH,(OGRGeomFieldDefnH,),arg1)
end

function OGR_GFld_SetSpatialRef(arg1::OGRGeomFieldDefnH,hSRS::OGRSpatialReferenceH)
    ccall((:OGR_GFld_SetSpatialRef,libogr),Void,(OGRGeomFieldDefnH,OGRSpatialReferenceH),arg1,hSRS)
end

function OGR_GFld_IsIgnored(hDefn::OGRGeomFieldDefnH)
    ccall((:OGR_GFld_IsIgnored,libogr),Cint,(OGRGeomFieldDefnH,),hDefn)
end

function OGR_GFld_SetIgnored(hDefn::OGRGeomFieldDefnH,arg1::Cint)
    ccall((:OGR_GFld_SetIgnored,libogr),Void,(OGRGeomFieldDefnH,Cint),hDefn,arg1)
end

function OGR_FD_Create(arg1::Ptr{Uint8})
    ccall((:OGR_FD_Create,libogr),OGRFeatureDefnH,(Ptr{Uint8},),arg1)
end

function OGR_FD_Destroy(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_Destroy,libogr),Void,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_Release(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_Release,libogr),Void,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_GetName(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_GetName,libogr),Ptr{Uint8},(OGRFeatureDefnH,),arg1)
end

function OGR_FD_GetFieldCount(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_GetFieldCount,libogr),Cint,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_GetFieldDefn(arg1::OGRFeatureDefnH,arg2::Cint)
    ccall((:OGR_FD_GetFieldDefn,libogr),OGRFieldDefnH,(OGRFeatureDefnH,Cint),arg1,arg2)
end

function OGR_FD_GetFieldIndex(arg1::OGRFeatureDefnH,arg2::Ptr{Uint8})
    ccall((:OGR_FD_GetFieldIndex,libogr),Cint,(OGRFeatureDefnH,Ptr{Uint8}),arg1,arg2)
end

function OGR_FD_AddFieldDefn(arg1::OGRFeatureDefnH,arg2::OGRFieldDefnH)
    ccall((:OGR_FD_AddFieldDefn,libogr),Void,(OGRFeatureDefnH,OGRFieldDefnH),arg1,arg2)
end

function OGR_FD_DeleteFieldDefn(hDefn::OGRFeatureDefnH,iField::Cint)
    ccall((:OGR_FD_DeleteFieldDefn,libogr),OGRErr,(OGRFeatureDefnH,Cint),hDefn,iField)
end

function OGR_FD_ReorderFieldDefns(hDefn::OGRFeatureDefnH,panMap::Ptr{Cint})
    ccall((:OGR_FD_ReorderFieldDefns,libogr),OGRErr,(OGRFeatureDefnH,Ptr{Cint}),hDefn,panMap)
end

function OGR_FD_GetGeomType(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_GetGeomType,libogr),OGRwkbGeometryType,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_SetGeomType(arg1::OGRFeatureDefnH,arg2::OGRwkbGeometryType)
    ccall((:OGR_FD_SetGeomType,libogr),Void,(OGRFeatureDefnH,OGRwkbGeometryType),arg1,arg2)
end

function OGR_FD_IsGeometryIgnored(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_IsGeometryIgnored,libogr),Cint,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_SetGeometryIgnored(arg1::OGRFeatureDefnH,arg2::Cint)
    ccall((:OGR_FD_SetGeometryIgnored,libogr),Void,(OGRFeatureDefnH,Cint),arg1,arg2)
end

function OGR_FD_IsStyleIgnored(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_IsStyleIgnored,libogr),Cint,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_SetStyleIgnored(arg1::OGRFeatureDefnH,arg2::Cint)
    ccall((:OGR_FD_SetStyleIgnored,libogr),Void,(OGRFeatureDefnH,Cint),arg1,arg2)
end

function OGR_FD_Reference(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_Reference,libogr),Cint,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_Dereference(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_Dereference,libogr),Cint,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_GetReferenceCount(arg1::OGRFeatureDefnH)
    ccall((:OGR_FD_GetReferenceCount,libogr),Cint,(OGRFeatureDefnH,),arg1)
end

function OGR_FD_GetGeomFieldCount(hFDefn::OGRFeatureDefnH)
    ccall((:OGR_FD_GetGeomFieldCount,libogr),Cint,(OGRFeatureDefnH,),hFDefn)
end

function OGR_FD_GetGeomFieldDefn(hFDefn::OGRFeatureDefnH,i::Cint)
    ccall((:OGR_FD_GetGeomFieldDefn,libogr),OGRGeomFieldDefnH,(OGRFeatureDefnH,Cint),hFDefn,i)
end

function OGR_FD_GetGeomFieldIndex(hFDefn::OGRFeatureDefnH,pszName::Ptr{Uint8})
    ccall((:OGR_FD_GetGeomFieldIndex,libogr),Cint,(OGRFeatureDefnH,Ptr{Uint8}),hFDefn,pszName)
end

function OGR_FD_AddGeomFieldDefn(hFDefn::OGRFeatureDefnH,hGFldDefn::OGRGeomFieldDefnH)
    ccall((:OGR_FD_AddGeomFieldDefn,libogr),Void,(OGRFeatureDefnH,OGRGeomFieldDefnH),hFDefn,hGFldDefn)
end

function OGR_FD_DeleteGeomFieldDefn(hFDefn::OGRFeatureDefnH,iGeomField::Cint)
    ccall((:OGR_FD_DeleteGeomFieldDefn,libogr),OGRErr,(OGRFeatureDefnH,Cint),hFDefn,iGeomField)
end

function OGR_FD_IsSame(hFDefn::OGRFeatureDefnH,hOtherFDefn::OGRFeatureDefnH)
    ccall((:OGR_FD_IsSame,libogr),Cint,(OGRFeatureDefnH,OGRFeatureDefnH),hFDefn,hOtherFDefn)
end

function OGR_F_Create(arg1::OGRFeatureDefnH)
    ccall((:OGR_F_Create,libogr),OGRFeatureH,(OGRFeatureDefnH,),arg1)
end

function OGR_F_Destroy(arg1::OGRFeatureH)
    ccall((:OGR_F_Destroy,libogr),Void,(OGRFeatureH,),arg1)
end

function OGR_F_GetDefnRef(arg1::OGRFeatureH)
    ccall((:OGR_F_GetDefnRef,libogr),OGRFeatureDefnH,(OGRFeatureH,),arg1)
end

function OGR_F_SetGeometryDirectly(arg1::OGRFeatureH,arg2::OGRGeometryH)
    ccall((:OGR_F_SetGeometryDirectly,libogr),OGRErr,(OGRFeatureH,OGRGeometryH),arg1,arg2)
end

function OGR_F_SetGeometry(arg1::OGRFeatureH,arg2::OGRGeometryH)
    ccall((:OGR_F_SetGeometry,libogr),OGRErr,(OGRFeatureH,OGRGeometryH),arg1,arg2)
end

function OGR_F_GetGeometryRef(arg1::OGRFeatureH)
    ccall((:OGR_F_GetGeometryRef,libogr),OGRGeometryH,(OGRFeatureH,),arg1)
end

function OGR_F_StealGeometry(arg1::OGRFeatureH)
    ccall((:OGR_F_StealGeometry,libogr),OGRGeometryH,(OGRFeatureH,),arg1)
end

function OGR_F_Clone(arg1::OGRFeatureH)
    ccall((:OGR_F_Clone,libogr),OGRFeatureH,(OGRFeatureH,),arg1)
end

function OGR_F_Equal(arg1::OGRFeatureH,arg2::OGRFeatureH)
    ccall((:OGR_F_Equal,libogr),Cint,(OGRFeatureH,OGRFeatureH),arg1,arg2)
end

function OGR_F_GetFieldCount(arg1::OGRFeatureH)
    ccall((:OGR_F_GetFieldCount,libogr),Cint,(OGRFeatureH,),arg1)
end

function OGR_F_GetFieldDefnRef(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_GetFieldDefnRef,libogr),OGRFieldDefnH,(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetFieldIndex(arg1::OGRFeatureH,arg2::Ptr{Uint8})
    ccall((:OGR_F_GetFieldIndex,libogr),Cint,(OGRFeatureH,Ptr{Uint8}),arg1,arg2)
end

function OGR_F_IsFieldSet(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_IsFieldSet,libogr),Cint,(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_UnsetField(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_UnsetField,libogr),Void,(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetRawFieldRef(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_GetRawFieldRef,libogr),Ptr{OGRField},(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetFieldAsInteger(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_GetFieldAsInteger,libogr),Cint,(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetFieldAsDouble(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_GetFieldAsDouble,libogr),Cdouble,(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetFieldAsString(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_GetFieldAsString,libogr),Ptr{Uint8},(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetFieldAsIntegerList(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{Cint})
    ccall((:OGR_F_GetFieldAsIntegerList,libogr),Ptr{Cint},(OGRFeatureH,Cint,Ptr{Cint}),arg1,arg2,arg3)
end

function OGR_F_GetFieldAsDoubleList(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{Cint})
    ccall((:OGR_F_GetFieldAsDoubleList,libogr),Ptr{Cdouble},(OGRFeatureH,Cint,Ptr{Cint}),arg1,arg2,arg3)
end

function OGR_F_GetFieldAsStringList(arg1::OGRFeatureH,arg2::Cint)
    ccall((:OGR_F_GetFieldAsStringList,libogr),Ptr{Ptr{Uint8}},(OGRFeatureH,Cint),arg1,arg2)
end

function OGR_F_GetFieldAsBinary(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{Cint})
    ccall((:OGR_F_GetFieldAsBinary,libogr),Ptr{GByte},(OGRFeatureH,Cint,Ptr{Cint}),arg1,arg2,arg3)
end

function OGR_F_GetFieldAsDateTime(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{Cint},arg4::Ptr{Cint},arg5::Ptr{Cint},arg6::Ptr{Cint},arg7::Ptr{Cint},arg8::Ptr{Cint},arg9::Ptr{Cint})
    ccall((:OGR_F_GetFieldAsDateTime,libogr),Cint,(OGRFeatureH,Cint,Ptr{Cint},Ptr{Cint},Ptr{Cint},Ptr{Cint},Ptr{Cint},Ptr{Cint},Ptr{Cint}),arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
end

function OGR_F_SetFieldInteger(arg1::OGRFeatureH,arg2::Cint,arg3::Cint)
    ccall((:OGR_F_SetFieldInteger,libogr),Void,(OGRFeatureH,Cint,Cint),arg1,arg2,arg3)
end

function OGR_F_SetFieldDouble(arg1::OGRFeatureH,arg2::Cint,arg3::Cdouble)
    ccall((:OGR_F_SetFieldDouble,libogr),Void,(OGRFeatureH,Cint,Cdouble),arg1,arg2,arg3)
end

function OGR_F_SetFieldString(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{Uint8})
    ccall((:OGR_F_SetFieldString,libogr),Void,(OGRFeatureH,Cint,Ptr{Uint8}),arg1,arg2,arg3)
end

function OGR_F_SetFieldIntegerList(arg1::OGRFeatureH,arg2::Cint,arg3::Cint,arg4::Ptr{Cint})
    ccall((:OGR_F_SetFieldIntegerList,libogr),Void,(OGRFeatureH,Cint,Cint,Ptr{Cint}),arg1,arg2,arg3,arg4)
end

function OGR_F_SetFieldDoubleList(arg1::OGRFeatureH,arg2::Cint,arg3::Cint,arg4::Ptr{Cdouble})
    ccall((:OGR_F_SetFieldDoubleList,libogr),Void,(OGRFeatureH,Cint,Cint,Ptr{Cdouble}),arg1,arg2,arg3,arg4)
end

function OGR_F_SetFieldStringList(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{Ptr{Uint8}})
    ccall((:OGR_F_SetFieldStringList,libogr),Void,(OGRFeatureH,Cint,Ptr{Ptr{Uint8}}),arg1,arg2,arg3)
end

function OGR_F_SetFieldRaw(arg1::OGRFeatureH,arg2::Cint,arg3::Ptr{OGRField})
    ccall((:OGR_F_SetFieldRaw,libogr),Void,(OGRFeatureH,Cint,Ptr{OGRField}),arg1,arg2,arg3)
end

function OGR_F_SetFieldBinary(arg1::OGRFeatureH,arg2::Cint,arg3::Cint,arg4::Ptr{GByte})
    ccall((:OGR_F_SetFieldBinary,libogr),Void,(OGRFeatureH,Cint,Cint,Ptr{GByte}),arg1,arg2,arg3,arg4)
end

function OGR_F_SetFieldDateTime(arg1::OGRFeatureH,arg2::Cint,arg3::Cint,arg4::Cint,arg5::Cint,arg6::Cint,arg7::Cint,arg8::Cint,arg9::Cint)
    ccall((:OGR_F_SetFieldDateTime,libogr),Void,(OGRFeatureH,Cint,Cint,Cint,Cint,Cint,Cint,Cint,Cint),arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
end

function OGR_F_GetGeomFieldCount(hFeat::OGRFeatureH)
    ccall((:OGR_F_GetGeomFieldCount,libogr),Cint,(OGRFeatureH,),hFeat)
end

function OGR_F_GetGeomFieldDefnRef(hFeat::OGRFeatureH,iField::Cint)
    ccall((:OGR_F_GetGeomFieldDefnRef,libogr),OGRGeomFieldDefnH,(OGRFeatureH,Cint),hFeat,iField)
end

function OGR_F_GetGeomFieldIndex(hFeat::OGRFeatureH,pszName::Ptr{Uint8})
    ccall((:OGR_F_GetGeomFieldIndex,libogr),Cint,(OGRFeatureH,Ptr{Uint8}),hFeat,pszName)
end

function OGR_F_GetGeomFieldRef(hFeat::OGRFeatureH,iField::Cint)
    ccall((:OGR_F_GetGeomFieldRef,libogr),OGRGeometryH,(OGRFeatureH,Cint),hFeat,iField)
end

function OGR_F_SetGeomFieldDirectly(hFeat::OGRFeatureH,iField::Cint,hGeom::OGRGeometryH)
    ccall((:OGR_F_SetGeomFieldDirectly,libogr),OGRErr,(OGRFeatureH,Cint,OGRGeometryH),hFeat,iField,hGeom)
end

function OGR_F_SetGeomField(hFeat::OGRFeatureH,iField::Cint,hGeom::OGRGeometryH)
    ccall((:OGR_F_SetGeomField,libogr),OGRErr,(OGRFeatureH,Cint,OGRGeometryH),hFeat,iField,hGeom)
end

function OGR_F_GetFID(arg1::OGRFeatureH)
    ccall((:OGR_F_GetFID,libogr),Clong,(OGRFeatureH,),arg1)
end

function OGR_F_SetFID(arg1::OGRFeatureH,arg2::Clong)
    ccall((:OGR_F_SetFID,libogr),OGRErr,(OGRFeatureH,Clong),arg1,arg2)
end

function OGR_F_DumpReadable(arg1::OGRFeatureH,arg2::Ptr{FILE})
    ccall((:OGR_F_DumpReadable,libogr),Void,(OGRFeatureH,Ptr{FILE}),arg1,arg2)
end

function OGR_F_SetFrom(arg1::OGRFeatureH,arg2::OGRFeatureH,arg3::Cint)
    ccall((:OGR_F_SetFrom,libogr),OGRErr,(OGRFeatureH,OGRFeatureH,Cint),arg1,arg2,arg3)
end

function OGR_F_SetFromWithMap(arg1::OGRFeatureH,arg2::OGRFeatureH,arg3::Cint,arg4::Ptr{Cint})
    ccall((:OGR_F_SetFromWithMap,libogr),OGRErr,(OGRFeatureH,OGRFeatureH,Cint,Ptr{Cint}),arg1,arg2,arg3,arg4)
end

function OGR_F_GetStyleString(arg1::OGRFeatureH)
    ccall((:OGR_F_GetStyleString,libogr),Ptr{Uint8},(OGRFeatureH,),arg1)
end

function OGR_F_SetStyleString(arg1::OGRFeatureH,arg2::Ptr{Uint8})
    ccall((:OGR_F_SetStyleString,libogr),Void,(OGRFeatureH,Ptr{Uint8}),arg1,arg2)
end

function OGR_F_SetStyleStringDirectly(arg1::OGRFeatureH,arg2::Ptr{Uint8})
    ccall((:OGR_F_SetStyleStringDirectly,libogr),Void,(OGRFeatureH,Ptr{Uint8}),arg1,arg2)
end

function OGR_F_GetStyleTable(arg1::OGRFeatureH)
    ccall((:OGR_F_GetStyleTable,libogr),OGRStyleTableH,(OGRFeatureH,),arg1)
end

function OGR_F_SetStyleTableDirectly(arg1::OGRFeatureH,arg2::OGRStyleTableH)
    ccall((:OGR_F_SetStyleTableDirectly,libogr),Void,(OGRFeatureH,OGRStyleTableH),arg1,arg2)
end

function OGR_F_SetStyleTable(arg1::OGRFeatureH,arg2::OGRStyleTableH)
    ccall((:OGR_F_SetStyleTable,libogr),Void,(OGRFeatureH,OGRStyleTableH),arg1,arg2)
end

function OGR_L_GetName(arg1::OGRLayerH)
    ccall((:OGR_L_GetName,libogr),Ptr{Uint8},(OGRLayerH,),arg1)
end

function OGR_L_GetGeomType(arg1::OGRLayerH)
    ccall((:OGR_L_GetGeomType,libogr),OGRwkbGeometryType,(OGRLayerH,),arg1)
end

function OGR_L_GetSpatialFilter(arg1::OGRLayerH)
    ccall((:OGR_L_GetSpatialFilter,libogr),OGRGeometryH,(OGRLayerH,),arg1)
end

function OGR_L_SetSpatialFilter(arg1::OGRLayerH,arg2::OGRGeometryH)
    ccall((:OGR_L_SetSpatialFilter,libogr),Void,(OGRLayerH,OGRGeometryH),arg1,arg2)
end

function OGR_L_SetSpatialFilterRect(arg1::OGRLayerH,arg2::Cdouble,arg3::Cdouble,arg4::Cdouble,arg5::Cdouble)
    ccall((:OGR_L_SetSpatialFilterRect,libogr),Void,(OGRLayerH,Cdouble,Cdouble,Cdouble,Cdouble),arg1,arg2,arg3,arg4,arg5)
end

function OGR_L_SetSpatialFilterEx(arg1::OGRLayerH,iGeomField::Cint,hGeom::OGRGeometryH)
    ccall((:OGR_L_SetSpatialFilterEx,libogr),Void,(OGRLayerH,Cint,OGRGeometryH),arg1,iGeomField,hGeom)
end

function OGR_L_SetSpatialFilterRectEx(arg1::OGRLayerH,iGeomField::Cint,dfMinX::Cdouble,dfMinY::Cdouble,dfMaxX::Cdouble,dfMaxY::Cdouble)
    ccall((:OGR_L_SetSpatialFilterRectEx,libogr),Void,(OGRLayerH,Cint,Cdouble,Cdouble,Cdouble,Cdouble),arg1,iGeomField,dfMinX,dfMinY,dfMaxX,dfMaxY)
end

function OGR_L_SetAttributeFilter(arg1::OGRLayerH,arg2::Ptr{Uint8})
    ccall((:OGR_L_SetAttributeFilter,libogr),OGRErr,(OGRLayerH,Ptr{Uint8}),arg1,arg2)
end

function OGR_L_ResetReading(arg1::OGRLayerH)
    ccall((:OGR_L_ResetReading,libogr),Void,(OGRLayerH,),arg1)
end

function OGR_L_GetNextFeature(arg1::OGRLayerH)
    ccall((:OGR_L_GetNextFeature,libogr),OGRFeatureH,(OGRLayerH,),arg1)
end

function OGR_L_SetNextByIndex(arg1::OGRLayerH,arg2::Clong)
    ccall((:OGR_L_SetNextByIndex,libogr),OGRErr,(OGRLayerH,Clong),arg1,arg2)
end

function OGR_L_GetFeature(arg1::OGRLayerH,arg2::Clong)
    ccall((:OGR_L_GetFeature,libogr),OGRFeatureH,(OGRLayerH,Clong),arg1,arg2)
end

function OGR_L_SetFeature(arg1::OGRLayerH,arg2::OGRFeatureH)
    ccall((:OGR_L_SetFeature,libogr),OGRErr,(OGRLayerH,OGRFeatureH),arg1,arg2)
end

function OGR_L_CreateFeature(arg1::OGRLayerH,arg2::OGRFeatureH)
    ccall((:OGR_L_CreateFeature,libogr),OGRErr,(OGRLayerH,OGRFeatureH),arg1,arg2)
end

function OGR_L_DeleteFeature(arg1::OGRLayerH,arg2::Clong)
    ccall((:OGR_L_DeleteFeature,libogr),OGRErr,(OGRLayerH,Clong),arg1,arg2)
end

function OGR_L_GetLayerDefn(arg1::OGRLayerH)
    ccall((:OGR_L_GetLayerDefn,libogr),OGRFeatureDefnH,(OGRLayerH,),arg1)
end

function OGR_L_GetSpatialRef(arg1::OGRLayerH)
    ccall((:OGR_L_GetSpatialRef,libogr),OGRSpatialReferenceH,(OGRLayerH,),arg1)
end

function OGR_L_FindFieldIndex(arg1::OGRLayerH,arg2::Ptr{Uint8},bExactMatch::Cint)
    ccall((:OGR_L_FindFieldIndex,libogr),Cint,(OGRLayerH,Ptr{Uint8},Cint),arg1,arg2,bExactMatch)
end

function OGR_L_GetFeatureCount(arg1::OGRLayerH,arg2::Cint)
    ccall((:OGR_L_GetFeatureCount,libogr),Cint,(OGRLayerH,Cint),arg1,arg2)
end

function OGR_L_GetExtent(arg1::OGRLayerH,arg2::Ptr{OGREnvelope},arg3::Cint)
    ccall((:OGR_L_GetExtent,libogr),OGRErr,(OGRLayerH,Ptr{OGREnvelope},Cint),arg1,arg2,arg3)
end

function OGR_L_GetExtentEx(arg1::OGRLayerH,iGeomField::Cint,psExtent::Ptr{OGREnvelope},bForce::Cint)
    ccall((:OGR_L_GetExtentEx,libogr),OGRErr,(OGRLayerH,Cint,Ptr{OGREnvelope},Cint),arg1,iGeomField,psExtent,bForce)
end

function OGR_L_TestCapability(arg1::OGRLayerH,arg2::Ptr{Uint8})
    ccall((:OGR_L_TestCapability,libogr),Cint,(OGRLayerH,Ptr{Uint8}),arg1,arg2)
end

function OGR_L_CreateField(arg1::OGRLayerH,arg2::OGRFieldDefnH,arg3::Cint)
    ccall((:OGR_L_CreateField,libogr),OGRErr,(OGRLayerH,OGRFieldDefnH,Cint),arg1,arg2,arg3)
end

function OGR_L_CreateGeomField(hLayer::OGRLayerH,hFieldDefn::OGRGeomFieldDefnH,bForce::Cint)
    ccall((:OGR_L_CreateGeomField,libogr),OGRErr,(OGRLayerH,OGRGeomFieldDefnH,Cint),hLayer,hFieldDefn,bForce)
end

function OGR_L_DeleteField(arg1::OGRLayerH,iField::Cint)
    ccall((:OGR_L_DeleteField,libogr),OGRErr,(OGRLayerH,Cint),arg1,iField)
end

function OGR_L_ReorderFields(arg1::OGRLayerH,panMap::Ptr{Cint})
    ccall((:OGR_L_ReorderFields,libogr),OGRErr,(OGRLayerH,Ptr{Cint}),arg1,panMap)
end

function OGR_L_ReorderField(arg1::OGRLayerH,iOldFieldPos::Cint,iNewFieldPos::Cint)
    ccall((:OGR_L_ReorderField,libogr),OGRErr,(OGRLayerH,Cint,Cint),arg1,iOldFieldPos,iNewFieldPos)
end

function OGR_L_AlterFieldDefn(arg1::OGRLayerH,iField::Cint,hNewFieldDefn::OGRFieldDefnH,nFlags::Cint)
    ccall((:OGR_L_AlterFieldDefn,libogr),OGRErr,(OGRLayerH,Cint,OGRFieldDefnH,Cint),arg1,iField,hNewFieldDefn,nFlags)
end

function OGR_L_StartTransaction(arg1::OGRLayerH)
    ccall((:OGR_L_StartTransaction,libogr),OGRErr,(OGRLayerH,),arg1)
end

function OGR_L_CommitTransaction(arg1::OGRLayerH)
    ccall((:OGR_L_CommitTransaction,libogr),OGRErr,(OGRLayerH,),arg1)
end

function OGR_L_RollbackTransaction(arg1::OGRLayerH)
    ccall((:OGR_L_RollbackTransaction,libogr),OGRErr,(OGRLayerH,),arg1)
end

function OGR_L_Reference(arg1::OGRLayerH)
    ccall((:OGR_L_Reference,libogr),Cint,(OGRLayerH,),arg1)
end

function OGR_L_Dereference(arg1::OGRLayerH)
    ccall((:OGR_L_Dereference,libogr),Cint,(OGRLayerH,),arg1)
end

function OGR_L_GetRefCount(arg1::OGRLayerH)
    ccall((:OGR_L_GetRefCount,libogr),Cint,(OGRLayerH,),arg1)
end

function OGR_L_SyncToDisk(arg1::OGRLayerH)
    ccall((:OGR_L_SyncToDisk,libogr),OGRErr,(OGRLayerH,),arg1)
end

function OGR_L_GetFeaturesRead(arg1::OGRLayerH)
    ccall((:OGR_L_GetFeaturesRead,libogr),GIntBig,(OGRLayerH,),arg1)
end

function OGR_L_GetFIDColumn(arg1::OGRLayerH)
    ccall((:OGR_L_GetFIDColumn,libogr),Ptr{Uint8},(OGRLayerH,),arg1)
end

function OGR_L_GetGeometryColumn(arg1::OGRLayerH)
    ccall((:OGR_L_GetGeometryColumn,libogr),Ptr{Uint8},(OGRLayerH,),arg1)
end

function OGR_L_GetStyleTable(arg1::OGRLayerH)
    ccall((:OGR_L_GetStyleTable,libogr),OGRStyleTableH,(OGRLayerH,),arg1)
end

function OGR_L_SetStyleTableDirectly(arg1::OGRLayerH,arg2::OGRStyleTableH)
    ccall((:OGR_L_SetStyleTableDirectly,libogr),Void,(OGRLayerH,OGRStyleTableH),arg1,arg2)
end

function OGR_L_SetStyleTable(arg1::OGRLayerH,arg2::OGRStyleTableH)
    ccall((:OGR_L_SetStyleTable,libogr),Void,(OGRLayerH,OGRStyleTableH),arg1,arg2)
end

function OGR_L_SetIgnoredFields(arg1::OGRLayerH,arg2::Ptr{Ptr{Uint8}})
    ccall((:OGR_L_SetIgnoredFields,libogr),OGRErr,(OGRLayerH,Ptr{Ptr{Uint8}}),arg1,arg2)
end

function OGR_L_Intersection(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_Intersection,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_L_Union(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_Union,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_L_SymDifference(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_SymDifference,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_L_Identity(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_Identity,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_L_Update(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_Update,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_L_Clip(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_Clip,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_L_Erase(arg1::OGRLayerH,arg2::OGRLayerH,arg3::OGRLayerH,arg4::Ptr{Ptr{Uint8}},arg5::GDALProgressFunc,arg6::Ptr{Void})
    ccall((:OGR_L_Erase,libogr),OGRErr,(OGRLayerH,OGRLayerH,OGRLayerH,Ptr{Ptr{Uint8}},GDALProgressFunc,Ptr{Void}),arg1,arg2,arg3,arg4,arg5,arg6)
end

function OGR_DS_Destroy(arg1::OGRDataSourceH)
    ccall((:OGR_DS_Destroy,libogr),Void,(OGRDataSourceH,),arg1)
end

function OGR_DS_GetName(arg1::OGRDataSourceH)
    ccall((:OGR_DS_GetName,libogr),Ptr{Uint8},(OGRDataSourceH,),arg1)
end

function OGR_DS_GetLayerCount(arg1::OGRDataSourceH)
    ccall((:OGR_DS_GetLayerCount,libogr),Cint,(OGRDataSourceH,),arg1)
end

function OGR_DS_GetLayer(arg1::OGRDataSourceH,arg2::Cint)
    ccall((:OGR_DS_GetLayer,libogr),OGRLayerH,(OGRDataSourceH,Cint),arg1,arg2)
end

function OGR_DS_GetLayerByName(arg1::OGRDataSourceH,arg2::Ptr{Uint8})
    ccall((:OGR_DS_GetLayerByName,libogr),OGRLayerH,(OGRDataSourceH,Ptr{Uint8}),arg1,arg2)
end

function OGR_DS_DeleteLayer(arg1::OGRDataSourceH,arg2::Cint)
    ccall((:OGR_DS_DeleteLayer,libogr),OGRErr,(OGRDataSourceH,Cint),arg1,arg2)
end

function OGR_DS_GetDriver(arg1::OGRDataSourceH)
    ccall((:OGR_DS_GetDriver,libogr),OGRSFDriverH,(OGRDataSourceH,),arg1)
end

function OGR_DS_CreateLayer(arg1::OGRDataSourceH,arg2::Ptr{Uint8},arg3::OGRSpatialReferenceH,arg4::OGRwkbGeometryType,arg5::Ptr{Ptr{Uint8}})
    ccall((:OGR_DS_CreateLayer,libogr),OGRLayerH,(OGRDataSourceH,Ptr{Uint8},OGRSpatialReferenceH,OGRwkbGeometryType,Ptr{Ptr{Uint8}}),arg1,arg2,arg3,arg4,arg5)
end

function OGR_DS_CopyLayer(arg1::OGRDataSourceH,arg2::OGRLayerH,arg3::Ptr{Uint8},arg4::Ptr{Ptr{Uint8}})
    ccall((:OGR_DS_CopyLayer,libogr),OGRLayerH,(OGRDataSourceH,OGRLayerH,Ptr{Uint8},Ptr{Ptr{Uint8}}),arg1,arg2,arg3,arg4)
end

function OGR_DS_TestCapability(arg1::OGRDataSourceH,arg2::Ptr{Uint8})
    ccall((:OGR_DS_TestCapability,libogr),Cint,(OGRDataSourceH,Ptr{Uint8}),arg1,arg2)
end

function OGR_DS_ExecuteSQL(arg1::OGRDataSourceH,arg2::Ptr{Uint8},arg3::OGRGeometryH,arg4::Ptr{Uint8})
    ccall((:OGR_DS_ExecuteSQL,libogr),OGRLayerH,(OGRDataSourceH,Ptr{Uint8},OGRGeometryH,Ptr{Uint8}),arg1,arg2,arg3,arg4)
end

function OGR_DS_ReleaseResultSet(arg1::OGRDataSourceH,arg2::OGRLayerH)
    ccall((:OGR_DS_ReleaseResultSet,libogr),Void,(OGRDataSourceH,OGRLayerH),arg1,arg2)
end

function OGR_DS_Reference(arg1::OGRDataSourceH)
    ccall((:OGR_DS_Reference,libogr),Cint,(OGRDataSourceH,),arg1)
end

function OGR_DS_Dereference(arg1::OGRDataSourceH)
    ccall((:OGR_DS_Dereference,libogr),Cint,(OGRDataSourceH,),arg1)
end

function OGR_DS_GetRefCount(arg1::OGRDataSourceH)
    ccall((:OGR_DS_GetRefCount,libogr),Cint,(OGRDataSourceH,),arg1)
end

function OGR_DS_GetSummaryRefCount(arg1::OGRDataSourceH)
    ccall((:OGR_DS_GetSummaryRefCount,libogr),Cint,(OGRDataSourceH,),arg1)
end

function OGR_DS_SyncToDisk(arg1::OGRDataSourceH)
    ccall((:OGR_DS_SyncToDisk,libogr),OGRErr,(OGRDataSourceH,),arg1)
end

function OGR_DS_GetStyleTable(arg1::OGRDataSourceH)
    ccall((:OGR_DS_GetStyleTable,libogr),OGRStyleTableH,(OGRDataSourceH,),arg1)
end

function OGR_DS_SetStyleTableDirectly(arg1::OGRDataSourceH,arg2::OGRStyleTableH)
    ccall((:OGR_DS_SetStyleTableDirectly,libogr),Void,(OGRDataSourceH,OGRStyleTableH),arg1,arg2)
end

function OGR_DS_SetStyleTable(arg1::OGRDataSourceH,arg2::OGRStyleTableH)
    ccall((:OGR_DS_SetStyleTable,libogr),Void,(OGRDataSourceH,OGRStyleTableH),arg1,arg2)
end

function OGR_Dr_GetName(arg1::OGRSFDriverH)
    ccall((:OGR_Dr_GetName,libogr),Ptr{Uint8},(OGRSFDriverH,),arg1)
end

function OGR_Dr_Open(arg1::OGRSFDriverH,arg2::Ptr{Uint8},arg3::Cint)
    ccall((:OGR_Dr_Open,libogr),OGRDataSourceH,(OGRSFDriverH,Ptr{Uint8},Cint),arg1,arg2,arg3)
end

function OGR_Dr_TestCapability(arg1::OGRSFDriverH,arg2::Ptr{Uint8})
    ccall((:OGR_Dr_TestCapability,libogr),Cint,(OGRSFDriverH,Ptr{Uint8}),arg1,arg2)
end

function OGR_Dr_CreateDataSource(arg1::OGRSFDriverH,arg2::Ptr{Uint8},arg3::Ptr{Ptr{Uint8}})
    ccall((:OGR_Dr_CreateDataSource,libogr),OGRDataSourceH,(OGRSFDriverH,Ptr{Uint8},Ptr{Ptr{Uint8}}),arg1,arg2,arg3)
end

function OGR_Dr_CopyDataSource(arg1::OGRSFDriverH,arg2::OGRDataSourceH,arg3::Ptr{Uint8},arg4::Ptr{Ptr{Uint8}})
    ccall((:OGR_Dr_CopyDataSource,libogr),OGRDataSourceH,(OGRSFDriverH,OGRDataSourceH,Ptr{Uint8},Ptr{Ptr{Uint8}}),arg1,arg2,arg3,arg4)
end

function OGR_Dr_DeleteDataSource(arg1::OGRSFDriverH,arg2::Ptr{Uint8})
    ccall((:OGR_Dr_DeleteDataSource,libogr),OGRErr,(OGRSFDriverH,Ptr{Uint8}),arg1,arg2)
end

function OGROpen(arg1::Ptr{Uint8},arg2::Cint,arg3::Ptr{OGRSFDriverH})
    ccall((:OGROpen,libogr),OGRDataSourceH,(Ptr{Uint8},Cint,Ptr{OGRSFDriverH}),arg1,arg2,arg3)
end

function OGROpenShared(arg1::Ptr{Uint8},arg2::Cint,arg3::Ptr{OGRSFDriverH})
    ccall((:OGROpenShared,libogr),OGRDataSourceH,(Ptr{Uint8},Cint,Ptr{OGRSFDriverH}),arg1,arg2,arg3)
end

function OGRReleaseDataSource(arg1::OGRDataSourceH)
    ccall((:OGRReleaseDataSource,libogr),OGRErr,(OGRDataSourceH,),arg1)
end

function OGRRegisterDriver(arg1::OGRSFDriverH)
    ccall((:OGRRegisterDriver,libogr),Void,(OGRSFDriverH,),arg1)
end

function OGRDeregisterDriver(arg1::OGRSFDriverH)
    ccall((:OGRDeregisterDriver,libogr),Void,(OGRSFDriverH,),arg1)
end

function OGRGetDriverCount()
    ccall((:OGRGetDriverCount,libogr),Cint,())
end

function OGRGetDriver(arg1::Cint)
    ccall((:OGRGetDriver,libogr),OGRSFDriverH,(Cint,),arg1)
end

function OGRGetDriverByName(arg1::Ptr{Uint8})
    ccall((:OGRGetDriverByName,libogr),OGRSFDriverH,(Ptr{Uint8},),arg1)
end

function OGRGetOpenDSCount()
    ccall((:OGRGetOpenDSCount,libogr),Cint,())
end

function OGRGetOpenDS(iDS::Cint)
    ccall((:OGRGetOpenDS,libogr),OGRDataSourceH,(Cint,),iDS)
end

function OGRRegisterAll()
    ccall((:OGRRegisterAll,libogr),Void,())
end

function OGRCleanupAll()
    ccall((:OGRCleanupAll,libogr),Void,())
end

function OGR_SM_Create(hStyleTable::OGRStyleTableH)
    ccall((:OGR_SM_Create,libogr),OGRStyleMgrH,(OGRStyleTableH,),hStyleTable)
end

function OGR_SM_Destroy(hSM::OGRStyleMgrH)
    ccall((:OGR_SM_Destroy,libogr),Void,(OGRStyleMgrH,),hSM)
end

function OGR_SM_InitFromFeature(hSM::OGRStyleMgrH,hFeat::OGRFeatureH)
    ccall((:OGR_SM_InitFromFeature,libogr),Ptr{Uint8},(OGRStyleMgrH,OGRFeatureH),hSM,hFeat)
end

function OGR_SM_InitStyleString(hSM::OGRStyleMgrH,pszStyleString::Ptr{Uint8})
    ccall((:OGR_SM_InitStyleString,libogr),Cint,(OGRStyleMgrH,Ptr{Uint8}),hSM,pszStyleString)
end

function OGR_SM_GetPartCount(hSM::OGRStyleMgrH,pszStyleString::Ptr{Uint8})
    ccall((:OGR_SM_GetPartCount,libogr),Cint,(OGRStyleMgrH,Ptr{Uint8}),hSM,pszStyleString)
end

function OGR_SM_GetPart(hSM::OGRStyleMgrH,nPartId::Cint,pszStyleString::Ptr{Uint8})
    ccall((:OGR_SM_GetPart,libogr),OGRStyleToolH,(OGRStyleMgrH,Cint,Ptr{Uint8}),hSM,nPartId,pszStyleString)
end

function OGR_SM_AddPart(hSM::OGRStyleMgrH,hST::OGRStyleToolH)
    ccall((:OGR_SM_AddPart,libogr),Cint,(OGRStyleMgrH,OGRStyleToolH),hSM,hST)
end

function OGR_SM_AddStyle(hSM::OGRStyleMgrH,pszStyleName::Ptr{Uint8},pszStyleString::Ptr{Uint8})
    ccall((:OGR_SM_AddStyle,libogr),Cint,(OGRStyleMgrH,Ptr{Uint8},Ptr{Uint8}),hSM,pszStyleName,pszStyleString)
end

function OGR_ST_Create(eClassId::OGRSTClassId)
    ccall((:OGR_ST_Create,libogr),OGRStyleToolH,(OGRSTClassId,),eClassId)
end

function OGR_ST_Destroy(hST::OGRStyleToolH)
    ccall((:OGR_ST_Destroy,libogr),Void,(OGRStyleToolH,),hST)
end

function OGR_ST_GetType(hST::OGRStyleToolH)
    ccall((:OGR_ST_GetType,libogr),OGRSTClassId,(OGRStyleToolH,),hST)
end

function OGR_ST_GetUnit(hST::OGRStyleToolH)
    ccall((:OGR_ST_GetUnit,libogr),OGRSTUnitId,(OGRStyleToolH,),hST)
end

function OGR_ST_SetUnit(hST::OGRStyleToolH,eUnit::OGRSTUnitId,dfGroundPaperScale::Cdouble)
    ccall((:OGR_ST_SetUnit,libogr),Void,(OGRStyleToolH,OGRSTUnitId,Cdouble),hST,eUnit,dfGroundPaperScale)
end

function OGR_ST_GetParamStr(hST::OGRStyleToolH,eParam::Cint,bValueIsNull::Ptr{Cint})
    ccall((:OGR_ST_GetParamStr,libogr),Ptr{Uint8},(OGRStyleToolH,Cint,Ptr{Cint}),hST,eParam,bValueIsNull)
end

function OGR_ST_GetParamNum(hST::OGRStyleToolH,eParam::Cint,bValueIsNull::Ptr{Cint})
    ccall((:OGR_ST_GetParamNum,libogr),Cint,(OGRStyleToolH,Cint,Ptr{Cint}),hST,eParam,bValueIsNull)
end

function OGR_ST_GetParamDbl(hST::OGRStyleToolH,eParam::Cint,bValueIsNull::Ptr{Cint})
    ccall((:OGR_ST_GetParamDbl,libogr),Cdouble,(OGRStyleToolH,Cint,Ptr{Cint}),hST,eParam,bValueIsNull)
end

function OGR_ST_SetParamStr(hST::OGRStyleToolH,eParam::Cint,pszValue::Ptr{Uint8})
    ccall((:OGR_ST_SetParamStr,libogr),Void,(OGRStyleToolH,Cint,Ptr{Uint8}),hST,eParam,pszValue)
end

function OGR_ST_SetParamNum(hST::OGRStyleToolH,eParam::Cint,nValue::Cint)
    ccall((:OGR_ST_SetParamNum,libogr),Void,(OGRStyleToolH,Cint,Cint),hST,eParam,nValue)
end

function OGR_ST_SetParamDbl(hST::OGRStyleToolH,eParam::Cint,dfValue::Cdouble)
    ccall((:OGR_ST_SetParamDbl,libogr),Void,(OGRStyleToolH,Cint,Cdouble),hST,eParam,dfValue)
end

function OGR_ST_GetStyleString(hST::OGRStyleToolH)
    ccall((:OGR_ST_GetStyleString,libogr),Ptr{Uint8},(OGRStyleToolH,),hST)
end

function OGR_ST_GetRGBFromString(hST::OGRStyleToolH,pszColor::Ptr{Uint8},pnRed::Ptr{Cint},pnGreen::Ptr{Cint},pnBlue::Ptr{Cint},pnAlpha::Ptr{Cint})
    ccall((:OGR_ST_GetRGBFromString,libogr),Cint,(OGRStyleToolH,Ptr{Uint8},Ptr{Cint},Ptr{Cint},Ptr{Cint},Ptr{Cint}),hST,pszColor,pnRed,pnGreen,pnBlue,pnAlpha)
end

function OGR_STBL_Create()
    ccall((:OGR_STBL_Create,libogr),OGRStyleTableH,())
end

function OGR_STBL_Destroy(hSTBL::OGRStyleTableH)
    ccall((:OGR_STBL_Destroy,libogr),Void,(OGRStyleTableH,),hSTBL)
end

function OGR_STBL_AddStyle(hStyleTable::OGRStyleTableH,pszName::Ptr{Uint8},pszStyleString::Ptr{Uint8})
    ccall((:OGR_STBL_AddStyle,libogr),Cint,(OGRStyleTableH,Ptr{Uint8},Ptr{Uint8}),hStyleTable,pszName,pszStyleString)
end

function OGR_STBL_SaveStyleTable(hStyleTable::OGRStyleTableH,pszFilename::Ptr{Uint8})
    ccall((:OGR_STBL_SaveStyleTable,libogr),Cint,(OGRStyleTableH,Ptr{Uint8}),hStyleTable,pszFilename)
end

function OGR_STBL_LoadStyleTable(hStyleTable::OGRStyleTableH,pszFilename::Ptr{Uint8})
    ccall((:OGR_STBL_LoadStyleTable,libogr),Cint,(OGRStyleTableH,Ptr{Uint8}),hStyleTable,pszFilename)
end

function OGR_STBL_Find(hStyleTable::OGRStyleTableH,pszName::Ptr{Uint8})
    ccall((:OGR_STBL_Find,libogr),Ptr{Uint8},(OGRStyleTableH,Ptr{Uint8}),hStyleTable,pszName)
end

function OGR_STBL_ResetStyleStringReading(hStyleTable::OGRStyleTableH)
    ccall((:OGR_STBL_ResetStyleStringReading,libogr),Void,(OGRStyleTableH,),hStyleTable)
end

function OGR_STBL_GetNextStyle(hStyleTable::OGRStyleTableH)
    ccall((:OGR_STBL_GetNextStyle,libogr),Ptr{Uint8},(OGRStyleTableH,),hStyleTable)
end

function OGR_STBL_GetLastStyleName(hStyleTable::OGRStyleTableH)
    ccall((:OGR_STBL_GetLastStyleName,libogr),Ptr{Uint8},(OGRStyleTableH,),hStyleTable)
end
