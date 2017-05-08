require("types")

module Args

using ArgParse
using Types
using Docile

@docstrings

@doc """
Define a global arguments

__args__:
  - *s::`ArgParseSettings`*: Object to store the allowed arguments and options.

__returns__: `Nothing`
""" ->
function add_general_args(s::ArgParseSettings)
  @add_arg_table s begin
    "new"
      help = "Generate skeleton"
      action = :command
    "build"
      help = "Compile the site source"
      action = :command
    "server"
      help = "Serve the compiled site"
      action = :command
    "clean"
      help = "Delete the site generated"
      action = :command
    "--config-path"
      help = "Where I pick the configurations"
      arg_type = Types.Path
      default = "."
  end
end


@doc """
Specify the arguments to scaffold a new project or override an existing.

__args__:
  - *s::`ArgParseSettings`*: Object to store the allowed arguments and options.

__returns__: `Nothing`
""" ->
function add_new_args(s::ArgParseSettings)
  @add_arg_table s begin
    "--no-extra", "-n"
      help = "no adds external tools"
      action = :store_true
    "--path", "-a"
      help = "destination path"
      arg_type = Types.Path
      default = "."
    "--light", "-l"
      help = "no add sample site"
      action = :store_true
  end
end


@doc """
Specify the arguments to create a new instance of Morsel to serve the static
site.

__args__:
  - *s::`ArgParseSettings`*: Object to store the allowed arguments and options.

returns: Nothing
""" ->
function add_server_args(s::ArgParseSettings)
    @add_arg_table s begin
      "--port", "-p"
      help = "Server port"
      arg_type = Int
      default = 8080
    "--host", "-H"
      help = "Host"
      arg_type = String
      default = "127.0.0.1"
  end
end

@doc """
Build the parser for general and subcommands configuration.

__args__: `Nothing`

__returns__: `Nothing`
""" ->
function parse_cli()
  s = ArgParseSettings("Julia static site generator",
                     commands_are_required = true,
                     version = "0.1",
                     add_version = true)
  add_general_args(s)
  add_new_args(s["new"])
  add_server_args(s["server"])

  parse_args(s)
end
end
