import Base.show
import Base.pmap 


exec_on_master(s, f, args...) = exec_request(s, :master, f, args...)
exec_pmap(s, f, args...) = exec_request(s, :pmap, f, args...)

function exec_request(s, mode, f, args...)
    serialize(s, mode)
    serialize(s, f)
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
    println(io, "hosts: ", o.hosts)
    println(io, "tunnelport: ", o.tunnelport)
    println(io, "pids: ", o.pids)
    if isdefined(o, :s)
        println(io, "socket connected")
    else
        println(io, "socket not connected")
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

    start = time()
    while (time() - start) < 15
        try
            println("Trying connect to $(node.host):$(h.port) via localhost:$(node.tunnelport)")
            s = connect("localhost", node.tunnelport)
            node.s = s
            println("Connected to $(node.host):$(h.port) via localhost:$(node.tunnelport)")
            break;
        
        catch e
            sleep(1.0)
        end
    end
    
    if !isdefined(node, :s)
        error("Unable to connect to node $(node.host):$(h.port)")
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
                    tunnelport = ssh_tunnel(ssh_user, host, port, sshflags)
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

tunnel_cmd(user, host, port, localp, sshflags) = `ssh -f -o ExitOnForwardFailure=yes $sshflags $(user)@$host -L $localp:$host:$(int(port)) sleep 60`

wc_tunnelport = 8500
function ssh_tunnel(user, host, port, sshflags)
    global wc_tunnelport
    localp = wc_tunnelport::Int
    c = tunnel_cmd(user, host, port, localp, sshflags)
    c.detach=true
    while !success(c) && localp < 10000
        println("Trying on port $localp")
        localp += 1
        c = tunnel_cmd(user, host, port, localp, sshflags)
        c.detach=true
    end
    
    if localp >= 10000
        error("Unable to assign a local tunnel port between 8500 and 10000")
    end
    
    wc_tunnelport = localp+1
    
    println("Successfully started tunnel on port $localp")
    localp
end

function pmap (NodeSet, f, args...)
# Assumes that each worker process has the same compute capabilty as any other.


end


#start_cluster(["localhost"])
