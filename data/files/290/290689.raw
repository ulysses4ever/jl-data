# Demo the usage of IPPCore functions

using IPPCore

# library version

println(ippversion())
println()

# status -> message

for i = 0:9
	msg = ippstatus_string(i)
	println("Status code $i ==> $msg")
end
println()

# cpu information

println("CPU: $(ippcpudescr())")
# println("CPU Freq: $(ippcpufreq()) MHz")
println()
