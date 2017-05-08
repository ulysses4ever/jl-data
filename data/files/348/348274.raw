println("---")
using FactCheck, CompressedVolumes, FunctionalData

shouldtest(f, a) = length(ARGS) == 0 || in(a, ARGS) ? facts(f, a) : nothing
shouldtestcontext(f, a) = length(ARGS) < 2 || a == ARGS[2] ? facts(f, a) : nothing


shouldtest("overall") do
end

siz(a) = reshape([size(a)...], (3,1))

shouldtest("init") do

    # shouldtestcontext("fromarray") do
		# v = zeros(512,512,10)
		# for i in 1:size(v,3) v[:,:,i] = CompressedVolumes.rawimread("/Users/rene/temp/in/$i.png") end
		# v ./= maximum(v);
		# @time a = encode!(CompressedVolume(v, qp = 0))
		# @time r = decode(a)
		# @fact size(r) --> size(v)
		# @fact r[1:10] --> v[1:10]
		# @fact mean(r) --> mean(v)
    # end

	shouldtestcontext("fromsize") do
		a = CompressedVolume((5,4,3), qp = 0)
		c = decode(encode!(a))
		@fact siz(c) --> a.siz
		@fact c --> zeros(5,4,3)

		b = encode((5,4,3), qp = 0, defaultvalue = 1)
   		d = decode(b)
		@fact siz(d) --> b.siz
		@fact d --> ones(5,4,3)
	end
end

shouldtest("getindex") do
	m = 5; n = 4; o = 3
	v = zeros(m,n,o)
	v[:] = 1:length(v)
	# @show v
	a = encode(v, qp = 0)
	b = a[1:m,1:n,1:o]
	@fact b --> v

	a2 = encode(v, qp = 0, blocksiz = [1;1;1])
	b2 = a2[1:m,1:n,1:o]
	@fact b2 --> v

	a3 = encode(v, qp = 0, blocksiz = [2;3;2])
	b3 = a3[1:m,1:n,1:o]
	@fact b3 --> v
end

shouldtest("setindex!") do
	m = 5; n = 4; o = 3
	v = zeros(m,n,o)
	v[:] = 1:length(v)
	# @show v
	a = CompressedVolume(v)
	a[1,1,1] = 10.
	@fact a[1,1,1] --> 10.
	@fact a[1:2,1,1] --> reshape([10., 2.], 2,1,1)

	a = CompressedVolume((m,n,o))
	a[1,1,1] = 10.
	@fact a[1,1,1] --> 10.
	@fact a[1:2,1,1] --> reshape([10., 0.], 2,1,1)

	a[1,1:4,1] = 10.
	@fact a[1,3,1] --> 10.
	@fact a[1:2,2,1] --> reshape([10., 0.], 2,1,1)
end

shouldtest("compact!") do
	v = rand(1:100,3,4,2)
	a = encode(v, qp = 0)
	b = decode(a)
	compact!(a)
	c = decode(a)
	@fact maximum(abs(c-v))<0.5 --> true
end





