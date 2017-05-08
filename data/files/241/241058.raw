## Creation of the DMumps structure

zero(::Type{Icntl}) = apply(Icntl, ntuple(40, i->zero(int32)))
zero(::Type{Info})  = apply(Info,  ntuple(40, i->zero(int32)))
zero(::Type{Rcntl}) = apply(Rcntl, ntuple(15, i->0.))
zero(::Type{Rinfo}) = apply(Rinfo, ntuple(40, i->0.))
zero(::Type{Array_16_Uint8}) = apply(Array_16_Uint8, ntuple(16, i->0x00))
zero(::Type{Array_64_Uint8}) = apply(Array_64_Uint8, ntuple(64, i->0x00))
zero(::Type{Array_256_Uint8}) = apply(Array_256_Uint8, ntuple(256, i->0x00))
