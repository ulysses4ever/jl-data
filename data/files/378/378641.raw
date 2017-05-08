module CompilerOptions

export compile_enabled, code_coverage, check_bounds, dump_bitcode

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
    immutable JL_CompilerOpts
        build_path::Ptr{Cchar}
        code_coverage::Int8
        malloc_log::Int8
        check_bounds::Int8
        dumpbitcode::Int8
        int_literals::Cint
    end

# 0.4, subject to change, catostrophic breakage, and such.
else
    #typedef struct {
    #char *build_path;
    #int8_t code_coverage;
    #int8_t malloc_log;
    #int8_t check_bounds;
    #int8_t dumpbitcode;
    #int int_literals;
    #int8_t compile_enabled;
    #} jl_compileropts_t;
    immutable JL_CompilerOpts
        build_path::Ptr{Cchar}
        code_coverage::Int8
        malloc_log::Int8
        check_bounds::Int8
        dumpbitcode::Int8
        int_literals::Cint
        compile_enabled::Int8
    end

end

function JL_CompilerOpts()
    return unsafe_load(cglobal(:jl_compileropts, JL_CompilerOpts))
end

# Module Global instantiation
jl_opts = JL_CompilerOpts()

function compile_enabled()
    if VERSION < v"0.4-"
        error("Julia <0.4 does not support compilation")
    else
        return jl_opts.compile_enabled == 1
    end
end

function code_coverage()
    return jl_opts.code_coverage == 1
end

function check_bounds()
    return jl_opts.check_bounds == 1
end

function dump_bitcode()
    return jl_opts.dumpbitcode == 1
end

end # module
