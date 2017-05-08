# A simple async-safe logger implemented with a macro.

type LogLevel
  name::String
  esc::String
  lvl::Int8
end

log_levels = Dict{Symbol, LogLevel}({
  :error => LogLevel("error", "\e[1;31m", 1),
  :info => LogLevel("info", "\e[1;32m", 2),
  :request => LogLevel("req", "\e[1;34m", 3),
  :debug => LogLevel("debug", "\e[1;35m", 4),
  :default => LogLevel("log", "\e[1;30m", 10)
})

log_level = log_levels[:default]

log_dir = "/tmp/jlogs"

function noop() end

macro log(lev::Symbol, msg...)
  local lvl = get(log_levels, lev, log_levels[:default])
  if lvl.name == "log"
    msg = [lev]
  end
  if lvl.lvl > log_level.lvl
    return :(noop())
  end
  return :( print("\e[1;30m[\e[0m "*$lvl.esc*$lvl.name*" \e[1;30m]\e[0m "*
                  (join($(Expr(:tuple,map(i->:(string($i)),msg)...)), " "))*"\n") )
end

try
  log_level = lowercase(ENV["LOG_LEVEL"])
catch end

if !isdir(log_dir)
  try
    mkdir(log_dir)
  catch ex
   @log error "Could not create log directory" log_dir ":" ex
  end
end

log_buffer_size = 0

function get_log_file()
  log_file_path = log_dir * "/out.log"
  global log_file = open(log_file_path, "w")
end

get_log_file()

function log_to_file(str::String)
  log_buffer_size += sizeof(str)
  write(log_file, str)
end
