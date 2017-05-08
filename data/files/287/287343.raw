__precompile__()

module CompressedVolumes

using Images, HDF5, JLD, FunctionalData

export CompressedVolume, encode, encode!, decode, compact!

type CompressedVolume         
	typ::Type
    siz::Array{Int,2}
    blocksiz
	nblocks
	blocksmi
	blocksma
    encoded
	decoded
	isdirty
	isencoded
	defaultvalue
	qp
end

defaultblocksiz = [64;64;64]

clamprange(a, mi, ma) = clamp(first(a),mi,ma):clamp(last(a),mi,ma)

function CompressedVolume{T}(a::Array{T,3}; kargs...)
    siz = reshape([size(a)...], (3,1))
	r = CompressedVolume(eltype(a), siz; kargs...)
    for o = 1:r.nblocks[3], n = 1:r.nblocks[2], m = 1:r.nblocks[1]
        r.decoded[m,n,o] = a[clamprange(r.blocksiz[1]*(m-1)+(1:r.blocksiz[1]), 1, siz[1]),
            clamprange(r.blocksiz[2]*(n-1)+(1:r.blocksiz[2]), 1, siz[2]),
            clamprange(r.blocksiz[3]*(o-1)+(1:r.blocksiz[3]), 1, siz[3])]
		r.isdirty[m,n,o] = true
    end
    r
end

CompressedVolume(size::Tuple; kargs...) = CompressedVolume([size...]'; kargs...)

CompressedVolume{T}(siz::Array{T,2}; kargs...) = CompressedVolume(Float32, siz; kargs...)
function CompressedVolume{T}(typ::Type, siz::Array{T,2}; blocksiz = defaultblocksiz, defaultvalue = 0.0, useblocks = true, 
	encoded = :undefined, decoded = :undefined, qp = 28)

	siz = reshape(siz, (length(siz), 1))
	if !useblocks
		blocksiz = [typemax(Int); typemax(Int); typemax(Int)]
	end
    nblocks = ceil(Int, siz ./ blocksiz)
	blocksmi = Array(Any, nblocks...)
	blocksma = Array(Any, nblocks...)
	for o = 1:nblocks[3], n = 1:nblocks[2], m = 1:nblocks[1]
		blocksmi[m,n,o] = [blocksiz[1]*(m-1)+1; blocksiz[2]*(n-1)+1; blocksiz[3]*(o-1)+1]
		blocksma[m,n,o] = [min(blocksiz[1]*m, siz[1]); min(blocksiz[2]*n, siz[2]); min(blocksiz[3]*o, siz[3])]
	end
    #@show nblocks
	if encoded == :undefined
		encoded = {nothing for m = 1:nblocks[1], n = 1:nblocks[2], o = 1:nblocks[3]}
	end
	if decoded == :undefined
		decoded = {nothing for m = 1:nblocks[1], n = 1:nblocks[2], o = 1:nblocks[3]}
	end
    isdirty = falses(nblocks...)
    isencoded = falses(nblocks...)
    CompressedVolume(typ, siz, blocksiz, nblocks, blocksmi, blocksma, encoded, decoded, isdirty, isencoded, defaultvalue, qp)
end

encode(a; kargs...) = encode!(CompressedVolume(a; kargs...))
function encode!(a::CompressedVolume)
	for o = 1:a.nblocks[3], n = 1:a.nblocks[2], m = 1:a.nblocks[1]
        encodeblock!(a, m, n, o)
	end
	a
end

function decode!(a::CompressedVolume)
	for o = 1:a.nblocks[3], n = 1:a.nblocks[2], m = 1:a.nblocks[1]
		decodeblock!(a, m, n, o)
	end
	a
end

decode(a::CompressedVolume) = getindex(a, 1:a.siz[1], 1:a.siz[2], 1:a.siz[3])
# function decode(a::CompressedVolume)
#     r = zeros(a.siz...)
#     @show a.siz
#     for o = 1:a.nblocks[3], n = 1:a.nblocks[2], m = 1:a.nblocks[1]
# 		decodeblock!(a, m, n, o)
#         @show size(dec)
#         r[ clamprange(a.blocksiz[1]*(m-1)+(1:a.blocksiz[1]),1,a.siz[1]),
#            clamprange(a.blocksiz[2]*(n-1)+(1:a.blocksiz[2]),1,a.siz[2]),
#            clamprange(a.blocksiz[3]*(o-1)+(1:a.blocksiz[3]),1,a.siz[3])] = dec
#     end
#     r
# end


function encodeblock!(a::CompressedVolume, m, n, o)
	dec = a.decoded[m,n,o]

	if a.isdirty[m,n,o]
		# @show "dec2" dec[1]
		mi = minimum(dec)
		ma = maximum(dec)
		# @show "encodeblocks" size(dec)
		v = map(Float32,copy(dec))
		v -= mi
        d = ma - mi
        if d > 0
            v /= d
        end
		# v = uint16(v*2^16)
		

 		d = tempname()*"/"
		mkpath(d)
		for i = 1:size(v,3)
			save("$d$i.png",v[:,:,i])
		end
		outfile = d*"movie.mp4"
		run(`ffmpeg -v 0 -i $d%d.png -y -vcodec libx264 -qp $(a.qp) $outfile`)

		#@show "encodeblock" size(v)
		# a.encoded[m,n,o] = Dict(("nslices", "data", "mi", "ma"), (size(v,3), open(readbytes, outfile), mi, ma))
		a.encoded[m,n,o] = Dict("nslices" => size(v,3), "data" => open(readbytes, outfile), "mi" => mi, "ma" => ma)
		a.isdirty[m,n,o] = false
		a.isencoded[m,n,o] = true
	end
	nothing
end


blocksize(a::CompressedVolume, m, n, o) = a.blocksma[m,n,o] - a.blocksmi[m,n,o] + 1
function decodeblock!(a::CompressedVolume, m, n, o)
	if a.isencoded[m,n,o]
		enc = a.encoded[m,n,o]
		d = tempname()*"/"
		mkpath(d)
		outfile = d*"movie.mp4"
		open(io -> write(io, enc["data"]), outfile,"w")
		run(`ffmpeg -i $outfile -v 0 -y $d%d.png`)
		#@profile rawimread("$(d)1.png")
		
		slices = pmap(i -> rawimread("$d$i.png"), 1:enc["nslices"])
		dec = zeros([size(slices[1])...,length(slices)]...)
		# @show dec
		for i = 1:size(dec,3)
			dec[:,:,i] = slices[i]
		end
		dec = dec * (enc["ma"]-enc["mi"]) + enc["mi"]
		a.decoded[m,n,o] = dec
		a.isdirty[m,n,o] = false
	else
		a.decoded[m,n,o] = ones(a.typ, blocksize(a,m,n,o)...) * a.defaultvalue
		a.isdirty[m,n,o] = false
	end
	a
end


getindex(a::CompressedVolume, ms::Integer, ns::Integer, os::Integer) = accessindex(a, ms, ns, os, 0, false)[1]
getindex(a::CompressedVolume, ms, ns, os) = accessindex(a, ms, ns, os, 0, false)
setindex!(a::CompressedVolume, v, ms, ns, os) = accessindex(a, ms, ns, os, v, true)

function accessindex(a::CompressedVolume, ms, ns, os, v, set)
	mblocks = unique(ceil(Int,ms/a.blocksiz[1]))
	nblocks = unique(ceil(Int,ns/a.blocksiz[2]))
	oblocks = unique(ceil(Int,os/a.blocksiz[3]))
	# @show mblocks nblocks oblocks

	r = set ? 0. : fill(NaN, maximum(ms)-minimum(ms)+1, maximum(ns)-minimum(ns)+1, maximum(os)-minimum(os)+1)
	mi = [minimum(ms); minimum(ns); minimum(os)] - 1
	
	# @show a.blocksmi a.blocksma


	for o = oblocks, n = nblocks, m = mblocks
		if a.decoded[m,n,o] == nothing
			decodeblock!(a, m, n, o)
		end
		bmi = a.blocksmi[m,n,o]
		rm = clamprange(ms, bmi[1], a.blocksma[m,n,o][1])
		rn = clamprange(ns, bmi[2], a.blocksma[m,n,o][2])
		ro = clamprange(os, bmi[3], a.blocksma[m,n,o][3])

		# @show size(r)
		# @show rm rn ro mi
		# @show size(a.decoded[m,n,o])
		# @show r[ rm - mi[1], rn - mi[2], ro - mi[3] ]  
		
		if set
			if typeof(v)<:Number
				a.decoded[m,n,o][rm - bmi[1] + 1, rn - bmi[2] + 1, ro - bmi[3] + 1] = v
			else
				a.decoded[m,n,o][rm - bmi[1] + 1, rn - bmi[2] + 1, ro - bmi[3] + 1] = 
					v[ rm - mi[1], rn - mi[2], ro - mi[3] ]
			end
			a.isdirty[m,n,o] = true
		else
			r[ rm - mi[1], rn - mi[2], ro - mi[3] ] = 
				a.decoded[m,n,o][rm - bmi[1] + 1, rn - bmi[2] + 1, ro - bmi[3] + 1]
		end
	end
	set ? a : r
end

function compact!(a::CompressedVolume)
	a.decoded[find(!a.isdirty)] = nothing
	a
end

function rawimread(a)
    img = load(a)
    img = convert(Array,img)
    try 
        float(img)
    catch
        #@show typeof(img[1])
        r = zeros(size(img))
        for i = 1:length(img)
            r[i] = img[i].r
        end
        r
    end
end




end # module
