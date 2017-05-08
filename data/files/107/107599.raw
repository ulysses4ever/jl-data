
exists(path) = stat(path).inode != 0

"""this package assumes [x,y] indexing, with x varying fastest and
origin bottom left.  this is not how julia displays matrices (not at
all), so things can be confusing if you use "print" on raw structures.
this function converts for display."""
fix{T}(x::Array{T, 2}) = x'[size(x)[1]:-1:1,:]
