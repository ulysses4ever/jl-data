#Count the frequency of item pairs

# "Map" function.
# Takes a string. Returns a Map with the number of each item.
function map_count_pair(item_counts, text)
    baskets = split(text, ['\n'])
    counts=Dict{(ASCIIString, ASCIIString), Int64}()
    for basket in baskets
        items = split(basket,[' ','\n','\t','-','.',',',':','_','"',';','!'])
        frequent_items = {}
        for item in items
            if haskey(item_counts, item)
                push!(frequent_items, item)
            end
        end
        len = length(frequent_items)
        for i = 1 : len-1
            for j = i+1 : len
                pair = (frequent_items[i], frequent_items[j])
                counts[pair] = get(counts, pair, 0) + 1
            end
        end
    end
    return counts
end

# "Reduce" function.
# Takes a collection of Map in the format returned by map_count()
# Returns a Map in which pairs that appear in multiple inputs have their totals added together.
# Combine same pairs with different order, e.g., [1,2] and [2,1]
function reduce_count_pair(pair_counts)
    reduced_counts = Dict{(ASCIIString, ASCIIString), Int64}()
    for pair_count in pair_counts
        for (pair,count) in pair_count
            reduced_counts[pair] = get(reduced_counts,pair,0)+count
        end
    end
    # Removed duplicated pairs (with different orders)
    for (pair, count) in reduced_counts
        reverse = (pair[2], pair[1])
        if haskey(reduced_counts, reverse)
            reduced_counts[reverse] += reduced_counts[pair]
            delete!(reduced_counts, pair)
        end
    end
    return reduced_counts
end

# Splits input string into nprocs() equal-sized chunks (last one rounds up), 
# and @spawns wordcount() for each chunk to run in parallel. Then fetch()s
# results and performs wcreduce().
function parallel_item_pair_count(item_counts, text)
    lines=split(text,'\n',false)
    np=nprocs()
    unitsize=ceil(length(lines)/np)
    pair_counts={}
    rrefs={}
    # spawn procs
    for i in 1:np
        first=unitsize*(i-1)+1
        last=unitsize*i
        if last>length(lines)
            last=length(lines)
        end
        subtext=join(lines[int(first):int(last)],"\n")
        push!(rrefs, @spawn map_count_pair(item_counts, subtext))
    end
    # fetch results
    while length(rrefs)>0
        push!(pair_counts,fetch(pop!(rrefs)))
    end
    # reduce
    count=reduce_count_pair(pair_counts)
    return count
end

# Build item pairs for the frequent single items.
# Input is a map of {item, count}.
# Output is an array of item pairs(arrays). [1,2] and [2,1] are viewed
# as one pair and only stored once in the output array
function build_pairs(item_counts)
    # First store the item IDs in an array
    len = length(item_counts)
    item_list = Array(ASCIIString, len)
    idx = 1
    for (item, count) in item_counts
        item_list[idx] = item
        idx += 1
    end
    # Then build item pairs and store them in the item_pair set
    item_pairs = Set()
    for i = 1:len
        if i < len
            for j = i+1:len
                push!(item_pairs, [item_list[i], item_list[j]])
            end
        end
    end
    return item_pairs          
end


function item_pair_count(item_counts,input_file_names...)
    text=""
    for f in input_file_names
        fh=open(f)
        text=join( {text,readall(fh)}, "\n" )
        close(fh)
    end
    return parallel_item_pair_count(item_counts, text)
end
