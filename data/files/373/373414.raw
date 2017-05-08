"""
PCL I/O

Reading / writing pcd/obj/ply files in Julia.

## Exports

$(EXPORTS)
"""
module PCLIO

export loadPCDFile, loadOBJFile, loadPLYFile, load, savePCDFile,
    saveOBJFile, savePLYFile

using LibPCL
using PCLCommon
using Cxx
using DocStringExtensions

libpcl_io = LibPCL.find_library_e("libpcl_io")
try
    Libdl.dlopen(libpcl_io, Libdl.RTLD_GLOBAL)
catch e
    warn("You might need to set DYLD_LIBRARY_PATH to load dependencies proeprty.")
    rethrow(e)
end

cxx"""
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/auto_io.h>
"""

for f in [
        :loadPCDFile,
        :loadOBJFile,
        :loadPLYFile,
        :load,
        ]
    ex = Expr(:macrocall, Symbol("@icxx_str"),
        "pcl::io::$f(\$(pointer(s)), *\$(cloud.handle));")
    @eval begin
        function $f{T}(s::AbstractString, cloud::PointCloud{T})
            ret = $ex
            if ret != 0
                error("failed to $f: code $ret")
            end
            ret
        end
    end
end

for f in [
        :savePCDFile,
        :saveOBJFile,
        :savePLYFile,
        ]
    ex = Expr(:macrocall, Symbol("@icxx_str"),
        "pcl::io::$f(\$(pointer(s)), *\$(cloud.handle), \$binary_mode);")
    @eval begin
        function $f{T}(s::AbstractString, cloud::PointCloud{T};
                binary_mode::Bool=true)
            ret = $ex
            if ret != 0
                error("failed to $f: code $ret")
            end
            ret
        end
    end
end

# Create PointCloud instance and then load PCD data
function (::Type{PointCloud{T}}){T}(path::AbstractString)
    handle = @boostsharedptr "pcl::PointCloud<\$T>"
    cloud = PointCloud(handle)
    @assert !isempty(path)
    load(path, cloud)
    return cloud
end

end # module
