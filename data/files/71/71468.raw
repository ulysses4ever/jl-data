using Base.Test
include("UTF16.jl")
using UTF16

u8 = "𝕥𝟶f𠂊"
u16 = utf16(u8)
@test length(u16.data) == 7
@test length(u16) == 4
@test utf8(u16) == u8
@test collect(u8) == collect(u16)
