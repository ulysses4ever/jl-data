function evaluate(t::Float64, y::Ptr{None}, ydot::Ptr{None}, p::Vector{Float64})
	
	# p[1] = mrna degredation
	# p[2] = protein translation
	# p[3] = prtoein degredation
	# p[4] = base transcription
	# p[5] = transcription
	# p[6] = KM
	# p[7] = Hill coeff

	y = Sundials.asarray(y)
    	ydot = Sundials.asarray(ydot)
	
	try

		ydot[1] = -p[1]*y[1] + p[4] + (p[5]*(p[6]^p[7]))/(p[6]^p[7]+y[4]^p[7])
		ydot[2] = -p[3]*y[2] + p[2]*y[1]
		ydot[3] = -p[1]*y[3] + p[4] + (p[5]*(p[6]^p[7]))/(p[6]^p[7]+y[6]^p[7])
		ydot[4] = -p[3]*y[4] + p[2]*y[3]
		ydot[5] = -p[1]*y[5] + p[4] + (p[5]*(p[6]^p[7]))/(p[6]^p[7]+y[2]^p[7])
		ydot[6] = -p[3]*y[6] + p[2]*y[5]
	
	catch
	end	

	return int32(0)
end
