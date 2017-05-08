#Conducting the four experiments from figure 6.2 in Boyd and Vandenberghe (page 297)

using Convex
using PyPlot
using SCS

x=Variable(100)

	A=rand(100,100)*100 #A random 100x100 matrix, with values between 0 and 100
	b=rand(100,1) *100 #A random vector to try and fit

	problem = minimize(norm(A*x-b,2)^2)
	solve!(problem)
h = plot(A*x.value-b)



        problem = minimize(norm(A*x-b,1))
        solve!(problem)
j = plot(A*x.value-b)


        problem = minimize(sum(max(abs(A*x-b)-.5,zeros(100,1))))
        problem.constraints= [A*x-b<=.5]
        solve!(problem)
end
l = plot(A*x.value-b)





        problem = minimize(sum(-log(ones(100,1)-(A*x-b).^2)))
        problem.constraints=[A*x-b<=.5]
        solve!(problem)
k = plot(A*x.value-b)

