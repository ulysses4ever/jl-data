require("DataFrames")
require("JSON")

using DataFrames

module ProjectTemplate
	using JSON
	using DataFrames

	export create_project, load_project
	include(joinpath(julia_pkgdir(), "ProjectTemplate", "src", "utils.jl"))
	include(joinpath(julia_pkgdir(), "ProjectTemplate", "src", "table_reader.jl"))
	include(joinpath(julia_pkgdir(), "ProjectTemplate", "src", "extensions_dispatch_table.jl"))
	include(joinpath(julia_pkgdir(), "ProjectTemplate", "src", "create_project.jl"))
	include(joinpath(julia_pkgdir(), "ProjectTemplate", "src", "load_project.jl"))
end
