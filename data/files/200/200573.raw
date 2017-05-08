# wrap_hypre.jl: Generate wrapping code. See Eglib.jl (thanks!)
# This file is not an active part of the package. This is the code
# that uses the Clang.jl package to wrap Hypre using the headers.

cd(dirname(@__FILE__))

using Clang.wrap_c

#Clang include path for system clang: /usr/include/clang/3.4/include

JULIAHOME = "/home/jgoldfar/Documents/work/projects/julia"

clang_includes = map(x->joinpath(JULIAHOME, x),[
                       "usr/include/clang/",
                       "usr/include",
                       "usr/include/llvm",
                       "usr/include/llvm-c",
                       ]
                     )

path = "/home/jgoldfar/Documents/work/projects/XBraid.jl/deps/usr/include"
headerlist = ["braid_defs.h","_braid.h","braid.h","braid_status.h","braid_test.h","util.h"]


headers = [joinpath(path, x) for x in headerlist]
#@show filter(x->contains(x,".h"), readdir(path))
#exit()

push!(clang_includes, path)
push!(clang_includes, "/usr/include/mpich")

check_use_header(path) = true

clang_extraargs = ["-D", "__STDC_LIMIT_MACROS", "-D", "__STDC_CONSTANT_MACROS", "-v"]
context = wrap_c.init(output_file = "libxbraid.jl",
                      headers = headers,
                      header_library=x->"libxbraid",
                      clang_args = clang_extraargs,
                      clang_includes = clang_includes,
                      common_file = "libxbraid_h.jl",
                      )

run(context)
