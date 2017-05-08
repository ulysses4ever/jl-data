#!/usr/local/julia-cb9bcae93a/bin/julia
filename = "nyc311calls.csv"
np = nprocs()
println("Started $(np) processes")
if (np > 1)
    if (myid() == 1)
        # Mulitprocess and I am the parent
        @sync begin
            for i = 2:nprocs()
                @async remotecall_wait(i, processOneFile, filename)
            end
        end
    end
else
    processOneFile(filename)
end
