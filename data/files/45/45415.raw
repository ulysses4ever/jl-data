# Find the port we need to listen on

idxarr = findin(ARGS, ["--port"])
if length(idxarr) == 0
    error("Must specify a port with a '--port' option to listen on")
end


port = int16(ARGS[int(idxarr[1]) + 1])
println(getpid(), ": Listening on $port")

server = listen(IPv4(0), port) 

function addworkers() 
    if nworkers() < CPU_CORES
        Base.addprocs(CPU_CORES - nworkers() + 1)
    end
    workers()
end

serverenv() = {:cpu_cores => CPU_CORES, :nprocs => nprocs(), :nworkers => nworkers()}

function handle_client(s)
    println(getpid(), ": Client connected to $port, sock : $(object_id(s))")
# Only handle require and function execution calls
    try
        while true
            println(getpid(), ": Waiting for a request")
            where = deserialize(s)
            arg0 = deserialize(s)
            args = deserialize(s)
            if where == :master
                println(getpid(), ": Got a :master request")
                f = arg0
                result = apply(f, args)
            elseif where == :workers
                println(getpid(), ": Got a :workers request")
                f = arg0
                result = cell(nworkers())
                @sync begin
                    i = 1
                    for pid in workers()
                        @async begin
                            result[i] = remotecall_fetch(pid, f, args...)
                        end
                        i += 1
                    end
                end
            elseif where == :mapred
                println(getpid(), ": Got a :mapred request")
                (mapf, redf, acc, start, total) = arg0        
            
                outs = cell(nworkers())
                @sync begin
                    i = 1
                    for pid in workers()
                        @async begin
                            outs[i] = remotecall_fetch(pid, mapf, start + i - 1, total)
                        end
                        i += 1
                    end
                end
                
                result = reduce(redf, acc, outs)
            end    
            println(getpid(), ": Sending back $(result)")
            serialize(s, result)
        end
    catch e
        println(getpid(), ": Error : ", e)
    end
    
    close(s)
end


while true
    sock = accept(server)
    @async handle_client(sock)
end


