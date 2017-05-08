
include("bash.jl")

#! Logger
module Logger
  import Base:
    lpad,
    length

  import Bash:
    clear,
    colors,
    format

  export
    Log,
    log

  #
  # Define a new `Log`.
  #

  type Log
    level::String
    color::String
  end

  #
  # Log given `Log` type with given `msg`.
  #

  function log (log::Log, msg::String)
    println(colors[log.color] * pad(log.level) * ": " * clear * msg)
  end

  #
  # Pad `level` by `10`.
  #

  function pad (level::String)
    max = 10
    len = max - length(level)
    lpad(level, len + 2, ' ')
  end
end