# HttpServer module
#
# Serve HTTP requests in Julia.
#
isdefined(Main, :__precompile__) && __precompile__()

module SimpleHttpCommon

const VERSION=v"0.1.0-dev"
const MODULE = current_module()
const NAME = module_name(MODULE)

using SimpleHttpIO

const N = SimpleHttpIO.N
const N_TYPE = SimpleHttpIO.N_TYPE
const STR_TYPE = SimpleHttpIO.STR_TYPE
import URIParser: URI, unescape

include("Chunk.jl")

export readlinebare,
       readlinestr,
       readlinebarestr,
       AbstractIOSocket,
       writeln,
       CRLF,
       AbstractIOSocket,
       IOSocket,
       readbyte,
       BYTE_TYPE

import DataStructures: OrderedDict
import Base: readbytes,
             readline,
             readuntil
using HttpCommon: STATUS_CODES,
       escapeHTML,
       mimetypes

import .Chunk

export IOChunked,
    AbstractIOSocket

include("common.jl")
include("protocol_api.jl")
include("request.jl")
include("response.jl")
include("protocols.jl")

end
