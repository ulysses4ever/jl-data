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
            r = mk_res()
            @fact headers_sent(r) --> false
            @fact r.writer == S.start_writer --> true
            @fact r.content_length --> S.EMPTY_CL
            S.start(r)
            @fact_throws S.start(r)
            @fact headers_sent(r) --> true
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

        context("Test content_length") do
            r = mk_res()
            @fact content_length(r) --> -1
            @fact content_length(r, 10) --> 10
            @fact content_length(r) --> 10
        end

        context("Test send_headers") do
            context("basic") do
                r = mk_res()
                r.headers = S.headers()
                @fact content_length(r) --> S.EMPTY_CL
                @fact content_length(r, 10) --> 10
                @fact content_length(r) --> 10
                S.send_headers(r)
                edata = "HTTP/1.1 200 OK\r\nContent-Length: 10\r\n\r\n"
                @fact str(r.io.io.data) --> edata
                @fact S.headers_size(r) --> sizeof(edata)
                @fact r.headers["Content-Length"] --> "10"
            end

            context("response status not accepts body") do
                r = mk_res()
                content_length(r, 10)
                r.status = r.protocol.status_wo_msg[1]

                fre(;key="status_not_accept_msg_body",
                    header="Content-Length",
                    status=r.protocol.status_wo_msg[1]) do
                    S.send_headers(r)
                end
            end

            context("chunked") do
                r = mk_res()
                r.headers = ["Transfer-Encoding" => "chunked"]
                S.send_headers(r)
                @fact headers_sent(r) --> true
                @fact content_length(r) --> -1

                r = mk_res()
                r.headers = ["Transfer-Encoding" => "chunked", "Content-Length" => "10"]

                fre(;key="invalid_header",
                    header="Content-Length") do
                    S.send_headers(r)
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
                        r = mk_res()
                        cl = sizeof(data)
                        fn(r, data)
                        @fact headers_sent(r) --> true
                        @fact sent_content_length(r) --> cl
                        @fact content_length(r) --> cl
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
                r = mk_res()
                data = "God is love!"
                write(r, data)
                @fact headers_sent(r) --> true
                cl = 12
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
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
                r = mk_res()
                content_length(r, cl)
                write(r, data[1])
                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> size[1]
                @fact content_length(r) --> cl
                @fact r.headers["Content-Length"] --> "$cl"
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]
                write(r, data[2])
                @fact str(r.io.io.data)[end-(cl-1):end] --> join(data, "")
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
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
                r = mk_res()
                content_length(r, cl)

                write(r, data[1])
                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> size[1]
                @fact content_length(r) --> cl
                @fact r.headers["Content-Length"] --> "$cl"
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]

                write(r, data[2])
                @fact str(r.io.io.data)[end-(cl-4):end] --> join(data, "")
                @fact sent_content_length(r) --> (cl-3)
                @fact content_length(r) --> cl
                @fact r.headers["Content-Length"] --> "$cl"

                extrapolates = "Jesus!!"

                fre(;key="exceeded_content_data",
                    content_length=cl,
                    data_size=sizeof(extrapolates),
                    exceeded=sizeof(extrapolates)-3) do
                    write(r, extrapolates)
                end

                @fact str(r.io.io.data)[end-(cl-1):end] --> string(join(data, ""), "\0\0\0")
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
                @fact r.headers["Content-Length"] --> "$cl"
            end
        end

        context("Buffered writer") do
            context("unique block") do
                r = mk_res()
                @fact r.writer --> exactly(S.start_writer)
                buffered(r)
                @fact r.writer --> exactly(S.start_writer)

                data = "God is love!"
                cl = sizeof(data)

                write(r, data)
                @fact r.writer --> exactly(S.buffered_writer)
                @fact headers_sent(r) --> false # is in buffer
                @fact sent_content_length(r) --> 0
                @fact content_length(r) --> S.EMPTY_CL

                flush(r)

                @fact r.writer --> exactly(S.buffered_writer)
                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
                @fact str(r.io.io.data)[end-(cl-1):end] --> data

                extrapolates = "Jesus Christ is God in human form 3!"

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
            context("unique block with set content_length") do
                r = mk_res()
                buffered(r)

                data = "God is love!"
                cl = sizeof(data)
                content_length(r, cl)

                write(r, data)

                @fact headers_sent(r) --> false # is in buffer
                @fact sent_content_length(r) --> 0
                @fact content_length(r) --> cl

                flush(r)

                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
                @fact str(r.io.io.data)[end-(cl-1):end] --> data

                extrapolates = "Jesus Christ is God in human form 4!"

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
            context("multiples blocks") do
                r = mk_res()
                buffered(r)

                data = ["God is", " love!"]
                size = [sizeof(_) for _ in data]
                cl = sum(size)

                write(r, data[1])

                @fact headers_sent(r) --> false # is in buffer
                @fact sent_content_length(r) --> 0
                @fact content_length(r) --> S.EMPTY_CL
                @fact str(r.buffer.data) --> data[1]
                @fact sizeof(r.io.io.data) --> 0

                write(r, data[2])

                @fact headers_sent(r) --> false # is in buffer
                @fact sent_content_length(r) --> 0
                @fact content_length(r) --> S.EMPTY_CL
                @fact str(r.buffer.data) --> join(data, "")
                @fact sizeof(r.io.io.data) --> 0

                flush(r)

                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
                @fact str(r.io.io.data)[end-(cl-1):end] --> join(data, "")

                extrapolates = "Jesus Christ is God in human form 5!"

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
            context("multiples blocks with set content_length") do
                r = mk_res()
                buffered(r)

                data = ["God is", " love!"]
                size = [sizeof(_) for _ in data]
                cl = sum(size)

                content_length(r, cl)

                write(r, data[1])

                @fact headers_sent(r) --> false # is in buffer
                @fact sent_content_length(r) --> 0
                @fact content_length(r) --> cl
                @fact str(r.buffer.data) --> data[1]
                @fact sizeof(r.io.io.data) --> 0

                flush(r)

                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> size[1]
                @fact content_length(r) --> cl
                @fact sizeof(r.buffer.data) --> 0
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]
                @fact sizeof(r.io.io.data) --> (S.headers_size(r) + size[1])

                write(r, data[2])

                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> size[1]
                @fact content_length(r) --> cl
                @fact str(r.buffer.data) --> data[2]
                @fact str(r.io.io.data)[end-(size[1]-1):end] --> data[1]
                @fact (sizeof(r.io.io.data)-S.headers_size(r)) --> size[1]

                flush(r)

                @fact headers_sent(r) --> true
                @fact sent_content_length(r) --> cl
                @fact content_length(r) --> cl
                @fact str(r.buffer.data) --> ""
                @fact str(r.io.io.data)[end-(cl-1):end] --> join(data, "")
                @fact (sizeof(r.io.io.data)-S.headers_size(r)) --> cl

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
            r = mk_res()
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
            @fact UTF8String(readbytes(io.io, S.headers_size(r))) --> edata
            @fact String[UTF8String(_) for _ in collect(S.Chunk.iterator(io))] --> blocks
        end

        context("chunked writer with buffer") do
            r = mk_res()
            r.headers = S.headers()

            chunk(r)
            buffered(r)

            blocks = String["For God so loved the world, that he gave his ",
                    "only begotten Son, that whosoever ",
                    "believeth in him should not perish, but ",
                    "have everlasting life.",
                    "(John 3:16)"]

            write_block = (i, b) -> begin
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
                write_block(i, b)
            end

            S.done(r)

            io = r.io
            seekstart(io.io)

            edata = "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n"
            @fact UTF8String(readbytes(io.io, S.headers_size(r))) --> edata
            @fact String[UTF8String(_) for _ in collect(S.Chunk.iterator(io))] --> blocks
        end
    end
end
