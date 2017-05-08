#__precompile__()
module FTD2XX

include("getFTD2XX.jl")

include("checkstatus.jl")
include("common_API.jl")
@linux? include("osx_linux_API.jl"):nothing
@osx? include("osx_linux_API.jl"):nothing
@windows? include("windows_API.jl"):nothing

end # module
