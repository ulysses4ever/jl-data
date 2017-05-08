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
#*--------------------------------------------------------------------
#* Author: Gerson Balbueno Bicca 
#* $Id: HairpinIncr.mso								$
#*------------------------------------------------------------------
type UpperPipe_basic
	UpperPipe_basic()=begin
		new(
			HairpinIncr_basic(),
			[
				:(_base_1.Details.Q(1:N) = _base_1.InletOuter.F*(_base_1.Outer.HeatTransfer.Enth(2:_base_1.Npoints) - _base_1.Outer.HeatTransfer.Enth(1:N))),
				:(_base_1.Details.Q(1:N) = -_base_1.InletInner.F*(_base_1.Inner.HeatTransfer.Enth(1:N) - _base_1.Inner.HeatTransfer.Enth(2:_base_1.Npoints))),
				:(_base_1.Details.Q = _base_1.Details.Ud*_base_1.Pi*_base_1.DoInner*(_base_1.Lpipe/N)*(_base_1.Outer.Properties.Average.T - _base_1.Inner.Properties.Average.T)),
				:(_base_1.Details.Q(1:N) = _base_1.InletInner.F*(_base_1.Inner.HeatTransfer.Enth(1:N)-_base_1.Inner.HeatTransfer.Enth(2:_base_1.Npoints))),
				:(_base_1.Details.Q(1:N) = -_base_1.InletOuter.F*(_base_1.Outer.HeatTransfer.Enth(2:_base_1.Npoints) - _base_1.Outer.HeatTransfer.Enth(1:N))),
				:(_base_1.Details.Q = _base_1.Details.Ud*_base_1.Pi*_base_1.DoInner*(_base_1.Lpipe/N)*(_base_1.Inner.Properties.Average.T - _base_1.Outer.Properties.Average.T)),
				:(_base_1.Inner.HeatTransfer.Enth(1) = _base_1.InletInner.h),
				:(_base_1.Inner.HeatTransfer.Enth(_base_1.Npoints) = _base_1.OutletInner.h),
				:(_base_1.Inner.HeatTransfer.Tlocal(1) = _base_1.InletInner.T),
				:(_base_1.Inner.HeatTransfer.Tlocal(_base_1.Npoints) = _base_1.OutletInner.T),
				:(_base_1.Inner.PressureDrop.Plocal(1) = _base_1.InletInner.P),
				:(_base_1.Inner.PressureDrop.Plocal(_base_1.Npoints) = _base_1.OutletInner.P),
				:(_base_1.Outer.HeatTransfer.Enth(_base_1.Npoints) = _base_1.InletOuter.h),
				:(_base_1.Outer.HeatTransfer.Enth(1) = _base_1.OutletOuter.h),
				:(_base_1.Outer.HeatTransfer.Tlocal(_base_1.Npoints) = _base_1.InletOuter.T),
				:(_base_1.Outer.HeatTransfer.Tlocal(1) = _base_1.OutletOuter.T),
				:(_base_1.Outer.PressureDrop.Plocal(_base_1.Npoints) = _base_1.InletOuter.P),
				:(_base_1.Outer.PressureDrop.Plocal(1) = _base_1.OutletOuter.P),
				:(_base_1.Outer.PressureDrop.Pd_fric([1:N]) = (2*_base_1.Outer.PressureDrop.fi([1:N])*_base_1.Lincr(1+_base_1.Npoints-[1:N])*_base_1.Outer.Properties.Average.rho([1:N])*_base_1.Outer.HeatTransfer.Vmean([1:N])^2)/(_base_1.Outer.PressureDrop.Dh*_base_1.Outer.HeatTransfer.Phi([1:N]))),
				:(_base_1.Outer.PressureDrop.Pd_fric(_base_1.Npoints) = 0*"kPa"),
				:(_base_1.Inner.PressureDrop.Pd_fric(2:_base_1.Npoints) = (2*_base_1.Inner.PressureDrop.fi*_base_1.Lincr(2:_base_1.Npoints)*_base_1.Inner.Properties.Average.rho*_base_1.Inner.HeatTransfer.Vmean^2)/(_base_1.DiInner*_base_1.Inner.HeatTransfer.Phi)),
				:(_base_1.Inner.PressureDrop.Pd_fric(1) = 0*"kPa"),
			],
			[
				"Energy Balance Outer Stream","Energy Balance Inner Stream","Incremental Duty","Energy Balance Hot Stream","Energy Balance Cold Stream","Incremental Duty","Enthalpy of Inner Side - Inlet Boundary","Enthalpy of inner Side - Outlet Boundary","Temperature of Inner Side - Inlet Boundary","Temperature of Inner Side - Outlet Boundary","Pressure of Inner Side - Inlet Boundary","Pressure of Inner Side - Outlet Boundary","Enthalpy of Outer Side - Inlet Boundary","Enthalpy of Outer Side - Outlet Boundary","Temperature of Outer Side - Inlet Boundary","Temperature of Outer Side - Outlet Boundary","Pressure of Outer Side - Inlet Boundary","Pressure of Outer Side - Outlet Boundary","Outer Pipe Pressure Drop for friction","Outer Pipe Pressure Drop for friction","Inner Pipe Pressure Drop for friction","Inner Pipe Pressure Drop for friction",
			],
		)
	end
	_base_1::HairpinIncr_basic
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	attributes::Dict{Symbol,Any}
end
export UpperPipe_basic
function setEquationFlow(in::UpperPipe_basic)
	let switch=HotSide
		if HotSide==InletInner.T > InletOuter.T
			set(switch,"inner")
		end
		if HotSide==InletInner.T < InletOuter.T
			set(switch,"outer")
		end
		if switch=="outer"
			addEquation(1)
			addEquation(2)
			addEquation(3)
		elseif switch=="inner"
			addEquation(4)
			addEquation(5)
			addEquation(6)
		end
	end
	addEquation(7)
	addEquation(8)
	addEquation(9)
	addEquation(10)
	addEquation(11)
	addEquation(12)
	addEquation(13)
	addEquation(14)
	addEquation(15)
	addEquation(16)
	addEquation(17)
	addEquation(18)
	addEquation(19)
	addEquation(20)
	addEquation(21)
	addEquation(22)
end
function atributes(in::UpperPipe_basic,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Incremental Hairpin Heat Exchanger. "
	fields[:Info]="Incremental approach for Hairpin heat exchanger. "
	drive!(fields,_)
	return fields
end
UpperPipe_basic(_::Dict{Symbol,Any})=begin
	newModel=UpperPipe_basic()
	newModel.attributes=atributes(newModel,_)
	newModel
end
