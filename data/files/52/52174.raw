using BinDeps

@BinDeps.setup

deps = [
  libtokenizer = library_dependency("libtokenizer", aliases = ["libtokenizer"])
]

prefix = joinpath(BinDeps.depsdir(libtokenizer), "usr")
pkgdir = BinDeps.pkgdir(libtokenizer)
srcdir = joinpath(BinDeps.depsdir(libtokenizer), "src", "tokenizer")
provides(BuildProcess,
  (@build_steps begin
    CreateDirectory(prefix)
    `cp $pkgdir/src/c/* $srcdir`
    @build_steps begin
      ChangeDirectory(srcdir)
      FileRule(joinpath(prefix, "lib", "libtokenizer"), @build_steps begin
        MakeTargets(["libtokenizer"])
      end)
    end
  end), libtokenizer)

@BinDeps.install [:libtokenizer => :libtokenizer]
