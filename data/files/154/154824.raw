#=
Bartłomiej Sadowski
=#
x =  [2.718281828,-3.141592654,1.414213562,0.577215664,0.301029995]
y =  [1486.2497,878366.9879,-22.37492,4773714.647,0.000185049]

i=length(x)
j=length(y)
sumUP=0.0
sumDOWN=0.0
sumMAX1=0.0
sumMIN1=0.0
sumMAX2=0.0
sumMIN2=0.0

counter=1

while counter<=i

	sumUP=sumUP+x[counter]*y[counter]
	counter+=1
end

counter=i

while counter>=1
	 
	sumDOWN=sumDOWN+x[counter]*y[counter]
	counter=counter-1
end

println("suma UP ",sumUP," suma DWON ", sumDOWN) 
###########################################################################
z=append!(x,y)
z=sort(z,rev=true)
counter=1;

while counter<=(i+j)
	if z[counter]>0
		sumMAX1=sumMAX1+z[counter]
	else
		sumMIN1=sumMIN1+z[counter]
end
	counter=counter+1
end

counter=i+j


while counter>=1
	 
	if z[counter]>0
		sumMIN2=sumMIN2+z[counter]
	else
		sumMAX2=sumMAX2+z[counter]
end
	counter=counter-1
end

println("suma c ",sumMAX1*sumMAX2," \n suma d",sumMIN1*sumMIN2)

