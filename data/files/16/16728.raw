readconfig(path::String) = JSON.parse(readall(path))

function checkconfig!(config::Dict, setting::String, default::Any)
    if !haskey(config, setting)
        msg = @sprintf(
            "Your configuration file is missing an entry: %s",
            setting
        )
        warn(msg)
        config[setting] = default
    end
    return
end

function cleanname(varname::String)
    varname = replace(varname, r"^[^a-zA-Z0-9]+", "")
    varname = replace(varname, r"[^a-zA-Z0-9]+$", "")
    varname = replace(varname, r"_+", "_")
    varname = replace(varname, r"-+", "_")
    varname = replace(varname, r"\\s+", "_")
    varname = replace(varname, r"\\.+", "_")
    varname = replace(varname, r"[\\\\/]+", "_")
    if ismatch(r"^\d", varname)
        varname = strcat("X", varname)
    end
    return varname
end

function loadproject(path::String = ".")
    # ---
    # Project configuration
    # ---
    info("Loading project configuration")

    if !isfile(joinpath(path, "config", "global.json"))
        msg = @sprintf(
            "You are missing the configuration file '%s'",
            joinpath(path, "config", "global.json")
        )
        error(msg)
    end

    config = readconfig(joinpath(path, "config", "global.json"))

    # ---
    # Load helper functions
    # ---
    helpers = UTF8String[]

    if isdir(joinpath(path, "lib"))
        info("Autoloading helper functions")

        for helper in readdir(joinpath(path, "lib"))
            if ismatch(r"\.jl$", helper)
                info(@sprintf(" Running helper script: %s", helper))
                # TODO: This won't eval in the right scope
                include(joinpath(path, "lib", helper))
                push!(helpers, helper)
            end
        end
    end

    # ---
    # Load packages
    # ---
    checkconfig!(config, "loadpackages", true)
    checkconfig!(config, "packages", UTF8String[])

    packages = UTF8String[]

    if config["loadpackages"]
        info("Autoloading packages")
        for toload in config["packages"]
            info(@sprintf(" Loading package: %s", toload))
            try
                # TODO: This won't eval in the right scope
                require(toload)
            catch
                error(@sprintf("Failed to load package: %s", toload))
            end
            push!(packages, toload)
        end
    end

    # ---
    # Load cache
    # ---
    checkconfig!(config, "loadcache", false)

    cache = UTF8String[]

    datasets = Dict{UTF8String, DataFrame}()

    if config["loadcache"]
        info("Autoloading cache")

        if !isdir(joinpath(path, "cache"))
            error("You are missing a directory: cache")
        end

        cachefiles = readdir(joinpath(path, "cache"))

        for cachefile in cachefiles
            filename = joinpath(path, "cache", cachefile)

            for extension in keys(extensions)
                if ismatch(extension, cachefile)
                    cachefile = replace(cachefile, extension, "")
                    varname = cleanname(cachefile)

                    info(@sprintf(" Loading cached data set: %s", varname))
                    datasets[varname] = extensions[extension](filename)
                    push!(cache, varname)
                    break
                end
            end
        end
    end

    # ---
    # Load data, skipping datasets already loaded from cache
    # ---
    checkconfig!(config, "loaddata", false)
    checkconfig!(config, "recursive", false)

    data = UTF8String[]

    # Then, we load from the data directory
    if config["loaddata"]
        info("Autoloading data")

        if !isdir(joinpath(path, "data"))
            error("You are missing a directory: data")
        end

        if config["recursive"]
            # TODO: Make this recursive
            datafiles = readdir(joinpath(path, "data"))
        else
            datafiles = readdir(joinpath(path, "data"))
        end

        for datafile in datafiles
            filename = joinpath(path, "data", datafile)

            for extension in keys(extensions)
                if ismatch(extension, datafile)
                    datafile = replace(datafile, extension, "")
                    varname = cleanname(datafile)

                    if !(varname in cache)
                        info(@sprintf(" Loading data set: %s", varname))
                        datasets[varname] = extensions[extension](filename)
                        push!(data, varname)
                    end

                    break
                end
            end
        end
    end

    # ---
    # Preprocess data
    # ---
    checkconfig!(config, "preprocess", false)

    preprocessors = UTF8String[]

    if config["preprocess"]
        info("Preprocessing data")
        potential_preprocessors = sort(readdir(joinpath(path, "preprocess")))
        for preprocessor in potential_preprocessors
            if ismatch(r"\.jl$", preprocessor)
                info(
                    @sprintf(
                        " Running preprocessing script: %s",
                        preprocessor
                    )
                )
                # TODO: Evaluate this with access to datasets
                include(joinpath(path, "preprocess", preprocessor))
                push!(preprocessors, preprocessor)
            end
        end
    end

    return Project(
        config,
        cache,
        data,
        datasets,
        helpers,
        packages,
        preprocessors
    )
end
