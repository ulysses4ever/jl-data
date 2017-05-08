#Count the frequency of item pairs

# "Map" function.
# Takes a string. Returns a Map with the number of each item.
function map_candidate_pair(item_counts, hash_type, text)
    baskets = split(text, ['\n'])
    counts=Dict{ASCIIString, Int64}()
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
            	if hash_type == "small_key"
                	hashKey = min(frequent_items[i], frequent_items[j])
                end
                
                if hash_type == "large_key"
                	hashKey = max(frequent_items[i], frequent_items[j])
                end
                
                if hash_type == "sum_keys"
                	hashKey = string( int(frequent_items[i]) + int(frequent_items[j]) )
                end
                
                counts[hashKey] = get(counts, hashKey, 0) + 1
            end
        end
    end
    return counts
end

# "Reduce" function.
# Takes a collection of Map in the format returned by map_count()
# Returns a Map in which pairs that appear in multiple inputs have their totals added together.
# Combine same pairs with different order, e.g., [1,2] and [2,1]
function reduce_candidate_pair(hash_counts)
    reduced_counts = Dict{ASCIIString, Int64}()
    for hash_count in hash_counts
        for (hashKey,count) in hash_count
            reduced_counts[hashKey] = get(reduced_counts,hashKey,0)+count
        end
    end
    return reduced_counts
end

# Splits input string into nprocs() equal-sized chunks (last one rounds up), 
# and @spawns wordcount() for each chunk to run in parallel. Then fetch()s
# results and performs wcreduce().
function parallel_candidate_pair(item_counts, hash_type, text)
    lines=split(text,'\n',false)
    np=nprocs()
    unitsize=ceil(length(lines)/np)
    hash_counts={}
    rrefs={}
    # spawn procs
    for i in 1:np
        first=unitsize*(i-1)+1
        last=unitsize*i
        if last>length(lines)
            last=length(lines)
        end
        subtext=join(lines[int(first):int(last)],"\n")
        push!(rrefs, @spawn map_candidate_pair(item_counts,hash_type, subtext))
    end
    # fetch results
    while length(rrefs)>0
        push!(hash_counts,fetch(pop!(rrefs)))
    end
    # reduce
    count=reduce_candidate_pair(hash_counts)
    return count
end



function candidate_pair(item_counts,hash_type, input_file_names...)
    text=""
    for f in input_file_names
        fh=open(f)
        text=join( {text,readall(fh)}, "\n" )
        close(fh)
    end
    return parallel_candidate_pair(item_counts,hash_type,text)
end