##
# Searching
##########################################################

require("ccconsts.jl")
require("ccutils.jl")

function search_part_idx(file, terms::Array, op)
    ## YOUR CODE HERE ##

    # useful functions: get, Set, IntSet, union, intersect, union!, add!
    (ind,doc)=as_deserialized(file)
    jj=Set()
    if op=="and"
	for i=1:length(terms)
    		if i==1
			jj=get(ind,terms[i],"false")
    		else
			jj=intersect(jj,get(ind,terms[i],"false"))
    		end
    	end
    else
    	for i=1:length(terms)
    		if i==1
			jj=get(ind,terms[i],"false")
    		else
			jj=union(jj,get(ind,terms[i],"false"))
    		end
    	end
    end
    return doc[jj]

end

function search_index(terms::String)
#    sd = StringDocument(terms)
#    td = preprocess(sd)
#    terms = tokens(td)
#    terms = filter(tok->!isempty(tok), terms)

    # The Blocks library provides many ways to divide work among processors.
    # Here, we call it on the part_idx_location directory, which tells it to
    # divide up the files in that directory.
    # The call localpart(master_idx) returns a list of files to be handled
    # by the calling processor.

    #master_idx =Blocks(File(part_idx_location), false, 2)

    ## YOUR CODE HERE ##
    #locallist=localpart(master_idx)
    locallist=readdir(part_idx_location)
    println(locallist)
    result_docs=Array(Any,1)
    
    for i=1:length(locallist)
	if terms[search(terms,"and")]=="and"
		result_docs=search_part_idx(joinpath(part_idx_location,locallist[i]),split(replace(terms,"and","")),"and")
	elseif terms[search(terms,"or")]=="or"
		result_docs=search_part_idx(joinpath(part_idx_location,locallist[i]),split(replace(terms,"or","")),"or")
   	else
		result_docs=search_part_idx(joinpath(part_idx_location,locallist[i]),split(terms))
	end
    end    

    println("results:\n$result_docs")

end
