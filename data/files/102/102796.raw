#!/usr/local/julia-cb9bcae93a/bin/julia
function processOneFile(filename)

    np = nprocs()
    jump = np - 1
    jump = jump == 0 ? 1 : jump

    selfid = myid()
    
    # in a multi-process setup, this function should not be called for parent (id=1)
    assert(jump == 1 || selfid != 1)
    f = open(filename);
    offset = np == 1 ? selfid : selfid - 1
    lnum = 0
    for l in eachline(f)
        lnum += 1
        if lnum == offset
            println("Process $(selfid) is processing line $(lnum)")
            offset += jump
        end
    end
end
