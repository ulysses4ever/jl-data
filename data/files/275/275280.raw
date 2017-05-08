function genrandfile(fname::AbstractString, nblks::Int)
    println("genrandfile starting at $(myid())")
    dfs = HDFSClient(TeraSort.DFSHOST, TeraSort.DFSPORT, UserGroupInformation(TeraSort.DFSUSER))
    open(dfs, "$fname-$(myid())", "w") do fptr
        for blk in 1:nblks
            for rec in 1:RECSPERBLK
                write(fptr, randstring(RECSZ-1), '\n')
            end
        end
    end
    println("genrandfile created $nblks blocks at $(myid())")
    nblks
end

function distgenrandfile(fname::AbstractString, nblkspernode::Int)
    wrkrs = workers()
    nwrkrs = length(wrkrs)
    refs = Array(RemoteRef, nwrkrs)
    idx = 1
    for nid in wrkrs
        refs[idx] = @spawnat nid TeraSort.genrandfile(fname, nblkspernode)
        idx += 1
    end
    nblks = 0
    for idx in 1:nwrkrs
        nblks += fetch(refs[idx])
    end
    nblks
end

function teragen()
    nblks,t,b,g = @timed distgenrandfile(joinpath(INDIR, "randstr"), 2)
    println("created $nblks blocks at 2 blocks per node")
    println("time:$t, memused:$b, gctime:$g")
end
