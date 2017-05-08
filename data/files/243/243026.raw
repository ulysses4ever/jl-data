
n = int(100000)
arr = randn(n)

function make_shared(a::AbstractArray,pids=workers())
	sh = SharedArray(typeof(a[1]),size(a),pids=pids)
	sh[:] = a[:]
	return sh
end

arr = make_shared(arr)
tasks = 1:n

#@time begin
#@parallel (+) for i in tasks
#		arr[i]
#	end
#end

@everywhere function f(task,arr)
	arr[task]
end

function mypmap(f::Function, tasks, arr)
	# if this resends the shared data every time, it shouldn't)
	np = nprocs() # determine the number of processes available
	n = length(tasks)
	results = zeros((np,1))
	i = 1
	# function to produce the next work item from the queue.
	# in this case it's just an index.

	nextidx() = (idx=i; i+=1; idx)
	@sync begin
		for p=1:np
			if p != myid() || np == 1
				@async begin
					while true
						idx = nextidx()
						if idx > n
							break
						end	
						task = tasks[idx]
						results[p] += remotecall_fetch(p, f, task, arr)
						#println("p= $(p), idx=$(idx), task=$(task), results=$(results[p])")
					end
				end
			end
		end
	end
	println("results = $(results)")
	println("sum of results = $(sum(results))")
	
end

@time mypmap(f,tasks,arr)