function create_project{T <: String}(project_name::T)
	mkdir("cache")

	mkdir("config")
	file_create(file_path("config", "global.json"))

	mkdir("data")

	mkdir("diagnotics")
	file_create(file_path("diagnotics", "01.jl"))

	mkdir("doc")

	mkdir("graphs")

	mkdir("lib")
	file_create(file_path("lib", "helpers.jl"))

	mkdir("logs")

	mkdir("munge")
	file_create(file_path("munge", "01-A.jl"))

	mkdir("profiling")
	file_create(file_path("profiling", "01.jl"))

	mkdir("reports")

	mkdir("src")
	file_create(file_path("src", "EDA.jl"))

	mkdir("tests")

	file_create("README.md")

	file_create("TODO.md")
end
