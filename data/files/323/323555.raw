module ChargedParticleVisualization_PyPlot

export plotParticlesXY

using Compat
using PyPlot
using ChargedParticleVisualization_Utilities

function plotParticlesXY(sim,filename)
  boxsize = 1e-3
  ioff()
  fig = figure()
  pl = plot(sim.positions[1,:],sim.positions[2,:], "r.")
  width = 1920
  height = 1080
  ratio = width / height
  xlim(-boxsize*ratio,boxsize*ratio)
  ylim(-boxsize,boxsize)
  #display(pl)
  savefig(filename*".png",width=width, height=height)
  close()

end

function plotParticles3d(sim,filename,zLimit=sim.c_L_m)
  width = 1920
  height = 1080
  ratio = width / height


  figure()
  subplot(111, projection="3d")
  xlim(-sim.c_R_m, sim.c_R_m)
  ylim(-sim.c_R_m, sim.c_R_m)
  zlim(0,zLimit)
  xlabel("x (m)")
  ylabel("y (m)")
  zlabel("z (m)")

  scatter3D(sim.positions[1,:],sim.positions[2,:],sim.positions[3,:])
  savefig(filename*".png",width=width, height=height)
  close()


end

end
