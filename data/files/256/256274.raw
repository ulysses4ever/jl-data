using StreamReader

if !isdefined(:TEST_DIR)
    include("utils.jl")
end

facts("Test Request.jl") do
    context("parse headers") do
        return
        context("parse headers from IO") do
            io = IOBuffer()
            wclf(io)
            seekstart(io)

            frqe(;info="Empty first line.") do
                S.read_http_first_line(io)
            end

            io = IOBuffer()
            line = "first line"
            ws = wclf(io, line)
            seekstart(io)
            @fact S.read_http_first_line(io) --> (ws, line)

            io = IOBuffer()
            ws = wclf(io, "H1: H1 value")
            ws += wclf(io, "HM: HM value 1")
            ws += wclf(io, "HM: HM value 2")
            ws += wclf(io)

            seekstart(io)
            hs = sizeof(io.data)

            eh = ["H1"=>"H1 value","HM"=>String["HM value 1","HM value 2"]]

            s, lnum, h = S.read_http_headers(io)
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
                    pr = nothing
                else
                    m, r, pr = parts
                    pr = split(pr, "/")
                end

                method, resource, protocol = S.parse_info(line)
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
                        pr = nothing
                    else
                        m, rs, pr = parts
                        pr = split(pr, "/")
                    end

                    r = S.Request(io)
                    S.read_info(r, S.PROTOCOLS)

                    @fact r.method --> m
                    @fact r.resource --> rs

                    if pr != nothing
                        @fact r.protocol.name --> pr[1]
                        @fact r.protocol.version --> pr[2]
                    else
                        @fact r.protocol --> pr
                    end
                end
            end
        end
    end

    context("parse multipart/form-data") do
        sample_path = joinpath(TEST_DIR, "data", "multipart", "rawdata", "sample.txt")
        sio = IOSocket(open(sample_path, "r"))
        s, info = S.read_info(sio, S.PROTOCOLS)
        size, linenum, headers = S.read_headers(sio)
        content_size = parseint(headers["Content-Length"])
        boundary = S.multipart_boundary(headers["Content-Type"])
        s, d, files = S.parse_multipart_formdata(sio, boundary)

        for f in files
            fpath = joinpath(TEST_DIR, "data", "multipart", "files", f.name)
            open(fpath, "r") do fio
                @fact f.io.data --> readbytes(fio, filesize(fpath)) "File Data mismatch '$(f.name)' -> '$(fpath)'"
            end
        end
    end
end
