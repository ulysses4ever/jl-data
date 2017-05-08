# Find the port we need to listen on


function addworkers() 
    if (nprocs() == 1) 
        Base.addprocs(CPU_CORES)
    elseif nworkers() < CPU_CORES
        Base.addprocs(CPU_CORES - nworkers())
    end
    workers()
end

function addworkers(nw::Integer) 
    nwe = nworkers()
    if (nprocs() == 1) 
        addprocs(nw)
    elseif (nw < nwe)
        addprocs(nw - nwe)
    end
    workers()
end

export addworkers


function checkworkers()
    outs = map(x->RemoteRef(), 1:nworkers())
    for (i,pid) in enumerate(workers())
        @async begin
            try
                outs[i] = remotecall(pid, ()->pid)
            catch e
                outs[i] = e
            end
        end
    end
    
    timedwait(1.0) do
        all(map(isready, outs))
    end
    
    outs = filter(isready, outs)
    map(x->fetch(x), outs)
end

export checkworkers

serverenv() = {:cpu_cores => CPU_CORES, :nprocs => nprocs(), :nworkers => nworkers()}

function exec_on_workers(result, f, args)
    @sync begin
        i = 1
        for pid in workers()
            @async begin
                try
                    result[i] = remotecall_fetch(pid, f, args...)
                catch e
                    result[i] = e
                end
            end
            i += 1
        end
    end
end

function handle_client(s, port)
    println(getpid(), ": Client connected to $port, sock : $(object_id(s))")
# Only handle require and function execution calls
    try
        while true
            println(getpid(), ": Waiting for a request")
            where = deserialize(s)
            arg0 = deserialize(s)
            args = deserialize(s)
            if where == :master
                println(getpid(), ": Got a :master request, $arg0, $args")
                result = apply(arg0, args)
                
            elseif where == :workers
                println(getpid(), ": Got a :workers request")
                result = cell(nworkers())
                exec_on_workers(result, arg0, args)

            elseif where == :everywhere
                println(getpid(), ": Got a :everywhere request")
                if nprocs() > nworkers()
                    result = cell(nworkers())
                    exec_on_workers(result, arg0, args)
                    result = unshift!(result, apply(arg0, args))
                else
                    result = cell(1)
                    result[1] = apply(arg0, args)
                end
                
            elseif where == :mapred
                println(getpid(), ": Got a :mapred request")
                mapf = arg0
                params = isa(args, Tuple) ? args[1] : args
                
                strt = params[:start]
                total = params[:total]
                redf = get(params, :redf, nothing)
                acc = (redf != nothing) ? params[:acc] : nothing
                pids = get(params, :pids, workers())
                timeout = get(params, :timeout, 0.0)
                
                if timeout == 0
                    outs = cell(length(pids))
                    @sync begin
                        i = 1
                        for pid in pids
                            @async begin
                                try
                                    outs[i] = remotecall_fetch(pid, mapf, strt + i - 1, total)
                                catch e
                                    outs[i] = e
                                end
                            end
                            i += 1
                        end
                    end
                else
                    outs = map(x->RemoteRef(), 1:length(pids))
                    i = 1
                    for pid in pids
                        @async begin
                            try
                                outs[i] = remotecall(pid, mapf, strt + i - 1, total)
                            catch e
                                outs[i] = e
                            end
                        end
                        i += 1
                    end
                    
                    if timeout > 0.1
                        timedwait(timeout) do
                            all(map(isready, outs))
                        end
                    else
                        timedwait(timeout, pollint=0.02) do
                            all(map(isready, outs))
                        end
                    end
                    
                    # If the response has not arrived just send set the default accumulator as the response
                    for i in [1:length(outs)]
                        out[i] = isready(out[i]) ? fetch(out[i]) : acc
                    end
                end
                
                if isa(redf, Function)
                    try
                        result = reduce(redf, acc, filter(v -> !isa(v, Exception),outs))
                    catch e
                        result = e
                    end
                else
                    result = outs
                end
            end    
            println(getpid(), ": Sending back $(result)")
            serialize(s, result)
        end
    catch e
        println(getpid(), ": Error : ", e)
    end
    
    close(s)
end

function start_server(port)
    println(getpid(), ": Listening on $port")
    server = listen(IPv4(0), port) 
    
    while true
        sock = accept(server)
        @async handle_client(sock, port)
    end
end


idxarr = findin(ARGS, ["--port"])
if length(idxarr) == 0
    error("Must specify a port with a '--port' option to listen on")
end

port = int16(ARGS[int(idxarr[1]) + 1])

start_server(port)
