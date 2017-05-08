#!/usr/bin/julia

println("converter from degrees to radians")
println("----------------------------------")
running = true

while running
	println()
	print("enter degrees <enter to exit>:")
	try 
		t = readline(STDIN)
		d = parsefloat(t)
		println("$(d*pi/180) radians")
       catch e
		running = false
		println("exit upon ",e)
      end
end
