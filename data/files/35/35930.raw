using Documenter, MergedMethods

makedocs(
    modules = MergedMethods,
    clean   = false,
)

deploydocs(
    deps = Deps.pip("pygments", "mkdocs", "mkdocs-material"),
    repo = "github.com/MichaelHatherly/MergedMethods.jl.git",
)
