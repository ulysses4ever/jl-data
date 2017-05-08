module ubitrack

using Cxx
using Compat, Compat.Libdl

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
    Libdl.dlopen(joinpath(utlibdir,i), Libdl.RTLD_GLOBAL)==C_NULL ? throw(ArgumentError("Skip loading $(i)")): nothing
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

# facade
cxxinclude(joinpath(utheaderdir, "utFacade/utFacade.h"))
cxxinclude(joinpath(utheaderdir, "utFacade/BasicFacadeTypes.h"))
cxxinclude(joinpath(utheaderdir, "utFacade/BasicFacadeComponents.h"))
cxxinclude(joinpath(utheaderdir, "utFacade/BasicFacade.h"))

# wrapping of methods and classes

# util
initLogging(name::AbstractString) = @cxx Ubitrack::Facade::initUbitrackLogging(pointer(name))

# basicmeasurements



# basicfacade
BasicFacade(components_path::AbstractString) = @cxx Ubitrack::Facade::BasicFacade(pointer(components_path))

cxx"""unsigned long long int BF_now() { return Ubitrack::Facade::BasicFacade::now(); }"""
now() = @cxx BF_now()

cxx"""bool BF_loadDataflow( Ubitrack::Facade::BasicFacade& facade, const char* sDfSrg ) { return facade.loadDataflow(sDfSrg); }"""
loadDataflow(facade, filename::AbstractString) = @cxx BF_loadDataflow(facade, pointer(filename))

cxx"""bool BF_loadDataflowString( Ubitrack::Facade::BasicFacade& facade, const char* sDataflow) { return facade.loadDataflowString(sDataflow); }"""
loadDataflowString(facade, dfdata::AbstractString) = @cxx BF_loadDataflowString(facade, pointer(dfdata))

cxx"""void BF_clearDataflow(Ubitrack::Facade::BasicFacade& facade) { facade.clearDataflow(); }"""
clearDataflow(facade) = @cxx BF_clearDataflow(facade)

cxx"""void BF_startDataflow(Ubitrack::Facade::BasicFacade& facade) { facade.startDataflow(); }"""
startDataflow(facade) = @cxx BF_startDataflow(facade)

cxx"""void BF_stopDataflow(Ubitrack::Facade::BasicFacade& facade) { facade.stopDataflow(); }"""
stopDataflow(facade) = @cxx BF_stopDataflow(facade)

cxx"""void BF_connectToServer(Ubitrack::Facade::BasicFacade& facade, const char* sAddress) { facade.connectToServer(sAddress); }"""
connectToServer(facade, sAddress::AbstractString) = @cxx BF_startDataflow(facade, pointer(sAddress))

cxx"""void BF_sendUtqlToServer(Ubitrack::Facade::BasicFacade& facade, const char* sUtqlFile) { facade.sendUtqlToServer(sUtqlFile); }"""
sendUtqlToServer(facade, sUtqlFile::AbstractString) = @cxx BF_sendUtqlToServer(facade, pointer(sUtqlFile))

cxx"""void BF_sendUtqlToServerString(Ubitrack::Facade::BasicFacade& facade, const char*  buffer) { facade.sendUtqlToServerString(buffer); }"""
sendUtqlToServerString(facade, buffer::AbstractString) = @cxx BF_sendUtqlToServerString(facade, pointer(buffer))


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




end # module ubitrack