#Bartłomiej Sadowski #
function f(x)
	sin(x)+cos(3*x)
end

function f_approx(h)
	(f(1+h)-f(1))/h
end

function f_(h)
	cos(x)-3sin(3x)
end

i=1
x=1.0
println("przyblizone wartosi funkcji w x_0 =1")

while i<55
	x=x*1/2
	println("\hline" )
	println(f_approx(x),"&",f_(x),"& ",abs(f_(1.0)-f_approx(x)),"\\\\" )
	
	i+=1
end

println("blad przyblizenia")
i=1
x=1.0
while i<54
	x=x*1/2
	println(abs(f_(1)-f_approx(x)))
	i+=1
end
