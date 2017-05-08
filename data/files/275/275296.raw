function sortfile(infname::AbstractString, outfname::AbstractString, offset::Int=0, len::Int=0)
    dfs = HDFSClient(TeraSort.DFSHOST, TeraSort.DFSPORT, UserGroupInformation(TeraSort.DFSUSER))
    exists(dfs, infname) || (return 0)
    fptr = open(dfs, infname, "r")
    wptr = open(dfs, outfname, "w")
    try
        (len == 0) && (len = Int(filesize(fptr)))
        sortfile(fptr, wptr, 0, len)
    finally
        close(fptr)
        close(wptr)
    end
    len
end

function sortfile(fptr::IO, wptr::IO, offset::Int, len::Int)
    seek(fptr, offset)
    data = Array(UInt8, len)
    read!(fptr, data)
    datastr = bytestring(data)
    dataarr = split(datastr)
    sort!(dataarr)
    for s in dataarr
        write(wptr, s, '\n')
    end
    nothing
end

function sortrandfile(fname::AbstractString)
    println("sortrandfile starting at $(myid())")
    locfname = "$(fname)-$(myid())"
    d,f = splitdir(locfname)
    sortedfname = joinpath(TeraSort.OUTDIR, f)
    nbytes = sortfile(locfname, sortedfname)
    println("sortrandfile sorted $nbytes bytes at $(myid())")
    nbytes
end

function distsortfile()
    wrkrs = workers()
    nwrkrs = length(wrkrs)
    refs = Array(RemoteRef, nwrkrs)
    idx = 1
    fname = joinpath(INDIR, "randstr")
    for nid in wrkrs
        refs[idx] = @spawnat nid TeraSort.sortrandfile(fname)
        idx += 1
    end
    nbytes = 0
    for idx in 1:nwrkrs
        nbytes += fetch(refs[idx])
    end
    nbytes
end

function terasort()
    nbytes, t, b, g = @timed distsortfile()
    println("sorted $nbytes bytes")
    println("time:$t, memused:$b, gctime:$g")
end
