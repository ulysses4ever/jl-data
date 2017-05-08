function changeVolume(t,Cach,Cnor,V0,compartment_name)
#	dr = (3*V0/(4*pi))^(1/3) #assume everything is a sphere
#	AcrossSectional = V0/dr
#	S50 = 77# mircomolar (log mol/L)^-1
#	wAch = 146.2074 #g/mol

#	normalAchPresentMass = 1264E-15 #g/mL
#	normalAchPresentMolar = normalAchPresentMass*1/wAch*1000.0 #1000 is to convert mL to L

#	normalNor = 1075.2*10.0^-15 #mol/L
#	
#	upperBoundAch = .8
#	lowerBoundAch =.45
#	lowerBoundNor = 1e-103
#	upperBoundNor= .1

#	norPresent = (Cnor-lowerBoundNor)*normalNor/(10E-116)

#	bloodvolume= 6.234 #in L, from Total blood volume in healthy young and older men

#	if(contains(compartment_name, "vein"))
#		Vmax = .18*bloodvolume*1.3
#		Vmin = .18*bloodvolume*.7
#	end

#	if(contains(compartment_name, "artery"))
#		Vmax =.06*bloodvolume*1.3
#		Vmin = .06*bloodvolume*.7
#	end

#	if(contains(compartment_name, "wound"))
#		Vmax = .005*bloodvolume*1.3
#		Vmin = .005*bloodvolume*.6
#	end

#	r = dr
#	V = V0

#	if(Cach<=upperBoundAch && Cach>=lowerBoundAch && Cnor<=upperBoundNor && Cnor>=lowerBoundNor)
#		#if within normal ranges, return normal volume
#		V = V0
#		r = dr
#	end

#	if(Cach>upperBoundAch)
#		#vasodiliate
#		logCach = log10((Cach-lowerBoundAch)*normalAchPresentMolar)
#		r = S50*logCach+dr
#		#println("Vasodilating")
#	end

#	if(Cach<lowerBoundAch)
#		#logCach = log10((Cach-lowerBoundAch)*normalAchPresentMolar)
#		r = dr
#		#r = dr
#		#println("vasoconstricting for lack of Ach")
#	end

#	if(Cnor >upperBoundNor)
#		#vasoconstrict
#		
#		if(contains(compartment_name, "vein"))
#			r = -14.08/(norPresent)+dr
#		elseif(contains(compartment_name, "artery"))
#			r = -4.42/norPresent+dr
#		else
#		#use some averaged slope
#			r = -9.25/norPresent+dr
#		end
#		#println("Vasoconstricting")
#	end

#	if(Cnor < lowerBoundNor)
#		if(contains(compartment_name, "vein"))
#			r = 14.08/(norPresent)+dr
#			#r = dr
#		elseif(contains(compartment_name, "artery"))
#			r = 4.42/norPresent+dr
#			#r = dr
#		else
#		#use some averaged slope
#			r = 9.25/norPresent+dr
#			#r = dr
#		end
#		#println("vasodilating for lack of nor")
#		
#	end
#	
#	if(r<0)
#		r = dr
#	end
#		V = AcrossSectional*r
#	#@show(compartment_name,V0,V,r)

#	if(V>Vmax)
#		V = Vmax
#	elseif(V<Vmin)
#		V = Vmin
#	end
	return V0
end
