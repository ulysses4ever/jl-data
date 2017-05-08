abstract Component

type Link <: Component
  length::Int
  breadth::Int
  begin_angle::Float64
  end_angle::Float64
  torque::Float64
  cost::Int
  weight::Int
  function Link(length, breadth; begin_angle=0, end_angle=0, torque=0, cost=0, weight=0)
    this = new()
    this.length = length
    this.breadth = breadth
    this.begin_angle = begin_angle
    this.end_angle = end_angle
    this.cost = cost
    this.weight = weight
    return this
  end
end

type Motor <: Component
  length::Int
  breadth::Int
  begin_angle::Float64
  end_angle::Float64
  torque::Float64
  cost::Int
  weight::Int
  function Motor(length, breadth; begin_angle=0, end_angle=0, torque=0, cost=0, weight=0)
    this = new()
    this.length = length
    this.breadth = breadth
    this.begin_angle = begin_angle
    this.end_angle = end_angle
    this.torque = torque
    this.cost = cost
    this.weight = weight
    return this
  end
end

function comp_length(comp::Component)
  return comp.length
end

LINKS = Array(Component,0)
push!(LINKS, Link(150, 50, weight=20, cost=100))
push!(LINKS, Link(50, 10, weight=10, cost=200))
push!(LINKS, Link(500, 100, weight=50, cost=1000))
push!(LINKS, Link(1000, 100, weight=100, cost=1500))
push!(LINKS, Link(225, 25, weight=22, cost=63))
push!(LINKS, Link(420, 40, weight=42, cost=45))
push!(LINKS, Link(680, 150, weight=68, cost=23))
push!(LINKS, Link(810, 210, weight=81, cost=35))
push!(LINKS, Link(8000, 3000, weight=800, cost=80))
push!(LINKS, Link(2600, 400, weight=260, cost=26))
push!(LINKS, Link(12600, 2600, weight=1260, cost=300))
sort!(LINKS, by=comp_length)

MOTORS = Array(Component,0)
push!(MOTORS, Motor(66, 20, begin_angle=-π/3, end_angle=π/3, torque=0.5, weight=5, cost=100))
push!(MOTORS, Motor(130, 30, begin_angle=-π/4, end_angle=π/4, torque=3, weight=10, cost=500))
push!(MOTORS, Motor(15, 5, begin_angle=-π/2, end_angle=π/2, torque=0.3, weight=1, cost=200))
push!(MOTORS, Motor(50, 15, begin_angle=-π/2, end_angle=π/2, torque=0.7, weight=1, cost=100))
push!(MOTORS, Motor(100, 20, begin_angle=-π/2, end_angle=π/2, torque=2, weight=8, cost=700))
push!(MOTORS, Motor(400, 100, begin_angle=-π/3, end_angle=π/3, torque=7, weight=35, cost=700))
push!(MOTORS, Motor(200, 70, begin_angle=-π/2, end_angle=π/2, torque=4, weight=15, cost=2000))
push!(MOTORS, Motor(150, 35, begin_angle=-π/4, end_angle=π/4, torque=3, weight=6, cost=6000))
sort!(MOTORS, by=comp_length)

COMP = Array(Array{Component,1},0)
push!(COMP, LINKS)
push!(COMP, MOTORS)
