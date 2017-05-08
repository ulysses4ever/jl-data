# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 03/09/2015

module Scenario_

export Scenario, ScenarioParams, ScenarioState
export updateState, isEndState


using UAV_
using Distributions


type ScenarioParams

    seed::Union(Uint64, Nothing)

    x::Float64
    y::Float64

    dt::Float64

    cell_towers::Union(Vector{Vector{Float64}}, Nothing)

    sa_dist::Float64

    bCAS::Bool

    UAVs::Union(Vector{UAV}, Nothing)
    nUAV::Int64


    function ScenarioParams()

        self = new()

        self.seed = nothing

        self.x = 0. # ft
        self.y = 0. # ft

        self.dt = 0 # seconds

        self.cell_towers = nothing

        self.sa_dist = 0. # ft

        self.bCAS = false

        self.UAVs = nothing
        self.nUAV = 0

        return self
    end
end


type Scenario

    seed::Uint64

    x::Float64
    y::Float64

    dt::Float64

    cell_towers::Union(Vector{Vector{Float64}}, Nothing)

    UAVs::Union(Vector{UAV}, Nothing)
    nUAV::Int64

    sa_dist::Float64

    bCAS::Bool


    function Scenario(params::ScenarioParams)

        self = new()

        if params.seed != nothing
            if params.seed != 0
                self.seed = uint(params.seed)
            else
                self.seed = uint(time())
            end

            srand(self.seed)
        end

        self.x = params.x
        self.y = params.y

        self.dt = params.dt

        self.cell_towers = params.cell_towers

        self.UAVs = params.UAVs
        self.nUAV = params.nUAV

        self.sa_dist = params.sa_dist

        self.bCAS = params.bCAS

        if self.bCAS
            resolve_conflict(self)
        end

        return self
    end
end


type ScenarioState

    UAVStates::Vector{UAVState}


    function ScenarioState(sc::Scenario)

        self = new()
        self.UAVStates = UAVState[]

        for uav in sc.UAVs
            push!(self.UAVStates, UAVState(uav))
        end

        return self
    end
end


function updateState(sc::Scenario, state::ScenarioState, t::Int64)

    for i = 1:sc.nUAV
        UAV_.updateState(sc.UAVs[i], state.UAVStates[i])
    end
end


function isEndState(sc::Scenario, state::ScenarioState)

    end_flag = true

    for i = 1:sc.nUAV
        end_flag &= UAV_.isEndState(sc.UAVs[i], state.UAVStates[i])
    end

    return end_flag
end


function is_safe(p1, q1, v1, p2, q2, v2, safe_margin)

    t_max = int(ceil(min(norm(q1 - p1) / v1, norm(q2 - p2) / v2)))

    for t = 0:t_max
        u1 = p1 + (q1 - p1) / norm(q1 - p1) * v1 * t
        u2 = p2 + (q2 - p2) / norm(q2 - p2) * v2 * t

        if norm(u1 - u2) < safe_margin
            return false
        end
    end

    return true
end


function resolve_conflict(sc::Scenario)

    indexes = sortperm(rand(sc.nUAV))

    for i in 1:sc.nUAV
        uav = sc.UAVs[indexes[i]]

        p1 = uav.start_loc
        q1 = uav.end_loc
        v1 = uav.velocity

        uav.cas_loc = q1

        if i > 1
            phi = 0

            while true
                bSafe = true

                for j = 1:i-1
                    uav_ = sc.UAVs[indexes[j]]

                    p2 = uav_.start_loc
                    q2 = uav_.end_loc
                    v2 = uav_.velocity

                    if !is_safe(p1, q1, v1, p2, q2, v2, sc.sa_dist)
                        bSafe = false
                        break
                    end
                end

                if bSafe
                    if phi != 0
                        #println("rotate route ", indexes[i], " by ", phi, " degrees")
                    end
                    uav.cas_loc = q1
                    break
                else
                    phi += 5
                    q1 = [cosd(phi) -sind(phi); sind(phi) cosd(phi)] * (q1 - p1) + p1

                    dt = 0
                    while q1[1] >= 0. && q1[1] <= sc.x && q1[2] >= 0. && q1[2] <= sc.y
                        dt += 1
                        q1 += (q1 - p1) / norm(q1 - p1) * v1 * dt
                    end
                    q1 += (q1 - p1) / norm(q1 - p1) * v1 * 5
                end
            end
        end
    end
end


end


