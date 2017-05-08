module PyLogging

using PyCall

export @critical, @error, @warning, @info, @debug
export getLogger

const logging = pyimport("logging")

# 50, 40, ..., 0
const CRITICAL = convert(Int, logging["CRITICAL"])
const ERROR = convert(Int, logging["ERROR"])
const WARNING = convert(Int, logging["WARNING"])
const INFO = convert(Int, logging["INFO"])
const DEBUG = convert(Int, logging["DEBUG"])
const NOTSET = convert(Int, logging["NOTSET"])


immutable Logger
    logger::PyObject
    # The followings are cached so that we don't have to create many pyobjects.
    isEnabledFor::PyObject
    _log::PyObject

    function Logger(logger::PyObject)
        new(
            logger,
            logger["isEnabledFor"],
            logger["_log"]
        )
    end
end



function getLogger()
    logger = pycall(logging["getLogger"], PyObject)
    Logger(logger)
end


function getLogger(name::AbstractString)
    logger = pycall(logging["getLogger"], PyObject, name)
    Logger(logger)
end

function basicConfig(;kwargs...)
    pycall(logging["basicConfig"], PyObject; kwargs...)
end



function _log(logger::Logger, level::Int, msg::AbstractString)
    logger._log(level, msg, [])
end


function critical(logger::Logger, msg::AbstractString)
    if logger.isEnabledFor(CRITICAL)
        _log(logger, CRITICAL, msg)
    end
end


function error(logger::Logger, msg::AbstractString)
    if logger.isEnabledFor(ERROR)
        _log(logger, ERROR, msg)
    end
end


function warning(logger::Logger, msg::AbstractString)
    if logger.isEnabledFor(WARNING)
        _log(logger, WARNING, msg)
    end
end


function info(logger::Logger, msg::AbstractString)
    if logger.isEnabledFor(INFO)
        _log(logger, INFO, msg)
    end
end


function debug(logger::Logger, msg::AbstractString)
    if logger.isEnabledFor(DEBUG)
        _log(logger, DEBUG, msg)
    end
end


macro critical(logger, msg)
    quote
        x = $(esc(logger))
        if x.isEnabledFor(CRITICAL)
            _log(x, CRITICAL, $(esc(msg)))
        end
    end
end


macro error(logger, msg)
    quote
        x = $(esc(logger))
        if x.isEnabledFor(ERROR)
            _log(x, ERROR, $(esc(msg)))
        end
    end
end


macro warning(logger, msg)
    quote
        x = $(esc(logger))
        if x.isEnabledFor(WARNING)
            _log(x, WARNING, $(esc(msg)))
        end
    end
end


macro info(logger, msg)
    quote
        x = $(esc(logger))
        if x.isEnabledFor(INFO)
            _log(x, INFO, $(esc(msg)))
        end
    end
end


macro debug(logger, msg)
    quote
        x = $(esc(logger))
        if x.isEnabledFor(DEBUG)
            _log(x, DEBUG, $(esc(msg)))
        end
    end
end

end