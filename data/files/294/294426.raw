module JuliaBoxUtils

export add_workers

function add_workers()
    mfile = "/home/juser/.juliabox/machinefile"
    @schedule begin
        active_machines = []
        sshflags = `-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o LogLevel=ERROR -i /home/juser/.ssh/id_rsa`

        while true
            if isfile(mfile)
                machines = [strip(x) for x in split(readall(mfile))]
                new_machines = setdiff(machines, active_machines)
                active_machines = machines

                for m in new_machines
                    try
                        # AWS route and key setup takes some time. Retry a few times.
                        n_try_connect = 30
                        np = 0
                        while n_try_connect > 0
                            try
                                cmd = `ssh $sshflags juser@$m nproc`
                                io, _= open(detach(cmd))
                                np = parseint(readall(io))
                                break;
                            catch
                                sleep(2.0)
                            end
                            n_try_connect = n_try_connect - 1
                        end                    
                        ((n_try_connect == 0) || (np == 0))  && error("Error detecting num cores on $m")

                        npids = addprocs(fill("juser@$m", np); sshflags=sshflags)

                        println("Added $(length(npids)) workers. Total workers $(nworkers())")
                    catch e
                        println("Error $e processing machine $(m).")
                    end
                end
            end
            sleep(1.0)
        end
    end
end

end # module
