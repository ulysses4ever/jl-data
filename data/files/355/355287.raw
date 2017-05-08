using PyPlot
include("DubinMDP.jl")

import PyPlot: plot

type DubinHistory
    x::Vector{Float64}
    y::Vector{Float64}
    v::Vector{Float64}
    t::Vector{Float64}
    s::Vector{DubinState}
    n::Int64
end

function DubinHistory()
    x=Float64[];y=Float64[]
    v=Float64[];t=Float64[]
    s=DubinState[]
    n=0
    return DubinHistory(x,y,v,t,s,n)
end

function Base.push!(h::DubinHistory, s::DubinState)
    v = sqrt(s.x^2+s.y^2)
    push!(h.x, s.x) 
    push!(h.y, s.y) 
    push!(h.t, s.theta)
    push!(h.v, v)
    push!(h.s, s)
    h.n+=1
end


function plot(mdp::DubinMDP)
    goal = mdp.goal
    gx=zeros(5); gy=zeros(5)
    bx=zeros(5); by=zeros(5)
    gx[1] = goal[1,1]; gy[1] = goal[1,2]
    gx[2] = goal[1,1]; gy[2] = goal[2,2]
    gx[3] = goal[2,1]; gy[3] = goal[2,2]
    gx[4] = goal[2,1]; gy[4] = goal[1,2]
    gx[5] = goal[1,1]; gy[5] = goal[1,2]
    println(gx)
    println(gy)
    plot(gx, gy, color="green", lw=2.0)
    xlim([0.0, mdp.x_size])
    ylim([0.0, mdp.y_size])
    xlabel("x")
    ylabel("y")
    title("Vehicle Path")
    grid()
end

function plot(h::DubinHistory)
    for i = 1:h.n
        plot(h.s[i])
    end
    plot(h.x, h.y, color="blue",lw=1.5)
end

function plot(s::DubinState)
    #norm = sqrt(s.x^2+s.y^2) 
    norm = 2*sqrt(s.x_velocity^2+s.y_velocity^2) 
    #plot([s.x,s.x+s.x_velocity/norm], [s.y, s.y+s.y_velocity/norm],color="red",lw=1.5)
    plot([s.x,s.x+s.x_velocity/norm], [s.y, s.y+s.y_velocity/norm],color="red",lw=1.5)
    plot(s.x, s.y,color="red",marker="o")
end

function sim!(h::DubinHistory, mdp::DubinMDP, s0::DubinState, actions::Vector{Int64})
    d = create_transition(mdp)
    s = deepcopy(s0)
    push!(h,s0)
    for a in actions
        println(s)
        transition!(d, mdp, s, a)
        rand!(s, d)
        sp = deepcopy(s)
        push!(h, sp)
    end
end

mdp = DubinMDP()
s0 = DubinState(1.0, 1.0, 0.0, 0.0, 0.0)
#acts = [20, 12, 12, 11, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18]
acts = [10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 6, 6, 6, 6, 10, 10, 10, 8, 8, 8] 
acts = [8, 8, 8, 8, 8, 10, 8, 8, 8, 10, 8, 8, 8, 10, 8, 8, 8] 
acts = [8, 7, 7, 10, 7, 7, 7, 9, 7, 7, 7, 9, 7, 7, 7, 9, 7, 7, 7, 9, 7, 7, 7, 7, 7, 7]
acts = [8, 10, 7, 9, 9, 7, 9, 9, 7, 9, 9, 7, 5, 5, 7, 5, 5, 7, 5, 5, 7, 7, 7, 7, 7, 7]
h = DubinHistory()
sim!(h,mdp,s0,acts)
plot(mdp)
plot(h)
