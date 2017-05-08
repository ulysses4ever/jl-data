using SimpleHttpIO
using StreamReader

if !isdefined(:TEST_DIR)
    include("utils.jl")
end

facts("Test Request.jl") do
    context("parse headers") do
        
        context("parse headers from IO") do
            io = IOBuffer()
            sio = IOSocket(io)
            wclf(io)
            seekstart(io)

            frqe(;message="Empty first line.") do
                S.readfirstline(sio)
            end

            io = IOBuffer()
            sio = IOSocket(io)

            line = "first line"
            ws = wclf(io, line)
            seekstart(io)
            @fact S.readfirstline(sio) --> (ws, line)

            io = IOBuffer()
            sio = IOSocket(io)

            ws = wclf(io, "H1: H1 value")
            ws += wclf(io, "HM: HM value 1")
            ws += wclf(io, "HM: HM value 2")
            ws += wclf(io)

            seekstart(io)
            hs = sizeof(io.data)

            eh = ["H1"=>"H1 value","HM"=>String["HM value 1","HM value 2"]]

            s, lnum, h = S.readheaders(sio)
            @fact ws --> hs
            @fact s --> hs
            @fact lnum --> 4

            for (k, v) in h
                @fact h[k] --> eh[k] ("Mismatch " * k * " Header")
            end
        end

        context("parse info") do
            for line in String["GET /index.html", "GET /index.html HTTP/1.1",
                "GET /directory%20name/file.txt HTTP/1.1"]
                parts = split(line, " ")

                if length(parts) == 2
                    m, r = parts
                    pr = default_protocol = astuple(S.FAKE_PROTOCOL)
                else
                    m, r, pr = parts
                    pr = split(pr, "/")
                    default_protocol = N
                end

                method, resource, protocol = S.parseinfo(line, default_protocol)
                @fact method --> m
                @fact r --> resource
                @fact protocol --> pr
            end
        end

        context("read request info") do
            for line in String["GET /index.html", "GET /index.html HTTP/1.1",
                "GET /directory%20name/file.txt HTTP/1.1"]
                context("read request info at " * repr(line)) do
                    io = IOBuffer()
                    wclf(io, line)
                    seekstart(io)

                    parts = split(line, " ")

                    if length(parts) == 2
                        m, rs = parts
                        pr = default_protocol = astuple(S.FAKE_PROTOCOL)
                        protocol!(S.FAKE_PROTOCOL)
                    else
                        m, rs, pr = parts
                        pr = split(pr, "/")
                        default_protocol = N
                    end

                    r = S.Request(IOSocket(io))
                    S.readinfo(r, S.PROTOCOLS, default_protocol)

                    @fact r.method --> m
                    @fact r.resource --> rs

                    if pr != N
                        @fact r.protocol.name --> pr[1]
                        @fact r.protocol.version --> pr[2]
                    else
                        @fact r.protocol --> pr
                    end
                end
            end
        end

        context("post request") do
            types = ["application/x-www-form-urlencoded" => ("postvar=pvalue&postvar2=pvalue2",
                    ["postvar2"=>{"pvalue2"},"postvar"=>{"pvalue"}]),
                "application/json" => ("{\"postvar\":\"pvalue\",\"postvar2\":\"pvalue2\"}",
                    ["postvar2"=>"pvalue2","postvar"=>"pvalue"])]

            for (tk, (tdata, tdatae)) in types
                context("test $tk content-type") do
                    req_io = IOBuffer()

                    write(req_io, "POST /page?getvar=gvalue HTTP/1.1\r\n" *
                        "Host: 0.0.0.0:7000\r\n" *
                        "Content-Type: $tk\r\n" *
                        "Content-Length: $(sizeof(tdata))\r\n" *
                        "\r\n" *
                        tdata)

                    seekstart(req_io)

                    req = Request(IOSocket(req_io))
                    init(req, S.PROTOCOLS)
                    data_parsed = parsedata(req)

                    @fact data_parsed --> true
                    @fact req.protocol --> HTTP_1_1
                    @fact req.content_length --> sizeof(tdata)
                    @fact req.content_type --> tk
                    @fact req.get --> ["getvar"=>{"gvalue"}]
                    @fact req.post --> tdatae
                end
            end
        end
    end

    context("parse multipart/form-data") do
        sample_path = joinpath(TEST_DIR, "data", "multipart", "rawdata", "sample.txt")
        sio = IOSocket(open(sample_path, "r"))
        s, info = S.readinfo(sio, S.PROTOCOLS)
        size, linenum, headers = S.readheaders(sio)
        content_size = parseint(headers["Content-Length"])
        boundary = S.multipartboundary(headers["Content-Type"])
        s, d, files = S.parsempfd(sio, boundary)

        for f in files
            fpath = joinpath(TEST_DIR, "data", "multipart", "files", f.name)
            open(fpath, "r") do fio
                @fact f.io.data --> readbytes(fio, filesize(fpath)) "File Data mismatch '$(f.name)' -> '$(fpath)'"
            end
        end
    end

end
