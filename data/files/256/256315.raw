# HttpServer module
#
# Serve HTTP requests in Julia.
#
isdefined(Main, :__precompile__) && __precompile__()

module SimpleHttpCommon

const VERSION=v"0.1.0-dev"
const MODULE = current_module()
const NAME=module_name(MODULE)

using SimpleHttpIO

include("Chunk.jl")

export readline_bare,
       readline_str,
       readline_bare_str,
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
       GET,
       POST,
       PUT,
       UPDATE,
       DELETE,
       OPTIONS,
       HEAD,
       RFC1123_datetime,
       HttpMethodBitmask,
       HttpMethodBitmasks,
       HttpMethodNameToBitmask,
       HttpMethodBitmaskToName,
       escapeHTML,
       encodeURI,
       decodeURI,
       mimetypes

export GET,
       POST,
       PUT,
       UPDATE,
       DELETE,
       OPTIONS,
       HEAD,
       escapeHTML,
       mimetypes,
       encodeURI,
       decodeURI

import .Chunk

export IOChunked,
    AbstractIOSocket

include("common.jl")
include("protocol_api.jl")
include("request.jl")
include("response.jl")
include("protocols.jl")

end
