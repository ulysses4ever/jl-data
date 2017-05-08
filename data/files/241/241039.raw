using BinDeps

@BinDeps.setup

dmumps = library_dependency("libdmumps", aliases=["libdmumps_seq"])

@linux_only begin
    provides(AptGet, "libmumps-seq-dev", dmumps)
    provides(Yum, "MUMPS-4.10.0", dmumps)
end

@osx_only begin
    using Homebrew
    provides( Homebrew.HB, "mumps", dmumps, os = :Darwin )
end

@BinDeps.install [:dmumps => :dmumps]
