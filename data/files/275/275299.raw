const KB = 1024
const MB = KB*KB
const BLKSZ = 128 * MB
const RECSZ = 100
const RECSPERBLK = round(Int, BLKSZ/RECSZ)

const DFSUSER = ENV["USER"]
const UGI = UserGroupInformation(DFSUSER)
const DFSHOST = "localhost"
const DFSPORT = 9000

const INDIR = "/sortinp"
const OUTDIR = "/sortout"
const SAMPDIR = "/sortsamp"

function cleanup()
    println("cleaning up last run...")
    dfs = HDFSClient(DFSHOST, DFSPORT, UGI)
    for d in (INDIR, OUTDIR, SAMPDIR)
        exists(dfs, d) && rm(dfs, d, true)
    end
    nothing
end

function startcluster(clean::Bool=false)
    if clean
        cleanup()
        println("creating empty folder...")
        dfs = HDFSClient(DFSHOST, DFSPORT, UGI)
        for d in (INDIR, OUTDIR, SAMPDIR)
            mkdir(dfs, d)
        end
    end

    println("creating app master...")
    yarncm = YarnManager(yarnhost="localhost", rmport=8032, schedport=8030, launch_timeout=60)
    nnodes = nodecount(yarncm.clnt)

    println("adding $nnodes nodes")
    appenv = Dict("JULIA_PKGDIR" => Pkg.dir())
    addprocs(yarncm; np=nnodes, env=appenv)
    if nworkers() != nnodes
        stopcluster()
        error("Error bringing up all nodes")
    end
    yarncm
end

function stopcluster(yarncm::YarnManager)
    rmprocs(workers())
    Elly.disconnect(yarncm)
end

function splitpoints(len::Int, n::Int)
    out = Int[]
    i = 0
    nrem = n
    while i < len
        s = ceil(Int, ((len - i) / nrem))
        nrem -= 1
        push!(out, i+=s)
   end
   out[1:(n-1)]
end
