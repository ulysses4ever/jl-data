module IPPCore

    const libippcore = dlopen("libippcore")

    # Get version

    immutable IPPVersion
        major::Int
        minor::Int
        majorBuild::Int
        build::Int
    end

    function Base.show(io::IO, v::IPPVersion)
        print(io, "IPP Version $(v.major).$(v.minor).$(v.majorBuild) (build=$(v.build))")
    end

    function version()
        p = ccall(dlsym(libippcore, :ippGetLibVersion), Ptr{Uint8}, ())
        nbytes = sizeof(Cint) * 4 + 4 + sizeof(Ptr{Uint}) * 4
        a = pointer_to_array(p, nbytes)
        buf = IOBuffer(a)

        major = int(read(buf, Cint))
        minor = int(read(buf, Cint))
        majorBuild = int(read(buf, Cint))
        build = int(read(buf, Cint))

        return IPPVersion(major, minor, majorBuild, build)  
    end
end
