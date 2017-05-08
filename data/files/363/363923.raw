function printsum(a)
	# summary generates summary of object
	println(summary(a), ": ", repr(a))
end

# initialize directly
a1 = [1, 2, 3]
printsum(a1)

# empty array
a2 = []

#if an array has no type then functions cannot work on them
a3 = Int64[]

# ranges are not arrays
a4 = 1:20

# but can be used to create arrays
a4 = [1:20]

# also can be generated from comprehensions
a5 = [2^i for i = 1:10]

#arrays are of any type so arrays of arrays
# these are also refered to as jagged arrays
a6 = (Array{Int64, 1,})[]

push!(a1, 4)

push!(a3, 1)

push!(a6, [1,2,3])

# using repeat to create arrays
a7 = repeat(a1, inner= [2], outer = [1])
a8 = repeat([4:-1:1], inner=[1], outer=[2])

#error handeling

a = []
# use try and catch

try 
	push!(a,1)
catch err
	showerror(STDOUT, err, backtrace()); println()
end

# multidimensional arrays
# repeat can be used like R's grid expand

m1 = hcat(repeat([1:2], inner=[1], outer=[3*2]),
	      repeat([1:3], inner=[2], outer=[2]),
	      repeat([1:4], inner=[3], outer=[1]))

# replicate arrays
m2 = repmat(m1, 1, 2 )

m3 = repmat(m1, 2, 1)

# make multidemensional array
m4 = [i + j + k for i = 1:2, j=1:3, k=1:2] # 64 bit array

m5 = ["hi im # $(i+2*(j-1 + 3*(k-1)))" for i=1:2, j=1:3, k=1:2]
m5 = ASCIIString["hi im # $(i+2*(j-1 + 3*(k-1))" for i=1:2, j=1:3, k=1:2]
printsum(m5)

sum(m4, 3)
sum(m4, (1,3))
maximum(m4, 2)
findmax(m4, 3)

# add three to all element in the array
m4 .+ 3
m4 .+ [1:2]

# get slices
m4[:,:,1] # holds dim 3 fixed 
m4[:,2,:] 

# get rid of dimensions size 1
squeeze(m4[:,2,:], 2) 

# assign new values to a certain view
m4[:,:,1] = rand(1:6, 2, 3)








