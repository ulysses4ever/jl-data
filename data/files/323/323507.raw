push!(LOAD_PATH, ".")

using ChargedParticle_BTree
using ProfileView

#using ChargedParticleVisualization_BTree
using ChargedParticle_Base
charge = 1.0
root = BTreeNode(
    Vector3d(0.0,0.0,0.0),
    Vector3d(10.0,10.0,10.0))

p1 = ChargedParticle(Vector3d(1.0,1.0,1.0))
p2 = ChargedParticle(Vector3d(1.0,1.0,5.0))
p3 = ChargedParticle(Vector3d(1.0,1.0,7.0))
#p4 =

insertParticle(root,p1)
insertParticle(root,p2)
insertParticle(root,p3)
computeChargeDistribution(root)
E = calculateEFieldFromTree(root,p3)
println(E)
