#module Ubitrack

using Cxx

# Check Julia version before continuing (also checked later in Cxx)
(VERSION >= v"0.4-") ? nothing :
     throw(ErrorException("Julia $VERSION does not support C++ FFI"))

# Load names of Ubitrack shared libraries (pre-compiled)
include(joinpath(Pkg.dir("Ubitrack"), "src/Ubitrack_libs.jl"))

# static directories for now
const utlibdir = "/usr/local/lib"
const utheaderdir = "/usr/local/include"

addHeaderDir(utlibdir; kind = C_System)

# Load Ubitrack shared libraries
# IMPORTANT: if necessary, make sure to link symbols accross libraries with RTLD_GLOBAL
for i in ubitrack_libraries
    dlopen_e(joinpath(utlibdir,i), RTLD_GLOBAL)==C_NULL ? throw(ArgumentError("Skip loading $(i)")): nothing
end

addHeaderDir(utheaderdir; kind = C_System)


# std includes
cxx"""
 #include <iostream>
 #include <unistd.h>
 #include <cstdlib>
 #include <cstdio>
 #include <cstddef>
 #include <cstring>
 #include <cfloat>
 #include <vector>
 #include <ctime>
 #include <map>
 #include <utility>
 #include <exception>
"""

# custom defines
# cxx"""
# #define TIXML_USE_STL
# #define HAVE_TINYXML

# #define HAVE_LOG4CPP

# #define BOOST_FILESYSTEM_VERSION 3
# #define HAVE_BOOST

# #define HAVE_LAPACK

# #define HAVE_OPENCV

# #define HAVE_TBB

# #define HAVE_FREEGLUT

# #define HAVE_PTHREAD
# """


# utilities
# cxxinclude(joinpath(utheaderdir, "utUtil/Logging.h"))
# cxxinclude(joinpath(utheaderdir, "utUtil/Exception.h"))

# utcore
# cxxinclude(joinpath(utheaderdir, "utCore.h"))

# math
# cxxinclude(joinpath(utheaderdir, "utMath/Vector.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/Matrix.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/VectorFunctions.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/MatrixOperations.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/Quaternion.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/RotationVelocity.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/Scalar.h"))
# cxxinclude(joinpath(utheaderdir, "utMath/Pose.h"))

# measurement
# cxxinclude(joinpath(utheaderdir, "utMeasurement/Measurement.h"))

# facade
cxxinclude(joinpath(utheaderdir, "utFacade/utFacade.h"))
cxxinclude(joinpath(utheaderdir, "utFacade/BasicFacadeTypes.h"))
cxxinclude(joinpath(utheaderdir, "utFacade/BasicFacadeComponents.h"))
cxxinclude(joinpath(utheaderdir, "utFacade/BasicFacade.h"))

# components
# cxxinclude(joinpath(utheaderdir, "utComponents/ApplicationPullSink.h"))
# cxxinclude(joinpath(utheaderdir, "utComponents/ApplicationPullSource.h"))
# cxxinclude(joinpath(utheaderdir, "utComponents/ApplicationPushSink.h"))
# cxxinclude(joinpath(utheaderdir, "utComponents/ApplicationPushSource.h"))
# cxxinclude(joinpath(utheaderdir, "utComponents/ApplicationEndpointsVision.h"))


# wrapping of methods and classes

# util
initLogging(name::String) = @cxx Ubitrack::Facade::initUbitrackLogging(pointer(name))


BasicFacade(components_path::String) = @cxx Ubitrack::Facade::BasicFacade(pointer(components_path))

cxx"""unsigned long long int BF_now(Ubitrack::Facade::BasicFacade& facade) { return facade.now(); }"""
now(facade) = @cxx BF_now(facade)

cxx"""bool BF_loadDataflow( Ubitrack::Facade::BasicFacade& facade, const std::string& sDfSrg ) { return facade.loadDataflow(sDfSrg); }"""
loadDataflow(facade, filename::String) = @cxx BF_loadDataflow(facade, pointer(filename))

cxx"""bool BF_loadDataflowString( Ubitrack::Facade::BasicFacade& facade, const std::string& sDataflow) { return facade.loadDataflowString(sDataflow); }"""
loadDataflowString(facade, dfdata::String) = @cxx BF_loadDataflowString(facade, pointer(dfdata))

cxx"""void BF_clearDataflow(Ubitrack::Facade::BasicFacade& facade) { facade.clearDataflow(); }"""
clearDataflow(facade) = @cxx BF_clearDataflow(facade)

cxx"""void BF_startDataflow(Ubitrack::Facade::BasicFacade& facade) { facade.startDataflow(); }"""
startDataflow(facade) = @cxx BF_startDataflow(facade)

cxx"""void BF_stopDataflow(Ubitrack::Facade::BasicFacade& facade) { facade.stopDataflow(); }"""
stopDataflow(facade) = @cxx BF_stopDataflow(facade)

cxx"""void BF_connectToServer(Ubitrack::Facade::BasicFacade& facade, const std::string& sAddress) { facade.connectToServer(sAddress); }"""
connectToServer(facade, sAddress::String) = @cxx BF_startDataflow(facade, pointer(sAddress))

cxx"""void BF_sendUtqlToServer(Ubitrack::Facade::BasicFacade& facade, const std::string& sUtqlFile) { facade.sendUtqlToServer(sUtqlFile); }"""
sendUtqlToServer(facade, sUtqlFile::String) = @cxx BF_sendUtqlToServer(facade, pointer(sUtqlFile))

cxx"""void BF_sendUtqlToServerString(Ubitrack::Facade::BasicFacade& facade, std::string& buffer) { facade.sendUtqlToServerString(buffer); }"""
sendUtqlToServerString(facade, buffer::String) = @cxx BF_sendUtqlToServerString(facade, pointer(buffer))


# cxx"""
# class JuliaObserver : public Ubitrack::Facade::BasicDataflowObserver
# {
# public:
#     virtual void notifyAddComponent( const char* sPatternName, const char* sComponentName ) throw() {
#     	$:(println("\ncomponents added")::Nothing);
#     };
#     virtual void notifyDeleteComponent( const char* sPatternName, const char* sComponentName ) throw() {
#     	$:(println("\ncomponents deleted")::Nothing);
#     };
# };

# void BF_setDataflowObserver(Ubitrack::Facade::BasicFacade& facade) { 
# 	Ubitrack::Facade::BasicDataflowObserver* observer = new JuliaObserver(); 
# 	facade.setDataflowObserver(observer); 
# }
# """
# setDataflowObserver(facade) = @cxx BF_setDataflowObserver(facade)

# cxx"""void BF_removeDataflowObserver(Ubitrack::Facade::BasicFacade& facade) { facade.removeDataflowObserver(); }"""
# removeDataflowObserver(facade) = @cxx BF_removeDataflowObserver(facade)




#end # module