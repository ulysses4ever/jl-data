##  JULIA QUICK REFERENCE

help()									# help
help(help)
help(transpose)
help(Base.transpose)

apropos("BLAS")

exit()									# misc system
gethostname()
pwd()	;	cd("..")	;	normpath("/.../.../....")
whos()									# show object space
ans
edit(func)		;		edit("file")
readcsv(...)
readdlm(...)

help(Base.error)						# exceptions / errors
help(Base.strerror)
help(Base.assert)
error("foo")
Base.error("foo")
assert(1)

methods(print)							# object inspection
which(print, "argument")				# which method will be called?
println(...)
ndims(...)
size(...)
length(...)
typeof(...)


Pkg.add("TensorOperations")				# packages
Pkg.update()

using TensorOperations, [package], [package]


#  type taxonomy, constructing constants

0x1f						# hex
1+2im						# complex
1 // 4						# rational
BigInt(0)					# arbitrary precision
eps(BigFloat(0))			# not arbitrary precision...?

1:5			;		reverse(1:5)		# range (< "iterable")
1:2:10		;		2:2:10				# odds and evens
linspace(1,5,5)							# array
a = ones(Int32,(4,4))					# 2-d array
'a' + 1									# character
(1,2,3)									# tuple
[1,2,3]									# array of three elements
{1,2,3}									# 'untyped' array (actually type "Any")
[1:3]									# same
rand(10)
rand(Int32,10,10)
eye(Int64, 10)									# identity matrix

nextfloat(0)				# error
nextfloat(0.)				# ok
nextfloat(nextfloat(0.))	# interesting to repeat a while
eps(Float64)

deepcopy(...)

#  matrix computation

b = a + a								# matrix (ident with 2-d array) arithmetic
a'			# transpose
a*b			# matrix mult (not Hadamard)
a/b			# linear solve
lu(
dot(
schurfact(
eig(
eigvec(
trace(
(u,s,v) = svd(rand(5,6))
norm(				# p-norm, default p=2


reshape(ones(Int32,(4,4)),(2,8))
reshape(ones(Int32,(4,4)),(2,10))

a=reshape(1:16, (4,4))
a[15]			# valid
a[1][1]			# valid
a[1][1][1]		# valid
a[1,1]			# valid
a[1:2]			# valid
a[(1,2)]		# not
a[1:2,]			# valid but does NOT get all columns
a[1:2,1:4]		# valid
stride(a,1)
stride(a,2)


#  programming

for i=1:10							# loop
	print(i)
	end

function f(x)						# function
       x^2
       end

[trace(rand(n,n)) for n=1:5]		# comprehensions
[i+j for i=1:5,j=5:10]
{eye(n) for n=1:5}




# other

factorial(6)



a[[1,2,3]]
Array(1:16,(4,4))





