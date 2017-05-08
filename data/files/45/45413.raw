import Base.show
import Base.pmap 


exec_on_master(s, f, args...) = exec_request(s, :master, f, args...)
exec_on_workers(s, f, args...) = exec_request(s, :workers, f, args...)

function exec_request(s, mode, arg0, args...)
    serialize(s, mode)
    serialize(s, arg0)
    serialize(s, args)
    deserialize(s)
end

abstract WorkerNode
export WorkerNode

abstract NodeSet
export NodeSet


type NodeHandle <: WorkerNode
    host::String
    tunnelport::Int
    h_nset::NodeSet
    
    pids::AbstractArray
    s::AsyncStream
    
    NodeHandle(host, port, h_nset) = new(host, port, h_nset)
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
end


type SetHandle <: NodeSet
    hosts::AbstractArray
    sshflags
    port
    ssh_user
    dir
    nodes::AbstractArray
    SetHandle(hosts, sshflags, port, ssh_user, dir) = new(hosts, sshflags, port, ssh_user, dir, WorkerNode[])
end

function show(io::IO, o::SetHandle)
    println(io, "hosts: ", o.hosts)
    println(io, "sshflags: ", o.sshflags)
    println(io, "port: ", o.port)
    println(io, "ssh_user: ", o.ssh_user)
    println(io, "dir: ", o.dir)
    println(io, "nodes: [")
        for n in o.nodes
            print(io, " ", n.host)
        end
    println(io, "]")
end

function execmd(c)
#    println("executing $c")
    c.detach = true
    if !success(c)
        error("Error executing $c")
    end
end

# starts the cluster on as many 
function start_cluster(node::WorkerNode)
    # first start the julia process
    h = node.h_nset
    
    execmd(`ssh -n $(h.sshflags) $(h.ssh_user)@$(node.host) "mkdir -p jrun; cd jrun; "`)
    execmd(`scp $(h.sshflags) Server.jl $(h.ssh_user)@$(node.host):jrun/Server.jl`)
    execmd(`ssh -n $(h.sshflags) $(h.ssh_user)@$(node.host) "bash -l -c \"cd jrun; $(h.dir)/julia-release-basic Server.jl --port $(h.port) </dev/null >> server.log 2>&1 &\" "`)

    # Compensate for Julia's startup delay.
    sleep(1.0)
    
    start = time()
    while (time() - start) < 15
        try
            println("Trying connect to $(node.host):$(h.port) via localhost:$(node.tunnelport)")
            s = connect("localhost", node.tunnelport)

            println("@1")
            resp = exec_on_master(s, x->x, "Hello") 
            println("@2")
            assert (resp == "Hello")
            println("@3")
            node.s = s
            
            break;
        
        catch e
            sleep(1.0)
        end
    end
    
    if !isdefined(node, :s)
        error("Unable to connect to node $(node.host):$(h.port)")
    else
        println("Connected to $(node.host):$(h.port) via localhost:$(node.tunnelport)")
    end

    node.pids = exec_on_master(node.s, ()->addworkers())
    println(node.pids)
end


function get_st()
    io = IOBuffer()
    Base.show_backtrace(io, catch_backtrace())
    seekstart(io)
    bt = readall(io)
    bt
end


function start_cluster(hosts::AbstractArray; port::Int=9500, sshflags::Cmd=``, ssh_user::String=ENV["USER"], dir=JULIA_HOME)
    h = SetHandle(hosts, sshflags, port, ssh_user, dir)
    @sync begin
        for host in hosts
            @async begin
                try
                    tunnelport = ssh_tunnel(host, h)
                    nodeinst = NodeHandle(host, tunnelport, h)
                    start_cluster(nodeinst)
                    push!(h.nodes, nodeinst)
                catch e
                    println("Could not start workers on node $host : ", e, "\n", get_st())
                end
            end
        end
    end
    h
end

tunnel_cmd(host, priv_ip, localp, h) = `ssh -f -o ExitOnForwardFailure=yes $(h.sshflags) $(h.ssh_user)@$host -L $localp:$(priv_ip):$(int(h.port)) sleep 60`

wc_tunnelport = 8500
function ssh_tunnel(host, h::SetHandle)
    ipcmd = `ssh $(h.ssh_user)@$host "$(h.dir)/julia-release-basic -e \"println(getipaddr())\""`
    println(ipcmd)
    io,_=readsfrom(ipcmd)    
    io.line_buffered = true
    priv_ip = strip(readline(io))
    println("Private ip $(priv_ip) of host $host")

    global wc_tunnelport
    localp = wc_tunnelport::Int
    c = tunnel_cmd(host, priv_ip, localp, h)
    c.detach=true
    while !success(c) && localp < 10000
        println("Trying on port $localp")
        localp += 1
        c = tunnel_cmd(host, priv_ip, localp, h)
        c.detach=true
    end
    
    if localp >= 10000
        error("Unable to assign a local tunnel port between 8500 and 10000")
    end
    
    wc_tunnelport = localp+1
    
    println("Successfully started tunnel on port $localp")
    localp
end

function mapred (ns::NodeSet, mapf::Function, redf::Function, acc::Any)
    # Assumes that each worker process has the same compute capabilty as any other.
    # Function mapf if of the form  mapf(pid, totalpids)
    
    totalp = reduce((acc, node) -> acc + length(node.pids), 0, ns.nodes)
    println("Total number of worker across NodeSets : ", totalp)
    
    results = cell(length(ns.nodes))
    
    @sync begin
        for i in 1:length(ns.nodes)
            j = 1
            @async begin
                results[i] = exec_request(ns.nodes[i].s, :mapred, (mapf, redf, acc, j, totalp), ()) 
            end
            j += length(ns.nodes[i].pids)
        end
    end

    #reduce the output
    reduce(redf, acc, results)
end


function stop_cluster (ns::NodeSet)
    @sync begin
        for n in ns.nodes
            @async begin
                try
                    exec_on_master(n.s, exit) 
                catch e
                    close(n.s)
                end
            end
        end
    end
end


# ns = start_cluster(["localhost"])
# ns = start_cluster(["julia.mit.edu"], dir="/home/amitm/julia/julia/usr/bin")
# mapred(ns, (id, tot) -> tot*1000 + id, (acc, v) -> acc + v, 0)
# stop_cluster(ns)

