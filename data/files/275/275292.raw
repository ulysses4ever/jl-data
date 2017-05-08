function samplefile(infname::AbstractString, outfname::AbstractString, pct::Float64=0.0005, sorted::Bool=true)
    dfs = HDFSClient(TeraSort.DFSHOST, TeraSort.DFSPORT, UserGroupInformation(TeraSort.DFSUSER))
    exists(dfs, infname) || (return 0)
    fptr = open(dfs, infname, "r")
    wptr = open(dfs, outfname, "w")
    nsamp = 0
    try
        nsamp = samplefile(fptr, wptr, pct, sorted)
    finally
        close(fptr)
        close(wptr)
    end
    nsamp
end

function samplefile(fptr::IO, wptr::IO, pct::Float64, sorted::Bool=true)
    len = filesize(fptr)
    data = Array(UInt8, len)
    read!(fptr, data)
    datastr = bytestring(data)
    dataarr = split(datastr)

    nsamp = round(Int, length(dataarr) * pct + 1)
    dataarr = sample(dataarr, nsamp)
    sorted && sort!(dataarr)

    for s in dataarr
        write(wptr, s, '\n')
    end
    nsamp
end

function samplerandfile(fname::AbstractString)
    println("samplerandfile starting at $(myid())")
    locfname = "$(fname)-$(myid())"
    d,f = splitdir(locfname)
    sampfname = joinpath(TeraSort.SAMPDIR, f)
    nsamp = samplefile(locfname, sampfname)
    println("samplerandfile sampled $nsamp records at $(myid())")
    nsamp
end

function samplefilenames(fname::AbstractString, wrkrs)
    d,f = splitdir(fname)
    sampfname = joinpath(TeraSort.SAMPDIR, f)
    ["$sampfname-$id" for id in wrkrs]
end

function getpartitionpoints(infname::AbstractString, outfname::AbstractString, nparts::Int)
    println("determining partition points...")
    dfs = HDFSClient(TeraSort.DFSHOST, TeraSort.DFSPORT, UserGroupInformation(TeraSort.DFSUSER))
    fptr = open(dfs, infname, "r")
    wptr = open(dfs, outfname, "w")
    splpts = splitpoints(Int(filesize(fptr)), nparts)
    for splpt in splpts
        seek(fptr, max(0, splpt-TeraSort.RECSZ))
        s = readline(fptr)
        (length(s) == TeraSort.RECSZ) || (s = readline(fptr))
        write(wptr, s)
    end
    close(fptr)
    close(wptr) 
    println("wrote $(length(splpts)) partition points for $nparts partitions")
    nothing
end

function distsamplefile()
    wrkrs = workers()
    nwrkrs = length(wrkrs)
    refs = Array(RemoteRef, nwrkrs)
    idx = 1
    fname = joinpath(INDIR, "randstr")
    for nid in wrkrs
        refs[idx] = @spawnat nid TeraSort.samplerandfile(fname)
        idx += 1
    end
    nrecs = 0
    for idx in 1:nwrkrs
        nrecs += fetch(refs[idx])
    end
    sampfnames = samplefilenames(fname, wrkrs)
    mergesorted("$fname-sample", sampfnames...)
    getpartitionpoints("$fname-sample", "$fname-partitions", 5)
    nrecs
end

function terasample()
    nrecs = t = b = g = 0
    nrecs, t, b, g = @timed distsamplefile()
    println("sampled $nrecs records")
    println("time:$t, memused:$b, gctime:$g")
end
