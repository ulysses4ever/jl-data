##
# Searching
##########################################################

require("ccconsts.jl")
require("ccutils.jl")

function search_part_idx(file, terms::Array, op="and")
    ## YOUR CODE HERE ##

    # useful functions: get, Set, IntSet, union, intersect, union!, add!
    ind=JSON.parse(open(readall,file))
    jj=Set()
    for i=1:length(terms)
    	if i==1
		jj=get(ind,terms[i],"false")
    	else
		jj=intersect(jj,get(ind,terms[i],"false"))
    	end
    end
    close(f) 
    return jj

end

function search_part_idx(file, terms::Array, op="or")
    ## YOUR CODE HERE ##

    # useful functions: get, Set, IntSet, union, intersect, union!, add!
    ind=JSON.parse(open(readall,file))
    jj=Set()
    for i=1:length(terms)
    	if i==1
		jj=get(ind,terms[i],"false")
    	else
		jj=union(jj,get(ind,terms[i],"false"))
    	end
    end
    close(f) 
    return jj

end

function search_part_idx(file, terms::Array)
    ## YOUR CODE HERE ##

    # useful functions: get, Set, IntSet, union, intersect, union!, add!
    ind=JSON.parse(open(readall,file))
    jj=Set()
    for i=1:length(terms)
    	if i==1
		jj=get(ind,terms[i],"false")
    	else
		jj=union(jj,get(ind,terms[i],"false"))
    	end
    end
    close(f) 
    return jj

end

function search_index(terms::String)
    sd = StringDocument(terms)
    td = preprocess(sd)
    terms = tokens(td)
    terms = filter(tok->!isempty(tok), terms)

    # The Blocks library provides many ways to divide work among processors.
    # Here, we call it on the part_idx_location directory, which tells it to
    # divide up the files in that directory.
    # The call localpart(master_idx) returns a list of files to be handled
    # by the calling processor.

    master_idx = Block(File(part_idx_location), false, 2)

    ## YOUR CODE HERE ##
    locallist=localpart(master_idx)
    for i=1:length(locallist)
	if terms[search(terms,"and")]=="and"
		search_part_idx(strip(string(locallist[i])),split(replace(terms,"and","")),"and")
	if terms[search(terms,"or")]=="or"
		search_part_idx(strip(string(locallist[i])),split(replace(terms,"or","")),"or")
    	else
		search_part_idx(strip(string(locallist[i])),split(terms))
	end
    end    

    println("results:\n$result_docs")
end
