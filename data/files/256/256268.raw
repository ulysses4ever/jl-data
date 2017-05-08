using FactCheck
using SimpleHttpIO

include(joinpath(dirname(@__FILE__), "..", "src", "Chunk.jl"))

using Chunk
const C = Chunk

facts("Test chunk.jl") do
    context("types") do
        cio = IOChunked(IOBuffer())
        @fact isa(cio, AbstractIOSocket) --> true
    end

    data = String["For God so loved the world, that he gave his ",
            "only begotten Son, that whosoever ",
            "believeth in him should not perish, but ",
            "have everlasting life.",
            "(John 3:16)"]

    context("writer") do
        io = IOChunked(IOBuffer())

        for d in data
            C.write(io, d)
        end

        C.done(io)

        seekstart(io.io)

        @fact UTF8String(io.io.data) --> string("2d\r\nFor God so loved the world, that he gave his ",
            "\r\n22\r\nonly begotten Son, that whosoever \r\n28\r\nbelieveth in him should not ",
            "perish, but \r\n16\r\nhave everlasting life.\r\nb\r\n(John 3:16)\r\n0\r\n\r\n")
    end

    context("reader") do
        io = IOChunked(IOBuffer())

        for d in data
            C.write(io, d)
        end

        C.done(io)
        r = C.iterator(io)

        seekstart(io.io)
        d = String[UTF8String(d) for d in collect(r)]
        @fact d --> data
    end
end
