#!/usr/bin/julia

println("Type arguments and multiple dispatch")
println("-------------------------")


#Struct style types: can not have sub types but can be instantiated
#Abstract types: can have sub types but can not be instantiated
 

abstract Ship

abstract SeaCraft <: Ship
abstract SpaceCraft <: Ship

abstract StarShipClass
abstract Constitution <: StarShipClass
abstract Galaxy <: StarShipClass

type FederationStarShip{StarShipClass} <: SpaceCraft
	topspeed
	nominalcrewsize::Int
	name::String
end

type Tardis <: SpaceCraft
	tardistype
	nominalcrewsize::Int
	name::String
end

immutable BlackPearl <: SeaCraft
	nominalcrewsize::Int  
	name::String
	BlackPearl() = new(42,"BlackPearl") #one and only constructor
end


function launch(ship::FederationStarShip)
	println("Engage...")
end

function launch(ship::Tardis) 
	println("Time rotor begins to move")
end

function launch(ship::SeaCraft)
	println("Aweigh anchor")
end

function shipname(ship::Ship) 
	return ship.name
end
function shipname(ship::Tardis) 
	return "TARDIS"
end


ships = [FederationStarShip{Galaxy}(9,100,"Enterprise"),
         Tardis(40,6,"Sexy"), 
         BlackPearl()]

println(ships)

names = map(shipname,ships)
println([names ships])


map(ships) do s
	println("$(shipname(s)) is now launching") 
	launch(s)
	println()
end



println(methods(launch))
 




