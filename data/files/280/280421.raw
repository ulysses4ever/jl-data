import Base.run
import Base.read
using HDF5

#Class Definitions
type H5Task
    file
    source
    sink
    jobs
    props
end


type H5Job
    task
    script
    func
    args
    props
    id
end

function H5Job(task, script, func, args)
    hh = H5Job(task, script, func, args, Dict{Any,Any}(), length(task.jobs)+1)
    push!(task.jobs, hh)
    k = [keys(task.props)...]
    for j=1:length(k)
        hh[k[j]] = task.props[k[j]]
    end
    hh
end

function setindex!(task::H5Task, val, name::ASCIIString)
    task.props[name] = val
end

function setindex!(job::H5Job, val, name::ASCIIString)
    job.props[name] = val
end

function read(job::H5Job)
    h5open(job.task.file) do file
        read(file[string("/results/",job.id,"/result")])
    end
end

function run(task::H5Task, N::Int)
    gc()
    taskfile = task.file
    lockfile = string(taskfile, ".lock")
    println("touch $lockfile")
    run(`touch $lockfile`)

    file = h5open(task.file, false, true, true, false, false)
    if(exists(file, task.source))
        o_delete(file[task.source])
    end
    if(exists(file, task.sink))
        o_delete(file[task.sink])
    end
    for i=1:length(task.jobs)
        k = [keys(task.jobs[i].props)...]
        for j=1:length(k)
            file[string(task.source,i,"/",k[j])] = task.jobs[i].props[k[j]]
        end
    end

    if(exists(file, "/sched/"))
        o_delete(file["/sched/"])
    end
    for i=1:length(task.jobs)
        file[string("/sched/",i,"/taken")]  = 0
        file[string("/sched/",i,"/script")] = task.jobs[i].script
        file[string("/sched/",i,"/func")]   = task.jobs[i].func
        file[string("/sched/",i,"/args")]   = task.jobs[i].args
    end

    close(file)

    running = Any[]

    println("Starting Jobs...")
    for i=1:N
        #println(`julia -e \"reload(\"child.jl\");main(\"$taskfile\",\"$lockfile\")\"`)
        #println(readall(`julia -e reload(\"child.jl\");main(\"$taskfile\",\"$lockfile\")`))
        push!(running, spawn(`julia --depwarn=no -e
        "using LocalJobs;child_main(\"$taskfile\",\"$lockfile\")"`,
        (open("/dev/null","r"), open("stdout.$i.log","w"), open("stderr.$i.log","w"))))
    end

    println("Merging Jobs...")
    for i=1:N
        wait(running[i])
    end

    println("Warnings: ")
    for i=1:N
        out = readall("stdout.$i.log")
        err = readall("stderr.$i.log")
        if(length(err) != 0)
            println("Worker $i Errors:")
            println(err)
        end
        if(length(out) != 0)
            println("Worker $i Output:")
            println(out)
        end
    end

    println("Cleanup Temporary Job Files...")
    for i=1:N
        rm("stdout.$i.log")
        rm("stderr.$i.log")
    end
    rm(lockfile)

    println("Done...")

end
