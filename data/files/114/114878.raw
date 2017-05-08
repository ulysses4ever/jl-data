# File Operations

# File type for reading direct from file

#Search Directory and filter by extension

type Files
    dir::String
    names::Array{}

    function Files(dir::String, names::Array{})
        new(dir, names)
    end

    function Files(names::Array{})
        dir = split(names[1], "/")[end]
        new(dir, names)
    end

    function Files(dir::String, filter=r"")
        names = String[]
        dirs = String[]

        push!(dirs,dir)

        c(a,b) = string(a, "/", b)

        try
            readdir(dir)
            while(length(dirs)>0)
                d = pop!(dirs)
                try
                    ns = readdir(d)
                    for name in ns
                        push!(dirs, c(d, name))
                    end
                catch
                    if ismatch(filter,d)
                        push!(names, d)
                    end
                end

            end
        catch
            push!(names, dir)
        end

        new(dir, names)
    end
end

# Helper functions

function _to_array(r::Range1)
    a=Int[]
    for i in r
        push!(a, i)
    end
    return a
end

function _search_all(string::String, text::String, overlap=false)
    indic=Array[]
    i = 1
    while true
        rang =  (search(text, string, i))
        if length(rang)>0
            inds = [rang[1],rang[end]]
            push!(indic, inds)
            if overlap
                i = indic[end][2]
            else
                i = indic[end][end]
            end
        else
            return indic
        end
    end
end

###### Front end #######

# General functions

# IO operations

function load_files(name::String)
    f = open(name)
    text = readall(f)
    close(f)
    return text
end

function load_files(names::Array)
    texts = String[]
    if length(names)==1
        return load_files(names[1])
    end
    for name in names
        push!(texts, load_files(name))
    end
    return texts
end


load_files(files::Files) = return load_files(files.names)

function to_file(name::String, list_texts::Array, nl="\n")
    # Write grep_context output to a file

    f = open(name, "w")
    for text in list_texts
        write(f, string(text, nl))
    end
    close(f)
end

#function to_file(name::String, collo::Collocation, nl="\n")
#end
