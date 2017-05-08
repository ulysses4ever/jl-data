include("../src/BlockCiphers.jl")

importall BlockCiphers

print("benching AES ")

plain = zeros(Uint8, 16)
k1 = AES(zeros(Uint8, int32(128/8)))

buff = zeros(Uint8, 16 * 1000000)

function gigs(len :: Int64)
    for i=0:(len - 1)
        s = slice(buff, ((i*16)+1) : ((i+1) * 16))
        encrypt!(k1, s, s)
    end
    show(buff[1:16])
    println()
end

gigs(1000)

@time gigs(100000)
@time gigs(1000000)
@time gigs(1000000)

println()