using LibExpat

filename = ARGS[1]

node_ids = Set{String}()
used_node_ids = Set{String}()

cbs = XPCallbacks()
cbs.start_element = function (handler::XPStreamHandler, name::String, attrs::Dict{String,String})
    if name == "edge"
        push!(used_node_ids, attrs["source"])
        push!(used_node_ids, attrs["target"])
    end

    if name == "node"
        push!(node_ids, attrs["id"])
    end
end

xp_streaming_parsefile(filename, cbs)

unused_nodes = setdiff(node_ids, used_node_ids)
@printf("Removing %d vertices\n", length(unused_nodes))

mv(filename, string(filename,"-tmp"))
infile = open(string(filename,"-tmp"), "r")
outfile = open(filename, "w")

node_re = r"\<node id=\"([^\"]*)\""

while !eof(infile)
    line = readline(infile)

    # We are exploiting the fact that we know how the generated XML looks like
    m = match(node_re, line)
    if m != nothing
        id = m.captures[1]
        if in(id, unused_nodes)
            continue
        end
    end

    write(outfile, line)
end

close(infile)
close(outfile)
rm(string(filename,"-tmp"))

