#__precompile__()
module FTD2XX

@linux? begin const d2xx = "/usr/local/lib/libftd2xx.so" end: nothing
@osx? begin const d2xx = "/usr/local/lib/libftd2xx.dylib" end: nothing
@windows? begin const d2xx = "ftd2xx.dll" end: nothing

include("checkstatus.jl")
include("common_api.jl")
@linux? include("osx_linux_api.jl"):nothing
@osx? include("osx_linux_api.jl"):nothing
@windows? include("windows_api.jl"):nothing

end # module
