type CircularArray{T,N}
	data::AbstractArray{T,N}
	cdim::Integer # dimension to cycle along
	cl::Integer # size of cycle dimension
	head::Integer # starting point of the array
end

# CONSTRUCTORS

function CircularArray(A,cdim)
	if cdim > ndims(A)
		error("A does not have enough dimensions to be indexed along dimension $c_dim")
	end
	CircularArray(A,cdim,size(A,cdim),1)
end

function CircularArray(A)
	CircularArray(A,ndims(A))
end

# helper function
function circ_slice(A::CircularArray, index...)
	slice = vcat([A.head:A.cl],[1:A.head-1])
	idx::Array{Any,1} = [i for i in index] # enables indexing by slicing, etc.
	idx[A.cdim] = slice[index[A.cdim]]
	return idx
end

# ACCESSOR
# colons dont seem to work in native julia getindex, setindex
function getindex(A::CircularArray, index...)
	idx = circ_slice(A,index...)
	getindex(A.data,idx...)
end



# MUTATORS
function setindex!(A::CircularArray, newdata, index...)
	idx = circ_slice(A,index...)
	setindex!(A.data,newdata,idx...) 
end

function advance_head!(A::CircularArray, offset::Integer)
	A.head += offset
end

function reset_head!(A::CircularArray)
	A.head = 1
end

