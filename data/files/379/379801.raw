using Winston

function plotParticlesXY(particles,filename)
  boxsize = 1e-3
  positions = zeros(3,length(particles))
  for i in eachindex(particles)
    positions[:,i] = particles[i].location
  end
  pl = plot(positions[1,:],positions[2,:], "r.")
  width = 1920
  height = 1080
  ratio = width / height
  xlim(-boxsize*ratio,boxsize*ratio)
  ylim(-boxsize,boxsize)
  savefig(filename*".png",width=width, height=height)
end
