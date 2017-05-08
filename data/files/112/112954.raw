module Utils

macro inject(x::Symbol)
    t = eval(x)
    @assert isa(t, DataType)
    returnValue = Expr[]
    for i =1:length(t.types)
        push!(returnValue, Expr(:(::), t.names[i], t.types[i].name.name))
    end
    esc((Expr(:block, returnValue...)))
end



foreach(func::Function, collection) = for elem in collection; func(elem); end

function mapvalues(func::Union(Function, Base.Func), collection::Dict)
   [key => func(value) for (key, value) in collection]
end
function mapkeys(func::Union(Function, Base.Func), collection::Dict)
   [func(key) => value for (key, value) in collection]
end
# Simple file wrapper, which encodes the type of the file in its parameter
# Usefull for file IO
immutable File{Ending}
  abspath::UTF8String
end
File(folders...) = File(joinpath(folders...))
function File(file)
  @assert !isdir(file) "file string refers to a path, not a file. Path: $file"
  file  = abspath(file)
  path  = dirname(file)
  name  = file[length(path):end]
  ending  = rsearch(name, ".")
  ending  = isempty(ending) ? "" : name[first(ending)+1:end]
  File{symbol(ending)}(file)
end

Base.open(x::File)    = open(abspath(x))
Base.abspath(x::File) = x.abspath


function print_with_lines(text::AbstractString)
    for (i,line) in enumerate(split(shadercode, "\n"))
        @printf("%-4d: %s\n", i, line)
    end
end

end # module
