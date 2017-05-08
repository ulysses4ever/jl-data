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

    landing_bases::Union(Vector{Vector{Float64}}, Nothing)

    jamming_time::Float64
    jamming_center::Vector{Float64}
    jamming_radius::Float64

    UAVs::Union(Vector{UAV}, Nothing)
    nUAV::Int64

    sa_dist::Float64

    bCAS::Bool


    function ScenarioParams()

        self = new()

        self.seed = nothing

        self.x = 0. # ft
        self.y = 0. # ft

        self.dt = 0 # seconds

        self.cell_towers = nothing

        self.landing_bases = nothing

        self.jamming_time = Inf
        self.jamming_center = [0., 0.]
        self.jamming_radius = 0.

        self.UAVs = nothing
        self.nUAV = 0

        self.sa_dist = 0. # ft

        self.bCAS = false

        return self
    end
end


type Scenario

    seed::Uint64

    x::Float64
    y::Float64

    dt::Float64

    cell_towers::Union(Vector{Vector{Float64}}, Nothing)

    landing_bases::Union(Vector{Vector{Float64}}, Nothing)

    jamming_time::Float64
    jamming_center::Vector{Float64}
    jamming_radius::Float64

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

        self.landing_bases = params.landing_bases

        self.jamming_time = params.jamming_time
        self.jamming_center = params.jamming_center
        self.jamming_radius = params.jamming_radius

        self.UAVs = params.UAVs
        self.nUAV = params.nUAV

        for i = 1:self.nUAV
            uav = self.UAVs[i]
            uav.sc = self
        end

        self.sa_dist = params.sa_dist

        self.bCAS = params.bCAS

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

    if t == sc.jamming_time
        if sc.bCAS
            indexes = Int64[]

            for i = 1:sc.nUAV
                uav_state = state.UAVStates[i]

                if norm(uav_state.curr_loc - sc.jamming_center) <= sc.jamming_radius
                    push!(indexes, i)
                end
            end

            resolve_conflict(sc, state, indexes)

            for i in 1:length(indexes)
                uav = sc.UAVs[indexes[i]]
                uav_state = state.UAVStates[indexes[i]]

                p1 = uav_state.curr_loc
                index, q1, v1 = uav_state.advisory

                while norm(q1 - sc.jamming_center) > sc.jamming_radius
                    q1 -= (q1 - p1) / norm(q1 - p1) * v1
                end
                q1 += (q1 - p1) / norm(q1 - p1) * v1 * 10

                if index != nothing
                    uav_state.advisory = (index - 1, q1, v1)
                else
                    uav_state.advisory = (index, q1, v1)
                end
            end
        end
    end

    if t > 0
        for i = 1:sc.nUAV
            UAV_.updateState(sc.UAVs[i], state.UAVStates[i], t)
        end
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


function getWaypointOutOfGPSLoss(sc::Scenario, uav::UAV, uav_state::UAVState)

    index = nothing
    loc = uav.end_loc

    if uav.nwaypoints > 0 && uav_state.waypoint != uav.end_loc
        for i = uav_state.waypoint_index:uav.nwaypoints+1
            if i != uav.nwaypoints+1
                if norm(uav.waypoints[i] - sc.jamming_center) > sc.jamming_radius
                    index = i
                    loc = uav.waypoints[i]
                    break
                end
            end
        end
    end

    return index, loc
end


function resolve_conflict(sc::Scenario, state::ScenarioState, indexes::Vector{Int64})

    shuffle!(indexes)
    nindex = length(indexes)

    dphi_list = Float64[]
    ndphilist = 72
    push!(dphi_list, 0.)
    dphi = 360 / ndphilist
    for j = 1:((ndphilist / 2) - 1)
        push!(dphi_list, dphi * j)
        push!(dphi_list, - dphi * j)
    end
    push!(dphi_list, 180.)

    for i in 1:nindex
        uav = sc.UAVs[indexes[i]]
        uav_state = state.UAVStates[indexes[i]]

        p1 = uav_state.curr_loc
        index, q1 = getWaypointOutOfGPSLoss(sc, uav, uav_state)
        v1 = uav.velocity

        #println("uav ", uav.number, ", velocity: ", v1, ", dphi: 0.")

        uav_state.bAdvisory = true
        uav_state.advisory = (index, q1, v1)
        uav_state.loss_loc = uav_state.curr_loc

        v_list = Float64[]
        nvlist = 9
        push!(v_list, v1)
        dv = (uav.velocity_max - uav.velocity_min) / (nvlist - 1)
        for j = 1:((nvlist - 1) / 2)
            push!(v_list, v1 + dv * j)
            push!(v_list, v1 - dv * j)
        end

        if i > 1
            q1_ = q1

            v_index = 1
            dphi_index = 1
            dphi = 0.

            while true
                bSafe = true

                for j = 1:i-1
                    uav_ = sc.UAVs[indexes[j]]
                    uav_state_ = state.UAVStates[indexes[j]]

                    p2 = uav_state_.curr_loc
                    (index2, q2, v2) = uav_state_.advisory

                    if !is_safe(p1, q1_, v1, p2, q2, v2, sc.sa_dist * 2)
                        bSafe = false
                        break
                    end
                end

                if bSafe
                    #println("uav ", uav.number, ", velocity: ", v1, ", dphi: ", dphi)
                    uav_state.advisory = (index, q1_, v1)
                    break
                else
                    v_index += 1

                    if v_index <= nvlist
                        v1 = v_list[v_index]
                    else
                        v_index = 1
                        v1 = v_list[v_index]

                        dphi_index += 1
                        dphi = dphi_list[dphi_index]
                    end

                    q1_ = [cosd(dphi) -sind(dphi); sind(dphi) cosd(dphi)] * (q1 - p1) + p1

                    #dt = 0
                    #while q1[1] >= 0. && q1[1] <= sc.x && q1[2] >= 0. && q1[2] <= sc.y
                    #    dt += 1
                    #    q1 += (q1 - p1) / norm(q1 - p1) * v1 * dt
                    #end
                    #q1 += (q1 - p1) / norm(q1 - p1) * v1 * 5

                    #if norm(q1 - sc.jamming_center) <= sc.jamming_radius
                    #    if index != nothing
                    #        if index + 1 <= uav.nwaypoints
                    #            index += 1
                    #            q1 = uav.waypoints[index]
                    #        end
                    #    end
                    #end
                end
            end
        end
    end
end


end


