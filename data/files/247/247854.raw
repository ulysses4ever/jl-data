module Fox

using Playground
using ArgParse
using URIParser
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

            # if ispath(playground_path)
            #     Logging.info("Cleaning existing playground $found ...")
            #     rm(config; dir=playground_path)
            # end

            Logging.info("Building test playground $found ...")
            create(
                config;
                dir=playground_path,
                julia=found
            )

            # Start setting up the current package in the playground
            # by 1) making a symlink 2) adding it to the REQUIRE file
            # and 3) calling Pkg.resolve()

            # Get current package name
            pkg_name = replace(basename(pwd()), ".jl", "")

            # Get the playground package version path
            pkg_path = ""
            for vpath in readdir(pg_config.pkg_path)
                if contains(found, strip(vpath, 'v'))
                    pkg_path = joinpath(pg_config.pkg_path, vpath)
                end
            end

            # Update the REQUIRE file
            if pkg_path != ""
                Playground.mklink(pwd(), joinpath(pkg_path, pkg_name))
                open(joinpath(pkg_path, "REQUIRE"), "w+") do fstream
                    existing = readall(fstream)
                    if !contains(existing, pkg_name)
                        write(fstream, "$pkg_name\n")
                    end
                end

                # Call resolve
                execute(config, `julia -e 'Pkg.resolve()'`, dir=playground_path)
            end

            # We'll need to update `execute` in Playground
            # to return the status code.
            for entry in settings["script"]
                cmd_str = entry

                # Handle the gross Pkg.clone conditions cause
                # duplicate runs will result in an error cause of cloning
                # a pkg that already exists.
                # This should probably be done in a more robust way...
                # Once we refactor in the future this should be its own function
                # and tested like crazy.
                if contains(cmd_str, "Pkg.clone(pwd())")
                    Logging.info("Ignoring clone of pwd as it has already been linked.")
                    cmd_str = replace(cmd_str, "Pkg.clone(pwd())", "")
                elseif contains(cmd_str, "Pkg.clone")
                    # Match against all 'Pkg.clone()'s
                    Logging.debug("Has 'Pkg.clone...' in it cmd_str")

                    for sub_str in matchall(r"Pkg.clone\(\"(.*?(?=\"))\"\)", cmd_str)
                        Logging.debug(sub_str)

                        # Extract the url
                        grps = match(r"Pkg.clone\(\"(.*?(?=\"))\"\)", sub_str).captures
                        Logging.debug(grps)

                        # Assuming we've extracted the url, extract the pkg name
                        # and add a check if the Pkg is available before running the line.
                        if grps != nothing && length(grps) == 1
                            remote_pkg_name = replace(basename(URI(grps[1]).path), ".jl", "")
                            new_clone = "try Pkg.available(\"$(remote_pkg_name)\") catch $sub_str end"

                            Logging.debug("Replacing $sub_str with $new_clone")
                            cmd_str = replace(
                                cmd_str,
                                sub_str,
                                new_clone
                            )
                        end
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
