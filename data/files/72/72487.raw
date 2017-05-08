module Reactor

type Worker
  available::Bool
  pid::Int
  rref::RemoteRef

  Worker(available::Bool, pid::Int) = new(available, pid, nothing)
end

function random_wait(n::Int)
  remotecall(n, ()-> sleep(rand(5:10)))
end

function wait_for_process(n::Int)
  for worker in workers()

  end
end

# From http://julia.readthedocs.org/en/latest/manual/parallel-computing/
function count_heads(n)
    c::Int = 0
    for i=1:n
        c += randbool()
    end
    c
end

function producer()
  produce(:(a = 7))
  for n=1:4
    produce(:(a + 1))
  end
  produce(:(println(a)))
end

#p = Task(producer)
# A task essentially "wraps" a function, suspending it each time produce(...) is called

:(begin  # none, line 2:
        eval(consume(p)) # line 3:
        eval(consume(p)) # line 4:
        eval(consume(p)) # line 5:
        eval(consume(p)) # line 6:
        eval(consume(p)) # line 7:
        eval(consume(p)) # line 8:
        eval(consume(p))
    end)


#workers::Array{Worker} = Array[]

#workers = []

function setup_workers(num_workers::Int)
  addprocs(num_workers)

  for i in procs()
    push!(workers, worker(true, i))
  end
end

function available_workers()
  filter(workers) do worker
    worker.available
  end
end

function find_worker_by_pid(pid::Int)
  filter(workers) do worker
    worker.pid == pid
  end
end

function get_available_worker()
  first(available_workers())
end

function unavailable(f::Function)
  f()
end

function fork(f::Function, args)
  worker = get_available_worker()
  rref = remotecall(worker.pid, f, args)
  worker.available = false


end

function after_fork()
end

function if_full()
end

function spawn_with_timeout(f::Function, n::Int)
end

function after_fork(f::Function)
end

function before_fork(f::Function)
end

function reactor()
  for i = 1:200
    for worker in workers
      if (worker.rref != nothing) && isready(worker.rref)
        fetch(worker.rref)
        worker.available = true
      end
    end
  end
end


##spawn_with_timeout(15) do
##end


# Reactor

# ```
# for proc in procs()
#   if isready
# end
# ```

# # Configuration

# num_workers
# timeout


end # module
