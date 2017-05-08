# MATLAB related functionality
using MATLAB

##############################################################################
##
## Matlab setup
##
##############################################################################

# Give access to BSR Benchmark code
@matlab addpath("/ais/gobi3/u/jsnell/projects/eccv2014/BSR/bench/benchmarks")

# Give access to BSR lib code for gPb and UCM
@matlab addpath("/u/jsnell/gobi3/projects/eccv2014/BSR/grouping/lib")

function mstatementquiet(ex::Expr)
    ss = IOBuffer()
    MATLAB.write_mstatement(ss, ex) 
    print(ss, ";")
    bytestring(ss)
end

macro mquiet(ex)
    :( MATLAB.eval_string($(mstatementquiet(ex))) )
end

##############################################################################
##
## Algorithms for computing superpixels
##
##############################################################################

function slic{T<:Real}(img::Array{T}, regionsize::Int=20, regularizer::Float64=0.1)
    @mput img
    eval_string("img = im2single(img);")
    eval_string("seg = vl_slic(img, $regionsize, $regularizer);")
    convert(Matrix{Int}, @mget seg) + 1     # minimum segment should be 1
end

##############################################################################
##
## Conversion functions
##
##############################################################################

function thinboundary(bmap::BitMatrix)
    @mput bmap
    @mquiet bmapthin = bwmorph(bmap, "thin", inf)
    convert(BitArray, @mget bmapthin)
end

function correspondpixels(bmap1::BitMatrix, bmap2::BitMatrix, maxdist::Float64=0.0075, outliercost::Float64=100.0)
    @mput bmap1  bmap2 maxdist outliercost
    @mquiet (match1, match2, cost, oc) = correspondPixels(double(bmap1), double(bmap2), maxdist, outliercost)
    @mget match1 match2 cost oc
    ([int(match1)], [int(match2)], cost, oc)
end

##############################################################################
##
## Compute gPb
##
##############################################################################

function gPb{T<:Real}(img::Array{T})
    @mput img
    @mquiet gPb_orient = globalPb_im(img)
    @mget gPb_orient
end

##############################################################################
##
## UCM
##
##############################################################################

function ucm_regions{T<:Real}(img::Array{T}, scale::T=0.0)
    gpb_res = gPb(img)
    @mput gpb_res
    eval_string("ucm2 = contours2ucm(gpb_res, 'doubleSize');")
    eval_string("labels2 = bwlabel(ucm2 <= $scale);")
    eval_string("labels = labels2(2:2:end, 2:2:end);")
    convert(Matrix{Int}, @mget labels)
end

function ucm_regions{T<:Real}(img::Array{T}, scales::Vector{T})
    gpb_res = gPb(img)
    @mput gpb_res
    eval_string("ucm2 = contours2ucm(gpb_res, 'doubleSize');")
    alllabels = map(scales) do scale
        eval_string("labels2 = bwlabel(ucm2 <= $scale);")
        eval_string("labels = labels2(2:2:end, 2:2:end);")
        convert(Matrix{Int}, @mget labels)
    end
    Matrix{Int}[l for l in alllabels]
end

function ucm_strength{T<:Real}(img::Array{T}, scale::T=0.0)
    # returns the result of a 0.0 strength ucm,
    # along with the corresponding horizontal and vertical strengths
    gpb_res = gPb(img)
    @mput gpb_res
    eval_string("ucm2 = contours2ucm(gpb_res, 'doubleSize');")
    eval_string("labels2 = bwlabel(ucm2 <= $scale);")
    eval_string("labels = labels2(2:2:end, 2:2:end);")
    labels = convert(Matrix{Int}, @mget labels)

    ucm2 = @mget ucm2

    hstrength = ucm2[2:2:end, 3:2:end]
    vstrength = ucm2[3:2:end, 2:2:end]

    labels, hstrength, vstrength
end
