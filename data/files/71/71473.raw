module UTF16

export UTF16String, utf16

import Base.convert, Base.endof, Base.next

type UTF16String <: String
    data::Array{Uint16,1}
end

endof(s::UTF16String) = thisind(s,length(s.data))

utf16_is_lead(c::Uint16) = (c & 0xfc00) == 0xd800
utf16_is_trail(c::Uint16) = (c & 0xfc00) == 0xdc00
utf16_is_surrogate(c::Uint16) = (c & 0xf800) == 0xd800
utf16_get_supplementary(lead::Uint16, trail::Uint16) = char((lead-0xd7f7)<<10 + trail)

function next(s::UTF16String, i::Int)
    if !utf16_is_surrogate(s.data[i])
        return char(s.data[i]), i+1
    elseif length(s.data) > i && utf16_is_lead(s.data[i]) && utf16_is_trail(s.data[i+1])
        return utf16_get_supplementary(s.data[i], s.data[i+1]), i+2
    end
    error("invalid UTF-16 character index")
end

# TODO: optmize this
function encode16(s::String)
    buf = Uint16[]
    for c in s
        if c < 0x10000
            push!(buf, uint16(c))
        else
            push!(buf, uint16(0xd7c0 + (c>>10) & 0x3ff))
            push!(buf, uint16(0xdc00 + c & 0x3ff))
        end
    end
    UTF16String(buf)
end

utf16(x) = convert(UTF16String, x)
convert(::Type{UTF16String}, s::UTF16String) = s
convert(::Type{UTF16String}, s::String) = encode16(s)
convert(::Type{UTF8String}, s::UTF16String) =
    sprint(length(s.data), io->for c in s; write(io,c::Char); end)

function test_utf16()
    u8 = "𝕥𝟶f𠂊"
    u16 = utf16(u8)
    @assert length(u16.data) == 7
    @assert length(u16) == 4
    @assert utf8(u16) == u8
end

end # module
