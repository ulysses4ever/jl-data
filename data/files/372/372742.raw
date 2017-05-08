#!/usr/bin/env julia

require("types")
require("dispatch")
require("args")
require("config")

using Lumberjack
using Types
using YAML

using Dispatch
using Args
#using Config

function main()
  args = Args.parse_cli()

  file = "$(args["config-path"])/config.yml"
  debug("Verify if the config file exists", {:path => file})

  #Get configuration
  config = if isfile(file)
    debug("Configuration file founded")
    data = YAML.load(open(file))

    info("Getting config info")
    println(data)
    data
  else
    info("Config file not founded")
    Dict{String, Any}()
  end

  #Collect files and metadata
  context = Config.create_context(args, config)

  #Apply configurations

  Dispatch.dispatch_command(args, config)
end
print(ARGS)
main()
