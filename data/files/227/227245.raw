# time: 2014-12-27 14:29:21 CST
# mode: julia
	using TensorOperations, IndexNotation
# time: 2014-12-27 14:29:30 CST
# mode: julia
	m = (3,4,5)			#  tensor size
# time: 2014-12-27 14:29:30 CST
# mode: julia
	d = length (m)		#  d-mode tensor
# time: 2014-12-27 14:29:30 CST
# mode: julia
	T = rand (m)
# time: 2014-12-27 14:29:34 CST
# mode: julia
	function f(j)
		x = rand (m [j])
		x / norm(x)
		end
# time: 2014-12-27 14:29:34 CST
# mode: julia
	x0 = ntuple (d, f)		# random starting point
# time: 2014-12-27 14:35:28 CST
# mode: julia
	help(Range)
# time: 2014-12-27 14:38:09 CST
# mode: julia
	help(cat)
# time: 2014-12-27 14:38:16 CST
# mode: julia
	cat(1:3,5:6)
# time: 2014-12-27 14:38:22 CST
# mode: julia
	cat(1,1:3,5:6)
# time: 2014-12-27 14:38:49 CST
# mode: julia
	for j in cat(1,1:3,5:8) do
	print(j)
	end
	
	
	end
# time: 2014-12-27 14:39:06 CST
# mode: julia
	for j in cat(1,1:3,5:8)
	print(j)
	end
	
	
	end
# time: 2014-12-27 14:39:11 CST
# mode: julia
	for j in cat(1,1:3,5:8)
	print(j)
	end
# time: 2014-12-27 14:39:22 CST
# mode: julia
	1:0
# time: 2014-12-27 14:39:27 CST
# mode: julia
	[1:0]
# time: 2014-12-27 14:40:01 CST
# mode: julia
	[5:4]
# time: 2014-12-27 14:40:07 CST
# mode: julia
	[5:4:-1]
# time: 2014-12-27 14:40:09 CST
# mode: julia
	[5:4:1]
# time: 2014-12-27 14:40:51 CST
# mode: julia
	tensorproduct(x0[1],x0[2])
# time: 2014-12-27 14:41:44 CST
# mode: julia
	tensorproduct(x0[1],"a",x0[2],"b")
# time: 2014-12-27 14:41:54 CST
# mode: julia
	tensorproduct(x0[1],l"a",x0[2],l"b")
# time: 2014-12-27 14:42:20 CST
# mode: julia
	x0[1]
# time: 2014-12-27 14:42:22 CST
# mode: julia
	x0[2]
# time: 2014-12-27 15:01:45 CST
# mode: julia
	x0[1] * x0[2]
# time: 2014-12-27 15:01:50 CST
# mode: julia
	x0[1] * t(x0[2])
# time: 2014-12-27 15:01:53 CST
# mode: julia
	x0[1] * T(x0[2])
# time: 2014-12-27 15:02:00 CST
# mode: julia
	help(T)
# time: 2014-12-27 15:02:11 CST
# mode: julia
	help(t)
# time: 2014-12-27 15:26:00 CST
# mode: julia
	x0[1] * transpose(x0[2])
# time: 2014-12-27 15:26:08 CST
# mode: julia
	transpose(x0[2]) * x0[1]
# time: 2014-12-27 15:26:26 CST
# mode: julia
	transpose(x0[1]) * x0[1]
# time: 2014-12-27 15:26:57 CST
# mode: julia
	methods(tensorproduct)
# time: 2014-12-27 15:27:42 CST
# mode: julia
	tensorproduct(x0[1],l"a",x0[2],l"b")
# time: 2014-12-27 15:28:04 CST
# mode: julia
	tensorproduct(x0[1], l"a,", x0[2], l"b,")
# time: 2014-12-27 15:28:18 CST
# mode: julia
	l"4"
# time: 2014-12-27 15:29:01 CST
# mode: julia
	tensorproduct(x0[1], 'a', x0[2], 'b')
# time: 2014-12-27 15:29:21 CST
# mode: julia
	l"a"
# time: 2014-12-27 15:29:30 CST
# mode: julia
	tensorproduct(x0[1], l'a', x0[2], l'b')
# time: 2014-12-27 15:29:39 CST
# mode: julia
	tensorproduct(x0[1], l"a", x0[2], l"b")
# time: 2014-12-27 15:30:00 CST
# mode: julia
	tensorproduct(x0[1], 1, x0[2], 1)
# time: 2014-12-27 15:30:09 CST
# mode: julia
	tensorproduct(x0[1], 'a', x0[2], 'b')
# time: 2014-12-27 15:30:37 CST
# mode: julia
	tensorproduct (tensorproduct(x0[1], 'a', x0[2], 'b'), l"a,b", x0[3], 'c')
# time: 2014-12-27 15:30:48 CST
# mode: julia
	tensorproduct (tensorproduct(x0[1], 'a', x0[2], 'b'), ('a','b'), x0[3], 'c')
# time: 2014-12-27 15:30:56 CST
# mode: julia
	tensorproduct (tensorproduct(x0[1], 'a', x0[2], 'b'), 1:2, x0[3], 'c')
# time: 2014-12-27 15:31:09 CST
# mode: julia
	tensorproduct (tensorproduct(x0[1], 'a', x0[2], 'b'), 1:2, x0[3], 3)
# time: 2014-12-27 15:31:13 CST
# mode: julia
	tensorproduct (tensorproduct(x0[1], 'a', x0[2], 'b'), 1, x0[3], 3)
# time: 2014-12-27 15:31:18 CST
# mode: julia
	tensorproduct (tensorproduct(x0[1], 'a', x0[2], 'b'), 1:2, x0[3], 3)
# time: 2014-12-27 15:34:28 CST
# mode: julia
	length ((2,3,5))
# time: 2014-12-27 15:34:35 CST
# mode: julia
	(2,3,5) [2:3]
# time: 2014-12-27 15:35:18 CST
# mode: julia
	i = 1
# time: 2014-12-27 15:35:29 CST
# mode: julia
	x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 15:35:37 CST
# mode: julia
	x =x0
# time: 2014-12-27 15:35:39 CST
# mode: julia
	x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 15:35:47 CST
# mode: julia
	i=2
# time: 2014-12-27 15:35:49 CST
# mode: julia
	x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 15:35:54 CST
# mode: julia
	i=3
# time: 2014-12-27 15:35:55 CST
# mode: julia
	x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 15:36:39 CST
# mode: julia
	Array
# time: 2014-12-27 15:36:41 CST
# mode: julia
	array()
# time: 2014-12-27 15:36:43 CST
# mode: julia
	Array()
# time: 2014-12-27 15:36:47 CST
# mode: julia
	Array(Float32)
# time: 2014-12-27 15:36:59 CST
# mode: julia
	typeof(x)
# time: 2014-12-27 15:37:01 CST
# mode: julia
	typeof(x[1])
# time: 2014-12-27 15:37:33 CST
# mode: julia
	tensorproduct(Array(Float64),'',x0[1],1)
# time: 2014-12-27 15:37:37 CST
# mode: julia
	tensorproduct(Array(Float64),0,x0[1],1)
# time: 2014-12-27 15:37:42 CST
# mode: julia
	tensorproduct(Array(Float64),1,x0[1],2)
# time: 2014-12-27 15:39:24 CST
# mode: julia
	i =3
# time: 2014-12-27 15:39:29 CST
# mode: julia
	z_fact = x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 15:39:45 CST
# mode: julia
	z_fact[1]
# time: 2014-12-27 15:39:53 CST
# mode: julia
	z_fact[2:length(z_fact)]
# time: 2014-12-27 15:40:01 CST
# mode: julia
	length(z_fact)
# time: 2014-12-27 15:40:10 CST
# mode: julia
	reduce (*, z_fact[1], z_fact[2:length(z_fact)])
# time: 2014-12-27 15:40:51 CST
# mode: julia
	prod(z_fact)
# time: 2014-12-27 15:41:34 CST
# mode: julia
	z_fact
# time: 2014-12-27 15:41:38 CST
# mode: julia
	typeof(z_fact[1])
# time: 2014-12-27 15:41:43 CST
# mode: julia
	typeof(z_fact[l"a"])
# time: 2014-12-27 15:42:00 CST
# mode: julia
	z_fact[1]
# time: 2014-12-27 15:42:04 CST
# mode: julia
	z_fact[1][l"a"]
# time: 2014-12-27 15:42:56 CST
# mode: julia
	'a'+1
# time: 2014-12-27 15:42:59 CST
# mode: julia
	"a"+1
# time: 2014-12-27 15:47:45 CST
# mode: julia
	letters
# time: 2014-12-27 15:47:48 CST
# mode: julia
	l'a'
# time: 2014-12-27 15:49:26 CST
# mode: julia
	help(string)
# time: 2014-12-27 15:49:32 CST
# mode: julia
	string('a')
# time: 2014-12-27 15:49:39 CST
# mode: julia
	l string('a')
# time: 2014-12-27 15:49:43 CST
# mode: julia
	lstring('a')
# time: 2014-12-27 15:50:08 CST
# mode: julia
	help(LabelList)
# time: 2014-12-27 15:50:20 CST
# mode: julia
	apropos(LabelList)
# time: 2014-12-27 15:50:34 CST
# mode: julia
	methods(LabelList)
# time: 2014-12-27 15:50:51 CST
# mode: julia
	LabelList('a')
# time: 2014-12-27 15:51:02 CST
# mode: julia
	LabelList(array('a'))
# time: 2014-12-27 15:51:05 CST
# mode: julia
	LabelList(Array('a'))
# time: 2014-12-27 15:51:08 CST
# mode: julia
	Array('a')
# time: 2014-12-27 15:51:11 CST
# mode: julia
	Array("a")
# time: 2014-12-27 15:51:50 CST
# mode: julia
	help(Symbol)
# time: 2014-12-27 15:51:55 CST
# mode: julia
	Symbol
# time: 2014-12-27 15:51:57 CST
# mode: julia
	Symbol(a)
# time: 2014-12-27 15:52:00 CST
# mode: julia
	Symbol('a')
# time: 2014-12-27 15:52:06 CST
# mode: julia
	help(symbol)
# time: 2014-12-27 15:52:11 CST
# mode: julia
	symbol('a')
# time: 2014-12-27 15:52:19 CST
# mode: julia
	LabelList(symbol('a'))
# time: 2014-12-27 15:52:32 CST
# mode: julia
	LabelList(Array(symbol('a')))
# time: 2014-12-27 15:55:08 CST
# mode: julia
	methods(Array)
# time: 2014-12-27 15:56:28 CST
# mode: julia
	['a']
# time: 2014-12-27 15:56:36 CST
# mode: julia
	[symbol('a')]
# time: 2014-12-27 15:56:41 CST
# mode: julia
	LabelList([symbol('a')])
# time: 2014-12-27 15:57:26 CST
# mode: julia
	x0 [1] LabelList([symbol('a')])
# time: 2014-12-27 15:57:34 CST
# mode: julia
	x0 [1] [LabelList([symbol('a')])]
# time: 2014-12-27 15:57:41 CST
# mode: julia
	i
# time: 2014-12-27 15:57:46 CST
# mode: julia
	fact = x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 15:57:49 CST
# mode: julia
	length(fact)
# time: 2014-12-27 15:58:02 CST
# mode: julia
	for j in 1:length(fact)
		fact[j] = fact[j] [LabelList ([symbol('a'+j-1)])]
	end
# time: 2014-12-27 15:58:19 CST
# mode: julia
	fact[1]
# time: 2014-12-27 15:58:31 CST
# mode: julia
	fact[1] [LabelList([symbol('a')])]
# time: 2014-12-27 15:58:47 CST
# mode: julia
	fact[1] [LabelList([symbol('a')])] * fact[1] [LabelList([symbol('a')])]
# time: 2014-12-27 15:58:57 CST
# mode: julia
	fact[1] [LabelList([symbol('a')])] * fact[1] [LabelList([symbol('b')])]
# time: 2014-12-27 16:00:11 CST
# mode: julia
	'a'+2
# time: 2014-12-27 16:00:27 CST
# mode: julia
	symbol('a'+2)
# time: 2014-12-27 16:00:55 CST
# mode: julia
	j=1
# time: 2014-12-27 16:01:18 CST
# mode: julia
	fact[j] = fact[j] [LabelList ([symbol('a'+j-1)])]
# time: 2014-12-27 16:01:33 CST
# mode: julia
	fact[j] [LabelList ([symbol('a'+j-1)])]
# time: 2014-12-27 16:01:37 CST
# mode: julia
	fact[j]
# time: 2014-12-27 16:01:46 CST
# mode: julia
	LabelList ([symbol('a'+j-1)])
# time: 2014-12-27 16:01:49 CST
# mode: julia
	[LabelList ([symbol('a'+j-1)])]
# time: 2014-12-27 16:02:14 CST
# mode: julia
	ll =LabelList ([symbol('a'+j-1)])
# time: 2014-12-27 16:02:20 CST
# mode: julia
	fact[j] [ll]
# time: 2014-12-27 16:02:45 CST
# mode: julia
	for j in 1:length(fact)
		ll = LabelList ([symbol('a'+j-1)])
		fact[j] = fact[j] [ll]
	end
# time: 2014-12-27 16:03:16 CST
# mode: julia
	for j in 1:length(fact)
		ll = LabelList ([symbol('a'+j-1)])
		fact[j] [ll]
	end
# time: 2014-12-27 16:03:35 CST
# mode: julia
	for j in 1:length(fact)
		ll = LabelList ([symbol('a'+j-1)])
		fact[j] [ll]
		print(fact[j][ll])
	end
# time: 2014-12-27 16:08:46 CST
# mode: julia
	function g(j)
		ll = LabelList ([symbol('a'+j-1)])
		fact[j] [ll]
	end
# time: 2014-12-27 16:08:52 CST
# mode: julia
	fact = x [cat(1,1:(i-1),(i+1):d)]
# time: 2014-12-27 16:08:53 CST
# mode: julia
	fact
# time: 2014-12-27 16:09:00 CST
# mode: julia
	fact_typed = ntuple (length (fact), g)
# time: 2014-12-27 16:10:35 CST
# mode: julia
	reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)])
# time: 2014-12-27 16:10:49 CST
# mode: julia
	fact_typed[1] * fact_typed[2]
# time: 2014-12-27 16:13:24 CST
# mode: julia
	x = x0
# time: 2014-12-27 16:13:24 CST
# mode: julia
	for i in 1:d
		fact = x [cat(1,1:(i-1),(i+1):d)]
	
		function g(j)
			ll = LabelList ([symbol('a'+j-1)])
			fact[j] [ll]
		end
	
		fact_typed = ntuple (length (fact), g)
	
	# maybe use mapreduce instead
	
		print (reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)]))
	end
# time: 2014-12-27 16:13:41 CST
# mode: julia
	x = x0
# time: 2014-12-27 16:13:41 CST
# mode: julia
	for i in 1:d
		fact = x [cat(1,1:(i-1),(i+1):d)]
	
		function g(j)
			ll = LabelList ([symbol('a'+j-1)])
			fact[j] [ll]
		end
	
		fact_typed = ntuple (length (fact), g)
	
	# maybe use mapreduce instead
	
		print (reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)]))
		print("\n")
	end
# time: 2014-12-27 16:13:53 CST
# mode: julia
	help(print)
# time: 2014-12-27 16:14:14 CST
# mode: julia
	x = x0
# time: 2014-12-27 16:14:14 CST
# mode: julia
	for i in 1:d
		fact = x [cat(1,1:(i-1),(i+1):d)]
	
		function g(j)
			ll = LabelList ([symbol('a'+j-1)])
			fact[j] [ll]
		end
	
		fact_typed = ntuple (length (fact), g)
	
	# maybe use mapreduce instead
	
		show (reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)]))
		print("\n")
	end
# time: 2014-12-27 16:14:21 CST
# mode: julia
	rand(2,2)
# time: 2014-12-27 16:14:25 CST
# mode: julia
	show(rand(2,2))
# time: 2014-12-27 16:15:48 CST
# mode: julia
	fact_typed
# time: 2014-12-27 16:15:54 CST
# mode: julia
	dim(fact_typed)
# time: 2014-12-27 16:15:58 CST
# mode: julia
	size(fact_typed)
# time: 2014-12-27 16:16:28 CST
# mode: julia
	reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)])
# time: 2014-12-27 16:16:33 CST
# mode: julia
	value
# time: 2014-12-27 16:16:34 CST
# mode: julia
	reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)])
# time: 2014-12-27 16:16:35 CST
# mode: julia
	result
# time: 2014-12-27 16:16:43 CST
# mode: julia
	z = reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)])
# time: 2014-12-27 16:16:44 CST
# mode: julia
	z
# time: 2014-12-27 16:16:55 CST
# mode: julia
	T
# time: 2014-12-27 16:17:06 CST
# mode: julia
	T [ l"c,a,b"]
# time: 2014-12-27 16:17:11 CST
# mode: julia
	z
# time: 2014-12-27 16:17:20 CST
# mode: julia
	T [ l"a,b,c"]
# time: 2014-12-27 16:17:47 CST
# mode: julia
	T[l"a,b,c"] * z
# time: 2014-12-27 16:18:18 CST
# mode: julia
	norm(T[l"a,b,c"] * z)
# time: 2014-12-27 16:18:25 CST
# mode: julia
	T[l"a,b,c"] * z []
# time: 2014-12-27 16:18:37 CST
# mode: julia
	Array (T[l"a,b,c"] * z )
# time: 2014-12-27 16:18:54 CST
# mode: julia
	norm(rand(5))
# time: 2014-12-27 16:18:57 CST
# mode: julia
	rand(5)
# time: 2014-12-27 16:19:35 CST
# mode: julia
	methods(norm)
# time: 2014-12-27 16:19:55 CST
# mode: julia
	T[l"a,b,c"] * z
# time: 2014-12-27 16:19:57 CST
# mode: julia
	T[l"a,b,c"] * z / 5
# time: 2014-12-27 16:20:09 CST
# mode: julia
	help(LabeledArray)
# time: 2014-12-27 16:20:18 CST
# mode: julia
	LabeledArray
# time: 2014-12-27 16:20:26 CST
# mode: julia
	apropos("LabeledArray")
# time: 2014-12-27 16:20:35 CST
# mode: julia
	help(TensorOperations)
# time: 2014-12-27 16:20:41 CST
# mode: julia
	help("TensorOperations")
# time: 2014-12-27 16:21:27 CST
# mode: julia
	norm(T[l"a,b,c"] * z)
# time: 2014-12-27 16:25:27 CST
# mode: julia
	methods(norm)
# time: 2014-12-27 16:27:44 CST
# mode: julia
	help(convert
	)
# time: 2014-12-27 16:27:57 CST
# mode: julia
	typeof(T[l"a,b,c"] * z)
# time: 2014-12-27 16:28:21 CST
# mode: julia
	Convert(Array{Float64,1}, T[l"a,b,c"] * z)
# time: 2014-12-27 16:28:24 CST
# mode: julia
	convert(Array{Float64,1}, T[l"a,b,c"] * z)
# time: 2014-12-27 16:28:34 CST
# mode: julia
	convert(Array, T[l"a,b,c"] * z)
# time: 2014-12-29 21:49:08 CST
# mode: julia
	m
# time: 2014-12-29 21:49:12 CST
# mode: julia
	T
# time: 2014-12-29 21:55:02 CST
# mode: julia
	help(transpose)
# time: 2014-12-29 21:55:29 CST
# mode: julia
	help(Base.transpose)
# time: 2014-12-29 21:55:36 CST
# mode: julia
	help("Linear Algebra")
# time: 2014-12-29 21:55:46 CST
# mode: julia
	help("help")
# time: 2014-12-29 21:55:55 CST
# mode: julia
	help()
# time: 2014-12-29 21:58:37 CST
# mode: julia
	help("Iteration")
# time: 2014-12-29 21:59:18 CST
# mode: julia
	apropos("iteration")
# time: 2014-12-29 21:59:27 CST
# mode: julia
	apropos("string")
# time: 2014-12-29 21:59:51 CST
# mode: julia
	apropos("matrix")
# time: 2014-12-29 21:59:59 CST
# mode: julia
	apropos("qr")
# time: 2014-12-29 22:00:04 CST
# mode: julia
	apropos("svd")
# time: 2014-12-29 22:00:29 CST
# mode: julia
	help(help)
# time: 2014-12-29 22:00:37 CST
# mode: julia
	help(.)
# time: 2014-12-29 22:01:12 CST
# mode: julia
	Pkg.add("TensorOperations")
# time: 2014-12-29 22:01:33 CST
# mode: julia
	Pkg.update()
# time: 2014-12-29 22:02:03 CST
# mode: julia
	help("BLAS")
# time: 2014-12-29 22:02:25 CST
# mode: julia
	help("deepcopy")
# time: 2014-12-29 22:03:14 CST
# mode: julia
	exit
# time: 2014-12-29 22:03:19 CST
# mode: julia
	methods(exit)
# time: 2014-12-29 22:05:42 CST
# mode: julia
	help("GLPK")
# time: 2014-12-29 22:05:51 CST
# mode: julia
	help(BLAS.dot)
# time: 2014-12-29 22:05:59 CST
# mode: julia
	help(dot)
# time: 2014-12-29 22:06:34 CST
# mode: julia
	apropos("types")
# time: 2014-12-29 22:06:51 CST
# mode: julia
	subtypes(UInt)
# time: 2014-12-29 22:06:55 CST
# mode: julia
	subtypes(UInt32)
# time: 2014-12-29 22:06:57 CST
# mode: julia
	subtypes(Int32)
# time: 2014-12-29 22:08:27 CST
# mode: julia
	typeof(1:5)
# time: 2014-12-29 22:08:32 CST
# mode: julia
	linspace(1,5)
# time: 2014-12-29 22:08:36 CST
# mode: julia
	linspace
# time: 2014-12-29 22:08:40 CST
# mode: julia
	methods(linspace)
# time: 2014-12-29 22:08:53 CST
# mode: julia
	linspace(1,5,1)
# time: 2014-12-29 22:08:56 CST
# mode: julia
	linspace(1,5,5)
# time: 2014-12-29 22:09:14 CST
# mode: julia
	linspace(Int32(1),Int32(5),5)
# time: 2014-12-29 22:09:18 CST
# mode: julia
	Int32
# time: 2014-12-29 22:09:32 CST
# mode: julia
	linspace(01,05,5)
# time: 2014-12-29 22:09:47 CST
# mode: julia
	typeof(1:5)
# time: 2014-12-29 22:10:40 CST
# mode: julia
	ones(UInt)
# time: 2014-12-29 22:10:44 CST
# mode: julia
	ones(I32nt)
# time: 2014-12-29 22:10:48 CST
# mode: julia
	ones(Int32)
# time: 2014-12-29 22:11:26 CST
# mode: julia
	linspace(0,10,20)
# time: 2014-12-29 22:11:29 CST
# mode: julia
	linspace(0,10.,20)
# time: 2014-12-29 22:11:37 CST
# mode: julia
	gethostname()
# time: 2014-12-29 22:12:27 CST
# mode: julia
	dir()
# time: 2014-12-29 22:12:29 CST
# mode: julia
	ls()
# time: 2014-12-29 22:12:31 CST
# mode: julia
	getwd()
# time: 2014-12-29 22:12:33 CST
# mode: julia
	pwd()
# time: 2014-12-29 22:12:36 CST
# mode: julia
	cd()
# time: 2014-12-29 22:12:40 CST
# mode: julia
	cd('..')
# time: 2014-12-29 22:12:44 CST
# mode: julia
	cd("..")
# time: 2014-12-29 22:12:46 CST
# mode: julia
	pwd()
# time: 2014-12-29 22:12:53 CST
# mode: julia
	cd ("Dan")
# time: 2014-12-29 22:14:19 CST
# mode: julia
	a = ones(Int32,(4,4))		;		b = a + a		;
# time: 2014-12-29 22:14:20 CST
# mode: julia
	a
# time: 2014-12-29 22:14:21 CST
# mode: julia
	b
# time: 2014-12-29 22:14:24 CST
# mode: julia
	a * b
# time: 2014-12-29 22:14:30 CST
# mode: julia
	a / b
# time: 2014-12-29 22:14:33 CST
# mode: julia
	a \b
# time: 2014-12-29 22:16:05 CST
# mode: julia
	dot(a,b)
# time: 2014-12-29 22:18:09 CST
# mode: julia
	a[1]									# indexing
# time: 2014-12-29 22:18:12 CST
# mode: julia
	a[1,1]
# time: 2014-12-29 22:18:16 CST
# mode: julia
	a[(1,2)]
# time: 2014-12-29 22:18:24 CST
# mode: julia
	a[1:2]
# time: 2014-12-29 22:18:26 CST
# mode: julia
	a[1:2,]
# time: 2014-12-29 22:18:28 CST
# mode: julia
	a
# time: 2014-12-29 22:18:37 CST
# mode: julia
	reshape(1:16, (4,4))
# time: 2014-12-29 22:18:43 CST
# mode: julia
	reshape(1:16, (4,4)) [1:2]
# time: 2014-12-29 22:18:47 CST
# mode: julia
	reshape(1:16, (4,4)) [,1:2]
# time: 2014-12-29 22:18:57 CST
# mode: julia
	reshape(1:16, (4,4)) [1,1:2]
# time: 2014-12-29 22:19:13 CST
# mode: julia
	a[1][1]
# time: 2014-12-29 22:19:16 CST
# mode: julia
	a[1][1][1]
# time: 2014-12-29 22:21:24 CST
# mode: julia
	a[(1,2),]
# time: 2014-12-29 22:21:47 CST
# mode: julia
	a[1:2,]
# time: 2014-12-29 22:21:50 CST
# mode: julia
	a
# time: 2014-12-29 22:22:03 CST
# mode: julia
	a=reshape(1:16, (4,4))
# time: 2014-12-29 22:22:06 CST
# mode: julia
	a[1:2,]
# time: 2014-12-29 22:22:09 CST
# mode: julia
	a[1:2,1]
# time: 2014-12-29 22:22:11 CST
# mode: julia
	a[1:2,2]
# time: 2014-12-29 22:22:18 CST
# mode: julia
	a[(1,2)]		# nb, not valid
# time: 2014-12-29 22:22:25 CST
# mode: julia
	a[1:2]
# time: 2014-12-29 22:23:39 CST
# mode: julia
	stride(a)
# time: 2014-12-29 22:23:43 CST
# mode: julia
	stride(5)
# time: 2014-12-29 22:23:47 CST
# mode: julia
	help(stride)
# time: 2014-12-29 22:23:53 CST
# mode: julia
	stride(a,1)
# time: 2014-12-29 22:23:55 CST
# mode: julia
	stride(a,2)
# time: 2014-12-29 22:24:03 CST
# mode: julia
	a [16]
# time: 2014-12-29 22:26:46 CST
# mode: julia
	a[[1,2,3]]
# time: 2014-12-29 22:26:56 CST
# mode: julia
	a[[1,10,3]]
# time: 2014-12-29 22:27:06 CST
# mode: julia
	[1,2,3]
# time: 2014-12-29 22:28:12 CST
# mode: julia
	Array(1:16,(4,4))
# time: 2014-12-29 22:28:30 CST
# mode: julia
	whos()
# time: 2014-12-29 22:29:20 CST
# mode: julia
	showhistory
# time: 2014-12-29 22:29:24 CST
# mode: julia
	history
# time: 2014-12-29 22:29:34 CST
# mode: julia
	apropos("history")
# time: 2014-12-29 22:30:37 CST
# mode: julia
	[trace(rand(n,n)) for n=1:5]
# time: 2014-12-29 22:31:07 CST
# mode: julia
	methods(rand)
# time: 2014-12-29 22:31:24 CST
# mode: julia
	rand(Int32,4,4)
# time: 2014-12-29 22:31:28 CST
# mode: julia
	rand(4,4)
# time: 2014-12-29 22:32:28 CST
# mode: julia
	eye(10)									# identity matrix
# time: 2014-12-29 22:32:37 CST
# mode: julia
	eye(Int64, 10)									# identity matrix
# time: 2014-12-29 22:32:57 CST
# mode: julia
	{eye[n] for n=1:5}
# time: 2014-12-29 22:33:04 CST
# mode: julia
	{eye(n) for n=1:5}
# time: 2014-12-29 22:36:52 CST
# mode: julia
	help(normpath)
# time: 2014-12-29 22:37:59 CST
# mode: julia
	size(a)
# time: 2014-12-29 22:38:08 CST
# mode: julia
	length
# time: 2014-12-29 22:38:49 CST
# mode: julia
	which
# time: 2014-12-29 22:38:52 CST
# mode: julia
	help(which)
# time: 2014-12-29 22:39:29 CST
# mode: julia
	which(print, "argument")				# which method will be called?
# time: 2014-12-29 22:40:01 CST
# mode: julia
	function f(x)						# function
	       x^2
	       end
# time: 2014-12-29 22:40:03 CST
# mode: julia
	edit(f)
# time: 2014-12-29 22:40:08 CST
# mode: julia
	edit("f")
# time: 2014-12-29 22:40:17 CST
# mode: julia
	help(edit)
# time: 2014-12-29 22:41:18 CST
# mode: julia
	help(plot)
# time: 2014-12-29 22:41:26 CST
# mode: julia
	apropos("plot")
# time: 2014-12-29 22:41:34 CST
# mode: julia
	factorial(6)
# time: 2014-12-29 22:43:10 CST
# mode: julia
	1:10:2
# time: 2014-12-29 22:43:15 CST
# mode: julia
	1:10:5
# time: 2014-12-29 22:43:21 CST
# mode: julia
	1.:10.:2
# time: 2014-12-29 22:43:58 CST
# mode: julia
	reverse(1:20)
# time: 2014-12-29 22:44:05 CST
# mode: julia
	1:1:10
# time: 2014-12-29 22:44:12 CST
# mode: julia
	[1:1:10]
# time: 2014-12-29 22:44:18 CST
# mode: julia
	[1:10:1]
# time: 2014-12-29 22:44:48 CST
# mode: julia
	1:2:5
# time: 2014-12-29 22:44:51 CST
# mode: julia
	[1:2:5]
# time: 2014-12-29 22:45:27 CST
# mode: julia
	1:2:10		;		2:2:10				# odds and evens
# time: 2014-12-29 22:45:31 CST
# mode: julia
	[1:2:10]
# time: 2014-12-29 22:45:35 CST
# mode: julia
	[2:2:10]
# time: 2014-12-29 22:47:43 CST
# mode: julia
	nextfloat
# time: 2014-12-29 22:47:46 CST
# mode: julia
	nextfloat(0)
# time: 2014-12-29 22:47:47 CST
# mode: julia
	eps
# time: 2014-12-29 22:47:50 CST
# mode: julia
	help(eps)
# time: 2014-12-29 22:48:01 CST
# mode: julia
	eps(Float64)
# time: 2014-12-29 22:48:15 CST
# mode: julia
	nextfloat(0.)
# time: 2014-12-29 22:48:31 CST
# mode: julia
	float(0)
# time: 2014-12-29 22:49:01 CST
# mode: julia
	nextfloat(0)		# error
# time: 2014-12-29 22:49:47 CST
# mode: julia
	1 // 4				# rational
# time: 2014-12-29 22:49:59 CST
# mode: julia
	BigFloat(0)
# time: 2014-12-29 22:50:05 CST
# mode: julia
	BigInt(0)
# time: 2014-12-29 22:50:23 CST
# mode: julia
	eps(BigInt(0))
# time: 2014-12-29 22:50:29 CST
# mode: julia
	eps(BigFloat(0))
# time: 2014-12-29 22:51:12 CST
# mode: julia
	0xa5
# time: 2014-12-29 22:51:15 CST
# mode: julia
	08
# time: 2014-12-29 22:51:19 CST
# mode: julia
	0177
# time: 2014-12-29 22:51:24 CST
# mode: julia
	float(0177)
# time: 2014-12-29 22:51:34 CST
# mode: julia
	float(0x177)
# time: 2014-12-29 22:52:01 CST
# mode: julia
	apropos("octal")
# time: 2014-12-29 22:52:05 CST
# mode: julia
	oct(5)
# time: 2014-12-29 22:52:12 CST
# mode: julia
	oct(77)
# time: 2014-12-29 22:52:30 CST
# mode: julia
	07
# time: 2014-12-29 22:52:32 CST
# mode: julia
	077
# time: 2014-12-29 22:52:39 CST
# mode: julia
	float(077)
# time: 2014-12-29 22:53:03 CST
# mode: julia
	[1,2,3]
# time: 2014-12-29 22:53:06 CST
# mode: julia
	{1,2,3}
# time: 2014-12-29 22:54:27 CST
# mode: julia
	(1)
# time: 2014-12-29 22:54:30 CST
# mode: julia
	(77)
# time: 2014-12-29 22:55:37 CST
# mode: julia
	readcsv
# time: 2014-12-29 22:55:40 CST
# mode: julia
	readdlm
# time: 2014-12-29 23:16:15 CST
# mode: julia
	help(time)
# time: 2014-12-29 23:16:20 CST
# mode: julia
	time()
# time: 2014-12-29 23:16:31 CST
# mode: julia
	s = time()
# time: 2014-12-29 23:16:33 CST
# mode: julia
	t = time()
# time: 2014-12-29 23:16:35 CST
# mode: julia
	t-s
# time: 2014-12-29 23:17:27 CST
# mode: julia
	println("elapsed time (sec): ", t-s)
# time: 2014-12-30 01:23:21 CST
# mode: julia
	quit()
