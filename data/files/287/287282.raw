using Clang.cindex

get_it(t::TypedefDecl) = get_it(cindex.getTypedefDeclUnderlyingType(t))
get_it(d::ParmDecl)    = get_it(cu_type(d))
get_it(t::TypeRef)     = spelling(t)
get_it(t::Pointer) = string("Ptr{", get_it(cindex.getPointeeType(t)), "}")
get_it(t::CLType)  = spelling(t)

get_it(c::CLCursor) = get_it(cindex.getCursorType(c))
get_it(f::FunctionDecl) = spelling(f)
printind(ind::Int, st...)              = println(join([repeat(" ", 2*ind), st...]))

printobj(cursor::cindex.CLCursor)      = printobj(0, cursor)
printobj(t::cindex.CLType)             = join(typeof(t), " ", spelling(t))
printobj(t::cindex.IntType)            = t
printobj(t::cindex.Pointer)            = cindex.pointee_type(t)
printobj(ind::Int, t::cindex.CLType)   = printind(ind, printobj(t))

function printobj(ind::Int, cursor::Union{cindex.FieldDecl, cindex.ParmDecl})
    printind(ind+1, typeof(cursor), " ", printobj(cu_type(cursor)), " ", name(cursor))
end

function printobj(ind::Int, node::Union{cindex.CLCursor,
                                        cindex.StructDecl,
                                        cindex.CompoundStmt,
                                        cindex.FunctionDecl,
                                        cindex.BinaryOperator} )
    printind(ind, " ", typeof(node), " ", name(node))
    for c in children(node)
        printobj(ind + 1, c)
    end
end# ajd27@withme:/usr/local/include$ ls unu*
# unuran.h        unuran_urng_gsl.h   unuran_urng_rngstreams.h
# unuran_tests.h  unuran_urng_prng.h


function unuheaders()
    clang_includes=["/usr/local/include",
            "/usr/lib/llvm-3.4/lib/clang/3.4/include"]
    # clang_includes=["/usr/local/include", "/usr/include/linux",
    #         "/usr/lib/llvm-3.4/lib/clang/3.4/include","/usr/include/c++/4.8/tr1"]
    cindex.parse_header("/usr/local/include/unuran.h", includes=clang_includes)
end

function generate()
    clang_includes=["/usr/local/include",
            "/usr/lib/llvm-3.4/lib/clang/3.4/include"]
    # clang_includes=["/usr/local/include", "/usr/include/linux",
    #         "/usr/lib/llvm-3.4/lib/clang/3.4/include","/usr/include/c++/4.8/tr1"]
    top=cindex.parse_header("/usr/local/include/unuran.h", includes=clang_includes)
    for cursor in children(top)
        if isa(cursor, EnumDecl)
            print("XXXXXXXXXXXXXXXXX\n")
            for enum in children(cursor)
                # println("$(enum.data)")
                # println("$(name(enum)) = $(value(enum))")
            end                        
        end
    end

    fdecls=cindex.search(top, FunctionDecl)
    for fdecl in fdecls
        name=get_it(fdecl)
        if ismatch(r"unu", name)
            println("$name")
            rt=return_type(fdecl)
            rt_pointer=isa(rt, Pointer)
            if rt_pointer
                pt=pointee_type(rt)
                ptname=get_it(pt)
                println("    RETURN: $(get_it(rt)), $ptname")
            else
                println("    RETURN: $(get_it(rt))")
            end
            pointer_arg=false
            child_idx=1
            for a in children(fdecl)
                if !(isa(a, TypeRef) || isa(a, ParmDecl))
                    print("What is a? $(get_it(a)), ")
                else
                    got=get_it(a)
                    aname=Clang.cindex.getCursorDisplayName(a)
                    if isa(cu_type(a), Pointer)
                        kind=tokenize(a)[1].text
                        tokens=join([t for t in tokenize(a)], ", ")
                        pointer_arg=true
                        arg_pt=pointee_type(cu_type(a))
                    else
                        kind=""
                        tokens=""
                        arg_pt=""
                    end
                    println("    $child_idx $got $aname $arg_pt [$tokens]")
                end
                child_idx+=1
            end
            if rt_pointer && !pointer_arg
                println("Makes distr $name")
            end
            println()
        end
    end
end


generate()
