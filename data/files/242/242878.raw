#-------------------------------------------------------------------
#* EMSO Model Library (EML) Copyright (C) 2004 - 2007 ALSOC.
#*
#* This LIBRARY is free software; you can distribute it and/or modify
#* it under the therms of the ALSOC FREE LICENSE as available at
#* http://www.enq.ufrgs.br/alsoc.
#*
#* EMSO Copyright (C) 2004 - 2007 ALSOC, original code
#* from http://www.rps.eng.br Copyright (C) 2002-2004.
#* All rights reserved.
#*
#* EMSO is distributed under the therms of the ALSOC LICENSE as
#* available at http://www.enq.ufrgs.br/alsoc.
#*
#*--------------------------------------------------------------------
#* Models to simulate a power plant.
#*--------------------------------------------------------------------
#* Author: Argimiro R. Secchi
#* $Id: power_plant.mso 195 2007-03-07 20:30:12Z arge $
#*-------------------------------------------------------------------
# Declaracao de tipos
type CorrenteZ
	CorrenteZ()=begin
		Ncomp=outers.Ncomp
		new(
			Corrente(),
			DanaInteger(),
			fill(fraction()),
			[:Ncomp,],
			[:z,]
		)
	end
	_base_1::Corrente
	Ncomp::DanaInteger
	z::Array{fraction}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
end
export CorrenteZ
