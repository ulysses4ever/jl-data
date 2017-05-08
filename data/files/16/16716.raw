function createproject(path::String = ".")
    if !ispath(path)
        mkdir(path)
    end

    mkdir(joinpath(path, "cache"))
    touch(joinpath(path, "cache", ".gitignore"))

    mkdir(joinpath(path, "config"))
    touch(joinpath(path, "config", "global.json"))
    config = {
                "recursive" => true,
                "loadpackages" => true,
                "loadcache" => true,
                "loaddata" => true,
                "preprocess" => true,
                "log" => false,
                "packages" => [],
             }
    config_text = JSON.json(config)
    config_text = replace(config_text, r",", ",\n")
    io = open(joinpath(path, "config", "global.json"), "w")
    println(io, config_text)
    close(io)

    mkdir(joinpath(path, "data"))
    touch(joinpath(path, "data", ".gitignore"))

    mkdir(joinpath(path, "diagnotics"))
    touch(joinpath(path, "diagnotics", "01.jl"))

    mkdir(joinpath(path, "doc"))
    touch(joinpath(path, "doc", ".gitignore"))

    mkdir(joinpath(path, "graphs"))
    touch(joinpath(path, "graphs", ".gitignore"))

    mkdir(joinpath(path, "lib"))
    touch(joinpath(path, "lib", "helpers.jl"))

    mkdir(joinpath(path, "logs"))
    touch(joinpath(path, "logs", ".gitignore"))

    mkdir(joinpath(path, "preprocess"))
    touch(joinpath(path, "preprocess", "01-A.jl"))

    mkdir(joinpath(path, "profile"))
    touch(joinpath(path, "profile", "01.jl"))

    mkdir(joinpath(path, "reports"))
    touch(joinpath(path, "reports", ".gitignore"))

    mkdir(joinpath(path, "src"))
    touch(joinpath(path, "src", "EDA.jl"))

    mkdir(joinpath(path, "tests"))
    touch(joinpath(path, "tests", ".gitignore"))

    touch(joinpath(path, "README.md"))

    touch(joinpath(path, "TODO.md"))
end
