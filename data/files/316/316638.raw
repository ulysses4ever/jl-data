module PyLogging

using PyCall
@pyimport logging
export @critical, @error, @warning, @info, @debug
export getLogger, basicConfig

# 50, 40, ..., 0
const CRITICAL = logging.CRITICAL
const ERROR = logging.ERROR
const WARNING = logging.WARNING
const INFO = logging.INFO
const DEBUG = logging.DEBUG
const NOTSET = logging.NOTSET


immutable Logger
	logger::PyObject
end


function getLogger()
	logger = logging.getLogger()
	Logger(logger)
end
 
 
function getLogger(name::AbstractString)
	logger = logging.getLogger(name)
	Logger(logger)
end

function basicConfig(;kwargs...)
	logging.basicConfig(;kwargs)
end



function _log(logger::Logger, level::Int, msg::AbstractString)
	logger.logger[:_log](level, msg, [])
end


function critical(logger::Logger, msg::AbstractString)
	if logger.logger[:isEnabledFor](CRITICAL)
		_log(logger, CRITICAL, msg)
	end
end


function error(logger::Logger, msg::AbstractString)
	if logger.logger[:isEnabledFor](ERROR)
		_log(logger, ERROR, msg)
	end
end


function warning(logger::Logger, msg::AbstractString)
	if logger.logger[:isEnabledFor](WARNING)
		_log(logger, WARNING, msg)
	end
end


function info(logger::Logger, msg::AbstractString)
	if logger.logger[:isEnabledFor](INFO)
		_log(logger, INFO, msg)
	end
end


function debug(logger::Logger, msg::AbstractString)
	if logger.logger[:isEnabledFor](DEBUG)
		_log(logger, DEBUG, msg)
	end
end


macro critical(logger, msg)
	quote
		x = $(esc(logger))
		if x.logger[:isEnabledFor](CRITICAL)
			_log(x, CRITICAL, $(esc(msg)))
		end
	end
end


macro error(logger, msg)
	quote
		x = $(esc(logger))
		if x.logger[:isEnabledFor](ERROR)
			_log(x, ERROR, $(esc(msg)))
		end
	end
end


macro warning(logger, msg)
	quote
		x = $(esc(logger))
		if x.logger[:isEnabledFor](WARNING)
			_log(x, WARNING, $(esc(msg)))
		end
	end
end


macro info(logger, msg)
	quote
		x = $(esc(logger))
		if x.logger[:isEnabledFor](INFO)
			_log(x, INFO, $(esc(msg)))
		end
	end
end


macro debug(logger, msg)
	quote
		x = $(esc(logger))
		if x.logger[:isEnabledFor](DEBUG)
			_log(x, DEBUG, $(esc(msg)))
		end
	end
end

end