#=
Bartłomiej Sadowski
=#
x =  [2.718281828,-3.141592654,1.414213562,0.5772156649,0.3010299957]
y =  [1486.2497,878366.9879,-22.37492,4773714.647,0.000185049]

i=length(x)
j=length(y)
sumUP=float32(0.0)
sumDOWN=float32(0.0)
sumMAX1=float32(0.0)
sumMIN1=float32(0.0)
sumMAX2=float32(0.0)
sumMIN2=float32(0.0)

counter=1

while counter<=i

	sumUP=float32(sumUP+float32(x[counter]*y[counter]))
	counter+=1
end

counter=i

while counter>=1
	 
	sumDOWN=float32(sumDOWN+float32(x[counter]*y[counter]))
	counter=counter-1
end

println("suma a ",sumUP," suma b ", sumDOWN) 
###########################################################################
z=append!(x,y)
z=sort(z,rev=true)
counter=1;

while counter<=(i+j)
	if z[counter]>0
		sumMAX1=float32(sumMAX1+z[counter])
	else
		sumMIN1=float32(sumMIN1+z[counter])
end
	counter=counter+1
end

counter=i+j


while counter>=1
	 
	if z[counter]>0
		sumMIN2=float32(sumMIN2+z[counter])
	else
		sumMAX2=float32(sumMAX2+z[counter])
end
	counter=counter-1
end

println("suma c ",sumMAX1*sumMAX2," \n suma d",sumMIN1*sumMIN2)

