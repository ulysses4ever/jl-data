module ChargedParticleVisualization_BTree

export plotBTree

using Compat
using PyPlot
using ChargedParticle_BTree
using ChargedParticle_Base

function plotParticle(particle::ChargedParticle)
  plot(particle.location[1],particle.location[2],"*r")
end

function plotBTreeNode(node::BTreeNode)
  broken_barh( [(node.min[1], node.max[2]-node.min[2])], (node.min[2], node.max[2]-node.min[2]), facecolors=[0.1*node.charge,0.2,0.2],lw=2.0, alpha=0.3)
  println(node)
  println(node.charge)
  if !isnull(node.particle)
    plotParticle(get(node.particle))
  end
  for child in node.quadNodes
    if !isnull(child)
      plotBTreeNode(get(child))
    end
  end
end

function plotBTree(tree::BTree,filename)
  ioff()
  figure()
  plotBTreeNode(tree.root)
  #show()


  savefig(filename*".png",width=800, height=800)
  close()
end


end