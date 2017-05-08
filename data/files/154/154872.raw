x =    [2.718281828,-3.141592654,1.414213562,0.5772156649,0.3010299957]
y =   [1486.2497,878366.9879,-22.37492,4773714.647,0.000185049]
z= [0.0 ,0.0 ,0.0 ,0.0 ,0.0 ]
i=length(x)
j=length(y)

sum= (0.0)
sumUP= (0.0)
sumDOWN= (0.0)
suma= (0.0)
sumb= (0.0)

counter=1

while counter<=i

	z[counter]=(x[counter]*y[counter])
	println(x[counter]," ",y[counter]," ",z[counter]) 
	suma+=z[counter]
	counter+=1
end
counter=i
while counter>0
	sumb+=z[counter]
	counter-=1
end

counter=1
z=sort(z,rev=true)

sumUP=z[1]
sumUP+=z[2]
sumUP+=z[3]
sumDOWN+=z[5]
sumDOWN+=z[4]

sum=sumUP+sumDOWN

println(z[1:end])
println(suma)
println(sumb)
println(sum)

sumUP=z[3]
sumUP+=z[2]
sumUP+=z[1]
sumDOWN+=z[4]
sumDOWN+=z[5]

sum=sumUP+sumDOWN
println(sum)
counter =i
sum=0
while counter>0
	sum+=z[counter]
	counter-=1
end

