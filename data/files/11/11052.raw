using BinDeps

@BinDeps.setup

libtweetnacl = library_dependency("tweetnacl", aliases=["libtweetnacl"])

const libtweetnacl_dir = joinpath(BinDeps.depsdir(libtweetnacl), "src")

provides(SimpleBuild,
         (@build_steps begin
              @build_steps begin
                  ChangeDirectory(libtweetnacl_dir)
                  `make`
                  `mv libtweetnacl.so ../usr/lib`
              end
          
          end), libtweetnacl, os=:Unix)

@BinDeps.install Dict([(:tweetnacl, :tweetnacl)])
