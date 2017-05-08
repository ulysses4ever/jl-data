module prefElicitation

export prefEl

importall Base

# Support for 32 bit machines
F = typeof(1.0)

# Main type to hold all our data
type prefEl
	data::Array{F,2}
	preferences::Array{Int,2}
	sense::Symbol
end
prefEl(data; preferences = zeros(Int,0,2), sense = :Max) = prefEl(data,preferences,sense)

function show(io::IO,prefEl::prefEl)
	println("test")
end

end