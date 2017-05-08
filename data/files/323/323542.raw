push!(LOAD_PATH, ".")

using ChargedParticle_BTree
using ProfileView

#using ChargedParticleVisualization_BTree
using ChargedParticle_Base
charge = 1.0
root = BTreeNode(
    [0.0,0.0,0.0],
    [10.0,10.0,10.0])
p1 = ChargedParticle([2.0,2.0,0.0],charge)
p2 = ChargedParticle([4.0,2.0,0.0],charge)
p3 = ChargedParticle([6.0,2.0,0.0],charge)
p4 = ChargedParticle([2.0,3.0,0.0],charge)
p5 = ChargedParticle([2.1,3.0,0.0],charge)
p6 = ChargedParticle([2.1,3.01,0.0],charge)

#X = linspace(0.1,0.9,1000)
#for x in X
#  insertParticle(root,ChargedParticle([x,4.0,0.0],charge))
#end
function insertParticlesTest(root)
  nIons = 100000;
  for i=0:nIons
    insertParticle(root,ChargedParticle([2.0,i*1/(nIons*2.0)+0.1,0.0]))
  end
end

#insertParticle(root,p1)
#insertParticle(root,p2)
#insertParticle(root,p3)
#insertParticle(root,p4)
#insertParticle(root,p5)
#insertParticle(root,p6)

tree = BTree(root)
#@profile computeChargeDistribution(tree.root)
#ProfileView.view()
@time insertParticlesTest(root)
@time computeChargeDistribution(tree.root)

root = BTreeNode(
    [0.0,0.0,0.0],
    [10.0,10.0,10.0])
tree = BTree(root)
@time insertParticlesTest(root)
@time computeChargeDistribution(tree.root)

#println("TEST TEST TEST ")
#function runTestOpt(nRuns)
#  for i=1:nRuns
#    eField = calculateEFieldFromTreeOpt(tree.root,p1)
#  end
#end

#function runTest(nRuns)
#  for i=1:nRuns
#    eField = calculateEFieldFromTree(tree.root,p1)
#  end
#end

#println(eField)
#runTestOpt(100000)
#Profile.clear()
#Profile.init()
#@profile runTestOpt(100000
#nRuns = 10000
#@time runTestOpt(nRuns)
#@time runTest(nRuns)
#@time runTestOpt(nRuns)
#@time runTest(nRuns)

#Profile.init()
#@profile runTest(100000)
#ProfileView.view()

#@code_warntype calculateEFieldOpt([1.0,1.0,0.0],[2.0,1.0,0.0],0.01)

#ProfileView.view()

#eField = calculateEFieldFromTreeOpt(tree.root,p2)
#println(eField)

#eField = calculateEFieldFromTreeOpt(tree.root,p3)
#println(eField)

#plotBTree(tree::BTree,"BTreeTest")
