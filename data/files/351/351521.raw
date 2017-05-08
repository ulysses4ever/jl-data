module IPPCore

    const libippcore = "libippcore"

    export 

    IppVersion, ippversion, 
    IppStatus, ippstatus_string,
    ippcputype, ippcpudescr, ippcpufreq

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
        nbytes = sizeof(Cint) * 4 + 4 + sizeof(Ptr{Uint}) * 4
        a = pointer_to_array(p, nbytes)
        buf = IOBuffer(a)

        major = int(read(buf, Cint))
        minor = int(read(buf, Cint))
        majorBuild = int(read(buf, Cint))
        build = int(read(buf, Cint))

        return IppVersion(major, minor, majorBuild, build)  
    end

    ## Status string

    typealias IppStatus Cint
    function ippstatus_string(s::Integer)
        p = ccall((:ippGetStatusString, libippcore), Ptr{Uint8}, (IppStatus,), s)
        return bytestring(p)
    end

    ## CPU info

    ippcputype() = uint8(ccall((:ippGetCpuType, libippcore), Cint, ()))

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
        r = Cint[0]
        ccall((:ippGetCpuFreqMhz, libippcore), IppStatus, (Ptr{Int64},), pointer(r))
        return int(r[1])
    end

end




