module JuliaBoxUtils

export add_workers

function add_workers()
    mfile = "/home/juser/.juliabox/machinefile"
    @schedule begin
        active_machines = Set()
        sshflags = `-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o LogLevel=ERROR -i /home/juser/.ssh/id_rsa`

        while true
            if isfile(mfile)
                machines = [strip(x) for x in split(readall(mfile))]
                new_machines = setdiff(machines, active_machines)
                active_machines = machines

                for m in new_machines
                    try
                        cmd = `ssh $sshflags juser@$m nproc`
                        io, _= open(detach(cmd))
                        np = parseint(readall(io))
                        npids = addprocs(fill("juser@$m", np))

                        println("Added $(length(npids)) workers. Total workers $(nworkers())")
                    catch e
                        println("Error detecting num cores on $m")
                    end
                end

            end
            sleep(1.0)
        end
    end
end

end # module
