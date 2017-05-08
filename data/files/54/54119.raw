using Mux

cd(dirname(@__FILE__))

@app test = (
    Mux.defaults,
    page(
        "/mylib.tar",
        respond(readall(`tar c -p mylib`))
    ),
    Mux.notfound()
)

serve(test)

using BinDeps

const testuri = URI("http://localhost:8000/mylib.tar")
const shlib_ext = BinDeps.shlib_ext

@BinDeps.setup

deps = [
    mylib = library_dependency("mylib", aliases = ["libmylib", "libmylib.so.1", "libmylib.so.1.0.0"])
]

provides(Sources, testuri, mylib)
provides(BuildProcess, Autotools(libtarget = "libmylib.$shlib_ext"), mylib)

@BinDeps.install Dict(:mylib => :mylib)
