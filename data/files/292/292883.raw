#
function find_exe_paths(prog)
    # 8f1kRCu
    env_pathext = get(ENV, "PATHEXT", "")

    # 4fpQ2RB
    if env_pathext == ""
        # 9dqlPRg
        return []
    end

    # 6qhHTHF
    # Split into a list of extensions
    ext_s = split(env_pathext, ";")


    # 2pGJrMW
    # Strip
    ext_s = [strip(ext) for ext=ext_s]

    # 2gqeHHl
    # Remove empty.
    # Must be done after the stripping at 2pGJrMW.
    ext_s = filter(x -> x != "", ext_s)

    # 2zdGM8W
    # Convert to lowercase
    ext_s = [lowercase(ext) for ext=ext_s]

    # 2fT8aRB
    # Uniquify
    ext_s = unique(ext_s)

    # 4ysaQVN
    env_path = get(ENV, "PATH", "")

    # 5gGwKZL
    if env_path == ""
        # 7bVmOKe
        # Go ahead with "dir_path_s" being empty
        dir_path_s = []
    else
        # 6mPI0lg
        # Split into a list of dir paths
        dir_path_s = split(env_path, ";")
    end

    # 5rT49zI
    # Insert empty dir path to the beginning.
    #
    # Empty dir handles the case that "prog" is a path, either relative or
    # absolute. See code 7rO7NIN.
    unshift!(dir_path_s, "")

    # 2klTv20
    # Uniquify
    dir_path_s = unique(dir_path_s)

    # 9gTU1rI
    # Check if "prog" ends with one of the file extension in "ext_s".
    #
    # "ext_s" are all in lowercase, ensured at 2zdGM8W.
    prog_lc = lowercase(prog)

    prog_has_ext = (findfirst(ext -> endswith(prog_lc, ext), ext_s)) != 0
    # Index value "0" means not found.

    # 6bFwhbv
    exe_path_s = String[]

    for dir_path=dir_path_s
        # 7rO7NIN
        # Synthesize a path
        if dir_path == ""
            path = prog
        else
            path = dir_path * "\\" *  prog
        end

        # 6kZa5cq
        # If "prog" ends with executable file extension
        if prog_has_ext
            # 3whKebE
            if isfile(path)
                # 2ffmxRF
                push!(exe_path_s, path)
            end
        end

        # 2sJhhEV
        # Assume user has omitted the file extension
        for ext=ext_s
            # 6k9X6GP
            # Synthesize a path with one of the file extensions in PATHEXT
            path_2 = path * ext

            # 6kabzQg
            if isfile(path_2)
                # 7dui4cD
                push!(exe_path_s, path_2)
            end
        end
    end

    # 8swW6Av
    # Uniquify
    exe_path_s = unique(exe_path_s)

    # 7y3JlnS
    return exe_path_s
end

#
function main()
    # 9mlJlKg
    # If not exactly one command argument is given
    if length(ARGS) != 1
        usage = """Usage: aoikwinwhich PROG

#/ PROG can be either name or path
aoikwinwhich notepad.exe
aoikwinwhich C:\\Windows\\notepad.exe

#/ PROG can be either absolute or relative
aoikwinwhich C:\\Windows\\notepad.exe
aoikwinwhich Windows\\notepad.exe

#/ PROG can be either with or without extension
aoikwinwhich notepad.exe
aoikwinwhich notepad
aoikwinwhich C:\\Windows\\notepad.exe
aoikwinwhich C:\\Windows\\notepad"""

        # 7rOUXFo
        # Print program usage
        print(usage)

        # 3nqHnP7
        # Exit
        return 1
    end

    # 9m5B08H
    # Get executable name or path
    prog = ARGS[1]

    # 8ulvPXM
    # Find executable paths
    exe_path_s = find_exe_paths(prog)


    # 5fWrcaF
    # If has found none
    if length(exe_path_s) == 0
        # 3uswpx0
        # Exit
        return 2
    # If has found some
    else
        # 9xPCWuS
        # Print result
        print(join(exe_path_s, "\n") * "\n")

        # 4s1yY1b
        # Exit
        return 0
    end
end

# 4zKrqsC
# Program entry
exit(main())
