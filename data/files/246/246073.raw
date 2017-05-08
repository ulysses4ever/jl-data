export coefficient
typealias Danacoefficient DanaRealParametric
type _coefficient
	function _coefficient(_::Dict{Symbol,Any})
		fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
		fields[:Brief]="General Coefficient"
		fields[:Default]=1
		fields[:Lower]=-50
		fields[:Upper]=50
		drive!(fields,_)
		new(fields)
	end
	value::Dict{Symbol,Any}
end
typealias coefficient DanaRealParametric{_coefficient}