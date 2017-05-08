using UNURAN

function Init()
    #push!(DL_LOAD_PATH,"/usr/local/lib")
    rngs=Libdl.dlopen("/usr/local/lib/librngstreams")
    unuran=Libdl.dlopen("/usr/local/lib/libunuran")
end

function First()
    #push!(DL_LOAD_PATH,".")
    distr=ccall( ("unur_distr_normal", "/usr/local/lib/libunuran"),
            Ptr{UInt8}, (Ptr{UInt8}, Int32), C_NULL, 0)
    par=ccall(("unur_hinv_new", "/usr/local/lib/libunuran"),
            Ptr{UInt8}, (Ptr{UInt8},), distr)
    gen=ccall(("unur_init", "/usr/local/lib/libunuran"),
            Ptr{UInt8}, (Ptr{UInt8},), par)
    for i=1:10
        val=ccall(("unur_sample_cont", "/usr/local/lib/libunuran"),
            Float64, (Ptr{UInt8},), gen)
        print(val, "\n")
    end
end

function mypdf( x, distr )
    ret=0
    if abs(x) >= 1
         ret=0
       else
         ret=(1-x*x)
    end
    convert(Cdouble, ret)::Cdouble
end     
function mydpdf( x, distr )
    ret=0
       if abs(x) < 1
         ret= (-2*x)
    end
    convert(Cdouble, ret)::Cdouble
end

function TryRng()
        seed=UInt64[111, 222, 333, 444, 555, 666]
        RngStream_SetPackageSeed(seed)
        urng1 = unur_urng_rngstream_new("urng-1")
end

function test()
    Init()

    TryRng()

    distr=unur_distr_normal(C_NULL, 0)
    par=unur_hinv_new(distr)
    gen=unur_init(par)
    unur_distr_free(distr)
    for i=1:10
        println(unur_sample_cont(gen))
    end
    unur_free(gen)


    const mypdf_c=cfunction(mypdf, Cdouble, (Cdouble, Ptr{UNUR_DISTR}))
    const mydpdf_c=cfunction(mydpdf, Cdouble, (Cdouble, Ptr{UNUR_DISTR}))
    distr=unur_distr_cont_new()
    unur_distr_cont_set_pdf( distr, mypdf_c )
    unur_distr_cont_set_dpdf( distr, mydpdf_c )

    par=unur_tdr_new(distr)
    gen=unur_init(par)
    unur_distr_free(distr)

    for i=1:10
        x = unur_sample_cont(gen)
        println(x)
    end
    unur_free(gen)
end

test()

