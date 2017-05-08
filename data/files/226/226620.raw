# basicfacade

BasicFacade_T = cxxt"""Ubitrack::Facade::BasicFacade"""
BasicFacade(components_path::AbstractString) = @cxx Ubitrack::Facade::BasicFacade(pointer(components_path))

loadDataflow(facade::BasicFacade_T, filename::AbstractString) = @cxx BF_loadDataflow(facade, pointer(filename))
loadDataflowString(facade::BasicFacade_T, dfdata::AbstractString) = @cxx BF_loadDataflowString(facade, pointer(dfdata))
clearDataflow(facade::BasicFacade_T) = @cxx BF_clearDataflow(facade)
startDataflow(facade::BasicFacade_T) = @cxx BF_startDataflow(facade)
stopDataflow(facade::BasicFacade_T) = @cxx BF_stopDataflow(facade)
connectToServer(facade::BasicFacade_T, sAddress::AbstractString) = @cxx BF_startDataflow(facade, pointer(sAddress))
sendUtqlToServer(facade::BasicFacade_T, sUtqlFile::AbstractString) = @cxx BF_sendUtqlToServer(facade, pointer(sUtqlFile))
sendUtqlToServerString(facade::BasicFacade_T, buffer::AbstractString) = @cxx BF_sendUtqlToServerString(facade, pointer(buffer))

# basicpullsinks
BasicPullSinkScalarInt_T = cxxt"""Ubitrack::Facade::BasicPullSink<Ubitrack::Facade::BasicScalarIntMeasurement>"""
getPullSinkScalarInt(facade::BasicFacade_T, name::AbstractString) = @cxx BF_getPullSinkScalarInt(facade, name)

BasicPullSinkScalarDouble_T = cxxt"""Ubitrack::Facade::BasicPullSink<Ubitrack::Facade::BasicScalarDoubleMeasurement>"""
getPullSinkScalarDouble(facade::BasicFacade_T, name::AbstractString) = @cxx BF_getPullSinkScalarDouble(facade, name)

pull_value(sink::BasicPullSinkScalarInt_T, ts::UInt64) = @cxx sink.get(ts)
pull_value(sink::BasicPullSinkScalarDouble_T, ts::UInt64) = @cxx sink.get(ts)
