module LibPCL

# PCL main dependenices are:
# - boost
# - flann
# - eigen
# - vtk (for visualization, optional)

const VERBOSE = Bool(parse(Int, get(ENV, "LIBPCLJL_VERBOSE", "0")))

const BOOST_INCLUDE_DIR = get(ENV, "BOOST_INCLUDE_DIR",
    @osx? "/usr/local/include" : "/usr/include")
const FLANN_INCLUDE_DIR = get(ENV, "FLANN_INCLUDE_DIR",
    @osx? "/usr/local/include" : "/usr/include")
const EIGEN_INCLUDE_DIR = get(ENV, "EIGEN_INCLUDE_DIR",
    @osx? "/usr/local/include/eigen3" : "/usr/include/eigen3")

searchdir(path, key) = filter(x->contains(x, key), readdir(path))

const VTK_INCLUDE_DIR_PARENT = get(ENV, "VTK_INCLUDE_DIR_PARENT",
    @osx? "/usr/local/include" : "/usr/include")

# Search GUI backend
vtk_dirs = searchdir(VTK_INCLUDE_DIR_PARENT, "vtk-")
const VTK_INCLUDE_DIR = get(ENV, "VTK_INCLUDE_DIR",
    isempty(vtk_dirs) ? "" : joinpath(VTK_INCLUDE_DIR_PARENT, vtk_dirs[1]))

const has_vtk_backend = isfile(joinpath(VTK_INCLUDE_DIR, "vtkVersion.h"))
if has_vtk_backend
    VERBOSE && info("vtk include directory found: $VTK_INCLUDE_DIR")
end

using BinDeps

# Load required dependency
deps = joinpath(Pkg.dir("LibPCL"), "deps", "deps.jl")
if isfile(deps)
    include(deps)
else
    error("LibPCL not properly installed. Please run Pkg.build(\"LibPCL\")")
end

using Cxx

Libdl.dlopen(libpcl_common, Libdl.RTLD_GLOBAL)

const libdir = dirname(libpcl_common)
const libext = splitext(libpcl_common)[2]

function find_library_e(mod, libdirs=[libdir], ext=libext)
    for libdir in libdirs
        libpath = joinpath(libdir, string(mod, ext))
        if isfile(libpath)
            return libpath
        end
    end

    error("Cannot find $mod")
end

function get_pcl_version(top)
    dirs = searchdir(top, "pcl-")
    isempty(dirs) && error("could not find pcl directory")
    pcl_dir = dirs[1]
    return pcl_dir[5:end]
end

# Check for include directory
const _incdir = replace(libdir, "\/lib", "\/include")
@assert isdir(_incdir)
const pcl_version = get_pcl_version(_incdir)
VERBOSE && info("pcl_version: $pcl_version")
const incdir = joinpath(_incdir, "pcl-$pcl_version")

# Make sure vtk libraries are loaded before calling @cxx vtkVersion::xxx()
if has_vtk_backend
    cxxinclude(joinpath(VTK_INCLUDE_DIR, "vtkVersion.h"))
    global const vtk_version = bytestring(icxx"vtkVersion::GetVTKVersion();")
end

function add_header_dirs(top=incdir)
    # Boost (required)
    addHeaderDir(BOOST_INCLUDE_DIR, kind=C_System)

    # Eigen (required)
    addHeaderDir(EIGEN_INCLUDE_DIR, kind=C_System)

    # FLANN (required)
    addHeaderDir(FLANN_INCLUDE_DIR, kind=C_System)

    # VTK (optional)
    has_vtk_backend && addHeaderDir(VTK_INCLUDE_DIR, kind=C_System)

    # PCL top directory
    addHeaderDir(top, kind=C_System)
    addHeaderDir(joinpath(top, "pcl"), kind=C_System)
end

function include_toplevel_headers()
    # This is necesarry, but not sure why...
    cxx"""#include <iostream>"""

    # top level
    VERBOSE && info("Include pcl top-level headers")
    cxx"""
    #include <pcl/pcl_base.h>
    #include <pcl/point_cloud.h>
    #include <pcl/point_types.h>
    #include <pcl/correspondence.h>
    #include <pcl/ModelCoefficients.h>
    """
end

# Add header search paths
add_header_dirs(incdir)

# Once we add proper header search paths, include necessary headers
include_toplevel_headers()

# Check boost version
cxxinclude(joinpath(BOOST_INCLUDE_DIR, "boost/version.hpp"))
const _BOOST_VERSION = icxx"BOOST_VERSION;"
const BOOST_VERSION_MAJOR = trunc(Int, _BOOST_VERSION / 100000)
const BOOST_VERSION_MINOR = trunc(Int, _BOOST_VERSION / 100 % 1000)
const BOOST_VERSION_PATCH = trunc(Int, _BOOST_VERSION % 100)
const BOOST_VERSION = join([BOOST_VERSION_MAJOR, BOOST_VERSION_MINOR, BOOST_VERSION_PATCH], ".")
VERBOSE && info("boost version: $BOOST_VERSION")

# Check FLANN vesion
# make sure FLANN_INCLUDE_DIR is addded as kind=C_System
cxxinclude(joinpath(FLANN_INCLUDE_DIR, "flann/flann.h"))
cxx"""
namespace libpcl {
std::string getFLANNVersion() { return FLANN_VERSION_; }
}
"""
getFLANNVersion() = bytestring(icxx"libpcl::getFLANNVersion();")
VERBOSE && info("FLANN version: $(getFLANNVersion())")

end # module
