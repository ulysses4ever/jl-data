#Count the frequency of single item

# "Map" function.
# Takes a string. Returns a Map with the number of each item.
function map_count(text)
    items=split(text,[' ','\n','\t','-','.',',',':','_','"',';','!'])
    counts=Dict{ASCIIString, Int64}()
    for item in items
        counts[item]=get(counts,item,0)+1
    end
    return counts
end

# "Reduce" function.
# Takes a collection of Map in the format returned by map_count()
# Returns a Map in which words that appear in multiple inputs have their totals added together.
function reduce_count(item_counts)
    reduced_counts = Dict{ASCIIString, Int64}()
    for item_count in item_counts
        for (item,count) in item_count
            reduced_counts[item] = get(reduced_counts,item,0)+count
        end
    end
    return reduced_counts
end

# Splits input string into nprocs() equal-sized chunks (last one rounds up), 
# and @spawns wordcount() for each chunk to run in parallel. Then fetch()s
# results and performs wcreduce().
function parallel_item_count(text)
    lines=split(text,'\n',false)
    np=nprocs()
    unitsize=ceil(length(lines)/np)
    item_counts={}
    rrefs={}
    # spawn procs
    for i in 1:np
        first=unitsize*(i-1)+1
        last=unitsize*i
        if last>length(lines)
            last=length(lines)
        end
        subtext=join(lines[int(first):int(last)],"\n")
        push!(rrefs, @spawn map_count( subtext ) )
    end
    # fetch results
    while length(rrefs)>0
        push!(item_counts,fetch(pop!(rrefs)))
    end
    # reduce
    count=reduce_count(item_counts)
    return count
end


function single_item_count(result_file,input_file_names...)
    text=""
    for f in input_file_names
        fh=open(f)
        text=join( {text,readall(fh)}, "\n" )
        close(fh)
    end
    return parallel_item_count(text)
end
