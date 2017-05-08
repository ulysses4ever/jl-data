#!/usr/bin/julia

println("Code Generation")
println("-------------------------")

#this is already done in Base module so we will be getting a warning.
for op = (:+, :*, :&, :|, :$)
  eval(:(($op)(a,b,c) = ($op)(($op)(a,b),c)))
end

println(*(2,3,4))

quit()

s = 13
radians = convert(Float64,.75)

array = zeros(Int128,s,s)
array[1,1] = 1
array[2,2] = 1
r = 3
expr = :(0)
while r<=s
   c = 1   
   while c<=r 
      #two times one up and to the left
	  t = c <= 1 ? 0 : 2*array[r-1,c-1]
      #minus value two rows above
	  if (r>2)
	  	t = t - array[r-2,c]
      end
      array[r,c] =  t
	  if t!=0 && r==s
		expr = :(($expr)+(($t)x^($(c-1))))
	  end
	  c=c+1
   end
   r=r+1
end
eval(:(multiAngleCos(x) = ($expr)   )    ) 	
println(array)

fraction = radians/(s-1);

println("computed cos($(radians)) from cos($(fraction)) using $(s-1) angle formula.")

v1 = cos(radians)
v2 = multiAngleCos(cos(fraction))
println("v1:",v1)
println("v2:",v2)
println("dif:$(v1-v2)")

println(expr)



