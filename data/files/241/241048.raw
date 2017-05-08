using BinDeps

@BinDeps.setup

libdmumps_seq = library_dependency("libdmumps_seq")

@linux_only begin
    provides(AptGet, "libmumps-seq-dev", libdmumps_seq)
#    provides(Yum, "MUMPS-4.10.0", libdmumps)
end

## @osx_only begin
##     using Homebrew
##     provides( Homebrew.HB, "mumps", dmumps, os = :Darwin )
## end

provides(Sources, URI("http://ftp.debian.org/debian/pool/main/m/mumps/mumps_4.10.0.dfsg.orig.tar.gz"), libdmumps_seq)

@BinDeps.install
