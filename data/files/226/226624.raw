
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
is_valid(m) = @cxx BM_isvalid(m)
get_time(m) = @cxx BM_gettime(m)
get_size(m) = @cxx BM_getsize(m)
get_dimx(m) = @cxx BM_getdimx(m)
get_dimy(m) = @cxx BM_getdimy(m)
get_dimz(m) = @cxx BM_getdimz(m)

BasicScalarIntMeasurement_T = cxxt"Ubitrack::Facade::BasicScalarIntMeasurement"
make_BasicScalarIntMeasurement() = @cxx Ubitrack::Facade::BasicScalarIntMeasurement()
make_measurement(ts::UInt64, value::Int32) = @cxx Ubitrack::Facade::BasicScalarIntMeasurement(ts, value)
get_value(m::BasicScalarIntMeasurement_T) = @cxx BSIM_getvalue(m)
Base.show(io::IO, m::BasicScalarIntMeasurement_T) = write(io, "IntMeasurement($(get_time(m)), $(get_value(m)))")

BasicScalarDoubleMeasurement_T = cxxt"Ubitrack::Facade::BasicScalarDoubleMeasurement"
make_BasicScalarDoubleMeasurement() = @cxx Ubitrack::Facade::BasicScalarDoubleMeasurement()
make_measurement(ts::UInt64, value::Float64) = @cxx Ubitrack::Facade::BasicScalarDoubleMeasurement(ts, value)
get_value(m::BasicScalarDoubleMeasurement_T) = @cxx BSDM_getvalue(m)
Base.show(io::IO, m::BasicScalarDoubleMeasurement_T) = write(io, "DoubleMeasurement($(get_time(m)), $(get_value(m)))")


