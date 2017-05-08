# ArgParse: Module for command-line argument parse //argparse.jl

using ArgParse

s = ArgParseSettings()
@add_arg_table s begin
  "filename"
    help = "a filename from which to read in text"
    arg_type = String
    required = true
end
args = parse_args(s)

# get words
f = open(args["filename"],"r")
str = readall(f)
words = split(str)

# count words
counts = Dict{String,Int}()
for w in words
  w = lowercase(w)
  counts[w] = get(counts,w,0) + 1
end

# get top 10 most common words
counts = [(k,v) for (k,v) in counts]
sort!(counts;by=(x->x[2]))
top10 = [pop!(counts) for x=1:(min(10,length(counts)))]
top10 = map(x->repr(x[1]),top10)
top10[end] = "and $(top5[end])"

# print summary
println("There are $(length(words)) words in that file.")
println("The ten most used words are: $(join(top10,", ")).")
