module Seglib

export
    randindex,
    randerror,
    contingencymatrix,
    seg2boundary,
    seg2boundaryindex,
    spdist

include("superpixel.jl")
include("metrics.jl")

matlab_homepath = begin
    try
        dirname(dirname(realpath(chomp(readall(`which matlab`)))))
    catch
        nothing
    end
end

if !is(matlab_homepath, nothing)
    include("matlab.jl")

    export
        @mquiet,
        slic,
        thinboundary,
        correspondpixels,
        gPb,
        ucm_regions,
        ucm_strength
end

end # module
