module JuliaBoxUtils

export add_workers

const mfile = "/home/juser/.juliabox/machinefile"
const sshflags = `-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o LogLevel=ERROR -i /home/juser/.ssh/id_rsa`

function add_workers(hostlist; debug=false)
    t0 = time()
    for m in hostlist
        try
            # AWS route and key setup takes some time. Retry a few times.
            n_try_connect = 30
            np = 0
            while n_try_connect > 0
                try
                    debug && println(time()-t0, " $m before nproc")
                    cmd = `ssh $sshflags juser@$m nproc`
                    io, _= open(detach(cmd))
                    debug && println(time()-t0, " $m after nproc")
                    np = parseint(readall(io))
                    debug && println(time()-t0, " $m nproc $np")
                    (np > 0) && break;
                catch e
                    debug && println(time()-t0, " $m error $e trying again")
                    sleep(5.0)
                end
                n_try_connect = n_try_connect - 1
            end                    
            (n_try_connect == 0) && error("Error detecting num cores on $m")

            debug && println(time()-t0, " $m before addprocs")
            npids = addprocs(fill("juser@$m", np); sshflags=sshflags)
            debug && println(time()-t0, " $m after addprocs")

            println("Added $(length(npids)) workers. Total workers $(nworkers())")
        catch e
            println("Error $e processing machine $(m).")
        end
    end
end

function add_workers(;block::Bool=true, active_machines::Array=Any[]; debug=false)
    if block
        while !isfile(mfile)
            sleep(1.0)
        end
        machines = [strip(x) for x in split(readall(mfile))]

        new_machines = setdiff(machines, active_machines)
        add_workers(new_machines; debug=debug)

        empty!(active_machines)
        append!(active_machines, machines)
    else
        @schedule begin
            while true
                add_workers(;block=true, active_machines=active_machines, debug=debug)
                sleep(1.0)
            end
        end
    end
    nothing
end

end # module
