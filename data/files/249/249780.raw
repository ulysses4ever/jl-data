#data type heirachy tree

#all tradeables have amt and qual
abstract tradeable

#function +(a::tradeable,b::tradeable)
#  return tradeable(a.amt+b.amt,(a.amt*a.qual+b.amt*b.qual)/(a.amt+b.amt))
#end

#all buildings have x::int,y::int,dx::int,dy::int,
abstract building
abstract retail <: building
abstract researchable <: building
abstract occupyable <: building
abstract headquarters <: building
abstract residential <: occupyable
abstract offices <: occupyable
abstract industrial <: building



