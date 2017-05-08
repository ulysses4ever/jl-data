function create_project(project_name::String)
    mkdir("cache")
    touch(joinpath("cache", ".gitignore"))

    mkdir("config")
    touch(joinpath("config", "global.json"))
    config = {
                "recursive_loading" => "on",
                "load_libraries" => "on",
                "cache_loading" => "on",
                "data_loading" => "on",
                "munging" => "on",
                "logging" => "off",
                "libraries" => []
             }
    config_text = JSON.to_json(config)
    config_text = replace(config_text, r",", ",\n")
    io = open(joinpath("config", "global.json"), "w")
    println(io, config_text)
    close(io)

    mkdir("data")
    touch(joinpath("data", ".gitignore"))

    mkdir("diagnotics")
    touch(joinpath("diagnotics", "01.jl"))

    mkdir("doc")
    touch(joinpath("doc", ".gitignore"))

    mkdir("graphs")
    touch(joinpath("graphs", ".gitignore"))

    mkdir("lib")
    touch(joinpath("lib", "helpers.jl"))

    mkdir("logs")
    touch(joinpath("logs", ".gitignore"))

    mkdir("munge")
    touch(joinpath("munge", "01-A.jl"))

    mkdir("profiling")
    touch(joinpath("profiling", "01.jl"))

    mkdir("reports")
    touch(joinpath("reports", ".gitignore"))

    mkdir("src")
    touch(joinpath("src", "EDA.jl"))

    mkdir("tests")
    touch(joinpath("tests", ".gitignore"))

    touch("README.md")

    touch("TODO.md")
end
