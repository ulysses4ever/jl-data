module Reinterprets

import Base: unbox, box
export reinterprets

@inline reinterprets(x,y) = reinterpret(x,y)

for (utype,itype,ftype) in ((:UInt16, :Int16, :Float16), (:UInt32, :Int32, :Float32), (:UInt64, :Int64, :Float64))
    @eval begin
        reinterprets(::Type{Signed}, x::($utype))   = box($itype,unbox($utype,x))
        reinterprets(::Type{Signed}, x::($itype))   = x
        reinterprets(::Type{Signed}, x::($ftype))   = box($itype,unbox($ftype,x))
        reinterprets(::Type{Unsigned}, x::($utype)) = x
        reinterprets(::Type{Unsigned}, x::($itype)) = box($utype,unbox($itype,x))
        reinterprets(::Type{Unsigned}, x::($ftype)) = box($utype,unbox($ftype,x))
        reinterprets(::Type{AbstractFloat}, x::($utype)) = box($ftype,unbox($utype,x))
        reinterprets(::Type{AbstractFloat}, x::($itype)) = box($ftype,unbox($itype,x))
        reinterprets(::Type{AbstractFloat}, x::($ftype)) = x
    end
end
for (utype,itype) in ((:UInt8, :Int8), (:UInt128, :Int128))
    @eval begin
        reinterprets(::Type{Signed}, x::($utype))   = box($itype,unbox($utype,x))
        reinterprets(::Type{Signed}, x::($itype))   = x
        reinterprets(::Type{Unsigned}, x::($utype)) = x
        reinterprets(::Type{Unsigned}, x::($itype)) = box($utype,unbox($itype,x))
    end
end

end # module
