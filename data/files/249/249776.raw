#data type heirachy tree

#all tradeables have n and q
abstract tradeable
#  n::Integer
#  q::float64 #should range in [0:1]
#  selling_min::float64
#  selling_max::float64
#end

#function +(a::tradeable,b::tradeable)
#  return tradeable(a.n+b.n,(a.n*a.q+b.n*b.q)/(a.n+b.n))
#end

abstract building
#  x::Integer #(x,y) == top,left corner
#  y::Integer
#  dx::Integer
#  dy::Integer
#  owner::agent
#  is_open::bool
#  cash_flow::float64
#  level::Integer
#  workers_per_level::Integer #currently no distinction for social classes
#  curr_workers::Integer
#  city::city


type buy_state
  item::tradeable
  buying::bool
  max_stock::Integer
  min_quality::Integer
  max_price::float64
end


abstract buyer <: building
#  list<buy_settings>
#

type retail_control
  item::tradeable
  last_sold::Integer
  selling_price::float64
end

abstract retail <: buyer
#  ads_per_level::Integer
#  current_ads::Integer
#  list<retail_control>


abstract researchable <: building
abstract occupyable <: building
abstract headquarters <: buyer
abstract residential <: occupyable
abstract offices <: occupyable
abstract industrial <: buyer



