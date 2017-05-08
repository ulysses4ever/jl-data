
const etDataTypeSCALARI = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::SCALARI")}(0)
const etDataTypeSCALARD = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::SCALARD")}(1)
const etDataTypeVECTORD = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::VECTORD")}(2)
const etDataTypeMATRIXD = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::MATRIXD")}(3)
const etDataTypePOSE = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::POSE")}(4)
const etDataTypeQUATERNION = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::QUATERNION")}(5)
const etDataTypeERROR_VECTOR = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::ERROR_VECTOR")}(6)
const etDataTypeERROR_POSE = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::ERROR_POSE")}(7)
const etDataTypeCAMERA_INTRINSICS = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::CAMERA_INTRINSICS")}(8)
const etDataTypeIMAGE = Cxx.CppEnum{symbol("Ubitrack::Facade::BasicMeasurement::DataType::IMAGE")}(9)

get_datatype(m) = @cxx BM_getdatatype(m)
get_dimx(m) = @cxx BM_getdimx(m)
get_dimy(m) = @cxx BM_getdimy(m)
get_dimz(m) = @cxx BM_getdimz(m)


make_BasicScalarIntMeasurement() = @cxx Ubitrack::Facade::BasicScalarIntMeasurement()
make_BasicScalarIntMeasurement(ts, value) = @cxx Ubitrack::Facade::BasicScalarIntMeasurement(ts, value)

get_value(m) = @cxx BSIM_getvalue(m)