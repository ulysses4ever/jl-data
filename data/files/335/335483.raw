function mergesorted(outfname::AbstractString, infnames::AbstractString...)
    dfs = HDFSClient(TeraSort.DFSHOST, TeraSort.DFSPORT, UserGroupInformation(TeraSort.DFSUSER))
    for infname in infnames
        exists(dfs, infname) || (return 0)
    end
    fptrs = [open(dfs, infname, "r") for infname in infnames]
    wptr = open(dfs, outfname, "w")
    try
        mergesorted(wptr, fptrs...)
    finally
        for fptr in fptrs
            close(fptr)
        end
        close(wptr)
    end
    nothing
end

function mergesorted(wfile::IO, fptrs::IO...)
    println("merging sorted files...")
    inio = [fptrs...]
    nio = length(inio)
    lines = map(x->readline(x), inio)
    while length(inio) > 0
        (str,pos) = findmin(lines)
        write(wfile, str)
        if eof(inio[pos])
            splice!(inio, pos)
            splice!(lines, pos)
        else
            lines[pos] = readline(inio[pos])
        end
    end
    println("merged $(length(fptrs)) files")
    nothing
end

function merge(outfname::AbstractString, infnames::AbstractString...)
    dfs = HDFSClient(TeraSort.DFSHOST, TeraSort.DFSPORT, UserGroupInformation(TeraSort.DFSUSER))
    for infname in infnames
        exists(dfs, infname) || (return 0)
    end
    fptrs = [open(dfs, infname, "r") for fname in infnames]
    wptr = open(dfs, outfname, "w")
    try
        merge(wptr, fptrs...)
    finally
        for fptr in fptrs
            close(fptr)
        end
        close(wptr)
    end
    nothing
end

function merge(wptr::IO, fptrs::IO...)
    for fptr in fptrs
        d = readall(fptr)
        write(wptr, d)
        if d[end] != '\n'
            write(wptr, '\n')
        end
    end
    nothing
end
