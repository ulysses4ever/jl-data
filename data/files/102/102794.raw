#!/Applications/Juno.app/Contents/Resources/app/julia/bin/julia
using ArgParse

np = nprocs()
println("Started $(np) processes")

s = ArgParseSettings(description = "Check id pair against the store")
@add_arg_table s begin
    # unnecessary options removed for brevity.
    "filename"
        help = "File with id pairs (two columns tab separated)"
end

parsed_args = parse_args(s)
filename = get(parsed_args, "filename", "test.txt")

if (np > 1)
    if (myid() == 1)
        # Mulitprocess and I am the parent
        @sync begin
            for i = 2:nprocs()
                @async remotecall_wait(i, processOneFile, 3085, 35649, filename)
            end
        end
    end
else
    processOneFile(3085, 35649, filename, 100) # Sample 100 lines to warm up JIT
    println("Profile run")
    @profile processOneFile(3085, 35649, filename, 0)
    Profile.print()
    #=
    bt, lidict = Profile.retrieve()
    println("Profiling done")
    for (k,v) in lidict
        println(v)
    end
    =#
end
