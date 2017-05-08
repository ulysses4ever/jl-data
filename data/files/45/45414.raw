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
            println(getpid(), ": Got a request")
            
            f = deserialize(s)
            args = deserialize(s)
            if where == :master
                retval = apply(f, args)
            elseif where == :pmap
                retval = pmap(f, args)
            end    
            println(getpid(), ": Sending back $(retval)")
            serialize(s, retval)
        end
    catch
        println(getpid(), ": Client disconnected")
    end
    
    close(s)
end


while true
    sock = accept(server)
    @async handle_client(sock)
end


