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

provides(Sources, URI("http://ftp.debian.org/debian/pool/main/m/mumps/mumps_4.10.0.dfsg.orig.tar.gz"), dmumps)

@BinDeps.install [:dmumps => :dmumps]
