module HadoopBlocks

using Base.Order
using URIParser
using Compat
using Elly
using Blocks

import Blocks: Block

import Base: close, eof, read, write, readbytes, peek, readall, flush, nb_available, position, filesize, seek, seekend, seekstart, skip,
             start, done, next, wait

export  close, eof, read, write, readbytes, peek, readall, flush, nb_available, position, filesize, seek, seekend, seekstart, skip,
        # from hdfs_jobs.jl
        dmap, dmapreduce, results, status, unload, wait, times, JobId,
        # from hdfs_reader.jl
        MRInput, BlockIO,
        MRMapInput, MRHdfsFileInput, MRFsFileInput,
        MapResultReader, HdfsBlockReader, FsBlockReader

export Block

abstract MapInputReader 
abstract MapStreamInputReader <: MapInputReader
abstract MRInput

function close(r::MapStreamInputReader)
    try
        close(get_stream(r))
    catch
        # do nothing
    end
end

function is_loaded(x::Symbol)
    try
        return (Module == typeof(eval(Main,x)))
    catch
        return false
    end
end

# enable logging only during debugging
using Logging
const logger = Logging.configure(level=DEBUG)
#const logger = Logging.configure(filename="/tmp/elly$(getpid()).log", level=DEBUG)
logmsg(s) = debug(s)
#logmsg(s) = nothing

typealias JobId     Int64
typealias FuncNone  Union(Function,Nothing)

include("scheduler.jl")
using HadoopBlocks.Scheduler
Scheduler.prep_remotes()

include("hdfs_blocks.jl")
include("fs_reader.jl")
include("hdfs_reader.jl")
include("map_result_reader.jl")

include("hdfs_jobs.jl")
include("hdfs_mrutils.jl")

#if(is_loaded(:DataFrames))
#    include("hdfs_mrutils_dataframes.jl")
#end

end # module
