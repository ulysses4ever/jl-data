module LBrownian

# using JLD

include("base.jl")

function next_timestep!(free_particle::particle,dt=1e-6)
    dB = sqrt(dt)*randn(length(free_particle.pos));
    free_particle.vel+=1/free_particle.mass*dB
    free_particle.pos+=free_particle.vel*dt
    return free_particle.pos
end

function next_timestep!(Free_L_Particle::L_particle,dt=1e-6)
    dB=sqrt(dt)*randn(6)
    v=Free_L_Particle.central_particle_vel
    θ=Free_L_Particle.angle_pos
    ω=Free_L_Particle.angle_vel
    m=Free_L_Particle.mass[1]
    l = Free_L_Particle.StickLength[1]
    # α=Free_L_Particle.angle_pos[1]
    # β=Free_L_Particle.angle_pos[2]
    # ω_α=Free_L_Particle.angle_vel[1]
    # ω_β=Free_L_Particle.angle_vel[2]

    v[1]+=
        (dB[1] - cot(θ[1])*dB[2] - 
        dt*m*(cot(θ[1])*v[1] + v[2])*ω[1] - 
        cos(θ[2])*csc(θ[1])*sec(θ[1])*(-(sin(θ[2])*dB[1]) + 
        cos(θ[2])*dB[2] + dt*m*(cos(θ[2])*v[1] + 
        sin(θ[2])*v[2])*ω[2]) + 
        csc(θ[1])*sec(θ[1])*(dB[2] + dB[6] + 
        dB[4] + dt*l*m*cos(θ[1])*ω[1]^2 + 
        dt*l*m*cos(θ[2])*ω[2]^2) + 
        (csc(θ[1])*sec(θ[1])*(-4 + cos(2*θ[1]) + cos(2*θ[2]) - sin(2*θ[2]))*
        ((cos(2*θ[1] - θ[2]) + 5*cos(θ[2]))*(-(sin(θ[2])*dB[1]) + 
        cos(θ[2])*dB[2] + dt*m*(cos(θ[2])*v[1] + 
        sin(θ[2])*v[2])*ω[2]) - 
        (5 + cos(2*θ[1]))*(dB[2] + dB[6] + 
        dB[4] + dt*l*m*cos(θ[1])*ω[1]^2 + 
        dt*l*m*cos(θ[2])*ω[2]^2) + 
        2*cos(θ[1])*(-2*sin(θ[1])*dB[1] + 
        3*cos(θ[1])*dB[2] + sin(θ[1])*dB[5] + 
        sin(θ[1])*dB[3] + 3*dt*m*cos(θ[1])*v[1]*
        ω[1] + 3*dt*m*sin(θ[1])*v[2]*
        ω[1] + dt*l*m*cos(θ[1])*sin(θ[1])*ω[1]^2 + 
        dt*l*m*cos(θ[2])*sin(θ[1])*ω[2]^2)))/
        (-19 + cos(2*θ[1]) + cos(2*(θ[1] - θ[2])) + 5*cos(2*θ[2]) - sin(2*θ[1]) + 
        sin(2*(θ[1] - θ[2])) - 5*sin(2*θ[2])))/m

    v[2]+=
        (-2*(-((cos(2*θ[1] - θ[2]) + 5*cos(θ[2]))*(-(sin(θ[2])*dB[1]) + 
        cos(θ[2])*dB[2] + dt*m*(cos(θ[2])*v[1] + 
        sin(θ[2])*v[2])*ω[2])) + 
        (5 + cos(2*θ[1]))*(dB[2] + dB[6] + 
        dB[4] + dt*l*m*cos(θ[1])*ω[1]^2 + 
        dt*l*m*cos(θ[2])*ω[2]^2) - 
        2*cos(θ[1])*(-2*sin(θ[1])*dB[1] + 
        3*cos(θ[1])*dB[2] + sin(θ[1])*dB[5] + 
        sin(θ[1])*dB[3] + 3*dt*m*cos(θ[1])*v[1]*
        ω[1] + 3*dt*m*sin(θ[1])*v[2]*
        ω[1] + dt*l*m*cos(θ[1])*sin(θ[1])*ω[1]^2 + 
        dt*l*m*cos(θ[2])*sin(θ[1])*ω[2]^2)))/
        (m*(-19 + cos(2*θ[1]) + cos(2*(θ[1] - θ[2])) + 5*cos(2*θ[2]) - sin(2*θ[1]) + 
        sin(2*(θ[1] - θ[2])) - 5*sin(2*θ[2])))

        ω[1]+=
          (sec(θ[1])*(dB[2] + dB[6] + dB[4] + 
          dt*l*m*cos(θ[1])*ω[1]^2 + dt*l*m*cos(θ[2])*
          ω[2]^2 - cos(θ[2])*(-(sin(θ[2])*dB[1]) + 
          cos(θ[2])*dB[2] + dt*m*(cos(θ[2])*v[1] + 
          sin(θ[2])*v[2])*ω[2]) + 
          (2*(-3 + cos(θ[2])^2 - cos(θ[2])*sin(θ[2]))*
          ((cos(2*θ[1] - θ[2]) + 5*cos(θ[2]))*(-(sin(θ[2])*dB[1]) + 
          cos(θ[2])*dB[2] + dt*m*(cos(θ[2])*v[1] + 
          sin(θ[2])*v[2])*ω[2]) - 
          (5 + cos(2*θ[1]))*(dB[2] + dB[6] + 
          dB[4] + dt*l*m*cos(θ[1])*ω[1]^2 + 
          dt*l*m*cos(θ[2])*ω[2]^2) + 
          2*cos(θ[1])*(-2*sin(θ[1])*dB[1] + 
          3*cos(θ[1])*dB[2] + sin(θ[1])*dB[5] + 
          sin(θ[1])*dB[3] + 3*dt*m*cos(θ[1])*v[1]*
          ω[1] + 3*dt*m*sin(θ[1])*v[2]*
          ω[1] + dt*l*m*cos(θ[1])*sin(θ[1])*ω[1]^
          2 + dt*l*m*cos(θ[2])*sin(θ[1])*ω[2]^2)))/
          (-19 + cos(2*θ[1]) + cos(2*(θ[1] - θ[2])) + 5*cos(2*θ[2]) - sin(2*θ[1]) + 
          sin(2*(θ[1] - θ[2])) - 5*sin(2*θ[2]))))/(l*m)

    ω[2]+=
        (-(sin(θ[2])*dB[1]) + cos(θ[2])*dB[2] + 
        dt*m*cos(θ[2])*v[1]*ω[2] + 
        dt*m*sin(θ[2])*v[2]*ω[2] - 
        (2*(cos(θ[2]) - sin(θ[2]))*((cos(2*θ[1] - θ[2]) + 5*cos(θ[2]))*
        (-(sin(θ[2])*dB[1]) + cos(θ[2])*dB[2] + 
        dt*m*(cos(θ[2])*v[1] + sin(θ[2])*v[2])*
        ω[2]) - (5 + cos(2*θ[1]))*(dB[2] + 
        dB[6] + dB[4] + dt*l*m*cos(θ[1])*
        ω[1]^2 + dt*l*m*cos(θ[2])*ω[2]^2) + 
        2*cos(θ[1])*(-2*sin(θ[1])*dB[1] + 
        3*cos(θ[1])*dB[2] + sin(θ[1])*dB[5] + 
        sin(θ[1])*dB[3] + 3*dt*m*cos(θ[1])*v[1]*
        ω[1] + 3*dt*m*sin(θ[1])*v[2]*
        ω[1] + dt*l*m*cos(θ[1])*sin(θ[1])*ω[1]^2 + 
        dt*l*m*cos(θ[2])*sin(θ[1])*ω[2]^2)))/
        (-19 + cos(2*θ[1]) + cos(2*(θ[1] - θ[2])) + 5*cos(2*θ[2]) - sin(2*θ[1]) + 
        sin(2*(θ[1] - θ[2])) - 5*sin(2*θ[2])))/(l*m)

    Free_L_Particle.central_particle_pos[1]+=v[1]*dt
    Free_L_Particle.central_particle_pos[2]+=v[2]*dt
    θ[1]+=ω[1]*dt
    θ[2]+=ω[2]*dt

    return (Free_L_Particle.central_particle_pos,θ)
end

function time_evolution!(file::AbstractString,L::L_particle,time_step::Int64,dt=1e-6)
    outputfile=open(file,"w")
    for i in collect(1:time_step)
        (pos,angle) = next_timestep!(L,dt)
        print("angle:$(angle[1]+angle[2])\n")
        write(outputfile,"$(pos[1])\t$(pos[2])\t$(angle[1])\t$(angle[2])\n")
    end
    close(outputfile)
end

function time_evolution!(file::AbstractString,free_par::particle,time_step::Int64,dt=1e-6)
    outputfile=open(file,"w")
    for i in collect(1:time_step)
        pos = next_timestep!(free_par,dt)
        write(outputfile,"$(pos[1])\t$(i*dt)\n")
    end
    close(outputfile)
end

export next_timestep!,time_evolution!,L_particle,particle

end

using LBrownian

 test = L_particle([0,0],[0,0],[π/3,-π/3],[0,0],[1e-6,1e-6,1e-6],[0.1,0.1])
# test = particle([0.0],[0.0],1e-3)
time_evolution!("data.dat",test,convert(Int64,1e3))
run(`python draw.py`)
# run(`gnuplot draw.gnu`)
# run(`eog test.png`)