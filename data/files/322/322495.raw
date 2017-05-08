module CompilerOptions

export compileropts

# C option forms
# found in https://github.com/JuliaLang/julia/blob/master/src/julia.h

# 0.3
if VERSION < v"0.4-"
    #typedef struct {
    #char *build_path;
    #int8_t code_coverage;
    #int8_t malloc_log;
    #int8_t check_bounds;
    #int int_literals;
    #} jl_compileropts_t;
    immutable JLCompilerOpts
        build_path::Ptr{Cchar}
        code_coverage::Int8
        malloc_log::Int8
        check_bounds::Int8
        dumpbitcode::Int8
        int_literals::Cint
    end

    compileropts() = unsafe_load(cglobal(:jl_compileropts, JLCompilerOpts))

# 0.4, subject to change, catostrophic breakage, and such.
else

    compileropts() = Base.compileropts()

end

end # module
