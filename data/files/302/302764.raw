#----------------------------------------------------------------------
# Test name: PR12364_iobufferread
#
# Issue/PR: https://github.com/JuliaLang/julia/pull/12364
#
# Description:
# Measures time to read from an IOBuffer one line at a time.
# Noticed while profiling GZip.jl:
#   https://github.com/JuliaLang/GZip.jl/pull/32
#
# Parameters:
# n         log10 size of the buffer
#----------------------------------------------------------------------

using Benchmarks

function PR12364_iobufferread(n)
    io = IOBuffer(randstring(10^n))
    f(io) = (seek(io, 0); x = 0; while !eof(io); x += read(io, UInt8); end)
    r = @benchmark f(io)
end

r = PR12364_iobufferread(8)
println(r)