"""Benchmark an problem against an algorithm
  `benchmark` is a generic function with no methods designed to
  be extended by other users of `DynamicAnalysis` as in:

  `benchmark(::Algorithm,::Problem)`"""
benchmark() = error()

"""Run each problem in a Vector of problems on each algorithm.
  Runs `length(problems) * length(algos)` analyses

  Params
  `newseed` - Resets randomseed before analysis of each problem-algorithm pair
  `prefix`  -
  `savedb` - Save results to an SQLiteDB
  `savefile` - Save results to a file
  `profile` - include profiling data with results
  `dbpath` - Location to save SQLiteDB file defaults to `homedir()/runs.sqlite`
  `exceptions` - When `true`, catches exceptions and continues to next analysis
"""
function record{A<:Algorithm, B<:Problem}(algos::Vector{A},problems::Vector{B};
                                            newseed = false,
                                            prefix::AbstractString = "",
                                            runname::AbstractString = "",
                                            # savedb::Bool = false,
                                            savefile::Bool = false,
                                            profile::Bool = false,
                                            #dbpath = default_dbpath,
                                            exceptions = true)

  # Database saving
  # local db
  #if savedb
  #  db = SQLiteDB(dbpath)
  #  !tableexists(db, "runs") && create_runs_table!(db)
  #end

  # Serialise data
  local thisrundir
  if savefile
    thisrundir = joinpath(prefix, "data", "$(runname)-$(string(Dates.now()))")
    mkdir(thisrundir)
  end

  results = Dict{Tuple{Algorithm, Problem}, Result}()
  runiter = 1
  nruns = length(problems) * length(algos)
  nfailures = 0

  for j = 1:length(problems), i = 1:length(algos)
    println("\nRunning $runiter of $nruns, $nfailures so far" )
    print("$(algos[i]) \n")
    print("$(problems[j]) \n")
    newseed && srand(345678) # Set Random Seed

    if exceptions
      try
        res = benchmark(algos[i], problems[j])
        results[(algos[i],problems[j])] = res
        #savedb && (addrundb(db,runname, algos[i],problems[j],"DONE",res))
        savefile && (dumpbenchmark(thisrundir,results))
      catch er
        nfailures += 1
        println("ERROR on problem $j algorithm $i:")
        println(er)
        @show length(problems)
        savefile && (results[(algos[i],problems[j])] = er)
        #savedb && (addrundb(db,runname, algos[i],problems[j],"FAIL",er))
      end
    else
      res = benchmark(algos[i], problems[j])
      results[(algos[i],problems[j])] = res
      #savedb && (addrundb(db,runname, algos[i],problems[j],"DONE",res))
      savefile && (dumpbenchmark(thisrundir,results))
    end
    runiter += 1
  end
  println("$nfailures failures")
  savefile && (dumpbenchmark(thisrundir,results,"all"))
  results
end

@doc "Run an algorithm on a computational problem and record results to db/file" ->
record(a::Algorithm, p::Problem; args...) = analyse([a],[p]; args...)

# Dump the benchmark data into a file
function dumpbenchmark(thisrundir,x,suffix::AbstractString = "")
  fname = "$(string(Dates.now()))-$suffix"
  path = joinpath(thisrundir, fname)
  f = open(path,"w")
  serialize(f,x)
  close(f)
end
