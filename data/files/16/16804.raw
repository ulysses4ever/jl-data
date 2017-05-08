function load_project()
  global project_info = Dict{ASCIIString, Any}()
  project_info["datasets"] = Dict{ASCIIString, Any}()

  message("Loading project configuration")
  if !isfile(file_path("config", "global.json"))
    error("You are missing a configuration file: config/global.json")
  end
  global config = read_config(file_path("config", "global.json"))
  if !has(config, "libraries")
    warning("Your configuration file is missing an entry: libraries")
  end

  project_info["config"] = config

  if isdir("lib")
    message("Autoloading helper functions")

    project_info["helpers"] = String[]

    for helper_script in readdir("lib")
      if ismatch(r"\.jl$", helper_script)
        message(" Running helper script: $(helper_script)")
        # How can we force execution of include()'s in Main?
        include(file_path("lib", helper_script))
        push(project_info["helpers"], helper_script)
      end
    end
  end

  if !has(config, "load_libraries")
    warning("Your configuration file is missing an entry: load_libraries")
  else
    if config["load_libraries"] == "on"
      message("Autoloading packages")
      project_info["packages"] = String[]
      for package_to_load in config["libraries"]
        message(" Loading package: $(package_to_load)")
        try
          require(package_to_load)
        catch
          error("Failed to load package: $(package_to_load)")
        end
        push(project_info["packages"], package_to_load)
      end
    end
  end

  if !has(config, "cache_loading")
    warning("Your configuration file is missing an entry: cache_loading")
    config["cache_loading"] = "off"
  end
  if !has(config, "data_loading")
    warning("Your configuration file is missing an entry: data_loading")
    config["data_loading"] = "off"
  end

  if config["data_loading"] != "on" && config["cache_loading"] == "on"
    message("Autoloading cache")

    # First, we load everything out of cache/.
    if !isdir("cache")
      error("You are missing a directory: cache")
    end
    cache_files = readdir("cache")
    project_info["cache"] = String[]

    for cache_file in cache_files
      filename = file_path("cache", cache_file)

      for extension in keys(extensions_dispatch_table)
        if ismatch(extension, cache_file)
          cache_file = replace(cache_file, extension, "")
          variable_name = clean_variable_name(cache_file)
          # If this variable already exists in the global environment, don"t load it from cache.
          # TODO: Make this work
          # if contains(whos(Main), variable_name)
          #   continue
          # end

          message(" Loading cached data set: variable_name")
          project_info["datasets"][variable_name] = apply(extensions_dispatch_table[extension], (filename, variable_name))
          push(project_info["cache"], variable_name)
          break
        end
      end
    end
  end

  if config["data_loading"] == "on"
    message("Autoloading data")

    # First, we load everything out of cache/.
    if !isdir("cache")
      error("You are missing a directory: cache")
    end
    cache_files = readdir("cache")
    project_info["cache"] = String[]

    for cache_file in cache_files
      filename = file_path("cache", cache_file)

      for extension in keys(extensions_dispatch_table)
        if ismatch(extension, cache_file)
          cache_file = replace(cache_file, extension, "")
          variable_name = clean_variable_name(cache_file)

          # If this variable already exists in the global environment, don"t load it from cache.
          # TODO: Make this work
          # if contains(whos(Main), variable_name)
          #   continue
          # end

          message(" Loading cached data set: $(variable_name)")
          project_info["datasets"][variable_name] = apply(extensions_dispatch_table[extension], (filename, variable_name))
          push(project_info["cache"], variable_name)
          break
        end
      end
    end

    # Then we consider loading things from data/.
    if !isdir("data")
      error("You are missing a directory: data")
    end

    # If recursive_loading
    if !has(config, "recursive_loading")
      warning("Your configuration file is missing an entry: recursive_loading")
      config["recursive_loading"] = "off"
    end

    if config["recursive_loading"] == "on"
      # Make this recursive
      data_files = readdir("data")
    else
      data_files = readdir("data")
    end
    project_info["data"] = String[]

    for data_file in data_files
      filename = file_path("data", data_file)

      for extension in keys(extensions_dispatch_table)
        if ismatch(extension, data_file)
          data_file = replace(data_file, extension, "")
          variable_name = clean_variable_name(data_file)

          # If this variable already exists in cache, don"t load it from data.
          # TODO: Make this work
          # if contains(whos(Main), variable_name)
          #   continue
          # end

          message(" Loading data set: $(variable_name)")
          project_info["datasets"][variable_name] = apply(extensions_dispatch_table[extension], (filename, variable_name))
          push(project_info["data"], variable_name)
          break
        end
      end
    end
  end

  if !has(config, "munging")
    warning("Your configuration file is missing an entry: munging")
  end
  if config["munging"] == "on"
    message("Munging data")
    for preprocessing_script in sort(readdir("munge"))
      if ismatch(r"\.jl$", preprocessing_script)
        message(" Running preprocessing script: $(preprocessing_script)")
        include(file_path("munge", preprocessing_script))
      end
    end
  end

  # TODO: Finish log4jl
  # if !has(config, "logging")
  #   warning("Your configuration file is missing an entry: logging")
  # end
  # if config["logging"] == "on"
  #   message("Initializing logger")
  #   load("log4jl")
  #   global logger = create_logger()
  #   if !isdir("logs")
  #     dir_create("logs")
  #   end
  #   logfile!(logger, file_path("logs", "project.log"))
  #   level!(logger, log4jl.INFO)
  # end

  return
end
