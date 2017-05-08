function changeHRBasedOnBleedOut(t,bleedoutrate)
	#values from Cardiovascular and endocrine responses to haemorrhage in the pig
	HR = 0.0
	bloodvolume = 6.234 #L
	restingHR = 100.0 #bpm
	timeto10percentloss = bloodvolume*.1/bleedoutrate
	timeto15percentloss = bloodvolume*.15/bleedoutrate
	timeto30percentloss = bloodvolume*.30/bleedoutrate

	if(t>timeto30percentloss)
		HR = 206
	elseif(t > timeto15percentloss)
		HR = 95
	elseif(t >timeto10percentloss)
		HR = 113
	else
		HR = restingHR
	end
	return HR

end

function changeNorBasedOnHR(t,HR)
	if HR > 120
		Cnor = .5+(t-20)/20
	else
		Cnor = .5
	end

	return Cnor
end

function changeBPBasedOnBleedOut(t,bleed_out_rate)
	
end
