run(`touch deps.jl`)
run(`rm deps.jl`)

run(`echo 'macro checked_lib(libname, path)
        (dlopen_e(path) == C_NULL) && error("Unable to load \n\n$libname ($path)\n\nPlease re-run Pkg.build(package), and restart Julia.")
        quote const $(esc(libname)) = $path end
    end
@checked_lib mylib "'"$(Pkg.dir())"'/MyLib/deps/usr/lib/libmylib.so.1"
'` |> "deps.jl")

cd("src/mylib/")
run(`make clean`)
run(`make all`)
cd("../../")
