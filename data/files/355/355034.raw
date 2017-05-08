module JuliaBoxUtils

export add_workers

const mfile = "/home/juser/.juliabox/machinefile.private"
const sshflags = `-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o LogLevel=ERROR -i /home/juser/.ssh/id_rsa`

function test_nproc(m, debug, t0)
    try
        cmd = `ssh $sshflags juser@$m nproc`
        io, _= open(detach(cmd))
        np = parseint(readall(io))
        (np > 0) ? true : false
    catch e
        str = " $m error $e trying again\n"
        debug && print(time()-t0, str)
    end
end

function add_workers(hostlist; debug=false, nproc=false)
    t0 = time()
    while length(hostlist) > 0
        hosts = splice!(hostlist, 1:(length(hostlist)>5 ? 5 : length(hostlist)))
        try
            # AWS route and key setup takes some time. Retry a few times.
            if nproc
                    n_try_connect = 30
                    np = 0
                    while n_try_connect > 0
                        results = cell(length(hosts))
                        @sync begin
                            for (idx,m) in enumerate(hosts)
                                let m=m, idx=idx
                                    @async results[idx] = test_nproc(m, debug, t0)
                                end
                            end
                        end
                        debug && println("hosts,results  : ", hosts, ", ", results)
                        if !all(results)
                            debug && println(time()-t0, " trying nproc again after 5 seconds")
                            sleep(5.0)
                        end
                        n_try_connect = n_try_connect - 1
                    end                    
                    (n_try_connect == 0) && error("Error detecting num cores")
            end

            np = 32  # The above is only to test connectivity. Assuming 32 cores anyways.
            ap_hosts=Any[]
            for m in hosts
                append!(ap_hosts, fill("juser@$m", np))
            end
            debug && println(time()-t0, " $hosts before addprocs")
            npids = addprocs(ap_hosts; sshflags=sshflags)
            debug && println(time()-t0, " $hosts after addprocs")

            println("Added $(length(npids)) workers. Total workers $(nworkers())")
        catch e
            println("Error $e processing machines $(hosts).")
        end
    end
end

function add_workers(;block::Bool=true, active_machines::Array=Any[], debug=false, nproc=false)
    if block
        while !isfile(mfile)
            sleep(1.0)
        end
        machines = [strip(x) for x in split(readall(mfile))]

        new_machines = setdiff(machines, active_machines)
        add_workers(new_machines; debug=debug, nproc=nproc)

        empty!(active_machines)
        append!(active_machines, machines)
    else
        @schedule begin
            while true
                add_workers(;block=true, active_machines=active_machines, debug=debug, nproc=nproc)
                sleep(1.0)
            end
        end
    end
    nothing
end

end # module
