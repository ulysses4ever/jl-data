using BinDeps

@BinDeps.setup

@linux_only begin
    geographiclib = library_dependency("libGeographic")
    provides(AptGet, "libgeographiclib-dev", geographiclib)
    # provides(Yum, "libgeographiclib-dev", geographiclib)
end

@osx_only begin
    using Homebrew
    geographiclib = library_dependency("libGeographic")
    provides(Homebrew.HB, "geographiclib", geographiclib, os=:Darwin)
end

@BinDeps.install
