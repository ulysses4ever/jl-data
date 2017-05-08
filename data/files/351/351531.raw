module IPPCore

    const libippcore = "libippcore"

    export  IPPInt,     ippint,
            IPP8u,      ipp8u,
            IPP8s,      ipp8s,
            IPP16u,     ipp16u,
            IPP16s,     ipp16s,
            IPP32u,     ipp32u,
            IPP32s,     ipp32s,
            IPP16f,     ipp16f,
            IPP32f,     ipp32f,
            IPP64f,     ipp64f,
            IPP16uc,    ipp16uc,
            IPP16sc,    ipp16sc,
            IPP32uc,    ipp32uc,
            IPP32sc,    ipp32sc,
            IPP16fc,    ipp16fc,
            IPP32fc,    ipp32fc,
            IPP64fc,    ipp64fc,
            IPPSuffix,  IPPTypeSignature,
            IppVersion, ippversion,
            IppStatus,  ippstatus_string,
            ippcputype, ippcpudescr, ippcpufreq

    # common types

    typealias IPPInt    Cint
    typealias IPP8u     Uint8
    typealias IPP8s     Int8
    typealias IPP16u    Uint16
    typealias IPP16s    Int16
    typealias IPP32u    Uint32
    typealias IPP32s    Int32
    typealias IPP16f    Float16
    typealias IPP32f    Float32
    typealias IPP64f    Float64
    typealias IPP16uc   Complex{Uint16}
    typealias IPP16sc   Complex{Int16}
    typealias IPP32uc   Complex{Uint32}
    typealias IPP32sc   Complex{Int32}
    typealias IPP16fc   Complex{Float16}
    typealias IPP32fc   Complex{Float32}
    typealias IPP64fc   Complex{Float64}

    ippint( x )  = convert( IPPInt, x )
    ipp8u( x )   = convert( IPP8u, x )
    ipp8s( x )   = convert( IPP8s, x )
    ipp16u( x )  = convert( IPP16u, x )
    ipp16s( x )  = convert( IPP16s, x )
    ipp32u( x )  = convert( IPP32u, x )
    ipp32s( x )  = convert( IPP32s, x )
    ipp16f( x )  = convert( IPP16f, x )
    ipp32f( x )  = convert( IPP32f, x )
    ipp64f( x )  = convert( IPP64f, x )
    ipp16uc( x ) = convert( IPP16uc, x )
    ipp16sc( x ) = convert( IPP16sc, x )
    ipp32uc( x ) = convert( IPP32uc, x )
    ipp32sc( x ) = convert( IPP32sc, x )
    ipp16fc( x ) = convert( IPP16fc, x )
    ipp32fc( x ) = convert( IPP32fc, x )
    ipp64fc( x ) = convert( IPP64fc, x )

    IPPTypeDict = [ IPP8u   => "8u",
                    IPP8s   => "8s",
                    IPP16u  => "16u",
                    IPP16s  => "16s",
                    IPP32u  => "32u",
                    IPP32s  => "32s",
                    IPP16f  => "16f",
                    IPP32f  => "32f",
                    IPP64f  => "64f",
                    IPP16uc => "16uc",
                    IPP16sc => "16sc",
                    IPP32uc => "32uc",
                    IPP32sc => "32sc",
                    IPP16fc => "16fc",
                    IPP32fc => "32fc",
                    IPP64fc => "64fc" ]

    function IPPTypeSignature( IPPType )
        IPPTypeDict[ eval( IPPType ) ]
    end

    function IPPSuffix( IPPType )
       string( "_", IPPTypeSignature( IPPType ))
    end

    function IPPSuffix( IPPTypes::Tuple )
        lenTypes = length( IPPTypes )
        lenTypes == 0 && return ""
        lenTypes == 1 && return IPPSuffix( IPPTypes[1] )

        suffix = IPPTypeSignature( IPPTypes[1] )
        for Tsymb in IPPTypes[2:end]
            suffix *= IPPSuffix( Tsymb )
        end

        suffix
    end


    ## Get version

    immutable IppVersion
        major::Int
        minor::Int
        majorBuild::Int
        build::Int
    end

    function Base.show(io::IO, v::IppVersion)
        print(io, "IPP Version $(v.major).$(v.minor).$(v.majorBuild) (build=$(v.build))")
    end

    function ippversion()
        p = ccall((:ippGetLibVersion, libippcore), Ptr{Uint8}, ())
        nbytes = sizeof(IPPInt) * 4 + 4 + sizeof(Ptr{Uint}) * 4
        a = pointer_to_array(p, nbytes)
        buf = IOBuffer(a)

        major = int(read(buf, IPPInt))
        minor = int(read(buf, IPPInt))
        majorBuild = int(read(buf, IPPInt))
        build = int(read(buf, IPPInt))

        return IppVersion(major, minor, majorBuild, build)
    end

    ## Status string

    typealias IppStatus IPPInt
    function ippstatus_string(s::Integer)
        p = ccall((:ippGetStatusString, libippcore), Ptr{Uint8}, (IppStatus,), s)
        return bytestring(p)
    end

    ## CPU info

    ippcputype() = uint8(ccall((:ippGetCpuType, libippcore), IPPInt, ()))

    const cpudescrmap = (Uint8=>ASCIIString)[
        0x00 => "Unknown CPU",
        0x01 => "Intel(R) Pentium(R) processor",
        0x02 => "Intel(R) Pentium(R) processor with MMX(TM) technology",
        0x03 => "Intel(R) Pentium(R) Pro processor",
        0x04 => "Intel(R) Pentium(R) II processor",
        0x05 => "Intel(R) Pentium(R) III processor and Pentium(R) III Xeon(R) processor",
        0x06 => "Intel(R) Pentium(R) 4 processor and Intel(R) Xeon(R) processor",
        0x07 => "Intel(R) Pentium(R) 4 Processor with HT Technology",
        0x08 => "Intel(R) Pentium(R) 4 processor with Intel(R) SSE 3",
        0x09 => "Intel(R) Centrino(R) mobile technology",
        0x0a => "Intel(R) Core(TM) Solo processor",
        0x0b => "Intel(R) Core(TM) Duo processor",
        0x10 => "Intel(R) Itanium(R) processor",
        0x11 => "Intel(R) Itanium(R) 2 processor",
        0x20 => "Intel(R) 64 Instruction Set Architecture (ISA)",
        0x21 => "Intel(R) Core(TM) 2 Duo processor",
        0x22 => "Intel(R) Core(TM) 2 Quad processor",
        0x23 => "Intel(R) Core(TM) 2 processor with Intel(R) SSE 4.1",
        0x24 => "Intel(R) Atom(TM) processor",
        0x25 => "Intel(R) Core(TM) i7 processor",
        0x26 => "Next Generation CPU",
        0x40 => "Processor supports Intel(R) SSE instruction set",
        0x41 => "Processor supports Intel(R) SSE 2 instruction set",
        0x42 => "Processor supports Intel(R) SSE 3 instruction set",
        0x43 => "Processor supports Intel(R) SSSE 3 instruction set",
        0x44 => "Processor supports Intel(R) SSE 4.1 instruction set",
        0x45 => "Processor supports Intel(R) SSE 4.2 instruction set",
        0x46 => "Processor supports Intel(R) AVX instruction set",
        0x47 => "Processor supports Intel(R) AES New Instructions",
        0x49 => "Processor supports RDRRAND & Float16 instructions",
        0x4a => "Processor supports Intel(R) AVX 2 instruction set",
        0x4b => "Processor supports ADCX and ADOX instructions",
        0x60 => "Processor supports 64 bit extension"]

    function ippcpudescr(i::Uint8)
        if haskey(cpudescrmap, i)
            return cpudescrmap[i]
        else
            return @sprintf("Unknown Processor (code = %02x)", i)
        end
    end

    ippcpudescr(i::Integer) = ippcpudescr(uint8(i))
    ippcpudescr() = ippcpudescr(ippcputype())

    function ippcpufreq()  # in terms of Mhz
        r = IPPInt[0]
        ccall((:ippGetCpuFreqMhz, libippcore), IppStatus, (Ptr{Int64},), pointer(r))
        return int(r[1])
    end

end