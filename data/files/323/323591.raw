using PyPlot

function plotParticlesXY(particles,filename)
  boxsize = 1e-3
  positions = zeros(3,length(particles))
  for i in eachindex(particles)
    positions[:,i] = particles[i].location
  end
  #figure(width=600, height=400)
  ioff()
  pl = plot(positions[1,:],positions[2,:], "r.")
  width = 1920
  height = 1080
  ratio = width / height
  xlim(-boxsize*ratio,boxsize*ratio)
  ylim(-boxsize,boxsize)
  #display(pl)
  #savefig(filename*".png",width=width, height=height)
  #pl = plot(x=positions[1,:], y=positions[2,:])
  #draw(PNG(filename*".png", 4inch, 4inch), pl)

end
