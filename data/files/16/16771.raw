function create_project{T <: String}(project_name::T)
	mkdir("cache")
	file_create(joinpath("cache", ".gitignore"))

	mkdir("config")
	file_create(joinpath("config", "global.json"))

	mkdir("data")
	file_create(joinpath("data", ".gitignore"))

	mkdir("diagnotics")
	file_create(joinpath("diagnotics", "01.jl"))

	mkdir("doc")
	file_create(joinpath("doc", ".gitignore"))

	mkdir("graphs")
	file_create(joinpath("graphs", ".gitignore"))

	mkdir("lib")
	file_create(joinpath("lib", "helpers.jl"))

	mkdir("logs")
	file_create(joinpath("logs", ".gitignore"))

	mkdir("munge")
	file_create(joinpath("munge", "01-A.jl"))

	mkdir("profiling")
	file_create(joinpath("profiling", "01.jl"))

	mkdir("reports")
	file_create(joinpath("reports", ".gitignore"))

	mkdir("src")
	file_create(joinpath("src", "EDA.jl"))

	mkdir("tests")
	file_create(joinpath("tests", ".gitignore"))

	file_create("README.md")

	file_create("TODO.md")
end
