using FactCheck
using SimpleHttpCommon
using StreamReader
const S = SimpleHttpCommon

if !isdefined(:TEST_DIR)
    include("utils.jl")
end

facts("Test Response.jl") do
    context("Basic") do
        context("Initial") do
            r = mkres()
            @fact r.headers_sent --> false
            @fact r.writer == S.startwriter --> true
            @fact r.content_length --> S.EMPTY_CL
            S.start(r)
            @fact_throws S.start(r)
            @fact r.headers_sent --> true
            @fact r.content_length --> 0

            expected_headers = ["Content-Length",
                                "Content-Type",
                                "Date",
                                "Server"]
            for k in keys(r.headers)
                @fact k in expected_headers --> true "Key '$k' not found"
            end

            @fact r.headers["Content-Length"] --> "0"
        end

        context("Test contentlength") do
            r = mkres()
            @fact r.content_length --> -1
            r.content_length = 10
            @fact r.content_length --> 10
        end

        context("Test sendheaders") do
            context("basic") do
                r = mkres()
                r.headers = S.headers()
                @fact r.content_length --> S.EMPTY_CL
                r.content_length = 10
                @fact r.content_length --> 10
                S.sendheaders(r)
                edata = "HTTP/1.1 200 OK\r\nContent-Length: 10\r\n\r\n"
                @fact str(r.io.io.data) --> edata
                @fact r.headers_size --> sizeof(edata)
                @fact r.headers["Content-Length"] --> "10"
            end

            context("response status not accepts body") do
                r = mkres()
                r.content_length = 10
                r.status = r.protocol.status_wo_msg[1]

                fre(;key="status_not_accept_msg_body",
                    header="Content-Length",
                    status=r.protocol.status_wo_msg[1]) do
                    S.sendheaders(r)
                end
            end

            context("chunked") do
                context("manual") do
                    r = mkres()
                    r.headers = ["Transfer-Encoding" => "chunked"]
                    S.sendheaders(r)
                    @fact r.headers_sent --> true
                    @fact r.content_length --> -1

                    r = mkres()
                    r.headers = ["Transfer-Encoding" => "chunked", "Content-Length" => "10"]

                    fre(;key="invalid_header",
                        header="Content-Length") do
                        S.sendheaders(r)
                    end
                end

                context("chunk()") do
                    r = mkres()
                    chunk(r)
                    S.sendheaders(r)
                    @fact r.headers_sent --> true
                    @fact r.content_length --> -1

                    r = mkres()
                    r.headers = ["Transfer-Encoding" => "chunked", "Content-Length" => "10"]

                    fre(;key="invalid_header",
                        header="Content-Length") do
                        S.sendheaders(r)
                    end
                end
            end
        end
    end

    context("Basic Response writer") do
        context("writer functions") do
            function t(fn::Function, title)
                l = {"God is love!", "Jesus is my best Friend!!"}
                l = {(l[1],l[1]), (l[2].data,l[2])}
                for (data, data_r) in l
                    context(@sprintf "The %s for write '%s'" title data) do
                        r = mkres()
                        cl = sizeof(data)
                        fn(r, data)
                        @fact r.headers_sent --> true
                        @fact sentcl(r) --> cl
                        @fact r.content_length --> cl
                        @fact r.headers["Content-Length"] --> "$cl"
                        @fact str(r.io.io.data)[end-(cl-1):end] --> data_r
                    end
                end
            end

            t("Base.write") do r, data
                write(r, data)
            end
            t("'data >> response'") do r, data
                data >> r
            end
            t("'response << data'") do r, data
                r << data
            end
        end

        context("Simple writer") do
            context("unique data block") do
                r = mkres()
                data = "God is love!"
                write(r, data)
                @fact r.headers_sent --> true
                cl = 12
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact r.headers["Content-Length"] --> "$cl"
                @fact str(r.io.io.data)[end-(cl-1):end] --> data

                extrapolates = "Jesus Christ is God in human form 1!"

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)) do
                    write(r, extrapolates)
                end
            end

            context("multiples data block") do
                data = ["God is love!", "Jesus is my King!"]
                size = [sizeof(_) for _ in data]
                cl = sum(size)
                r = mkres()
                r.content_length = cl
                write(r, data[1])
                @fact r.headers_sent --> true
                @fact sentcl(r) --> size[1]
                @fact r.content_length --> cl
                @fact r.headers["Content-Length"] --> "$cl"
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]
                write(r, data[2])
                @fact str(r.io.io.data)[end-(cl-1):end] --> join(data, "")
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact r.headers["Content-Length"] --> "$cl"

                extrapolates = "Jesus Christ is God in human form 2!"
                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)) do
                    write(r, extrapolates)
                end
            end

            context("multiples data block with partial extrapolation") do
                data = ["God is love!", "Jesus is my King!"]
                size = [sizeof(_) for _ in data]
                cl = sum(size) + 3
                r = mkres()
                r.content_length = cl

                write(r, data[1])
                @fact r.headers_sent --> true
                @fact sentcl(r) --> size[1]
                @fact r.content_length --> cl
                @fact r.headers["Content-Length"] --> "$cl"
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]

                write(r, data[2])
                @fact str(r.io.io.data)[end-(cl-4):end] --> join(data, "")
                @fact sentcl(r) --> (cl-3)
                @fact r.content_length --> cl
                @fact r.headers["Content-Length"] --> "$cl"

                extrapolates = "Jesus!!"

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)-3) do
                    write(r, extrapolates)
                end

                @fact str(r.io.io.data)[end-(cl-1):end] --> string(join(data, ""), "\0\0\0")
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact r.headers["Content-Length"] --> "$cl"
            end
        end

        context("Buffered writer") do
            context("unique block") do
                r = mkres()
                @fact r.writer --> exactly(S.startwriter)
                buffered(r)
                @fact r.writer --> exactly(S.startwriter)

                data = "God is love!"
                cl = sizeof(data)

                r << data
                @fact r.writer --> exactly(S.bufferedwriter)
                @fact r.headers_sent --> false # is in buffer
                @fact sentcl(r) --> 0
                @fact r.content_length --> S.EMPTY_CL

                flush(r)

                @fact r.writer --> exactly(S.bufferedwriter)
                @fact r.headers_sent --> true
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact str(r.io.io.data)[end-(cl-1):end] --> data

                extrapolates = "Jesus Christ is God in human form 3!"

                # write in buffer
                r << extrapolates

                @fact str(r.buffer.data) --> extrapolates

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)) do
                    flush(r)
                end
            end
            context("unique block with set contentlength") do
                r = mkres()
                buffered(r)

                data = "God is love!"
                cl = sizeof(data)
                r.content_length = cl

                r << data

                @fact r.headers_sent --> false # is in buffer
                @fact sentcl(r) --> 0
                @fact r.content_length --> cl

                flush(r)

                @fact r.headers_sent --> true
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact str(r.io.io.data)[end-(cl-1):end] --> data

                extrapolates = "Jesus Christ is God in human form 4!"

                # write in buffer
                r << extrapolates

                @fact str(r.buffer.data) --> extrapolates

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)) do
                    flush(r)
                end
            end
            context("multiples blocks") do
                r = mkres()
                buffered(r)

                data = ["God is", " love!"]
                size = [sizeof(_) for _ in data]
                cl = sum(size)

                r << data[1]

                @fact r.headers_sent --> false # is in buffer
                @fact sentcl(r) --> 0
                @fact r.content_length --> S.EMPTY_CL
                @fact str(r.buffer.data) --> data[1]
                @fact sizeof(r.io.io.data) --> 0

                r << data[2]

                @fact r.headers_sent --> false # is in buffer
                @fact sentcl(r) --> 0
                @fact r.content_length --> S.EMPTY_CL
                @fact str(r.buffer.data) --> join(data, "")
                @fact sizeof(r.io.io.data) --> 0

                flush(r)

                @fact r.headers_sent --> true
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact str(r.io.io.data)[end-(cl-1):end] --> join(data, "")

                extrapolates = "Jesus Christ is God in human form 5!"

                # write in buffer
                r << extrapolates

                @fact str(r.buffer.data) --> extrapolates

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)) do
                    flush(r)
                end
            end
            context("multiples blocks with set contentlength") do
                r = mkres()
                buffered(r)

                data = ["God is", " love!"]
                size = [sizeof(_) for _ in data]
                cl = sum(size)

                r.content_length = cl

                write(r, data[1])

                @fact r.headers_sent --> false # is in buffer
                @fact sentcl(r) --> 0
                @fact r.content_length --> cl
                @fact str(r.buffer.data) --> data[1]
                @fact sizeof(r.io.io.data) --> 0

                flush(r)

                @fact r.headers_sent --> true
                @fact sentcl(r) --> size[1]
                @fact r.content_length --> cl
                @fact sizeof(r.buffer.data) --> 0
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]
                @fact sizeof(r.io.io.data) --> (r.headers_size + size[1])

                write(r, data[2])

                @fact r.headers_sent --> true
                @fact sentcl(r) --> size[1]
                @fact r.content_length --> cl
                @fact str(r.buffer.data) --> data[2]
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]
                @fact (sizeof(r.io.io.data)-r.headers_size) --> size[1]

                flush(r)

                @fact r.headers_sent --> true
                @fact sentcl(r) --> cl
                @fact r.content_length --> cl
                @fact str(r.buffer.data) --> ""
                @fact str(r.io.io.data)[end-(cl-1):end] --> join(data, "")
                @fact (sizeof(r.io.io.data)-r.headers_size) --> cl

                extrapolates = "Jesus Christ is God in human form 6!"

                # write in buffer
                write(r, extrapolates)

                @fact str(r.buffer.data) --> extrapolates

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)) do
                    flush(r)
                end
            end
        end

        context("chunked writer") do
            r = mkres()
            r.headers = S.headers()
            chunk(r)

            blocks = String["For God so loved the world, that he gave his ",
                    "only begotten Son, that whosoever ",
                    "believeth in him should not perish, but ",
                    "have everlasting life.",
                    "(John 3:16)"]

            for b in blocks
                b >> r
            end

            S.done(r)

            io = r.io
            seekstart(io.io)

            edata = "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n"
            @fact UTF8String(readbytes(io.io, r.headers_size)) --> edata
            @fact String[UTF8String(_) for _ in collect(S.Chunk.iterator(io))] --> blocks
        end

        context("chunked writer with buffer") do
            r = mkres()
            r.headers = S.headers()

            chunk(r)
            buffered(r)

            blocks = String["For God so loved the world, that he gave his ",
                    "only begotten Son, that whosoever ",
                    "believeth in him should not perish, but ",
                    "have everlasting life.",
                    "(John 3:16)"]

            writeblock = (i, b) -> begin
                s = sizeof(b)
                total_parts, parts_size, last_part_size = calculate(s, 7)
                prev_pn = 1
                start_ = 0

                for pn in 1:(total_parts-1)
                    pd = b[(start_+1):start_ + parts_size]
                    @fact sizeof(pd) --> parts_size
                    r << pd
                    prev_pn = pn
                    start_ += parts_size
                end

                pd = b[(start_+1):end]
                @fact sizeof(pd) --> last_part_size
                r << pd

                flush(r)
            end

            for (i, b) in enumerate(blocks)
                writeblock(i, b)
            end

            S.done(r)

            io = r.io
            seekstart(io.io)

            edata = "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n"
            @fact UTF8String(readbytes(io.io, r.headers_size)) --> edata
            @fact String[UTF8String(_) for _ in collect(S.Chunk.iterator(io))] --> blocks
        end

        context("chunked on done") do
            r = mkres()
            r.headers = S.headers()
            chunk(r)

            blocks = String["For God so loved the world, that he gave his ",
                    "only begotten Son, that whosoever ",
                    "believeth in him should not perish, but ",
                    "have everlasting life.",
                    "(John 3:16)"]
                    
            r.data = blocks
            S.done(r)

            io = r.io
            seekstart(io.io)

            edata = "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n"
            @fact UTF8String(readbytes(io.io, r.headers_size)) --> edata
            @fact String[UTF8String(_) for _ in collect(S.Chunk.iterator(io))] --> blocks
        end
    end
end
