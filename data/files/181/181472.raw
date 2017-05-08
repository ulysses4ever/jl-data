a = [4,2,3,1]
sort(a) #out-of-place/non-mutating sort
sort!(a) # in-place/mutating sort
sort([2,3,1], rev=true)
p = sortperm(a) #compute a permutation to put array into sorted order
sort(a, by=abs) #sort ac. to arbitrary transformation of values
sort(v, alg=InsertionSort) #chose insertion sort

# build-in sort
A = [("UK", "London"), ("US", "New York"), ("US", "Birmingham"), ("UK", "Birmingham")];
sort(A, by=x -> x[2])
###
4-element Array{(ASCIIString,ASCIIString),1}:
 ("US","Birmingham")
 ("UK","Birmingham")
 ("UK","London")
 ("US","New York") 
###