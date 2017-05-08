
include("concordance.jl")

text = ""
if !isempty(ARGS)
    text = readall(ARGS[1])
else
    text = readline(STDIN)
end

println("\n>Running concordance on:")
println(text)

c = concordance(text)

println("\n>Results:")
show(c)
