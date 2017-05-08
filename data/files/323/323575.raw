module ChargedParticle_BTree

  using ChargedParticle_Base
  using Compat

  export BTree,BTreeNode,insertParticle,computeChargeDistribution,calculateEFieldFromTree,calculateEFieldFromTreeOpt,calculateEFieldOpt

  const epsilon0 = 8.854e-12
  const elecConst = 4*pi*epsilon0
  const theta = 0.9

abstract Enum
immutable Quadrant <: Enum
    val::Int
    function Quadrant(i::Integer)
        #@assert 1<=i<=4
        new(i)
    end
end
const SWT = Quadrant(1)
const NWT = Quadrant(2)
const SET = Quadrant(3)
const NET = Quadrant(4)
const SWB = Quadrant(5)
const NWB = Quadrant(6)
const SEB = Quadrant(7)
const NEB = Quadrant(8)



type BTreeNode
  #parent::Nullable{BTreeNode}
  root::Bool
  quadNodes::Array{Nullable{BTreeNode},1}
  center::Vector3d
  min::Vector3d
  max::Vector3d
  particle::Nullable{ChargedParticle}
  numP::Int64
  charge::Float64
  centerOfCharge::Vector3d
end

BTreeNode() = BTreeNode(
  Vector3d(0.0,0.0,0.0),
  Vector3d(0.0,0.0,0.0)
  )

BTreeNode(min::Vector3d,max::Vector3d) = BTreeNode(
  false,
  [Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}(),Nullable{BTreeNode}()],
  min+(max-min)/2.0,
  min,
  max,
  Nullable{ChargedParticle}(),
  0,
  0.0,
  Vector3d(0.0,0.0,0.0)
  )

type BTree
  root::BTreeNode
end

function BTree(min::Vector3d,max::Vector3d)
  BTree( BTreeNode(min,max))
end


function isRoot(node::BTreeNode)
  return node.root
end

function getQuadrant(self::BTreeNode,location::Vector3d)
  if (location.z<=self.center.z)
    if (location.x<=self.center.x)
      if (location.y<=self.center.y)
        return SWB
      else
        return NWB
      end
    else
      if (location.y>=self.center.y)
        return NEB
      else
        return SEB
      end
    end
  else
    if (location.x<=self.center.x)
      if (location.y<=self.center.y)
        return SWT
      else
        return NWT
      end
    else
      if (location.y>=self.center.y)
        return NET
      else
        return SET
      end
    end
  end

end

function getQuadrant(self::BTreeNode,particle::ChargedParticle)
  getQuadrant(self,particle.location)
end

function createQuadNode(self::BTreeNode, quad::Quadrant)
  if quad == SWB
    return BTreeNode(self.min,self.center)
  elseif quad == NWB
    return BTreeNode(
              Vector3d(self.min.x,self.center.y,self.min.z),
              Vector3d(self.center.x,self.max.y,self.center.z))
  elseif quad == NEB
    return BTreeNode(
              Vector3d(self.center.x,self.center.y,self.min.z),
              Vector3d(self.max.x,self.max.y,self.center.z))
  elseif quad == SEB
    return BTreeNode(
              Vector3d(self.center.x,self.min.y,self.min.z),
              Vector3d(self.max.x,self.center.y,self.center.z))
  elseif quad == SWT
    return BTreeNode(
              Vector3d(self.min.x,self.min.y,self.center.z),
              Vector3d(self.center.x,self.center.y,self.max.z))
  elseif quad == NWT
    return BTreeNode(
              Vector3d(self.min.x,self.center.y,self.center.z),
              Vector3d(self.center.x,self.max.y,self.max.z))
  elseif quad == NET
    return BTreeNode(self.center,self.max)
  elseif quad == SET
    return BTreeNode(
              Vector3d(self.center.x,self.min.y,self.center.z),
              Vector3d(self.max.x,self.center.y,self.max.z))
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
  else
    self.particle = particle
  end
  self.numP+=1
end

function computeChargeDistribution(self::BTreeNode)
  #println("compChargeDist 152 "*string(self.center))
  if self.numP == 1
    self.centerOfCharge.x = get(self.particle).location.x
    self.centerOfCharge.y = get(self.particle).location.y
    self.centerOfCharge.z = get(self.particle).location.z
      #deepcopy(get(self.particle).location)
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
        self.centerOfCharge.x += node.charge*node.centerOfCharge.x
        self.centerOfCharge.y += node.charge*node.centerOfCharge.y
        self.centerOfCharge.z += node.charge*node.centerOfCharge.z
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

function calculateEField(r1::Vector3d,r2::Vector3d,charge2::Float64)
  d = norm(r1-r2)
  if d>0
    return charge2/elecConst*(r1-r2)/(d^3.0)
  else
    return Vector3d(0.0,0.0,0.0)
  end
end

function calculateEFieldFromTree(self::BTreeNode,targetP::ChargedParticle)
  if self.numP == 1
    #println("calculateEfieldFromTree 188")
    eField = calculateEField(targetP.location,get(self.particle).location,get(self.particle).charge)
  else
    r = norm(targetP.location-self.centerOfCharge)
    d = self.max.x - self.min.x

    if d/r < theta
      #println("calculateEfieldFromTree 194")
      eField = calculateEField(targetP.location,self.centerOfCharge,self.charge)
    else
      eField = Vector3d(0.0,0.0,0.0)
      for node in self.quadNodes
        if !isnull(node)
          eField+= calculateEFieldFromTree(get(node),targetP)
        end
      end
    end
  end
  return(eField)
end

end
