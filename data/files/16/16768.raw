function create_project{T <: String}(project_name::T)
	mkdir("cache")
	file_create(file_path("cache", ".gitignore"))

	mkdir("config")
	file_create(file_path("config", "global.json"))

	mkdir("data")
	file_create(file_path("data", ".gitignore"))

	mkdir("diagnotics")
	file_create(file_path("diagnotics", "01.jl"))

	mkdir("doc")
	file_create(file_path("doc", ".gitignore"))

	mkdir("graphs")
	file_create(file_path("graphs", ".gitignore"))

	mkdir("lib")
	file_create(file_path("lib", "helpers.jl"))

	mkdir("logs")
	file_create(file_path("logs", ".gitignore"))

	mkdir("munge")
	file_create(file_path("munge", "01-A.jl"))

	mkdir("profiling")
	file_create(file_path("profiling", "01.jl"))

	mkdir("reports")
	file_create(file_path("reports", ".gitignore"))

	mkdir("src")
	file_create(file_path("src", "EDA.jl"))

	mkdir("tests")
	file_create(file_path("tests", ".gitignore"))

	file_create("README.md")

	file_create("TODO.md")
end
