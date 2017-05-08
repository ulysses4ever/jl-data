module Jake

  export desc,
         task,
         list,
         execute

  include("Task.jl")

  tasks = Dict()
  recent_description = String[]

  function desc(description)
    push!(recent_description, description)
  end

  function task(f::Function, name::Symbol)
    last_description = pop!(recent_description)
    tasks[name] = Task(name, last_description, f)
  end

  function list()
    println(tasks)
  end

  function execute(task_name::Symbol)
    task = tasks[task_name]
    task.task()
  end

end
