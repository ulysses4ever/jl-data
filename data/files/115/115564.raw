
using JSON

length(ARGS) < 1 && error("The first argument to dependency-resolver.jl is a path to dependency config file.")

dependency_file = abspath(ARGS[1])
dependency_data = JSON.parse(readall(dependency_file))

job_signals = { job_name => RemoteRef() for (job_name, data) in dependency_data }

function run_job(signal::RemoteRef, dependencies::Dict, job_command)
    # yield until all of our dependencies have finished
    [ wait(dep_signal) for (dep_name, dep_signal) in dependencies ]

    # execute the job (obviously silly, but this is just an example)
    result = eval(parse(job_command))

    # signal that we're finished
    put!(signal, result)
end

println("Starting jobs...")

# sync will block until all async blocks created inside have finished
@sync begin

    for (job_name, job_data) in dependency_data
        dep_names = get(job_data, "dependencies", [])

        # find all the dependencies for this job
        deps = Dict()
        for dep_name in dep_names
            deps[dep_name] = job_signals[dep_name]
        end

        @async begin
            run_job(job_signals[job_name], deps, job_data["command"])
        end
    end

end

println("\nAll jobs complete!")
