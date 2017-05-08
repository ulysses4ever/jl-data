#!/Applications/Juno.app/Contents/Resources/app/julia/bin/julia

using Requests
import JSON

function checkSegment (userid, segmentid, id1, id2, fp)

    # this is edited out
    segmentURL = "http://<SUB-WITH-YOUR-HOST>?id1=$(id1)&id2=$(id2)"
    
    segmentURL = replace(segmentURL,"@","%40")  # Requests.jl is stricter about badly formatted URL.
    write(fp, @sprintf("Fetching %s\n", segmentURL))
    resp = get(segmentURL)
    if resp.status != 200
        write(fp, @sprintf("ERROR: Unable to get data id pair %s, %s\n", id1, id2))
        sleep(0.1)
        return
    end
    foundMatch = false
    if resp.data != "{ 0 }"  # Valid response, but Invalid JSON. Legacy issues.
        j = JSON.parse(resp.data)
        sgmts = get(j, "sgmts", {})
        if length(sgmts) > 0
            for (s, t) in sgmts
                if s == segmentid
                    foundMatch = true
                    break
                end
            end
            write(fp, @sprintf("Segment %s for id pair %s, %s\n", foundMatch, id1, id2))
            # sleep(0.001)
        end
    end
end

function processOneLine(userid, segmentid, idPair, fp)
    id1, id2 = split(idPair)
    return checkSegment(userid, segmentid, id1, id2, fp)
end

function processOneFile(userid, segmentid, filename) 

    np = nprocs()
    jump = np - 1
    jump = jump == 0 ? 1 : jump

    selfid = myid()

    fp = open("tmp.$(selfid).out.log", "w")
    
    # in a multi-process setup, this function should not be called for parent (id=1)
    assert(jump == 1 || selfid != 1)
    f = open(filename);
    offset = np == 1 ? selfid : selfid - 1
    lnum = 0
    for l in eachline(f)
        lnum += 1
        if lnum == offset
            write(fp, @sprintf("Process %d is processing line %d\n", selfid, lnum))
            processOneLine(userid, segmentid, l, fp)
            offset += jump
        end
    end
end
