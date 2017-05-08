module SPH
  using Vec
  export Particle, SetupSPH, Parameters, AABB, ApplyForces, PredictPositions, FindNeighbors,
         CalculateDensity, CalculateLambda, AverageDensity, CalculateΔp, CollisionResponse,
         UpdatePosition★, UpdateVelocity, UpdatePosition, WritePositions

  type AABB
    x_min::Float64
    x_max::Float64
    y_min::Float64
    y_max::Float64
    z_min::Float64
    z_max::Float64
  end
  function AABB()
    return(AABB(0.0, 0.0, 0.0, 0.0, 0.0, 0.0))
  end

  type Particle
    p★::Vec3
    p::Vec3
    Δp::Vec3
    v::Vec3
    ω::Vec3
    λ::Float64
    ρ::Float64
    neighbors::Array{Particle}
  end
  function Particle()
    return Particle(Vec3(),Vec3(),Vec3(),Vec3(),Vec3(),0.0,0.0,Array(Particle,0))
  end

  type Parameters
    spacing::Float64
    h::Float64
    mass::Float64
    Δt::Float64
    ρ0::Float64
  end
  function Parameters()
    return Parameters(0.0, 0.0, 0.0, 0.0, 0.0)
  end

  function SetupSPH(particles, params, walls)
    coords = readcsv("sim-0.csv")
    for i in 1:size(coords,1)
      push!(particles, Particle())
      particles[end].p = Vec3(coords[i,1], coords[i,2], coords[i,3])
      particles[end].p★ = particles[end].p
      particles[end].v = Vec3(0.0)
    end
    println("Read in ", length(particles), " particles")

    params.spacing = particles[2].p.x - particles[1].p.x
    params.h = 2.0 * params.spacing
    params.ρ0 = 1000.0
    params.mass = params.spacing^3.0 * params.ρ0
    params.Δt = 1/60.0

    walls.x_max = maximum(coords[:,1]) * 1.5
    walls.y_max = maximum(coords[:,2])
    walls.z_max = maximum(coords[:,3]) * 2.0
    println(walls)
  end

  ########################################
  ############ SPH functions #############
  ########################################

  function W(r, h)
    r_mag = mag(r)
    if r_mag > h return 0.0 end

    return 315.0/(65.0*π*h^9)*(h^2 - r_mag^2)^3
  end

  function ∇W(r, h)
    r_mag = mag(r)
    if r_mag > h return Vec3(0.0) end

    magnitude = -45.0/(π*h^6)*(h - r_mag)^2
    r_unit = r / r_mag
    return magnitude * r_unit
  end

  function ApplyForces(particles, params)
    for particle in particles
      gravity = Vec3(0.0, 0.0, -9.8)
      particle.v = particle.v + params.Δt * gravity
    end
  end

  function PredictPositions(particles, params)
    for particle in particles
      particle.p★ = particle.p + params.Δt * particle.v
    end
  end

  function FindNeighbors(particles, params)
    for pᵢ in particles
      resize!(pᵢ.neighbors, 0)
      for pⱼ in particles
        if(pᵢ == pⱼ) continue end
        r = pᵢ.p★ - pⱼ.p★
        if mag(r) < params.h
          push!(pᵢ.neighbors, pⱼ)
        end
      end
    end
  end

  function CalculateDensity(particles, params)
    for pᵢ in particles
      pᵢ.ρ = params.mass * W(Vec3(0.0), params.h)
      for pⱼ in pᵢ.neighbors
        pᵢ.ρ += params.mass * W(pᵢ.p★ - pⱼ.p★, params.h)
      end
    end
  end

  function AverageDensity(particles, params)
    ρ_avg = 0.0
    for pᵢ in particles
      ρ_avg += pᵢ.ρ
    end
    ρ_avg /= length(particles)
    println("averege ρ: ", ρ_avg)
  end

  function CalculateLambda(particles, params)
    for pᵢ in particles
      Σ∇Ci2 = 0.0
      grad = Vec3(0.0)
      Σi = Vec3(0.0)
      for pⱼ in pᵢ.neighbors
        grad = ∇W(pᵢ.p★ - pⱼ.p★, params.h)
        Σi += grad
        # k = j
        Σ∇Ci2 += mag(grad/params.ρ0)^2.0
      end
      # k = i
      Σ∇Ci2 += mag(Σi/params.ρ0)^2.0
      Ci = pᵢ.ρ/params.ρ0 - 1.0
      ϵ = 1.0
      pᵢ.λ = -Ci / (Σ∇Ci2 + ϵ)
    end
  end

  function CalculateΔp(particles, params)
    for pᵢ in particles
      pᵢ.Δp = Vec3(0.0)
      for pⱼ in pᵢ.neighbors
        pᵢ.Δp += (pᵢ.λ + pⱼ.λ) * ∇W(pᵢ.p★ - pⱼ.p★, params.h)
      end
      pᵢ.Δp /= params.ρ0
    end
  end

  function CollisionResponse(particles, params, walls)
    for pᵢ in particles
      x = pᵢ.p★.x
      y = pᵢ.p★.y
      z = pᵢ.p★.z
      if x < walls.x_min
        x = walls.x_min
      elseif x > walls.x_max
        x = walls.x_max
      end
      if y < walls.y_min
        y = walls.y_min
      elseif y > walls.y_max
        y = walls.y_max
      end
      if z < walls.z_min
        z = walls.z_min
      elseif z > walls.z_max
        z = walls.z_max
      end
      pᵢ.p★ = Vec3(x,y,z)
    end
  end

  function UpdatePosition★(particles, params)
    for pᵢ in particles
      pᵢ.p★ += pᵢ.Δp
    end
  end

  function UpdateVelocity(particles, params)
    for pᵢ in particles
      pᵢ.v = 1.0/params.Δt * (pᵢ.p★ - pᵢ.p)
    end
  end

  function UpdatePosition(particles, params)
    for pᵢ in particles
      pᵢ.p = pᵢ.p★
    end
  end

  function WritePositions(particles, i)
    out_file = open("sim-"*string(i)*".csv" ,"w")
    for pᵢ in particles
      write(out_file, join((pᵢ.p.x, pᵢ.p.y, pᵢ.p.z), ","),"\n")
    end
    close(out_file)
  end

end

using SPH
using Vec

function main()
  particles = Vector{Particle}(0)
  params = Parameters()
  walls = AABB()

  SetupSPH(particles, params, walls)
  println(params)

  for i in 1:200
    ApplyForces(particles, params)
    PredictPositions(particles, params)
    FindNeighbors(particles, params)

    for j in 1:4
      CalculateDensity(particles, params)
      CalculateLambda(particles, params)
      CalculateΔp(particles, params)
      CollisionResponse(particles, params, walls)
      UpdatePosition★(particles, params)
    end

    AverageDensity(particles, params)

    UpdateVelocity(particles, params)
    UpdatePosition(particles, params)

    WritePositions(particles, i)
  end

end

main()
