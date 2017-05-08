using BinDeps

@BinDeps.setup

deps = [
  libtokenizer = library_dependency("libtokenizer", aliases = ["libtokenizer"])
]

prefix = joinpath(BinDeps.depsdir(libtokenizer), "usr")
pkgdir = BinDeps.pkgdir(libtokenizer)
srcdir = joinpath(BinDeps.depsdir(libtokenizer), "src", "tokenizer")
c_srcdir = joinpath(pkgdir, "src", "c")
target=joinpath(prefix, "lib", "libtokenizer.dylib")
provides(BuildProcess,
  (@build_steps begin
    CreateDirectory(prefix)
    CreateDirectory(joinpath(prefix, "lib"))
    CreateDirectory(srcdir)
    `cp -r $c_srcdir $srcdir`
    @build_steps begin
      ChangeDirectory(joinpath(srcdir, "c"))
      FileRule(target, @build_steps begin
        MakeTargets(["libtokenizer"])
        `cp $srcdir/c/libtokenizer.dylib $target`
      end)
    end
  end), libtokenizer)

@BinDeps.install [:libtokenizer => :libtokenizer]
