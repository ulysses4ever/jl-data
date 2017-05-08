##
# MapInputReader to read block sized dataframes
type HdfsBlockReader <: MapStreamInputReader
    hbr::BlockIO
    end_byte::Union{Char,Void}
    function HdfsBlockReader(url::AbstractString="", end_byte::Union{Char,Void}=nothing)
        ret = new()
        ret.end_byte = end_byte
        !isempty(url) && reset_pos(ret, url)
        ret
    end
end
get_stream(hdfr::HdfsBlockReader) = hdfr.hbr
function reset_pos(hdfr::HdfsBlockReader, url::AbstractString)
    u = URI(url)
    frag = u.fragment
    url = string(defrag(u))

    f = open(HDFSFile(url), "r")
    blksz = f.block_sz
    blk = parse(Int, frag)
    begn = blksz*(blk-1)+1
    endn = min(filesize(f),blksz*blk)
    #logmsg("processing block $blk range $begn : $endn")
    hdfr.hbr = BlockIO(f, begn:endn, hdfr.end_byte)
end


##
# Input for map
type MRHdfsFileInput <: MRInput
    source_spec
    reader_fn::Function

    file_list
    file_info
    file_blocks

    function MRHdfsFileInput(source_spec, reader_fn::Function, rdr_type::AbstractString="")
        new(source_spec, reader_fn, nothing, nothing, nothing)
    end
end

# allowed types: buffer, stream
input_reader_type(inp::MRHdfsFileInput) = (MRHdfsFileInput, "")
get_input_reader(::Type{MRHdfsFileInput}, rdr_typ::AbstractString) = HdfsBlockReader("", '\n')

function expand_file_inputs(inp::MRHdfsFileInput)
    #logmsg("expand_file_inputs begin")
    fl = ASCIIString[]
    infol = HDFSFileInfo[]
    blockl = Any[]
    rwild = r"[\*\[\?]"
    fspec = ""
   
    function add_file(f::HDFSFile) 
        push!(fl, string(convert(URI, f)))
        push!(infol, stat(f))
        push!(blockl, hdfs_blocks(f))
    end

    function add_dir(d::HDFSFile, pattern::Regex=r".*")
        basep = string(convert(URI, f))
        endswith(basep, '/') || (basep = basep * "/")

        for cname in readdir(f)
            cfile = HDFSFile(basep * cname)
            if !isdir(cfile) && ismatch(pattern, cname)
                add_file(cfile)
            end
        end
    end

    for fspec in inp.source_spec
        up = URI(fspec)
        if(ismatch(rwild, fspec))                                   # a directory with wild card specification
            url,pattern = rsplit(fspec, '/', limit=2)               # separate the directory path and wild card specification
            ((pattern == "") || ismatch(rwild,url)) && error(string("wild card must be part of file name. invalid url: ", fspec))
            add_dir(HDFSFile(url * "/"), Regex(pattern))
        else
            f = HDFSFile(fspec)
            isdir(f) ? add_dir(f) : add_file(f)
        end
    end
    inp.file_list = fl
    inp.file_info = infol
    inp.file_blocks = blockl
    #logmsg("expand_file_inputs ret: $inp")
    inp
end

