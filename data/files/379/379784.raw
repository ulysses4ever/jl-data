push!(LOAD_PATH, ".")

using ChargedParticle_BTree
using ProfileView

#using ChargedParticleVisualization_BTree
using ChargedParticle_Base
charge = 1.0
root = BTreeNode(
    Vector3d(0.0,0.0,0.0),
    Vector3d(10.0,10.0,10.0))

#X = linspace(0.1,0.9,1000)
#for x in X
#  insertParticle(root,ChargedParticle([x,4.0,0.0],charge))
#end
function insertParticlesTest(root,nIons)
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

#insertParticle(root,p1)
#insertParticle(root,p2)
#insertParticle(root,p3)
#insertParticle(root,p4)
#insertParticle(root,p5)
#insertParticle(root,p6)

function testRun(nIons)
  println("-----------"*string(nIons))
  root = BTreeNode(
    Vector3d(0.0,0.0,0.0),
    Vector3d(10.0,10.0,10.0))
  tree = BTree(root)
  part = ChargedParticle(Vector3d(2.1,3.0,0.0),1.0)
  insertParticle(root,part)
  tElapsed = 0
  @time insertParticlesTest(root,nIons)
  @time computeChargeDistribution(tree.root)
  @time E = calculateEFieldTest(root,part,nIons)
  #println(tElapsed)
  println(E)
  return(tElapsed)
end

function testRunRepeated(nIons)
  nRuns = 6
  tElapsed = zeros(nRuns)
  for i=1:6
    tElapsed[i] = testRun(nIons)
  end
  return mean(tElapsed)
end

function testRunScaled()
  nIons = [10000,50000,100000,250000,500000,1000000]
  result = zeros(length(nIons),2)
  for i=1:length(nIons)
    result[i,1] = nIons[i]
    result[i,2] = testRunRepeated(nIons[i])
  end

  print(result)
end

nIons = 1000000;
#testRunScaled()
testRun(nIons)
testRun(nIons)
testRun(nIons)
testRun(nIons)
#testRun(nIons)
#testRun(nIons)
#testRun(nIons)
#testRun(nIons)
#testRun(1000000)
#testRun(10000)
#testRun(50000)
#testRun(100000)
#testRun(250000)
#testRun(500000)

#testRun(20*nIons)
#testRun(20*nIons)
#testRun(nIons*2)

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
