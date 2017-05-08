module JuliaBoxUtils

export add_workers

const mfile = "/home/juser/.juliabox/machinefile"
const sshflags = `-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o LogLevel=ERROR -i /home/juser/.ssh/id_rsa`

function add_workers(hostlist)
    for m in hostlist
        try
            # AWS route and key setup takes some time. Retry a few times.
            n_try_connect = 30
            np = 0
            while n_try_connect > 0
                try
                    cmd = `ssh $sshflags juser@$m nproc`
                    io, _= open(detach(cmd))
                    np = parseint(readall(io))
                    (np > 0) && break;
                catch
                    sleep(5.0)
                end
                n_try_connect = n_try_connect - 1
            end                    
            (n_try_connect == 0) && error("Error detecting num cores on $m")

            npids = addprocs(fill("juser@$m", np); sshflags=sshflags)

            println("Added $(length(npids)) workers. Total workers $(nworkers())")
        catch e
            println("Error $e processing machine $(m).")
        end
    end
end

function add_workers(;block::Bool=true, active_machines::Array=Any[])
    if block
        while !isfile(mfile)
            sleep(1.0)
        end
        machines = [strip(x) for x in split(readall(mfile))]

        new_machines = setdiff(machines, active_machines)
        add_workers(new_machines)

        empty!(active_machines)
        append!(active_machines, machines)
    else
        @schedule begin
            while true
                add_workers(;block=true, active_machines=active_machines)
                sleep(1.0)
            end
        end
    end
    nothing
end

end # module
