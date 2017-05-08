push!(LOAD_PATH, ".")

using ChargedParticle_BTree
using ProfileView

#using ChargedParticleVisualization_BTree
using ChargedParticle_Base
charge = 1.0

function insertParticlesTest(root)
  nIons = 10000;
  for i=0:nIons
    insertParticle(root,ChargedParticle(Vector3d(2.0,i*1/(nIons*2.0)+0.1,0.0)))
  end
end

function calculateEFieldTest(root,part,nRuns)
  E = []
  for i=1:nRuns
    E = calculateEFieldFromTree(root,part)
  end
  return E
end


root = BTreeNode(
    Vector3d(0.0,0.0,0.0),
    Vector3d(10.0,10.0,10.0))
tree = BTree(root)
insertParticlesTest(root)
computeChargeDistribution(tree.root)


root = BTreeNode(
    Vector3d(0.0,0.0,0.0),
    Vector3d(10.0,10.0,10.0))
tree = BTree(root)
part = ChargedParticle(Vector3d(2.1,3.0,0.0),1.0)
insertParticle(root,part)

Profile.init(90000000,0.00001)
insertParticlesTest(root)
computeChargeDistribution(tree.root)
E = calculateEFieldTest(root,part,10000)
@profile E = calculateEFieldTest(root,part,10000)

ProfileView.view()
