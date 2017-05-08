module ChargedParticleVisualization_Gadfly

export plotParticlesXY,plot2dHistogramXZ,plot2dHistogramXY

using Compat
using Gadfly
using Colors
using ChargedParticleVisualization_Utilities

function plotParticlesXY(particles,filename)
  boxsize = 1e-3
  width = 1920
  height = 1080
  ratio = width / height
  positions = positionsFromParticleCloud(particles)
  pl = Gadfly.plot(x=positions[1,:], y=positions[2,:],Geom.point,
            Theme(highlight_width=0.0cm,default_point_size=1px),
            Coord.Cartesian(ymin=-boxsize,ymax=boxsize,xmin=-boxsize*ratio,xmax=boxsize*ratio),
            )

  Gadfly.draw(PNG(filename*".png", width*px, height*px), pl)
end



function plot2dHistogram(pos,filename)
  width = 1000
  height = 1000
  boxsize = 1e-3
  nelems = 50
  xE = linspace(-boxsize,boxsize,nelems)
  yE = linspace(-boxsize,boxsize,nelems)

  x,y,freqs = hist2d(pos,xE,yE)

  X = zeros((length(x)-1)*(length(y)-1))
  Y = zeros((length(x)-1)*(length(y)-1))
  Z = zeros((length(x)-1)*(length(y)-1))

  i = 1
  for xi= 1:length(x)-1
    for yi= 1:length(y)-1
      X[i] = (x[xi]+x[xi+1])/2
      Y[i] = (y[yi]+y[yi+1])/2
      Z[i]= freqs[xi,yi]
      i+=1
    end
  end
  pl = Gadfly.plot(x=X, y=Y,color=Z,Gadfly.Geom.rectbin,
            Gadfly.Scale.ContinuousColorScale(
              Scale.lab_gradient(colorant"#002222",
                                 colorant"#DD0044")))
            #,
            #  minvalue=0,
            #  maxvalue=length(sim.particles)),
            #                )

  Gadfly.draw(PNG(filename*".png", width*px, height*px), pl)
end

function plot2dHistogramXY(sim,filename)
  pos = transpose(sim.positions[1:2,:])
  plot2dHistogram(pos,filename)
end

function plot2dHistogramXZ(sim,filename)
  pos = transpose(sim.positions[[1,3],:])
  plot2dHistogram(pos,filename)
end


end
