module Jake

  export desc,
         task

  include("Task.jl")

  tasks = Task[]
  recent_description = String[]

  function desc(description)
    push!(recent_description, description)
  end

  function task(f::Function, name::Symbol)
    last_description = pop!(recent_description)
    push!(tasks, Task(name, last_description, f))
  end

end
