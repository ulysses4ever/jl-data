
# calculates column max of a large matrix stored in HDFS
# julia -p 3
# include("test_maxval.jl")

using Elly
using HadoopBlocks

const INP = "hdfs://tan@localhost:9000/maxvalinp.csv"

if myid() == 1
    function gendata(M, N)
        open(HDFSFile(INP), "w") do f
            for m in 1:M
                write(f, join(map(string, rand(N)), ","), "\n")
            end
        end
    end
    gendata(10^5, 5)
end

# split script here and uncomment below lines to run data generation and computation separately
#using Elly
#using HadoopBlocks
#const INP = "hdfs://tan@localhost:9000/maxvalinp.csv"

findrow(r::HdfsBlockReader, iter_status) = HadoopBlocks.find_rec(r, iter_status, Vector)

maprow(rec) = [tuple([parse(Float64, x) for x in rec]...)]

function collectrow(results, rec)
    isempty(rec) && (return results)
    (results == nothing) && (return rec)
    tuple([max(results[x],rec[x]) for x in 1:length(results)]...)
end

function reducerow(reduced, results...)
    (nothing == reduced) && (reduced = zeros(Float64, length(results[1])))
    for res in results
        (nothing == res) && continue
        for x in 1:length(res)
            reduced[x] = max(reduced[x], res[x])
        end
    end
    reduced
end

function wait_results(j_mon)
    loopstatus = true
    while(loopstatus)
        sleep(5)
        jstatus,jstatusinfo = status(j_mon,true)
        ((jstatus == "error") || (jstatus == "complete")) && (loopstatus = false)
        (jstatus == "running") && println("$(j_mon): $(jstatusinfo)% complete...")
    end
    wait(j_mon)
    println("time taken (total time, wait time, run time): $(times(j_mon))")
    println("")
end


j = dmapreduce(MRHdfsFileInput([INP], findrow), maprow, collectrow, reducerow)
wait_results(j)
println(results(j))
