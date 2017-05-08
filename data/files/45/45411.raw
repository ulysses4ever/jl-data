import Base.show

abstract WorkerNode
export WorkerNode

abstract NodeSet
export NodeSet

#export ns_start, ns_stop, ns_nworkers

type NodeHandle <: WorkerNode
    host::String
    tunnelport::Int

    pids::AbstractArray
    s::AsyncStream

    # If specified, these will override the ones in NodeSet 
    sshflags
    port
    ssh_user
    dir
    nworkers
    
    NodeHandle(host) = new(host)
end 

function show(io::IO, o::NodeHandle)
    println(io, "hosts: ", o.host)
    println(io, "tunnelport: ", o.tunnelport)
    println(io, "pids: ", o.pids)
    if isdefined(o, :s)
        if isopen(o.s)
            println(io, "socket connected")
        else
            println(io, "socket not connected")
        end
    else
        println(io, "no socket")
    end
    
    println(io, "sshflags: ", o.sshflags)
    println(io, "port: ", o.port)
    println(io, "ssh_user: ", o.ssh_user)
    println(io, "dir: ", o.dir)
end


type SetHandle <: NodeSet
    machines::AbstractArray
    nodes::AbstractArray
    SetHandle(machines) = new(machines, WorkerNode[])
end

function show(io::IO, o::SetHandle)
    println(io, "machines: [")
    for m in o.machines
        println(io, "    ", m)
    end
    println(io, "]")
    
    println(io, "nodes: [")
        for n in o.nodes
            print(io, " ", n.host)
        end
    println(io, "]")
end



exec_on_master(s, f, args...) = exec_request(s, :master, f, args...)
exec_on_workers(s, f, args...) = exec_request(s, :workers, f, args...)
exec_everywhere(s, f, args...) = exec_request(s, :everywhere, f, args...)

function exec_request(s, mode, arg0, args...)
    serialize(s, mode)
    serialize(s, arg0)
    serialize(s, args)
    
    deserialize(s)
end


function execmd(c)
#    println("executing $c")
    c.detach = true
    if !success(c)
        error("Error executing $c")
    end
end

# starts the cluster on as many 
function ns_start(n::WorkerNode)
    # first start the julia process
    execmd(`ssh -n $(n.sshflags) $(n.ssh_user)@$(n.host) "mkdir -p jrun; cd jrun; "`)
    
    sfile = "nodeserver.jl"
#    sfilefull = Pkg.dir() * "/PTools/src/$(sfile)" 
    sfilefull = "./$(sfile)" 
    execmd(`scp $(n.sshflags) $(sfilefull) $(n.ssh_user)@$(n.host):jrun/$(sfile)`)
    execmd(`ssh -n $(n.sshflags) $(n.ssh_user)@$(n.host) "bash -l -c \"cd jrun; $(n.dir)/julia-release-basic $(sfile) --port $(n.port) </dev/null >> server.log 2>&1 &\" "`)

    # Compensate for Julia's startup delay.
    sleep(2.0)
    
    start = time()
    while (time() - start) < 15
        try
            println("Trying connect to $(n.host):$(n.port) via localhost:$(n.tunnelport)")
            s = connect("localhost", n.tunnelport)

            # ping test
            resp = exec_on_master(s, x->x, "Hello") 
            assert (resp == "Hello")
            n.s = s
            
            break;
        
        catch e
            println("Caught Exception ", e)
            sleep(2.0)
        end
    end
    
    if !isdefined(n, :s)
        error("Unable to connect to node $(n.host):$(n.port)")
    else
        println("Connected to $(n.host):$(n.port) via localhost:$(n.tunnelport)")
    end

    n.pids = exec_on_master(
        n.s, 
        x -> begin
                if x == 0 
                    addworkers()
                else
                    addworkers(x)
                end
            end,
        n.nworkers
    )
    println(n.pids)
end


function get_st()
    io = IOBuffer()
    Base.show_backtrace(io, catch_backtrace())
    seekstart(io)
    bt = readall(io)
    bt
end


function ns_start(machines::AbstractArray; port::Int=9500, sshflags::Cmd=``, ssh_user::String=ENV["USER"], dir=JULIA_HOME)
    h = SetHandle(machines)
    @sync begin
        for m in machines
            if isa(m, String)
                m = {:host => m}
            end
            n = NodeHandle(m[:host])
            n.sshflags = get(m, :sshflags, sshflags) 
            n.port = get(m, :port, port)
            n.ssh_user = get(m, :ssh_user, ssh_user)
            n.dir = get(m, :dir, dir)
            n.nworkers = get(m, :nworkers, 0)
            
            @async begin
                try
                    ssh_tunnel!(n)
                    ns_start(n)
                    push!(h.nodes, n)
                catch e
                    println("Could not start workers on node $(n.host) : ", e, "\n", get_st())
                end
            end
        end
    end
    h
end

tunnel_cmd(priv_ip, localp, n) = `ssh -f -o ExitOnForwardFailure=yes $(n.sshflags) $(n.ssh_user)@$(n.host) -L $localp:$(priv_ip):$(int(n.port)) sleep 60`

wc_tunnelport = 8500
function ssh_tunnel!(n::NodeHandle)
    ipcmd = `ssh $(n.ssh_user)@$(n.host) "$(n.dir)/julia-release-basic -e \"println(getipaddr())\""`
#    println(ipcmd)
    io,_=readsfrom(ipcmd)    
    io.line_buffered = true
    priv_ip = strip(readline(io))
    println("Private ip $(priv_ip) of host $(n.host)")

    global wc_tunnelport
    localp = wc_tunnelport::Int
    c = tunnel_cmd(priv_ip, localp, n)
    c.detach=true
    while !success(c) && localp < 10000
        println("Trying on port $localp")
        localp += 1
        c = tunnel_cmd(priv_ip, localp, n)
        c.detach=true
    end
    
    if localp >= 10000
        error("Unable to assign a local tunnel port between 8500 and 10000")
    end
    
    wc_tunnelport = localp+1
    
    println("Successfully started tunnel on port $localp")
    n.tunnelport = localp
    localp
end

ns_map(ns::NodeSet, mapf::Function) = ns_mapr (ns, mapf)

function ns_mapr (ns::NodeSet, mapf::Function; redf=nothing, acc=0, timeout=0.0, testpids=false)
    # Assumes that each worker process has the same compute capabilty as any other.
    # Function mapf if of the form  mapf(pid, totalpids)
    
    testpids && ns_refresh!(ns)
    
    totalp = ns_nworkers(ns) 
    println("Total number of worker across NodeSets : ", totalp)
    
    results = cell(length(ns.nodes))
    
    @sync begin
        for i in 1:length(ns.nodes)
            j = 1
            @async begin
                params = {:redf=>redf, :acc=>acc, :start=>j, :total=>totalp, :timeout=>timeout}
                
                if testpids 
                    params[:pids] = ns.nodes[i].pids
                end
                
                results[i] = exec_request(ns.nodes[i].s, :mapred, mapf, params) 
            end
            j += length(ns.nodes[i].pids)
        end
    end

    #reduce the output
    redf != nothing ? reduce(redf, acc, results) : results
end
    

function ns_stop (ns::NodeSet)
    @sync begin
        for n in ns.nodes
            @async begin
                !isopen(n.s) && println("Connection to host $(n.host) is closed")
                
                try
                    exec_on_master(n.s, exit) 
                catch e
                    close(n.s)
                end
            end
        end
    end
end

ns_nworkers(ns::NodeSet) = reduce((acc, node) -> acc + length(node.pids), 0, ns.nodes)

function ns_refresh!(ns::NodeSet)
    @sync begin
        for n in ns.nodes
            @async begin
                n.pids = exec_on_master(n.s, () -> checkworkers()) 
            end
        end
    end
end

ns_using(ns, m) = ns_everywhere(ns, () -> usingmodule(m))

function ns_everywhere(ns, f)
    f()
    for n in ns.nodes
        exec_everywhere(n.s, () -> f())
    end
end

# include("nodesets.jl")
# ns = ns_start(["localhost"])
# ns = ns_start(["julia.mit.edu"], dir="/home/amitm/julia/julia/usr/bin")
# mapred(ns, (id, tot) -> tot*1000 + id, (acc, v) -> acc + v, 0)
# ns_stop(ns)

# ns = ns_start([{:host -=> "julia.mit.edu", dir=>"/home/amitm/julia/julia/usr/bin", :nworkers => 10}, "localhost"])
# ns = ns_start([{:host -=> "localhost", :port => 9501}, "localhost", {:host -=> "localhost", :port => 9502}])
