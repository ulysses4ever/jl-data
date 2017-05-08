using Compat
@compat readstring
# Markdown Report Generation #
#----------------------------#

function printreport(io::IO, results)
    # print report preface + job properties #
    #---------------------------------------#
    println(io, """
    # Benchmark Report
    The percentages accompanying time and memory values in the below table are noise tolerances. The "true"
    time/memory value for a given benchmark is expected to fall within this percentage of the reported value.
    """)

    # print result table #
    #--------------------#
    print(io, """
    | ID | time | GC time | memory | allocations |
    |----|------|---------|--------|-------------|
    """)

    entries = BenchmarkTools.leaves(median(results))

    try
        entries = entries[sortperm(map(x -> string(first(x)), entries))]
    end

    for (ids, t) in entries
        println(io, resultrow(ids, t))
    end

    println(io)

    # print list of executed benchmarks #
    #-----------------------------------#
    println(io, """
    ## Benchmark Group List
    Here's a list of all the benchmark groups executed by this job:
    """)

    for id in unique(map(pair -> pair[1][1:end-1], entries))
        println(io, "- `", idrepr(id), "`")
    end

    println(io)

    # print build version info #
    #--------------------------#
    print(io, """
    ## Version Info
    #### Module Commit ID
    ```
    $(chomp(readstring(`git rev-parse HEAD`)))
    ```
    #### Julia Version
    ```
    $(first(split(chomp(readstring(`julia -e 'versioninfo(true)'`)), "Environment")))
    ```
    """)
end

idrepr(id) = (str = repr(id); str[searchindex(str, '['):end])

function resultrow(ids, t::BenchmarkTools.TrialEstimate)
    t_tol = BenchmarkTools.prettypercent(BenchmarkTools.params(t).time_tolerance)
    m_tol = BenchmarkTools.prettypercent(BenchmarkTools.params(t).memory_tolerance)
    timestr = string(BenchmarkTools.prettytime(BenchmarkTools.time(t)), " (", t_tol, ")")
    memstr = string(BenchmarkTools.prettymemory(BenchmarkTools.memory(t)), " (", m_tol, ")")
    gcstr = BenchmarkTools.prettytime(BenchmarkTools.gctime(t))
    allocstr = string(BenchmarkTools.allocs(t))
    return "| `$(idrepr(ids))` | $(timestr) | $(gcstr) | $(memstr) | $(allocstr) |"
end
