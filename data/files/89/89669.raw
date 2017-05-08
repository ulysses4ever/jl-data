include("Jake.jl")

export run

using ArgParse
using Jake

function args()
  settings = ArgParseSettings()

  @add_arg_table settings begin
      "task"
        help = "The jake task to execute."
      "--file", "-f"
        help = "Specify the Jakefile to use."
        arg_type = String
        default = "./Jakefile"
      "--list", "-l"
        help = "Display the tasks with description, then exit."
        action = :store_true
      "--version", "-v"
        help =  "Show the current jake version."
        action = :store_true
  end

  return parse_args(settings)
end

function run(dir)
  parsed_args = args()

  if parsed_args["version"] == true
    println("jake v0.0.-1 as it's just not ready yet")
    exit()
  end

  include("$(dir)/$(parsed_args["file"])")

  if parsed_args["list"] == true
    list()
    exit()
  end

  if isa(parsed_args["task"], String)
    s = symbol(parsed_args["task"])
    execute(s)
  end

end
