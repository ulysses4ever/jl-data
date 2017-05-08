#! /usr/local/bin/julia

using YAML, AnsiColor, Lint

# Because I don't want to be above board right away
const INSTALL_DIR = homedir() * "/.writer/"

# Creates a project. Creates directory, filt, refs.bib, figures, scripts, tables
function create_project(project)
    working_dir = pwd() * "/"
    print("Creating $project in local directory... ")
    run(`cp -r $(INSTALL_DIR)init_template $(working_dir)$project`)
    println(colorize(:green, "done"))
    exit()
end

# Get which directory we are working in
if !isempty(ARGS)
    if ARGS[1] == "init"
        create_project(ARGS[2])
    elseif ARGS[1][end] == "/"
        working_dir = ARGS[1]
    else
        working_dir = ARGS[1] * "/"
    end
else
    working_dir = pwd() * "/"
end

# Reads the settings file, and uses defaults it none are specified
function get_settings()
    settings = YAML.load_file(INSTALL_DIR * "settings.yaml")
    if isfile(working_dir * "settings.yaml")
        o_settings = YAML.load_file(working_dir * "settings.yaml")
    else
        o_settings = Dict()
    end

    # Overwrite the default variables
    if !isempty(o_settings)
        for k in keys(o_settings)
            settings[k] = o_settings[k]
        end
    end

    return settings
end

# Returns true if file has the .md extension. Keep things simple
function ismd(filename)
    # Do some "intelegant" extension checking
    return filename[end-2:end] == ".md" ? true : false
end

function isjl(filename)
    # Do some "intelegant" extension checking
    return filename[end-2:end] == ".jl" ? true : false
end

function compile(file)
    global SETTINGS

    # Let's standardize where the file goes
    if !isdir(working_dir * "out")
        mkdir(working_dir * "out")
    end
    outfile = file[1:end-3] * SETTINGS["out-format"]

    # Build the command
    cmd = `pandoc
        -s
        --template $(INSTALL_DIR)templates/template.latex
        --latex-engine=xelatex
        -H $(INSTALL_DIR)templates/$(SETTINGS["template"])/style.tex
        --biblio $working_dir/refs.bib
        --csl $(INSTALL_DIR)CLSs/$(SETTINGS["csl"])
        -V geometry:margin=$(SETTINGS["margins"])
        -V fontsize:$(SETTINGS["font-size"])
        $file
        -o ./out/$outfile`

    try
        run(cmd)
    catch e
        println()
        println(colorize(:red, "ERROR: Document did not compile!"))
        print(e)
    end
end

# pandoc
#   -H ./options/options.sty
#   --biblio ./paper/refs.bib
#   --csl ./styles/american-chemical-society-with-titles-no-et-al.csl
#   -V geometry:margin=1in
#   -V fontsize:12pt
#   ./paper/paper.md
#   -o ./paper/output/paper.tex
#   --latex-engine=latex

print("Loading settings...")
SETTINGS = get_settings()
println(colorize(:green, " done"))

println("Doing initial compiles...")
for file in readdir()
    if ismd(file)
        compile(file)
        println("\t$file")
    end
end
println(colorize(:green, "done"))

# For now assume we are compiling all .md files
watch_file(working_dir) do filename, events, status
    # show(filename)
    # show(events)
    # show(status)
    # println()
    if ismd(filename) && events.changed
        @async begin
            print("Recompiling $filename...")
            compile(filename)
            println(colorize(:green, " done"))
        end
        # Do stuff to compitle our md
    # elseif isjl(filename) && events.changed
    #     @async lintfile(filename)
    elseif filename == "settings.yaml" && events.changed
        @async begin
            print("Reloading setttings...")
            SETTINGS = get_settings()
            println(colorize(:green, " done"))
        end
    elseif ismd(filename) && events.renamed && isfile(working_dir * filename)
        @async begin
            print("Compiling $filename...")
            compile(filename)
            println(colorize(:green, " done"))
        end
    end
end

println("Stop with Ctl-C")
while true
    sleep(3)
end
