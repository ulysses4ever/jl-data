module ChargedParticle_BTree

  using ChargedParticle_Base
  using Compat


  export BTreeNode,BTree,insertParticle,computeChargeDistribution,calculateEFieldFromTree,calculateEFieldFromTreeOpt,calculateEFieldOpt

  const epsilon0 = 8.854e-12
  const elecConst = 4*pi*epsilon0
  const theta = 0.9

abstract Enum
immutable Quadrant <: Enum
    val::Int
    function Quadrant(i::Integer)
        @assert 1<=i<=4
        new(i)
    end
end
const SW = Quadrant(1)
const NW = Quadrant(2)
const SE = Quadrant(3)
const NE = Quadrant(4)


type BTreeNode
  parent::Nullable{BTreeNode}
  quadNodes::Array{Nullable{BTreeNode},1}
  center::Array{Float64,1}
  min::Array{Float64,1}
  max::Array{Float64,1}
  particle::Nullable{ChargedParticle}
  numP::Int
  charge::Float64
  centerOfCharge::Array{Float64,1}
end

BTreeNode() = BTreeNode(
  Nullable{BTreeNode}(),
  [Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}()],
  [0,0,0],
  [0,0,0],
  [0,0,0],
  Nullable{ChargedParticle}(),
  0,
  0.0,
  [0,0,0]
  )

BTreeNode(min::Array{Float64,1},max::Array{Float64,1},parent::Nullable{BTreeNode}=Nullable{BTreeNode}()) = BTreeNode(
  parent,
  [Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}()],
  min+(max-min)/2.0,
  min,
  max,
  Nullable{ChargedParticle}(),
  0,
  0.0,
  [0,0,0]
  )

BTreeNode(min::Array{Float64,1},max::Array{Float64,1},parent::BTreeNode) = BTreeNode(
  min,
  max,
  Nullable{BTreeNode}(parent)
  )


type BTree
  root::BTreeNode
end

function BTree(min::Array{Float64,1},max::Array{Float64,1})
  BTree( BTreeNode(min,max,Nullable{BTreeNode}()))
end


function isRoot(node::BTreeNode)
  isnull(node.parent) ? true : false
end

function getQuadrant(self::BTreeNode,location::Array{Float64,1})
  if (location[1]<=self.center[1] && location[2]<=self.center[2])
    return SW
  elseif (location[1]<=self.center[1] && location[2]>=self.center[2])
    return NW
  elseif (location[1]>=self.center[1] && location[2]>=self.center[2])
    return NE
  elseif (location[1]>=self.center[1] && location[2]<=self.center[2])
    return SE
  end
end

function getQuadrant(self::BTreeNode,particle::ChargedParticle)
  getQuadrant(self,particle.location)
end

function createQuadNode(self::BTreeNode, quad::Quadrant)
  if quad == SW
    return BTreeNode(self.min,self.center,self)
  elseif quad == NW
    return BTreeNode(
              [self.min[1],self.center[2],self.min[3]],
              [self.center[1],self.max[2],self.min[3]],
              self)
  elseif quad == NE
    return BTreeNode(self.center,self.max,self)
  elseif quad == SE
    return BTreeNode(
              [self.center[1],self.min[2],self.min[3]],
              [self.max[1],self.center[2],self.min[3]],
              self)
  end
end


function insertParticle(self::BTreeNode, particle::ChargedParticle)
  if self.numP > 1
    quad = getQuadrant(self,particle)
    if isnull(self.quadNodes[quad.val])
      self.quadNodes[quad.val] = Nullable{BTreeNode}(createQuadNode(self,quad))
    end
    insertParticle(get(self.quadNodes[quad.val]),particle)

  elseif self.numP == 1
    p2= get(self.particle)

    if !(p2.location == particle.location)
      # There is already a particle
      # subdivide the node and relocate that particle
      quad = getQuadrant(self,p2)
      if isnull(self.quadNodes[quad.val])
        self.quadNodes[quad.val] = Nullable{BTreeNode}(createQuadNode(self,quad))
      end
      insertParticle(get(self.quadNodes[quad.val]),p2)
      self.particle = Nullable{BTreeNode}()

      quad = getQuadrant(self,particle)
      if isnull(self.quadNodes[quad.val])
        self.quadNodes[quad.val] = Nullable{BTreeNode}(createQuadNode(self,quad))
      end
      insertParticle(get(self.quadNodes[quad.val]),particle)
    end
  elseif self.numP == 0
    self.particle = particle
  end
  self.numP+=1
end

function computeChargeDistribution(self::BTreeNode)
  #println("compChargeDist 152 "*string(self.center))
  if self.numP == 1
    self.centerOfCharge = deepcopy(get(self.particle).location)
    self.charge = get(self.particle).charge
    #println("self.centerOfCharge 155"*string(self.centerOfCharge))
  else
    for node in self.quadNodes
      if !isnull(node)
        node = get(node)
        #println("compChargeDist 161 "*string(node.center)*string(self.charge)*string(self.centerOfCharge))
        computeChargeDistribution(node)
        #println("compChargeDist 163 "*string(node.center)*string(self.charge)*string(self.centerOfCharge))
        self.charge+=node.charge
        self.centerOfCharge += node.charge*node.centerOfCharge
        #println("compChargeDist 166 "*string(node.center)*string(self.charge)*string(self.centerOfCharge))
      end
    end
    if self.charge != 0.0
      #println("self.centerOfCharge 164"*string(self.centerOfCharge))
      self.centerOfCharge /= self.charge
      #println("compChargeDist 168"*string(self.centerOfCharge))
      #println("self.center 167"*string(self.center))
    else
      self.centerOfCharge = self.center
    end
  end
end

function calculateEField(r1::Array{Float64,1},r2::Array{Float64,1},charge2::Float64)
  d = norm(r1-r2)
  if d>0
    #println(d)
    #println(r1)
    #println(r2)
    #println(r1-r2)
    E = charge2/elecConst * (r1-r2)/(d^3.0)
    #println(E)
  else
    E = [0.0,0.0,0.0]
  end
end

function calculateEFieldFromTree(self::BTreeNode,targetP::ChargedParticle)
  if self.numP == 1
    #println("calculateEfieldFromTree 188")
    eField = calculateEField(targetP.location,get(self.particle).location,get(self.particle).charge)
  else
    r = norm(targetP.location-self.centerOfCharge)
    d = self.max[1] - self.min[1]

    if d/r < theta
      #println("calculateEfieldFromTree 194")
      eField = calculateEField(targetP.location,self.centerOfCharge,self.charge)
    else
      eField = [0.0,0.0,0.0]
      for node in self.quadNodes
        if !isnull(node)
          eField+= calculateEFieldFromTree(get(node),targetP)
        end
      end
    end
  end
  return(eField)
end


function calculateEFieldOpt(r1::Array{Float64,1},r2::Array{Float64,1},charge2::Float64)
  #local d::Float64 = norm(r1-r2)
  #if d>0
    #println(d)
    #println(r1)
    #println(r2)
    #println(r1-r2)
  #  return(charge2/elecConst * (r1-r2)/(d^3.0))
    #println(E)
  #else
    return([0.0,0.0,0.0])
  #end
end

function calculateEFieldFromTreeOpt(self::BTreeNode,targetP::ChargedParticle)
  #println("calculateEFieldFromTreeOpt "*string(self.center))
  if self.numP == 1
    #println("calculateEfieldFromTree 188")
    eField = calculateEFieldOpt(targetP.location,get(self.particle).location,get(self.particle).charge)
  else
    local r = norm(targetP.location-self.centerOfCharge)
    local d = self.max[1] - self.min[1]

    if d/r < theta
      #println("calculateEfieldFromTree 194")
      eField = calculateEFieldOpt(targetP.location,self.centerOfCharge,self.charge)
    else
      eField = [0.0,0.0,0.0]
      for node in self.quadNodes
        if !isnull(node)
          eField+= calculateEFieldFromTreeOpt(get(node),targetP)
        end
      end
    end
  end
  return(eField)
end


end