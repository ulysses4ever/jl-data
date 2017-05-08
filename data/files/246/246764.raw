
using EA


include("Component.jl")
include("DH.jl")

const ANGLES = [0,π/2, 3π/2]

const DISCRETE_MUT_CHANCE = 0.2

const CONTINUOUS_MUT_CHANCE = 0.1
const ANGLE_MUT_RATE = 10π/180

const DIST_LIMIT = 50;

const BUDGET = 2000

type Target
  x::Float64
  y::Float64
  z::Float64
  N::Float64
end

type Point
  x::Float64
  y::Float64
  z::Float64
  R::Matrix
  function Point(x,y,z,R)
    this = new()
    this.x = x
    this.y = y
    this.z = z
    this.R = R
    return this
  end
  function Point(v::Vector,R)
    this = new()
    this.x = v[1]
    this.y = v[2]
    this.z = v[3]
    this.R = R
    return this
  end
end

const TARGETS = [Target(200, 200, 200, 0.5),
                 Target(500,100,500,0.3),
                 Target(-200,500,200,2),# was - 500, testing to see if less fokoppies occur
                 Target(400, 200, 200, 1)]
                 #Target(500,1000,500,0.1),
                 #Target(-200,0,200,2)]

type ResultSet
  DHList::DHSet
  points::Array{Array{Point,1},1}
  torques::Array{Array{Array{Float64,1},1},1}
  cost::Float64
  fdiff::Float64
  pointDiffs::Array{Float64,1}
  length
  fitness
  function ResultSet()
    this = new()
    this.points = Array(Array{Point,1},0)
    this.cost = 0
    this.fdiff = 0
    this.DHList = DHSet()
    return this
  end
end

type Gene <: AbstractGene
  comp_type::Int
  index::Int
  angles::Array{Float64,1}
  α::Float64
  θ::Float64
  change_type::Int
  function Gene(comp_type::Int, index::Int, angles::Array{Float64,1}, α::Float64, θ::Float64, change_type::Int)
    this = new()
    this.comp_type = comp_type
    this.index = index
    this.angles = angles
    this.change_type = change_type
    this.α = α
    this.θ = θ
    return this
  end

  function Gene()
    this = new()
    this.comp_type = rand(1:2)
    this.index = rand(1:length(COMP[this.comp_type]))
    comp::Component = COMP[this.comp_type][this.index]
    this.change_type = rand(0:2)
    this.angles = Array(Float64,length(TARGETS))
    this.α = ANGLES[rand(1:3)]
    this.θ = ANGLES[rand(1:3)]
    if this.comp_type == 2
      for i=1:length(this.angles)
        this.angles[i] = rand() * comp.begin_angle * 2 - comp.end_angle
      end
    else
      for i=1:length(this.angles)
        this.angles[i] = 0
      end
    end
    return this
  end
end

function mutate!(gene::Gene)
  if rand() < DISCRETE_MUT_CHANCE
    gene.comp_type = rand(1:length(COMP))
    gene.index = rand(1:length(COMP[gene.comp_type]))
    gene.θ = ANGLES[rand(1:3)]
    gene.α = ANGLES[rand(1:3)]
    gene.change_type = rand(0:2)
  end

  comp::Component = COMP[gene.comp_type][gene.index]

  if rand() < CONTINUOUS_MUT_CHANCE
    for i=1:length(gene.angles)
      if gene.comp_type == 2
        cur_angle = gene.angles[i]
        cur_angle += rand() * 2 * ANGLE_MUT_RATE - ANGLE_MUT_RATE
        sign = cur_angle/abs(cur_angle)
        cur_angle = (sign > 0)? cur_angle % comp.end_angle : cur_angle % comp.begin_angle
        gene.angles[i] = cur_angle
      end
    end
  end
end

function updateFitness!(input::AbstractIndividual, a, b, y)
  results::ResultSet = ResultSet()
  results.cost = getCost(input)
  results.DHList, results.length = getDH(input)
  getPoints!(results, input)
  results.torques = getTorque(results, input)
  total = 0
  results.pointDiffs = Array(Float64, length(results.points))
  for i = 1:length(results.points)
    valR = 0
    val = TARGETS[i].x - results.points[i][end].x
    valR += val*val

    val = TARGETS[i].y - results.points[i][end].y
    valR += val*val

    val = TARGETS[i].z - results.points[i][end].z
    valR += val*val
    valR = sqrt(valR)
    results.pointDiffs[i] = valR
    total += (valR - DIST_LIMIT > 0)? valR-DIST_LIMIT:0
  end

  toruqe_negatives = 0
  #make total negative torque
  for target in results.torques
    for motor in target
      for torque in motor
        if torque < 0
          toruqe_negatives += abs(torque)
        end
      end
    end
  end

  input.fitness = 0
  toruqe_negatives = toruqe_negatives*100
  torque_fitness = (toruqe_negatives < 1)? 1:1/(toruqe_negatives) #i.e. decreases for every negative
  cost_fitness = (results.cost == 0)? 99999:1/results.cost

  f1 = (total <= 1)? 1:(1/total)

  input.fitness = f1 * a + torque_fitness * b + cost_fitness * y
  input.total_acc = f1
  input.torque_error = torque_fitness
  input.total_cost = cost_fitness
  results.fitness = input.fitness
  input.results = results
  return input.fitness, results
end

function getCost(input::AbstractIndividual)
  total = 0
  list = input.chromosome
  for i = 1:length(list)
    gene = list[i]
    total += COMP[gene.comp_type][gene.index].cost
  end
  return total
end

function getDH(input::AbstractIndividual)
  lengths = 0
  curGene::Gene = input.chromosome[1]
  curComp::Component = COMP[curGene.comp_type][curGene.index]
  lengths += curComp.length
  z_buffer = 0.0
  rSet = DHSet()

  if curGene.change_type == 0 || curGene.comp_type == 1
    newLink = DHLink(0.0,π/2,curComp.length,curGene.θ)
    z_buffer = π/2
    push!(rSet.links, newLink)
  elseif curGene.change_type == 1
    newLink = DHLink(0.0,0.0,curComp.breadth/2,curGene.θ)
    push!(rSet.links, newLink)
  else
    newLink = DHLink(0.0,π/2,curComp.breadth/2,curGene.θ)
    push!(rSet.links, newLink)
  end


  for i = 2:length(input.chromosome)
    prevGene::Gene = curGene
    prevComp::Component = curComp
    curGene = input.chromosome[i]
    curComp = COMP[curGene.comp_type][curGene.index]
    lengths += curComp.length
    if curGene.change_type == 0 || curGene.comp_type == 1
      #no transform
      newLink = DHLink(curComp.length,0.0,0.0, z_buffer)
      z_buffer = 0.0
      push!(rSet.links, newLink)
    elseif curGene.change_type == 1
      #simple transform i.e. no extra information required, plain α and θ rotation only
      newLink = DHLink(curComp.length,curGene.α,0.0, z_buffer + curGene.θ)
      z_buffer = 0.0
      push!(rSet.links, newLink)
    else
      #Complex transform -> 2 step process + buffer filled
      newLink = DHLink(0.0,0.0,prevComp.breadth/2, z_buffer  + curGene.θ + π/2)
      push!(rSet.links, newLink)
      newLink = DHLink(0.0,π/2,curComp.length,  π/2)
      z_buffer = π/2
      push!(rSet.links, newLink)
    end
  end
  return rSet , lengths
end

function getTorque(results::ResultSet, input::AbstractIndividual)


  torque_list = Array(Array{Array{Float64,1},1},0)

  for tar_iter = 1:length(results.points)

    t = Array(Array{Float64,1},0)
    for i = 2:length(results.points[tar_iter])
      torques = Array(Float64,0)
      rot = results.points[tar_iter][i].R[1:3,1:3]

      comp_type = input.chromosome[i-1].comp_type
      index = input.chromosome[i-1].index
      comp::Component = COMP[comp_type][index]

      x1 = results.points[tar_iter][i].x
      y1 = results.points[tar_iter][i].y
      z1 = results.points[tar_iter][i].z

      for j = i+1:length(results.points[tar_iter])

        x2 = results.points[tar_iter][j].x
        y2 = results.points[tar_iter][j].y
        z2 = results.points[tar_iter][j].z

        x = x2-x1
        y = y2-y1
        z = z2-z1

        comp_type = input.chromosome[j-1].comp_type
        index = input.chromosome[j-1].index
        weight_comp::Component = COMP[comp_type][index]
        force = weight_comp.weight * 0.00980665002864 #weight is in grams

        r = Float64[x,y,z] .* 0.001
        F = Float64[0,0,force]

        M = cross(r,F)
        M = rot * M
        m = comp.torque - M[3]

        push!(torques, m)
      end
      x2 = TARGETS[tar_iter].x
      y2 = TARGETS[tar_iter].y
      z2 = TARGETS[tar_iter].z

      x = x2 - x1
      y = y2 - y1
      z = z2 - z1

      r = Float64[x,y,z] .* 0.001 #mm to m
      F = Float64[0,0,TARGETS[tar_iter].N]

      M = cross(r,F)
      M = rot * M
      m = comp.torque - M[3]

      push!(torques, m)

      push!(t,torques)
    end
    push!(torque_list,t)
  end
  return torque_list
end



function getPoints!(results::ResultSet, input::AbstractIndividual)
  set = results.DHList.links
  cur = input.chromosome

  A = Array(Matrix,0)
  empty = Float64 [0 0 0
                   0 0 0
                   0 0 0]
  for i = 1:length(cur[1].angles)
    push!(results.points, Array(Point,0))
    push!(results.points[i], Point(0,0,0,empty))
    push!(A, nextLink(set[1],0.0))
    push!(results.points[i], Point(A[i][1:3,4],A[i]))
  end
  x = 1
  skip = false
  for i = 2:length(set)
    if skip
      skip = false
      continue
    end
    for j = 1:length(cur[1].angles)
      if cur[x+1].comp_type == 1
        A[j] = A[j]*nextLink(set[i], 0.0)
      elseif cur[x+1].change_type != 2
        A[j] = A[j]*nextLink(set[i], cur[x].angles[j])
      else
        skip = true
        A[j] = A[j]*nextLink(set[i], cur[x].angles[j])
        #push!(results.points[j], Point(A[j][1:3,4]))
        #A[j] = A[j]*nextLink(set[i+1], 0.0)
      end
      push!(results.points[j], Point(A[j][1:3,4],A[j]))
    end
    x+=1
  end
end
