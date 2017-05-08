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

# include cpp helpers
include(joinpath(Pkg.dir("ubitrack"), "src", "Ubitrack_cpp.jl"))

# global
initLogging() = @cxx Ubitrack::Facade::initUbitrackLogging(pointer("log4cpp.conf"))
initLogging(name::AbstractString) = @cxx Ubitrack::Facade::initUbitrackLogging(pointer(name))
now() = @cxx BF_now()


# basicmeasurements
include(joinpath(Pkg.dir("ubitrack"), "src", "Ubitrack_Types.jl"))
include(joinpath(Pkg.dir("ubitrack"), "src", "Ubitrack_Facade.jl"))


include(joinpath(Pkg.dir("ubitrack"), "src", "Ubitrack_tests.jl"))


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