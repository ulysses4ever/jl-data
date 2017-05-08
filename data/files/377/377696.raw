#!/usr/bin/julia
#adding new signature to this function requires import
import Base.readline

readline(f, io, prompt = "enter degrees <enter to exit>:") =  
	begin 
		print(prompt); 
		f(readline(io)) 
	end

println("converter from degrees to radians")
println("----------------------------------")

while readline(STDIN) do t
		try
			d = parsefloat(t)
			println("$(d*pi/180) radians")	
			return true
		catch e
			println("exit upon ",e)
			return false
		end
	end
end


# f(x) = x*2
# map(f,[1,2,3])
#
# map([1,2,3]) do x return x*2 end
