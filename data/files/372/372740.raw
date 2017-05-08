module Dispatch
  require("server")
  require("new")
  require("scaffold")
  require("Monad")

  using Docile

  @docstrings

  @doc """
  Call the appropiate action to execute.

  __args__:
    - *command::`Symbol`*: Action to execute.
      + new
      + generate
      + server
    - *config::`Dict{Any, Any}`*: Context around the action.

  __return__: `Nothing`
  """ ->
  function dispatch_command(command::Symbol, config::Dict{Any, Any})
    @mdo Maybe begin
      m <- Monad(Expr(:call, command, config))
      return m.state
    end
  end
end
