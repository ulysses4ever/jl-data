#Conducting the four experiments from figure 6.2 in Boyd and Vandenberghe (page 297)

using Convex
using PyPlot

x=Variable(100)

R=zeros(100)
for i=1:100 
	A=rand(100,100)*100 #A random 100x100 matrix, with values between 0 and 100
	b=rand(100,1) *100 #A random vector to try and fit

	problem = minimize(norm(A*x-b,2)^2)
	solve!(problem)
	R[i]=problem.optval
end
h = PyPlot.plt.hist(R,15)


for i=1:100 
        A=rand(100,100)*100 #A random 100x100 matrix, with values between 0 and 100
        b=rand(100,1) *100 #A random vector to try and fit

        problem = minimize(norm(A*x-b,1))
        solve!(problem)
        R[i]=problem.optval
end
j = PyPlot.plt.hist(R,15)

for i=1:100
        A=rand(100,100)*100 #A random 100x100 matrix, with values between 0 and 100
        b=rand(100,1) *100 #A random vector to try and fit

        problem = minimize(sum(max(abs(A*x-b)-.5,zeros(100,1))))
        problem.constraints= [A*x-b<=.5]
        solve!(problem)
        R[i]=problem.optval
end
l = PyPlot.plt.hist(R,15)



for i=1:100
        A=rand(100,100)*100 #A random 100x100 matrix, with values between 0 and 100
        b=rand(100,1) *100 #A random vector to try and fit


        problem = minimize(sum(-log(ones(100,1)-(A*x-b).^2)))
        problem.constraints=[A*x-b<=.5]
        solve!(problem)
        R[i]=problem.optval
end
k = PyPlot.plt.hist(R,15)

