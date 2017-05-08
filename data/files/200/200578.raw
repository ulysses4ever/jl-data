using BinDeps

@BinDeps.setup

libxbraid = library_dependency("libbraid", aliases=["libbraid"])
xbraidver="1.0.b"
xbraidfilebase = "braid-$(xbraidver)"

provides(Sources,
         URI("https://bitbucket.org/jgoldfar/xbraid.jl/downloads/$(xbraidfilebase).tar.gz"),
         libxbraid,
unpacked_dir="braid")
#println(BinDeps.depsdir(libxbraid))
prefix = joinpath(BinDeps.depsdir(libxbraid), "usr")
srcdir = joinpath(BinDeps.depsdir(libxbraid), "src", "braid")
isdir(srcdir) && rm(srcdir, recursive=true)
buildfiledir = dirname(@__FILE__)
println("Installing XBraid source to ", srcdir)

provides(SimpleBuild, (@build_steps begin
                         GetSources(libxbraid)
CreateDirectory(srcdir)
@build_steps begin
                           ChangeDirectory(srcdir)
FileRule(joinpath(prefix, "lib", "libbraid.so"),
                         @build_steps begin 
`patch makefile.inc $buildfiledir/makefile.inc.patch`
`patch Makefile $buildfiledir/Makefile.patch`
`make clean`#MakeTargets("clean")
`make`#MakeTargets()
`make libbraid.so`#MakeTargets("libbraid.so")#`make libbraid.so`
`make install prefix=$prefix`#MakeTargets("install --prefix=$prefix")
end
)
end
                       end), libxbraid, os=:Unix)

@BinDeps.install [:libxbraid => :libxbraid]
