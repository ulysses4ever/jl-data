"""
particle:
particle is a base type for classical particles in physics
----
parameters:
    pos::Array{T<:Real,1}#position
    vel::Array{T<Real,1}#velocity
    mass::Real                  #mass
"""
type particle
    pos::Array{Real,1}
    vel::Array{Real,1}
    mass::Real

    particle(pos,vel,mass)=new(pos,vel,mass)
end

# particle{T<:Real}(pos::Array{T,1},vel::Array{T,1},mass::T)=particle{T}(pos,vel,mass)
# particle(pos::Array{Int64,1},vel::Array{Float64,1},mass::Float64)=particle(convert(Array{Float64,1},pos),vel,mass)
# particle(pos::Array{Float64,1},vel::Array{Int64,1},mass::Float64)=particle(pos,convert(Array{Float64,1},pos),vel,mass)
# particle(pos::Array{Float64,1},vel::Array{Float64,1},mass::Int64)=particle(pos,vel,convert(Float64,mass))

"""
L_particle:
L_particle is a base type for L-shaped particle in classical conditions
----
parameters:
    particle_set::Array{particle{T},1}
        a set of particles for classical particle type

    RightStickLength::Real
        the  Stick length on the Right

    LeftStickLength::Real
        the Stick length on the left
"""
type L_particle
    central_particle_pos::Array{Real,1}
    central_particle_vel::Array{Real,1}
    angle_pos::Array{Real,1}
    angle_vel::Array{Real,1}
    mass::Array{Real,1}
    StickLength::Array{Real,1}

    function L_particle(RightStickLength::Real,LeftStickLength::Real,ParticleA::particle...)
        #Bounds check
        if length(ParticleA)!=3
            throw(DomainError())
        end

        central_pos=ParticleA[2].pos
        central_vel=ParticleA[2].vel
        R_angle=atan((ParticleA[1].pos[2]-ParticleA[2].pos[2])/(ParticleA[1].pos[1]-ParticleA[2].pos[1]))
        L_angle=atan((ParticleA[3].pos[2]-ParticleA[2].pos[2])/(ParticleA[3].pos[1]-ParticleA[2].pos[1]))
        angle_pos=[R_angle,L_angle]

        R_omega = (ParticleA[2].vel[1]-ParticleA[1].vel[1])/(ParticleA[2].vel[2]-ParticleA[1].vel[2])*cot(R_angle)
        L_omega = (ParticleA[2].vel[1]-ParticleA[3].vel[1])/(ParticleA[2].vel[2]-ParticleA[3].vel[2])*cot(L_angle)
        angle_vel=[R_omega,L_omega]
        mass=[ParticleA[i].mass for i in collect(1:3)]

        StickLength=[RightStickLength,LeftStickLength]
        print("$(typeof(angle_pos))")
        new(central_pos,central_vel,angle_pos,angle_vel,mass,StickLength)
    end

    L_particle(
        central_pos::Array{Real,1},
        central_vel::Array{Real,1},
        α::Real,β::Real,
        ω_α::Real,ω_β::Real,
        mass::Array{Real,1},
        R_sticklength::Real,
        L_sticklength::Real
        )=new(central_pos,central_vel,[α,β],[ω_α,ω_β],mass,[R_sticklength,L_sticklength])

    function L_particle{T<:Real}(
        central_pos::Array{T,1},
        central_vel::Array{T,1},
        angle::Array{T,1},
        angle_vel::Array{T,1},
        mass::Array{T,1},
        StickLength::Array{T,1}
        )
        #bounds check
        if length(central_vel)!=2
            throw(error("central velocity out of domain"))
        elseif length(central_pos)!=2
            throw(error("central position out of domain"))
        elseif length(angle)!=2
            throw(error("angle position out of domain"))
        elseif length(angle_vel)!=2
            throw(error("angle velocity out of domain"))
        elseif length(mass)!=3
            throw(error("mass out of domain"))
        elseif length(StickLength)!=2
            throw(error("stick length out of domain"))
        end
        new(central_pos,central_vel,angle,angle_vel,mass,StickLength)
    end
end

L_particle(
        central_pos::AbstractVector,
        central_vel::AbstractVector,
        angle::AbstractVector,
        angle_vel::AbstractVector,
        mass::AbstractVector,
        StickLength::AbstractVector
        )=L_particle(promote(central_pos,central_vel,angle,angle_vel,mass,StickLength)...)