reload("master.jl")

#Setup Task Parameters
task         = H5Task("work.h5", "input/", "results/", H5Job[], Dict{Any,Any}())
task["cols"] = 18
script       = "example-job.jl"
func         = "job_function"

#Define Individual Jobs
job1         = H5Job(task, script, func, ["cols", "rows"])
job1["rows"] = 3
job2         = H5Job(task, script, func, ["cols", "rows"])
job2["rows"] = 4
job3         = H5Job(task, script, func, ["cols", "rows"])
job3["rows"] = 2
job4         = H5Job(task, script, func, ["cols", "rows"])
job4["rows"] = 1
job5         = H5Job(task, script, func, ["cols", "rows"])
job5["rows"] = 30
job6         = H5Job(task, script, func, ["cols", "rows"])
job6["rows"] = 3

#Run The Jobs
run(task, 8)

#View Some Results
read(job6)
