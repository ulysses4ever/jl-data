##  EXAMPLE: HILBERT MATRIX IS ILL-CONDITIONED

n = 10

A = Array (Float64, n, n)				# using Rational here...
for i in 1:n, j in 1:n
	A [i,j] = 1.0 / (i+j-1)				# and // here... make no difference
	end
x = ones (Float64, n)					# x [:] = linspace (10//1, 10//1, 10) makes no difference
b = A * x
luf = lu (A)
inv (luf[2]) * inv (luf[1]) * b [luf[3]]


A = Array (Float32, n, n)				# but Float32 vs Float64 makes a big difference
for i in 1:n, j in 1:n
	A [i,j] = 1.0 / (i+j-1)
	end
x = ones (Float32, n)
b = A * x
luf = lu (A)
inv (luf[2]) * inv (luf[1]) * b [luf[3]]

n = 14
A = Array (Float64, n, n)				# and n=14 instead of 10 makes a HUGE difference
for i in 1:n, j in 1:n
	A [i,j] = 1.0 / (i+j-1)
	end
x = ones (Float64, n)
b = A * x
luf = lu (A)
inv (luf[2]) * inv (luf[1]) * b [luf[3]]




