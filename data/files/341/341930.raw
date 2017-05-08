using HDF5

"""
Create a lock file
"""
lock_create(filename) = open(filename,"w")

const LOCK_SH = 1
const LOCK_EX = 2
const LOCK_NB = 4
const LOCK_UN = 8
has_job     = false
job_info    = nothing
job_results = nothing

flock(fd::Int, op::Int) = ccall(:flock, Int, (Int, Int), fd, op)

lock_read(lock::Int)   = flock(lock, LOCK_SH)
lock_write(lock::Int)  = flock(lock, LOCK_EX)
lock_unlock(lock::Int) = flock(lock, LOCK_UN)

"""
Aquire a job from the task scheduler
"""
function get_job(task_file)
    h5open(task_file, "r+") do file
        id = 1
        while(true)
            #println('*')
            addr   = string("/sched/",id,"/taken")
            script = string("/sched/",id,"/script")
            func   = string("/sched/",id,"/func")
            args   = string("/sched/",id,"/args")
            if(!exists(file, addr))
                #println(":(")
                global has_job
                has_job = false
                break
            elseif(read(file[addr]) == 0)
                #println(":)")
                println("job id = $id")
                global has_job
                global job_info
                has_job  = true
                arg_name = read(file[args])
                arg_val  = map(x->read(file[string("/input/",id,"/",x)]),arg_name)
                job_info = (id, read(file[script]), read(file[func]), arg_val)
                o_delete(file, addr)
                file[addr] = 1
                break
            end
            id += 1
        end
    end

    #println("get_job...")
    #has_job = false
end

"""
Run the job
"""
function perform_job()
    #println("Performing job: ", job_info)
    reload(job_info[2])
    global job_results
    job_results = eval(parse(string(job_info[3], "(job_info[4]...)")))
    #println("job results = ", job_results)
end

"""
Put the results into the task file
"""
function dump_results(task_file)
    h5open(task_file, "r+") do file
        if(!isa(job_results, Tuple))
            file[string("/results/",job_info[1], "/result")] = job_results
        else
            for i=1:length(job_results)
                file[string("/results/",job_info[1], "/result/",i)] = job_results[i]
            end
        end
    end
end


"""
Consume jobs from task_file, using lock_file to avoid concurency issues until no
jobs remain
"""
function child_main(task_file, lock_file)
    #println("Main...");
    global has_job
    lock    = lock_create(lock_file)
    lock_id = fd(lock)
    while(true)
        lock_write(lock_id)
        get_job(task_file)
        lock_unlock(lock_id)
        if(!has_job)
            break
        end

        perform_job()

        lock_write(lock_id)
        dump_results(task_file)
        lock_unlock(lock_id)
    end
end
