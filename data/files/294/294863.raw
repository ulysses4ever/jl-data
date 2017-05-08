using Distributions

type DubinMDP
    goal::Matrix{Float64} 
    action_map::Dict{Int64, (Float64,Float64)}
    acceleration_penalty::Float64
    reward_value::Float64
    x_size::Float64
    y_size::Float64
    friction_acceleration::Float64
    
end

function make_actions()
    accel = [0.0, 0.25]
    angles = [-45.0:15:45]
    
    idx = 1
    action_map = Dict{Int64, (Float64,Float64)}()
    for ang in angles, acc in accel
        action_map[idx] = (ang, acc)
        idx+=1
    end
    return action_map
end

function DubinMDP(;goal::Matrix{Float64}=[[8.0, 9.0] [8.0, 9.0]],
                    ap::Float64=-0.1,
                    rw::Float64=1.0,
                    x::Float64=10.0,
                    y::Float64=10.0,
                    fa::Float64=0.05)
    action_map = make_actions()  
    return DubinMDP(goal, action_map, ap, rw, x, y, fa)
end

type StateSpace
    xd::Uniform
    yd::Uniform
    theta::Uniform
    x_velocity::Uniform
    y_velocity::Uniform
end

type DubinsDistribution
    x::Normal   #Normal Distribution
    y::Normal
    theta::Float64
    x_velocity::Float64
    y_velocity::Float64
    
end

function create_transition(mdp::DubinMDP) 
    x = Normal(1.0, 0.1) 
    y = Normal(1.0, 0.1) 
    return DubinsDistribution(x, y, 0.0, 0.0, 0.0)    
end

type DubinState
    x::Float64
    y::Float64
    theta::Float64
    x_velocity::Float64
    y_velocity::Float64 
end

function reward(mdp::DubinMDP, state::DubinState, action::Int64)
    goal = mdp.goal
    
    x1 = goal[1,1]
    x2 = goal[2,1]
    y1 = goal[1,2]
    y2 = goal[2,2]
     
    x = state.x
    y = state.y
       r = 0.0
    if x1 <= x <= x2 && y1 <= y <= y2 
        r += mdp.reward_value
    end
    if mdp.action_map[action][2] == 0.2
        r += mdp.acceleration_penalty
    end 

    if !inbounds(mdp, x, y) 
        r += -1e3
    end 
    return r
end

function inbounds(mdp::DubinMDP, x::Float64, y::Float64)
    if 0.0 <= x <= mdp.x_size && 0.0 <= y <= mdp.y_size 
        return true
    end  
    return false
end

function states(mdp::DubinMDP, state::DubinState, action::Int64)
    xd = Uniform(0,10)
    yd = Uniform(0,10)
    theta = Uniform(0,360)
    x_velocity = Uniform(-15, 15)
    y_velocity = Uniform(-15, 15)
    
    return StateSpace(xd, yd, theta, x_velocity, y_velocity)
end

function transition!(d::DubinsDistribution, mdp::DubinMDP, state::DubinState, action::Int64) 
    x = state.x 
    y = state.y 
    theta = state.theta 
    xv = state.x_velocity 
    yv = state.y_velocity 
    
    fa = mdp.friction_acceleration
    acceleration = mdp.action_map[action][2] 
    vi = sqrt(xv^2 + yv^2)
    
    vf = 0.0
    if vi < fa 
        vf = vi + acceleration
    else
        #vf = vi + (acceleration - fa)
        vf = vi + (acceleration)
    end
     
    new_theta = theta + mdp.action_map[action][1]
    vi_x = xv
    vi_y = yv
    vf_x = cosd(theta) * vf 
    vf_y = sind(theta) * vf
    
    xp = x + (vf_x + vi_x) / 2 #x
    yp = y + (vf_y + vi_y) / 2
    
    d.x = Normal(xp,0.1)  
    d.y = Normal(yp, 0.1)
    d.theta = theta + mdp.action_map[action][1]  
    d.x_velocity = vf_x #cosd(d.theta) * vf   
    d.y_velocity = vf_y 
 
    
   #if vi == 0.0 && vf == 0.0 && theta > 0.0
   #     d = DubinsDistribution(n, n, state.theta, 0.0, 0.0)
   #end 
    
    d
end



function Base.rand!(s::DubinState, d::DubinsDistribution)
    s.x = rand(d.x) 
    s.y = rand(d.y)
    s.theta = d.theta
    s.x_velocity = d.x_velocity
    s.y_velocity = d.y_velocity
    s
end 

