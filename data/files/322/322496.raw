module CompilerOptions

export JLOptions

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
    immutable JLOptions
        build_path::Ptr{Cchar}
        cpu_target::Ptr{Cchar}
        code_coverage::Int8
        malloc_log::Int8
        check_bounds::Int8
        int_literals::Cint
    end

    JLOptions() = unsafe_load(cglobal(:jl_compileropts, JLOptions))

# 0.4, subject to change, catostrophic breakage, and such.
else
# https://github.com/JuliaLang/julia/blob/master/base/options.jl
    JLOptions() = Base.JLOptions()

end

end # module
