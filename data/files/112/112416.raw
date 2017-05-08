module CvGeom

# package code goes here

export hom, ihom, homNorm, homNormRobust, isHomEq, norm1!, fitConic
#export Point2, InterestPoint, SRF


function hom(A)
  sz = size(A)
  o = ones(eltype(A), tuple(1, sz[2:end]...))
  return cat(1, A, o)
end

function ihom{T<:Number}(A::Vector{T})
  return A[1:end-1] / A[end]
end

function ihom{T<:Number}(A::Array{T, 2})
  return A[1:end-1,:] ./ A[end, :]
end

function homNorm{T<:Number}(a::Vector{T})
  return a / a[end]
end

function homNormRobust{T<:Number}(a::Vector{T})
  bestMag = abs(a[1])
  bestIdx = 1
  N = size(a)[1]
  for idx=2:N
    mag = abs(a[idx])
    if mag > bestMag
      bestMag = mag
      bestIdx = idx
    end
  end
  return a / a[bestIdx]
end

function norm1!{T<:FloatingPoint}(a::Vector{T})
  a = a / norm(a)
end

function isHomEq(a::Vector, b::Vector)
  if size(a) != size(b)
    return false
  end

  return homNormRobust(a) == homNormRobust(b)

end

function isPoint2OnLine{T<:Number}(p::Vector{T})
  @assert size(p) == 2
  return false
end

function fitConic{T<:Number}(points::Array{T,2})
  d,n = size(points)
  @assert d==2
  @assert n>=5

  A = Array(Float64, (n, 6))
  for i=1:n
    x,y = points[:,i]
    A[i,:] = [x*x x*y y*y x y 1]
  end

  _,d,V = svd(A, thin=false)

  return V[:,end], A, d
end


type Point2{T<:Real}
  x::T
  y::T

  Point2() = new()
  Point2(v) = new(v, v)
  Point2(x, y) = new(x, y)
end

# flesh out parametric constructors
Point2{T<:Real}(v::T) = Point2{T}(v)
Point2{T<:Real}(x::T, y::T) = Point2{T}(x,y)
# some additional constructors for convenience
Point2(x::Real, y::Real) = Point2(promote(x,y)...)
# conversion between Point2 types
import Base.convert
convert{T<:Real}(::Type{Point2{T}}, pt::Point2) = Point2{T}(convert(T, pt.x), convert(T, pt.y))

type InterestPoint{T<:Real}
  pt::Point2{T}
  scale::T
  orientation::T

  InterestPoint() = new(Point2{T}(), -1, -1)
  InterestPoint(pt, scale, orientation) = new(pt, scale, orientation)
end

# flesh out parametric constructors
InterestPoint{T<:Real}(pt::Point2{T}, s::T, o::T) = InterestPoint{T}(pt, s, o)
# some additional constructors for convenience
InterestPoint{T<:Real}(pt::Point2{T}) = (ip = InterestPoint{T}(); ip.pt = pt; return ip)
InterestPoint{T<:Real}(x::T, y::T, s::T, o::T) = InterestPoint(Point2(x,y), s, o)
InterestPoint(x::Real, y::Real, s::Real, o::Real) = InterestPoint(promote(x,y,s,o)...)
InterestPoint{T<:Real}(::Type{T}, x::Real, y::Real, s::Real, o::Real) = InterestPoint(convert((T,T,T,T), (x,y,s,o)))


#########################################
## Match (with and without image index)
#########################################
type Match_0{T<:Number}
    img1_idx::Unsigned
    img2_idx::Unsigned
    img1_pt_idx::Unsigned
    img2_pt_idx::Unsigned
    score::T
end
Match_0{T<:Number}(img1_idx, img2_idx, img1_pt_idx, img2_pt_idx, score::T) =
    Match_0{T}(img1_idx, img2_idx, img1_pt_idx, img2_pt_idx, score)

type Match_1{T<:Number}
    idx1::Uint
    idx2::Uint
    score::T
end
Match_1{T<:Number}(idx1, idx2, score::T) =
  Match_1{T}(idx1, idx2, score)

########################################
## countBits
########################################
export countBits
function countBits_naive{T<:Unsigned}(a::T)
    sum::Uint = 0
    while(bool(a))
        sum += a&1
        a >>>= 1
    end
    return uint8(sum)
end

LUT8  = Uint8[countBits_naive(a) for a in 0x00:0xFF]
LUT16 = Uint8[countBits_naive(a) for a in 0x0000:0xFFFF]

function countBits(a::Uint8)
    return LUT8[a+1]
end

function countBits(a::Uint16)
    return LUT16[a+1]
end

function countBits{T<:Unsigned}(a::T)
    sum::Uint = 0
    while(bool(a))
        sum += LUT16[uint16(a) + 1]
        a >>>= 16
    end
    return uint8(sum)
end

function countBits!(ret, a)
    for (i,v) in enumerate(a)
        ret[i] = countBits(v)
    end
end

function countBits!{T<:Unsigned}(ret::Vector{Uint8}, a::Vector{T})
  for i=1:length(a)
    ret[i] = countBits(a[i])
  end
end

function countBits{T<:Unsigned}(a::AbstractArray{T})
    ret = similar(a, Uint8)
    countBits!(ret, a)
    return ret
end

#########################################
## Hamming distance
#########################################
export distance_hamming, distance2_hamming
function distance_hamming{T<:Unsigned}(p1::Vector{T}, p2::Vector{T})
    diff = p1 $ p2
    #display(diff)
    return uint8(sum(countBits(diff)))
end
function distance2_hamming{T<:Unsigned}(p1::Matrix{T}, p2::Matrix{T})
    d1, n1 = size(p1)
    d2, n2 = size(p2)
    assert(d1 == d2)
    ret = Array(Uint8, d1, n1, n2)
    for j=1:n2
        for i=1:n1
            for k=1:d1
                ret[k,i,j] = countBits_naive(p1[k,i] $ p2[k,j])
            end
        end
    end
    return sum(ret,1)
end

######################################
## nearest neighbors
######################################
export knnSearch
function knnSearch(tDescs, qDescs, k, dist_fn)
    assert(size(tDescs,1) == size(qDescs,1))
    assert(k >= 1)
    nT = size(tDescs,2)
    nQ = size(qDescs,2)
    assert(nT >= k)
    ret = Array(Match_1{Uint8}, k, nQ)

    for i=1:nQ
        # initialize first match with first train descriptor
        ret[1,i] = Match_1(1, i, dist_fn(tDescs[:,1], qDescs[:,i]))
        # initialize next k-1 matches with next k-1 train descriptors (with sorting)
        for j = 2:k
            mji = Match_1(j, i, dist_fn(tDescs[:,j], qDescs[:,i]))
            l = 1
            while l < j
                if mji.score < ret[l,i].score
                    ret[l+1:j,i] = ret[l:j-1,i]
                    break;
                end
                l += 1
            end
            ret[l,i] = mji
        end
        # go through the rest of the train descriptors
        for j=k+1:nT
            mji = Match_1(j, i, dist_fn(tDescs[:,j], qDescs[:,i]))
            l = 1
            for l = 1:k
                if mji.score < ret[l,i].score
                    ret[l+1:k,i] = ret[l:k-1,i]
                    ret[l,i] = mji
                    break;
                end
            end
        end
    end

    return ret
end

end # module
