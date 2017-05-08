include("./ipp.jl")

### IPP tests - testing the interface code to IPP routines

## AddC floating point data
for elty in (Float32, Float64, Complex64, Complex128)

    X     = ones (elty, 4)
    Y     = ones (elty, 4)
    Z     = zeros(elty, 4)
    val   = convert(elty, -1)  

    @assert all(IPP.Signals.AddC (val, Y     ) .== Z)  # Z = Y + val
    @assert all(IPP.Signals.AddC!(val, Y     ) .== Z)  # Y = Y + val

end

## AddC integer data
for elty in (Uint8, Int16, Uint16, Int32)

    X     = zeros(elty, 4)
    Y     = zeros(elty, 4)
    Z     = ones (elty, 4)
    val   = convert(elty,  1)  
    scale = convert(Int32, 0)  

    @assert all(IPP.Signals.AddC (val, Y     ,scale) .== Z)  # Z = Y + val
    @assert all(IPP.Signals.AddC!(val, Y     ,scale) .== Z)  # Y = Y + val

end
