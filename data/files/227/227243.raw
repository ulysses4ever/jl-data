##  parallel computing examples
##  from manual section 1.19

$ ./julia -p 2								#  startup with two processes.

r = remotecall(2, rand, 2, 2)				#  remote call creates remote reference.
fetch(r)									#  fetch() gets the object of a remote reference.
s = @spawnat 2 1+fetch(r)					#  macro spawns command running on specified process.
fetch(s)


r = @spawn rand(2,2)						# macro variation picks which process for you.
s = @spawn 1+fetch(r)
fetch(s)


remotecall_fetch(2, getindex, r, 1, 1)		#  a bit faster than fetch(remotecall(...))
@everywhere id = myid()						#  execute something on all processes


function count_heads(n) c::Int = 0			#  suppose this is defined on all processes
	for i=1:n
		c += randbool()
	end
	c
end
a = @spawn count_heads(100000000)			#  to share computation evenly between two processes.
b = @spawn count_heads(100000000)
fetch(a)+fetch(b)

nheads = @parallel (+) for i=1:200000000	#  but it is more elegantly done with this macro.
	int(randbool())
end

a = randn(1000)
@parallel (+) for i=1:100000				# the (+) specifies a "reduction operation".
	f(a[randi(end)])
end

M = {rand(1000,1000) for i=1:10}			#  parallel-map a function across a collection.
pmap(svd, M)
