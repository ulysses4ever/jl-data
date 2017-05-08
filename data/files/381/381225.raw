function getFileName(a1::CXFile,)
  c = ccall( (:clang_getFileName, libclang), CXString, (CXFile,), a1)
  return get_string(c)
end
function getNullLocation()
#  c = CXSourceLocation()
  ccall( (:clang_getNullLocation, libclang), CXSourceLocation, ())
  return c
end
function equalLocations(a1::CXSourceLocation,a2::CXSourceLocation,)
  ccall( (:clang_equalLocations, libclang), Uint32, (CXSourceLocation,CXSourceLocation), a1,a2, )
end
function getNullRange()
  ccall( (:clang_getNullRange, libclang), CXSourceRange, ())
end
function getRange(a1::CXSourceLocation,a2::CXSourceLocation,)
 ccall( (:clang_getRange, libclang), CXSourceRange, (CXSourceLocation,CXSourceLocation), a1,a2)
end
function equalRanges(a1::CXSourceRange,a2::CXSourceRange,)
  ccall( (:clang_equalRanges, libclang), Uint32, (CXSourceRange,CXSourceRange), a1,a2, )
end
function Range_isNull(a1::CXSourceRange,)
  ccall( (:clang_Range_isNull, libclang), Int32, (Ptr{Void},), a1, )
end
function getNullCursor()
  ccall( (:clang_getNullCursor, libclang), CXCursor, ())
end
function getTranslationUnitCursor(a1::CXTranslationUnit,)
  ccall( (:clang_getTranslationUnitCursor, libclang), CXCursor, (CXTranslationUnit,), a1)
end
function equalCursors(a1::CXCursor,a2::CXCursor,)
  ccall( (:clang_equalCursors, libclang), Uint32, (CXCursor,CXCursor), a1,a2)
end
function Cursor_isNull(a1::CXCursor,)
  ccall( (:clang_Cursor_isNull, libclang), Int32, (CXCursor,), a1)
end
function hashCursor(a1::CXCursor,)
  ccall( (:clang_hashCursor, libclang), Uint32, (CXCursor,), a1, )
end
function getCursorKind(a1::CXCursor,)
  ccall( (:clang_getCursorKind, libclang), CXCursorKind, (CXCursor,), a1, )
end
function isDeclaration(a1::CXCursorKind,)
  ccall( (:clang_isDeclaration, libclang), Uint32, (CXCursorKind,), a1, )
end
function isReference(a1::CXCursorKind,)
  ccall( (:clang_isReference, libclang), Uint32, (CXCursorKind,), a1, )
end
function getCursorLinkage(a1::CXCursor,)
  ccall( (:clang_getCursorLinkage, libclang), CXLinkageKind, (CXCursor,), a1)
end
function getCursorAvailability(a1::CXCursor,)
  ccall( (:clang_getCursorAvailability, libclang), CXAvailabilityKind, (CXCursor,), a1, )
end
function getCursorLanguage(a1::CXCursor,)
  ccall( (:clang_getCursorLanguage, libclang), CXLanguageKind, (CXCursor,), a1, )
end
function getCursorSemanticParent(a1::CXCursor,)
  ccall( (:clang_getCursorSemanticParent, libclang), CXCursor, (CXCursor,), a1)
end
function getCursorLexicalParent(a1::CXCursor,)
  ccall( (:clang_getCursorLexicalParent, libclang), CXCursor, (CXCursor,), a1)
end
function getCursorType(a1::CXCursor,)
  ccall( (:clang_getCursorType, libclang), CXType, (CXCursor,), a1,)
end
function getTypedefDeclUnderlyingType(a1::CXCursor,)
  ccall( (:clang_getTypedefDeclUnderlyingType, libclang), CXType, (CXCursor,), a1)
end
function getEnumDeclIntegerType(a1::CXCursor,)
  ccall( (:clang_getEnumDeclIntegerType, libclang), CXCursor, (CXCursor,), a1,)
end
function getEnumConstantDeclValue(a1::CXCursor,)
  ccall( (:clang_getEnumConstantDeclValue, libclang), Int, (CXCursor,), a1, )
end
function getEnumConstantDeclUnsignedValue(a1::CXCursor,)
  ccall( (:clang_getEnumConstantDeclUnsignedValue, libclang), Uint, (CXCursor,), a1, )
end
function Cursor_getNumArguments(a1::CXCursor,)
  ccall( (:clang_Cursor_getNumArguments, libclang), Int32, (CXCursor,), a1, )
end
function Cursor_getArgument(a1::CXCursor,a2::Int32,)
  ccall( (:clang_Cursor_getArgument, libclang), CXCursor, (CXCursor,Int32), a1,a2)
end
function equalTypes(a1::CXType,a2::CXType,)
  ccall( (:clang_equalTypes, libclang), Uint32, (CXType,CXType), a1,a2, )
end
function getCanonicalType(a1::CXType,)
  ccall( (:clang_getCanonicalType, libclang), CXType, (CXType,), a1)
end
function isConstQualifiedType(a1::CXType,)
  ccall( (:clang_isConstQualifiedType, libclang), Uint32, (CXType,), a1)
end
function isVolatileQualifiedType(a1::CXType,)
  ccall( (:clang_isVolatileQualifiedType, libclang), Uint32, (CXType,), a1)
end
function isRestrictQualifiedType(a1::CXType,)
  ccall( (:clang_isRestrictQualifiedType, libclang), Uint32, (CXType,), a1, )
end
function getPointeeType(a1::CXType,)
  ccall( (:clang_getPointeeType, libclang), CXType, (CXType,), a1)
end
function getTypeDeclaration(a1::CXType,)
  ccall( (:clang_getTypeDeclaration, libclang), CXCursor, (CXType,), a1)
end

function getDeclObjCTypeEncoding(a1::CXCursor,)
  c = ccall( (:clang_getDeclObjCTypeEncoding, libclang), CXString, (CXCursor,), a1)
  return get_string(c)
end
function getTypeKindSpelling(a1::CXTypeKind,)
  c = ccall( (:clang_getTypeKindSpelling, libclang), CXString, (CXTypeKind,), a1)
  return get_string(c)
end

function getFunctionTypeCallingConv(a1::CXType,)
  ccall( (:clang_getFunctionTypeCallingConv, libclang), Int32, (CXType,), a1, )
end
function getResultType(a1::CXType,)
  ccall( (:clang_getResultType, libclang), CXType, (CXType,), a1)
end
function getNumArgTypes(a1::CXType,)
  ccall( (:clang_getNumArgTypes, libclang), Int32, (CXType,), a1, )
end
function getArgType(a1::CXType,a2::Uint32,)
  ccall( (:clang_getArgType, libclang), CXType, (Ptr{Void},Uint32), a1,a2)
end
function isFunctionTypeVariadic(a1::CXType,)
  ccall( (:clang_isFunctionTypeVariadic, libclang), Uint32, (CXType,), a1, )
end
function getCursorResultType(a1::CXCursor,)
  ccall( (:clang_getCursorResultType, libclang), CXType, (CXCursor,), a1)
end
function isPODType(a1::CXType,)
  ccall( (:clang_isPODType, libclang), Uint32, (CXType,), a1)
end
function getElementType(a1::CXType,)
  ccall( (:clang_getElementType, libclang), CXType, (CXType,), a1,)
end
function getNumElements(a1::CXType,)
  ccall( (:clang_getNumElements, libclang), Int64, (CXType,), a1, )
end
function getArrayElementType(a1::CXType,)
  ccall( (:clang_getArrayElementType, libclang), CXType, (CXType,), a1,)
end
function getArraySize(a1::CXType,)
  ccall( (:clang_getArraySize, libclang), Int64, (CXType,), a1, )
end
function isVirtualBase(a1::CXCursor,)
  ccall( (:clang_isVirtualBase, libclang), Uint32, (CXCursor,), a1, )
end
function getCXXAccessSpecifier(a1::CXCursor,)
  ccall( (:clang_getCXXAccessSpecifier, libclang), Int64, (CXCursor,), a1, )
end
function getNumOverloadedDecls(a1::CXCursor,)
  ccall( (:clang_getNumOverloadedDecls, libclang), Uint32, (CXCursor,), a1, )
end
function getOverloadedDecl(a1::CXCursor,a2::Uint32,)
  ccall( (:clang_getOverloadedDecl, libclang), CXCursor, (CXCursor,Uint32), a1,a2)
end

function getCursorUSR(a1::CXCursor,)
  c = ccall( (:clang_getCursorUSR, libclang), CXString, (CXCursor,), a1)
  return get_string(c)
end
function getCursorSpelling(a1::CXCursor,)
  c = ccall( (:clang_getCursorSpelling, libclang), CXString, (CXCursor,), a1)
  return get_string(c)
end
function getCursorDisplayName(a1::CXCursor,)
  ccall( (:clang_getCursorDisplayName, libclang), CXString, (CXCursor,), a1)
  return get_string(c)
end

function getCursorReferenced(a1::CXCursor,)
  ccall( (:clang_getCursorReferenced, libclang), CXCursor, (CXCursor,), a1)
end
function getCursorDefinition(a1::CXCursor,)
  ccall( (:clang_getCursorDefinition, libclang), CXCursor, (CXCursor,), a1)
end
function isCursorDefinition(a1::CXCursor,)
  ccall( (:clang_isCursorDefinition, libclang), Uint32, (CXCursor,), a1, )
end
function getCanonicalCursor(a1::CXCursor,)
  ccall( (:clang_getCanonicalCursor, libclang), CXCursor, (CXCursor,), a1)
end
function CXXMethod_isStatic(a1::CXCursor,)
  ccall( (:clang_CXXMethod_isStatic, libclang), Uint32, (CXCursor,), a1, )
end
function CXXMethod_isVirtual(a1::CXCursor,)
  ccall( (:clang_CXXMethod_isVirtual, libclang), Uint32, (CXCursor,), a1, )
end
function getTemplateCursorKind(a1::CXCursor,)
  ccall( (:clang_getTemplateCursorKind, libclang), Int32, (CXCursor,), a1, )
end
function getSpecializedCursorTemplate(a1::CXCursor,)
  ccall( (:clang_getSpecializedCursorTemplate, libclang), CXCursor, (CXCursor,), a1)
end
function getTokenKind(a1::CXToken,)
  ccall( (:clang_getTokenKind, libclang), Int32, (CXCursor,), a1, )
end

function getTokenSpelling(a1::CXTranslationUnit,a2::CXToken,)
  ccall( (:clang_getTokenSpelling, libclang), CXString, (CXTranslationUnit,CXToken,), a1,a2)
  return get_string(c)
end

function getCursorKindSpelling(a1::CXCursorKind,)
  c = ccall( (:clang_getCursorKindSpelling, libclang), CXString, (CXCursorKind,), a1)
  return get_string(c)
end
function getClangVersion()
  c = ccall( (:clang_getClangVersion, libclang), CXString, ())
  return get_string(c)
end
