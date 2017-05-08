using Clang.cindex
using Clang.wrap_c
using Compat

POLYLIB_INCLUDE = "./polylib-5.22.5/include"

petsc_header = [joinpath(POLYLIB_INCLUDE, "polylib/polylib64.h")]

# Set up include paths
clang_includes = ASCIIString[]
push!(clang_includes, "/usr/lib/llvm-3.4/lib/clang/3.4/include")
push!(clang_includes, POLYLIB_INCLUDE)

# Clang arguments
clang_extraargs = ["-v"]
# clang_extraargs = ["-D", "__STDC_LIMIT_MACROS", "-D", "__STDC_CONSTANT_MACROS"]

# Callback to test if a header should actually be wrapped (for exclusion)
function wrap_header(top_hdr::ASCIIString, cursor_header::ASCIIString)
    return startswith(dirname(cursor_header), POLYLIB_INCLUDE)
end

lib_file(hdr::ASCIIString) = "polylib"
output_file(hdr::ASCIIString) = "PolyLib.jl"

const wc = wrap_c.init(;
                        headers = petsc_header,
                        output_file = "libpolylib64_h.jl",
                        common_file = "libpolylib64_common.jl",
                        clang_includes      = clang_includes,
                        clang_args          = clang_extraargs,
                        header_wrapped      = wrap_header,
                        header_library      = lib_file,
                        header_outputfile   = output_file,
                        clang_diagnostics = true)

run(wc)