module ChargedParticle_BTree

  using ChargedParticle_Base
  using Compat


  export BTreeNode

  const epsilon0 = 8.854e-12
  const elecConst = 4*pi*epsilon0
  const theta = 0.9

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

end