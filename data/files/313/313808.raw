# Automatically generated using Clang.jl wrap_c, version 0.0.0

using Compat

const OGRERR_NONE = 0
const OGRERR_NOT_ENOUGH_DATA = 1
const OGRERR_NOT_ENOUGH_MEMORY = 2
const OGRERR_UNSUPPORTED_GEOMETRY_TYPE = 3
const OGRERR_UNSUPPORTED_OPERATION = 4
const OGRERR_CORRUPT_DATA = 5
const OGRERR_FAILURE = 6
const OGRERR_UNSUPPORTED_SRS = 7
const OGRERR_INVALID_HANDLE = 8
const wkb25DBit = 0x80000000

# Skipping MacroDefinition: wkbFlatten ( x ) ( ( OGRwkbGeometryType ) ( ( x ) & ( ~ wkb25DBit ) ) )

const ogrZMarker = 0x21125711

# Skipping MacroDefinition: DB2_V72_FIX_BYTE_ORDER ( x ) ( ( ( ( x ) & 0x31 ) == ( x ) ) ? ( OGRwkbByteOrder ) ( ( x ) & 0x1 ) : ( x ) )
# Skipping MacroDefinition: DB2_V72_UNFIX_BYTE_ORDER ( x ) ( ( unsigned char ) ( OGRGeometry : : bGenerate_DB2_V72_BYTE_ORDER ? ( ( x ) | 0x30 ) : ( x ) ) )

const ALTER_NAME_FLAG = 0x01
const ALTER_TYPE_FLAG = 0x02
const ALTER_WIDTH_PRECISION_FLAG = 0x04
const ALTER_ALL_FLAG = (ALTER_NAME_FLAG | ALTER_TYPE_FLAG) | ALTER_WIDTH_PRECISION_FLAG
const OGRNullFID = -1
const OGRUnsetMarker = -21121
const OLCRandomRead = "RandomRead"
const OLCSequentialWrite = "SequentialWrite"
const OLCRandomWrite = "RandomWrite"
const OLCFastSpatialFilter = "FastSpatialFilter"
const OLCFastFeatureCount = "FastFeatureCount"
const OLCFastGetExtent = "FastGetExtent"
const OLCCreateField = "CreateField"
const OLCDeleteField = "DeleteField"
const OLCReorderFields = "ReorderFields"
const OLCAlterFieldDefn = "AlterFieldDefn"
const OLCTransactions = "Transactions"
const OLCDeleteFeature = "DeleteFeature"
const OLCFastSetNextByIndex = "FastSetNextByIndex"
const OLCStringsAsUTF8 = "StringsAsUTF8"
const OLCIgnoreFields = "IgnoreFields"
const OLCCreateGeomField = "CreateGeomField"
const ODsCCreateLayer = "CreateLayer"
const ODsCDeleteLayer = "DeleteLayer"
const ODsCCreateGeomFieldAfterCreateLayer = "CreateGeomFieldAfterCreateLayer"
const ODrCCreateDataSource = "CreateDataSource"
const ODrCDeleteDataSource = "DeleteDataSource"

# Skipping MacroDefinition: GDAL_CHECK_VERSION ( pszCallingComponentName ) GDALCheckVersion ( GDAL_VERSION_MAJOR , GDAL_VERSION_MINOR , pszCallingComponentName )

typealias GDALProgressFunc Ptr{Void}

type OGREnvelope
    MinX::Cdouble
    MaxX::Cdouble
    MinY::Cdouble
    MaxY::Cdouble
end

type OGREnvelope3D
    MinX::Cdouble
    MaxX::Cdouble
    MinY::Cdouble
    MaxY::Cdouble
    MinZ::Cdouble
    MaxZ::Cdouble
end

typealias OGRErr Cint
typealias OGRBoolean Cint

# begin enum ANONYMOUS_1
typealias ANONYMOUS_1 Uint32
const wkbUnknown = (UInt32)(0)
const wkbPoint = (UInt32)(1)
const wkbLineString = (UInt32)(2)
const wkbPolygon = (UInt32)(3)
const wkbMultiPoint = (UInt32)(4)
const wkbMultiLineString = (UInt32)(5)
const wkbMultiPolygon = (UInt32)(6)
const wkbGeometryCollection = (UInt32)(7)
const wkbNone = (UInt32)(100)
const wkbLinearRing = (UInt32)(101)
const wkbPoint25D = (UInt32)(0x0000000080000001)
const wkbLineString25D = (UInt32)(0x0000000080000002)
const wkbPolygon25D = (UInt32)(0x0000000080000003)
const wkbMultiPoint25D = (UInt32)(0x0000000080000004)
const wkbMultiLineString25D = (UInt32)(0x0000000080000005)
const wkbMultiPolygon25D = (UInt32)(0x0000000080000006)
const wkbGeometryCollection25D = (UInt32)(0x0000000080000007)
# end enum ANONYMOUS_1

# begin enum OGRwkbGeometryType
typealias OGRwkbGeometryType Uint32
const wkbUnknown = (UInt32)(0)
const wkbPoint = (UInt32)(1)
const wkbLineString = (UInt32)(2)
const wkbPolygon = (UInt32)(3)
const wkbMultiPoint = (UInt32)(4)
const wkbMultiLineString = (UInt32)(5)
const wkbMultiPolygon = (UInt32)(6)
const wkbGeometryCollection = (UInt32)(7)
const wkbNone = (UInt32)(100)
const wkbLinearRing = (UInt32)(101)
const wkbPoint25D = (UInt32)(0x0000000080000001)
const wkbLineString25D = (UInt32)(0x0000000080000002)
const wkbPolygon25D = (UInt32)(0x0000000080000003)
const wkbMultiPoint25D = (UInt32)(0x0000000080000004)
const wkbMultiLineString25D = (UInt32)(0x0000000080000005)
const wkbMultiPolygon25D = (UInt32)(0x0000000080000006)
const wkbGeometryCollection25D = (UInt32)(0x0000000080000007)
# end enum OGRwkbGeometryType

# begin enum ANONYMOUS_2
typealias ANONYMOUS_2 Uint32
const wkbVariantOgc = (UInt32)(0)
const wkbVariantIso = (UInt32)(1)
# end enum ANONYMOUS_2

# begin enum OGRwkbVariant
typealias OGRwkbVariant Uint32
const wkbVariantOgc = (UInt32)(0)
const wkbVariantIso = (UInt32)(1)
# end enum OGRwkbVariant

# begin enum ANONYMOUS_3
typealias ANONYMOUS_3 Uint32
const wkbXDR = (UInt32)(0)
const wkbNDR = (UInt32)(1)
# end enum ANONYMOUS_3

# begin enum OGRwkbByteOrder
typealias OGRwkbByteOrder Uint32
const wkbXDR = (UInt32)(0)
const wkbNDR = (UInt32)(1)
# end enum OGRwkbByteOrder

# begin enum ANONYMOUS_4
typealias ANONYMOUS_4 Uint32
const OFTInteger = (UInt32)(0)
const OFTIntegerList = (UInt32)(1)
const OFTReal = (UInt32)(2)
const OFTRealList = (UInt32)(3)
const OFTString = (UInt32)(4)
const OFTStringList = (UInt32)(5)
const OFTWideString = (UInt32)(6)
const OFTWideStringList = (UInt32)(7)
const OFTBinary = (UInt32)(8)
const OFTDate = (UInt32)(9)
const OFTTime = (UInt32)(10)
const OFTDateTime = (UInt32)(11)
const OFTMaxType = (UInt32)(11)
# end enum ANONYMOUS_4

# begin enum OGRFieldType
typealias OGRFieldType Uint32
const OFTInteger = (UInt32)(0)
const OFTIntegerList = (UInt32)(1)
const OFTReal = (UInt32)(2)
const OFTRealList = (UInt32)(3)
const OFTString = (UInt32)(4)
const OFTStringList = (UInt32)(5)
const OFTWideString = (UInt32)(6)
const OFTWideStringList = (UInt32)(7)
const OFTBinary = (UInt32)(8)
const OFTDate = (UInt32)(9)
const OFTTime = (UInt32)(10)
const OFTDateTime = (UInt32)(11)
const OFTMaxType = (UInt32)(11)
# end enum OGRFieldType

# begin enum ANONYMOUS_5
typealias ANONYMOUS_5 Uint32
const OJUndefined = (UInt32)(0)
const OJLeft = (UInt32)(1)
const OJRight = (UInt32)(2)
# end enum ANONYMOUS_5

# begin enum OGRJustification
typealias OGRJustification Uint32
const OJUndefined = (UInt32)(0)
const OJLeft = (UInt32)(1)
const OJRight = (UInt32)(2)
# end enum OGRJustification

# begin enum ogr_style_tool_class_id
typealias ogr_style_tool_class_id Uint32
const OGRSTCNone = (UInt32)(0)
const OGRSTCPen = (UInt32)(1)
const OGRSTCBrush = (UInt32)(2)
const OGRSTCSymbol = (UInt32)(3)
const OGRSTCLabel = (UInt32)(4)
const OGRSTCVector = (UInt32)(5)
# end enum ogr_style_tool_class_id

# begin enum OGRSTClassId
typealias OGRSTClassId Uint32
const OGRSTCNone = (UInt32)(0)
const OGRSTCPen = (UInt32)(1)
const OGRSTCBrush = (UInt32)(2)
const OGRSTCSymbol = (UInt32)(3)
const OGRSTCLabel = (UInt32)(4)
const OGRSTCVector = (UInt32)(5)
# end enum OGRSTClassId

# begin enum ogr_style_tool_units_id
typealias ogr_style_tool_units_id Uint32
const OGRSTUGround = (UInt32)(0)
const OGRSTUPixel = (UInt32)(1)
const OGRSTUPoints = (UInt32)(2)
const OGRSTUMM = (UInt32)(3)
const OGRSTUCM = (UInt32)(4)
const OGRSTUInches = (UInt32)(5)
# end enum ogr_style_tool_units_id

# begin enum OGRSTUnitId
typealias OGRSTUnitId Uint32
const OGRSTUGround = (UInt32)(0)
const OGRSTUPixel = (UInt32)(1)
const OGRSTUPoints = (UInt32)(2)
const OGRSTUMM = (UInt32)(3)
const OGRSTUCM = (UInt32)(4)
const OGRSTUInches = (UInt32)(5)
# end enum OGRSTUnitId

# begin enum ogr_style_tool_param_pen_id
typealias ogr_style_tool_param_pen_id Uint32
const OGRSTPenColor = (UInt32)(0)
const OGRSTPenWidth = (UInt32)(1)
const OGRSTPenPattern = (UInt32)(2)
const OGRSTPenId = (UInt32)(3)
const OGRSTPenPerOffset = (UInt32)(4)
const OGRSTPenCap = (UInt32)(5)
const OGRSTPenJoin = (UInt32)(6)
const OGRSTPenPriority = (UInt32)(7)
const OGRSTPenLast = (UInt32)(8)
# end enum ogr_style_tool_param_pen_id

# begin enum OGRSTPenParam
typealias OGRSTPenParam Uint32
const OGRSTPenColor = (UInt32)(0)
const OGRSTPenWidth = (UInt32)(1)
const OGRSTPenPattern = (UInt32)(2)
const OGRSTPenId = (UInt32)(3)
const OGRSTPenPerOffset = (UInt32)(4)
const OGRSTPenCap = (UInt32)(5)
const OGRSTPenJoin = (UInt32)(6)
const OGRSTPenPriority = (UInt32)(7)
const OGRSTPenLast = (UInt32)(8)
# end enum OGRSTPenParam

# begin enum ogr_style_tool_param_brush_id
typealias ogr_style_tool_param_brush_id Uint32
const OGRSTBrushFColor = (UInt32)(0)
const OGRSTBrushBColor = (UInt32)(1)
const OGRSTBrushId = (UInt32)(2)
const OGRSTBrushAngle = (UInt32)(3)
const OGRSTBrushSize = (UInt32)(4)
const OGRSTBrushDx = (UInt32)(5)
const OGRSTBrushDy = (UInt32)(6)
const OGRSTBrushPriority = (UInt32)(7)
const OGRSTBrushLast = (UInt32)(8)
# end enum ogr_style_tool_param_brush_id

# begin enum OGRSTBrushParam
typealias OGRSTBrushParam Uint32
const OGRSTBrushFColor = (UInt32)(0)
const OGRSTBrushBColor = (UInt32)(1)
const OGRSTBrushId = (UInt32)(2)
const OGRSTBrushAngle = (UInt32)(3)
const OGRSTBrushSize = (UInt32)(4)
const OGRSTBrushDx = (UInt32)(5)
const OGRSTBrushDy = (UInt32)(6)
const OGRSTBrushPriority = (UInt32)(7)
const OGRSTBrushLast = (UInt32)(8)
# end enum OGRSTBrushParam

# begin enum ogr_style_tool_param_symbol_id
typealias ogr_style_tool_param_symbol_id Uint32
const OGRSTSymbolId = (UInt32)(0)
const OGRSTSymbolAngle = (UInt32)(1)
const OGRSTSymbolColor = (UInt32)(2)
const OGRSTSymbolSize = (UInt32)(3)
const OGRSTSymbolDx = (UInt32)(4)
const OGRSTSymbolDy = (UInt32)(5)
const OGRSTSymbolStep = (UInt32)(6)
const OGRSTSymbolPerp = (UInt32)(7)
const OGRSTSymbolOffset = (UInt32)(8)
const OGRSTSymbolPriority = (UInt32)(9)
const OGRSTSymbolFontName = (UInt32)(10)
const OGRSTSymbolOColor = (UInt32)(11)
const OGRSTSymbolLast = (UInt32)(12)
# end enum ogr_style_tool_param_symbol_id

# begin enum OGRSTSymbolParam
typealias OGRSTSymbolParam Uint32
const OGRSTSymbolId = (UInt32)(0)
const OGRSTSymbolAngle = (UInt32)(1)
const OGRSTSymbolColor = (UInt32)(2)
const OGRSTSymbolSize = (UInt32)(3)
const OGRSTSymbolDx = (UInt32)(4)
const OGRSTSymbolDy = (UInt32)(5)
const OGRSTSymbolStep = (UInt32)(6)
const OGRSTSymbolPerp = (UInt32)(7)
const OGRSTSymbolOffset = (UInt32)(8)
const OGRSTSymbolPriority = (UInt32)(9)
const OGRSTSymbolFontName = (UInt32)(10)
const OGRSTSymbolOColor = (UInt32)(11)
const OGRSTSymbolLast = (UInt32)(12)
# end enum OGRSTSymbolParam

# begin enum ogr_style_tool_param_label_id
typealias ogr_style_tool_param_label_id Uint32
const OGRSTLabelFontName = (UInt32)(0)
const OGRSTLabelSize = (UInt32)(1)
const OGRSTLabelTextString = (UInt32)(2)
const OGRSTLabelAngle = (UInt32)(3)
const OGRSTLabelFColor = (UInt32)(4)
const OGRSTLabelBColor = (UInt32)(5)
const OGRSTLabelPlacement = (UInt32)(6)
const OGRSTLabelAnchor = (UInt32)(7)
const OGRSTLabelDx = (UInt32)(8)
const OGRSTLabelDy = (UInt32)(9)
const OGRSTLabelPerp = (UInt32)(10)
const OGRSTLabelBold = (UInt32)(11)
const OGRSTLabelItalic = (UInt32)(12)
const OGRSTLabelUnderline = (UInt32)(13)
const OGRSTLabelPriority = (UInt32)(14)
const OGRSTLabelStrikeout = (UInt32)(15)
const OGRSTLabelStretch = (UInt32)(16)
const OGRSTLabelAdjHor = (UInt32)(17)
const OGRSTLabelAdjVert = (UInt32)(18)
const OGRSTLabelHColor = (UInt32)(19)
const OGRSTLabelOColor = (UInt32)(20)
const OGRSTLabelLast = (UInt32)(21)
# end enum ogr_style_tool_param_label_id

# begin enum OGRSTLabelParam
typealias OGRSTLabelParam Uint32
const OGRSTLabelFontName = (UInt32)(0)
const OGRSTLabelSize = (UInt32)(1)
const OGRSTLabelTextString = (UInt32)(2)
const OGRSTLabelAngle = (UInt32)(3)
const OGRSTLabelFColor = (UInt32)(4)
const OGRSTLabelBColor = (UInt32)(5)
const OGRSTLabelPlacement = (UInt32)(6)
const OGRSTLabelAnchor = (UInt32)(7)
const OGRSTLabelDx = (UInt32)(8)
const OGRSTLabelDy = (UInt32)(9)
const OGRSTLabelPerp = (UInt32)(10)
const OGRSTLabelBold = (UInt32)(11)
const OGRSTLabelItalic = (UInt32)(12)
const OGRSTLabelUnderline = (UInt32)(13)
const OGRSTLabelPriority = (UInt32)(14)
const OGRSTLabelStrikeout = (UInt32)(15)
const OGRSTLabelStretch = (UInt32)(16)
const OGRSTLabelAdjHor = (UInt32)(17)
const OGRSTLabelAdjVert = (UInt32)(18)
const OGRSTLabelHColor = (UInt32)(19)
const OGRSTLabelOColor = (UInt32)(20)
const OGRSTLabelLast = (UInt32)(21)
# end enum OGRSTLabelParam

typealias OGRGeometryH Ptr{Void}
typealias OGRSpatialReferenceH Ptr{Void}
typealias OGRCoordinateTransformationH Ptr{Void}

type _CPLXMLNode
end

typealias OGRFieldDefnH Ptr{Void}
typealias OGRFeatureDefnH Ptr{Void}
typealias OGRFeatureH Ptr{Void}
typealias OGRStyleTableH Ptr{Void}

type OGRGeomFieldDefnHS
end

typealias OGRGeomFieldDefnH Ptr{OGRGeomFieldDefnHS}
typealias OGRLayerH Ptr{Void}
typealias OGRDataSourceH Ptr{Void}
typealias OGRSFDriverH Ptr{Void}
typealias OGRStyleMgrH Ptr{Void}
typealias OGRStyleToolH Ptr{Void}
