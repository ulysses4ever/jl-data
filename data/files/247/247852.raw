module Fox

using Playground
using ArgParse
import Logging
import YAML: load


PLAYGROUND_CONFIG_PATH = joinpath(homedir(), ".playground")
PLAYGROUND_CONFIG_FILE = joinpath(PLAYGROUND_CONFIG_PATH, "config.yml")


function run(cmd_args=ARGS)
    config = load_config(PLAYGROUND_CONFIG_FILE, PLAYGROUND_CONFIG_PATH)
    parse_settings = ArgParseSettings(suppress_warnings=true)

    @add_arg_table parse_settings begin
        "--julia-versions", "-j"
            help = "A list of julia versions to test on. Must available via Playgournd.jl"
            action = :store_arg
            nargs = '*'
            default = []
        "--config", "-c"
            help = "By default the fox.yml or .travis.yml in the local directory will be used."
            action = :store_arg
            default = ""
    end

    args = parse_args(cmd_args, parse_settings)
    config_file = args["config"]
    if config_file == ""
        root_files = readdir(pwd())

        if "fox.yml" in root_files
            config_file = joinpath(pwd(), "fox.yml")
        elseif ".travis.yml" in root_files
            config_file = joinpath(pwd(), ".travis.yml")
        else
            error("$(pwd()) doesn't contain a fox.yml or .travis.yml file. Please provide one.")
        end
    elseif !ispath(config_file)
        error("$config_file is not a valid path")
    end

    settings = load(open(config_file))

    julia_versions = settings["julia"]
    if !isempty(args["julia-versions"])
        julia_versions = intersect(
            julia_versions,
            args["julia-versions"]
        )
    end

    found = AbstractString[]
    for j in julia_versions
        Logging.debug(j)
        found = ""

        for v in readdir(config.dir.bin)
            # Split on "-" cause Playground.jl suggests labelling
            # julia versions as julia-0.4 rather than just 0.4
            Logging.debug(v)
            extracted = split(v, "-")
            Logging.debug(extracted)

            if v == j || (length(extracted) == 2 && extracted[2] == string(j))
                found = v
            end
        end

        if found == ""
            Logging.info("$j not installed. Skipping.")
        else
            # Process tests for julia version
            # Create the playground
            playground_path = joinpath(pwd(), ".fox", found)
            pg_config = Playground.PlaygroundConfig(config, playground_path, "")

            # Make sure the default_shell is set to
            pg_config.default_shell = "/bin/sh"

            if ispath(playground_path)
                Logging.info("Cleaning existing playground $found ...")
                rm(config; dir=playground_path)
            end

            Logging.info("Building test playground $found ...")
            create(
                config;
                dir=playground_path,
                julia=found
            )

            # We'll need to update `execute` in Playground
            # to return the status code.
            for entry in settings["script"]
                cmd_str = entry
                if contains(cmd_str, "Pkg.clone(pwd());")
                    pkg_name = replace(basename(pwd()), ".jl", "")
                    pkg_path = ""
                    for vpath in readdir(pg_config.pkg_path)
                        if contains(found, strip(vpath, 'v'))
                            pkg_path = joinpath(pg_config.pkg_path, vpath)
                        end
                    end

                    if pkg_path != ""
                        Playground.mklink(pwd(), joinpath(pkg_path, pkg_name))
                        open(joinpath(pkg_path, "REQUIRE"), "a+") do fstream
                            write(fstream, pkg_name)
                        end

                        execute(config, `julia -e 'Pkg.resolve()'`, dir=playground_path)
                        cmd_str = replace(cmd_str, "Pkg.clone(pwd());", "")
                    end
                end
                if !contains(cmd_str, "git fetch --unshallow")
                    execute(
                        config,
                        `$(Base.shell_split(cmd_str))`;
                        dir=playground_path
                    )
                end
            end
        end
    end
end


end # module
