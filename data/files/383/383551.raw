function stopBleeding(t,stoptime,data_dictionary)
	if(t>stoptime)
		data_dictionary["FLOW_PARAMETER_ARRAY"][13] = 0.0 #wound_to_degredation: wound -> []
		data_dictionary["FLOW_PARAMETER_ARRAY"][12] = data_dictionary["FLOW_PARAMETER_ARRAY"][11] #set flow into wound the same as flow out
		data_dictionary["FLOW_PARAMETER_ARRAY"][9] =  data_dictionary["FLOW_PARAMETER_ARRAY"][10] #match flow from bulk_to_vein as flow from artery_to_bulk 
	end
	return data_dictionary

end

function stopBleedingSlowly(t,stoptime,data_dictionary)
	#let's assume that bleeding stops over a period of 5 minutes, starting at stoptime
	stopPeriod = 15.0
	if(t> stoptime && t<stoptime+stopPeriod)
		#@show t
		wound_to_degredation_final = 0
		artery_to_wound_reverse_final = data_dictionary["FLOW_PARAMETER_ARRAY"][11]
		artery_to_bulk_final = data_dictionary["FLOW_PARAMETER_ARRAY"][10]

		wound_to_degredation_initial = 0.0015
		artery_to_wound_reverse_initial = 0.0005
		artery_to_bulk_initial =  0.597

		changeWound = (wound_to_degredation_final-wound_to_degredation_initial)/stopPeriod
		#@show changeWound
		data_dictionary["FLOW_PARAMETER_ARRAY"][13] = wound_to_degredation_initial +t*changeWound
		#@show data_dictionary["FLOW_PARAMETER_ARRAY"][13]
		changeArteryWound = (artery_to_wound_reverse_final-artery_to_wound_reverse_initial)/stopPeriod
		data_dictionary["FLOW_PARAMETER_ARRAY"][12]=artery_to_wound_reverse_initial+changeArteryWound*t
		#@show data_dictionary["FLOW_PARAMETER_ARRAY"][12]
		changeArteryBulk = (artery_to_bulk_final -artery_to_bulk_initial)/stopPeriod
		data_dictionary["FLOW_PARAMETER_ARRAY"][9]=artery_to_bulk_initial+changeArteryBulk*t
		#@show data_dictionary["FLOW_PARAMETER_ARRAY"][9]

	elseif(t>stoptime+stopPeriod)
		data_dictionary["FLOW_PARAMETER_ARRAY"][13] = 0.0 #wound_to_degredation: wound -> []
		data_dictionary["FLOW_PARAMETER_ARRAY"][12] = data_dictionary["FLOW_PARAMETER_ARRAY"][11] #set flow into wound the same as flow out
		data_dictionary["FLOW_PARAMETER_ARRAY"][9] =  data_dictionary["FLOW_PARAMETER_ARRAY"][10] #match flow from bulk_to_vein as flow from artery_to_bul
	end


	return data_dictionary
end
