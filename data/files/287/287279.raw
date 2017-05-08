using Clang.cindex

get_it(t::TypedefDecl) = get_it(cindex.getTypedefDeclUnderlyingType(t))
get_it(d::ParmDecl)    = get_it(cu_type(d))
get_it(t::TypeRef)     = spelling(t)
get_it(t::Pointer) = string("Ptr{", get_it(cindex.getPointeeType(t)), "}")
get_it(t::CLType)  = spelling(t)

get_it(c::CLCursor) = get_it(cindex.getCursorType(c))
get_it(f::FunctionDecl) = spelling(f)

function Constants(top)
    f=open("Constants.jl", "w")

    fdecls=cindex.search(top, EnumDecl)
    for cursor in fdecls
        const_dict=Dict{ASCIIString,Int}()
        for enum in children(cursor)
            if ismatch(r"UNUR", name(enum))
                const_dict[name(enum)]=value(enum)
            end
        end
        if length(const_dict)>0
            data_type="UInt32"
            if haskey(const_dict, "UNUR_DISTR_CONT")
                data_type="Cuint"
            elseif haskey(const_dict, "UNUR_DISTR_GAUSSIAN")
                data_type="Cuint"
            elseif haskey(const_dict, "UNUR_SUCCESS")
                data_type="Cint"
            end
            all_keys=join(keys(const_dict), ", ")
            println(f, "export $all_keys")
            println()
            for (k, v) in const_dict
                hv=v
                if data_type=="Cuint"
                    hv="0x$(hex(v))"
                end
                println(f, "const $k = ($(data_type)($hv))")
            end
            println()
        end
    end
end

header="""
export UNUR_DISTR, UNUR_PAR, UNUR_GEN, UNUR_URNG
export unur_urng_gsl_new, unur_urng_gslptr_new, unur_urng_gslqrng_new
export unur_urng_prng_new, unur_urng_prngptr_new
export RngStream_SetPackageSeed, unur_urng_rngstream_new, unur_urng_rngstreamptr_new

# Provides typed opaque pointers.
type UNUR_DISTR
end

type UNUR_PAR
end

type UNUR_GEN
end

type UNUR_URNG
end

### GSL generators
function unur_urng_gsl_new(urngtype)
    ccall((:unur_urng_gsl_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void},), urngtype)
end

function unur_urng_gslptr_new(urngtype)
    ccall((:unur_urng_gslptr_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void},), urngtype)
end

function unur_urng_gslqrng_new(qrngtype, dim)
    ccall((:unur_urng_gslqrng_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void}, Cuint), qrngtype, dim)
end

### PRNG generators
function unur_urng_prng_new( prngstr )
    ccall((:unur_urng_prng_new, "libunuran"), Ptr{UNUR_URNG}, (Cstring,), prngstr)
end

function unur_urng_prngptr_new( prng_urng )
    ccall((:unur_urng_prngptr_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UInt8},), prng_urng)
end

### RngStreams
function RngStream_SetPackageSeed(seed)
  assert(length(seed)==6)
  assert(eltype(seed)==UInt64)
  ccall((:RngStream_SetPackageSeed, "librngstreams"), Void,
                (Ptr{UInt64},), seed)
end

function unur_urng_rngstream_new( urngstr )
    ccall((:unur_urng_rngstream_new, "libunuran"), Ptr{UNUR_URNG}, (Cstring,), urngstr)
end

function unur_urng_rngstreamptr_new( rngstream )
    ccall((:unur_urng_rngstream_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UInt8},), rngstream)
end

"""

parsed_to_jl=Dict{ASCIIString,ASCIIString}(
    "Int" => "Cint",
    "Double" => "Cdouble",
    "UInt" => "Cuint",
    "ULong" => "Cuint",
    "Void" => "Void",
    "size" => "Csize_t",
    )

function Functions(top)
    f=open("Functions.jl", "w")
    print(f, header)

    fdecls=cindex.search(top, FunctionDecl)
    for fdecl in fdecls
        function_name=get_it(fdecl)
        if ismatch(r"^unu", function_name)

            kids=[c for c in children(fdecl)]
            rt=return_type(fdecl)
            rt_pointer=isa(rt, Pointer)
            argstart=1
            if rt_pointer
                pt=pointee_type(rt)
                rt_str=get_it(kids[1])
                rt_type="Ptr{$rt_str}"
                if rt_str=="Void"
                    argstart=1
                else
                    argstart=2
                end
            else
                rt_simple=get_it(rt)
                if haskey(parsed_to_jl, rt_simple)
                    rt_type=parsed_to_jl[rt_simple]
                else
                    println("missing parsed_to_jl $rt_simple")
                    rt_type=rt_simple
                end
            end
            pointer_arg=false
            argnames=Array(ASCIIString, 0)
            argtypes=Array(ASCIIString, 0)
            for child_idx = argstart:length(kids)
                a=kids[child_idx]
                if !(isa(a, TypeRef) || isa(a, ParmDecl))
                else
                    got=get_it(a)
                    aname=Clang.cindex.getCursorDisplayName(a)
                    push!(argnames, aname)
                    if isa(cu_type(a), Pointer)
                        kind=tokenize(a)[1].text
                        for t in tokenize(a)
                            if ismatch(r"UNUR", t.text)
                                if ismatch(r"FUNCT", t.text)
                                    got="Ptr{Void}"
                                elseif ismatch(r"ERR", t.text)
                                    got="Ptr{Void}"
                                else
                                    got="Ptr{$(t.text)}"
                                end
                            elseif ismatch(r"char", t.text)
                                got="Cstring"
                            elseif ismatch(r"^double", t.text)
                                got="Ptr{Cdouble}"
                            end
                        end
                        push!(argtypes, got)
                    else
                        kind=""
                        tokens=""
                        if got=="Typedef"
                            got=Clang.cindex.getCursorDisplayName(a)
                        end
                        if haskey(parsed_to_jl, got)
                            push!(argtypes, parsed_to_jl[got])
                        else
                            println("missing $child_idx $got for $function_name")
                        end
                    end
                end
            end

            println(f, "export $(function_name)")
            all_args=join(argnames, ", ")
            println(f, "function $(function_name)($all_args)")
            sym="(:$(function_name), \"libunuran\")"
            if length(argnames)<1
                println(f, "    res=ccall($sym, $rt_type, () )")
            else
                args_type=join(argtypes, ", ")
                println(f, "    res=ccall($sym, $rt_type, ($args_type, ), $all_args)")
            end
            if rt_pointer
                if rt_str=="UNUR_DISTR"
                    println(f, "    if res==C_NULL")
                    println(f, "        throw(SystemError(\"Null distribution returned by calling $(function_name)\"))")
                    println(f, "    end")
                end
            end
            println(f, "    res")
            println(f, "end")
            println(f)
        end
    end
end

function Generate()
    clang_includes=["/usr/local/include",
            "/usr/lib/llvm-3.4/lib/clang/3.4/include"]
    # clang_includes=["/usr/local/include", "/usr/include/linux",
    #         "/usr/lib/llvm-3.4/lib/clang/3.4/include","/usr/include/c++/4.8/tr1"]
    top=cindex.parse_header("/usr/local/include/unuran.h", includes=clang_includes)

    Constants(top)
    Functions(top)
end




Generate()

