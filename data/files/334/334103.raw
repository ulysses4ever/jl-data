module Logging

using Match

import Base.show

export debug, info, warn, err, critical, log,
       @debug, @info, @warn, @err, @critical, @loglevel,
       Logger,
       LogLevel, DEBUG, INFO, WARNING, ERROR, CRITICAL

include("enum.jl")

@enum LogLevel DEBUG INFO WARNING ERROR CRITICAL

type Logger
    name::String
    level::LogLevel
    output::IO
    parent::Logger

    Logger(name::String, level::LogLevel, output::IO, parent::Logger) = new(name, level, output, parent)
    Logger(name::String, level::LogLevel, output::IO) = (x = new(); x.name = name; x.level=level; x.output=output; x.parent=x)
end

show(io::IO, logger::Logger) = print(io, "Logger(", join([logger.name, 
                                                          logger.level, 
                                                          logger.output,
                                                          logger.parent.name], ","), ")")

const _root = Logger("root", WARNING, STDERR)
Logger(name::String;args...) = configure(Logger(name, WARNING, STDERR); args...)

for (fn,lvl,clr) in ((:debug,    DEBUG,    :cyan),
                     (:info,     INFO,     :blue),
                     (:warn,     WARNING,  :magenta),
                     (:err,      ERROR,    :red),
                     (:critical, CRITICAL, :red))

    @eval function $fn(msg::String, logger = _root)
        if $lvl >= logger.level
            Base.print_with_color($(Expr(:quote, clr)), logger.output, string($lvl), ":", logger.name, ":", msg, "\n")
        end
    end
end

function configure(logger=_root; args...)
    for (tag, val) in args
        if tag == :parent
            logger.parent = parent = val::Logger
            logger.level = parent.level
            logger.output = parent.output
        end
    end

    for (tag, val) in args
        @match tag begin
            :io       => logger.output = val::IO
            :filename => logger.output = open(val, "w")
            :level    => logger.level  = val::LogLevel  #if logger == _root;  @loglevel(val::LogLevel) else logger.level  = val::LogLevel end
            :parent   => logger.parent = val::Logger
            unk       => Base.error("Logging: unknown configure argument \"$unk\"")
        end
    end

    logger
end

macro loglevel(level)
    quote
        configure(level=$(esc(level)))
        evalfile("LoggingMacro.jl")
    end
end

@loglevel(WARNING)

end # module
