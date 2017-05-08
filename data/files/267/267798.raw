# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 03/09/2015

module Scenario_

export Scenario, ScenarioParams, ScenarioState
export updateState, isEndState


using Distributions


type ScenarioParams

    seed::Union(Uint64, Nothing)

    x::Float64
    y::Float64

    dt::Int64

    uav_start_loc::Union(Vector{Float64}, Nothing)
    uav_end_loc::Union(Vector{Float64}, Nothing)
    uav_waypoints::Union(Vector{Vector{Float64}}, Nothing)
    uav_velocity::Float64

    uav_localization::Symbol

    # for dead reckoning
    uav_IMU_acc_instability::Union(Float64, Nothing)
    uav_IMU_acc_VRW::Union(Float64, Nothing)
    uav_IMU_gyr_instability::Union(Float64, Nothing)
    uav_IMU_gyr_ARW::Union(Float64, Nothing)

    # for radiolocation
    cell_towers::Union(Vector{Vector{Float64}}, Nothing)
    uav_rl_error_bound::Float64


    function ScenarioParams()

        self = new()

        self.seed = nothing

        self.x = 0. # ft
        self.y = 0. # ft

        self.dt = 0 # seconds

        self.uav_start_loc = nothing    # [x:ft, y:ft]
        self.uav_end_loc = nothing      # [x:ft, y:ft]
        self.uav_waypoints = nothing    # list of [x:ft, y:ft]
        self.uav_velocity = 0.          # ft/s

        self.uav_localization = :GPS_INS

        self.uav_IMU_acc_instability = nothing
        self.uav_IMU_acc_VRW = nothing
        self.uav_IMU_gyr_instability = nothing
        self.uav_IMU_gyr_ARW = nothing

        self.cell_towers = nothing
        self.uav_rl_error_bound = 0.    # ft

        return self
    end
end


type Scenario

    seed::Uint64

    x::Float64
    y::Float64

    dt::Int64

    uav_start_loc::Vector{Float64}
    uav_end_loc::Vector{Float64}
    uav_waypoints::Union(Vector{Vector{Float64}}, Nothing)
    uav_nwaypoints::Int64
    uav_velocity::Float64

    uav_localization::Symbol

    # for dead reckoning
    uav_IMU_acc_instability::Union(Float64, Nothing)
    uav_IMU_acc_VRW::Union(Float64, Nothing)
    uav_IMU_gyr_instability::Union(Float64, Nothing)
    uav_IMU_gyr_ARW::Union(Float64, Nothing)

    # for radiolocation
    cell_towers::Union(Vector{Vector{Float64}}, Nothing)
    uav_rl_error_bound::Float64
    rss_params::Vector{Float64}


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

        self.uav_start_loc = params.uav_start_loc
        self.uav_end_loc = params.uav_end_loc
        self.uav_waypoints = params.uav_waypoints
        if self.uav_waypoints != nothing
            self.uav_nwaypoints = length(self.uav_waypoints)
        else
            self.uav_nwaypoints = 0
        end
        self.uav_velocity = params.uav_velocity

        self.uav_localization = params.uav_localization

        self.uav_IMU_acc_instability = params.uav_IMU_acc_instability
        self.uav_IMU_acc_VRW = params.uav_IMU_acc_VRW
        self.uav_IMU_gyr_instability = params.uav_IMU_gyr_instability
        self.uav_IMU_gyr_ARW = params.uav_IMU_gyr_ARW

        self.cell_towers = params.cell_towers
        self.uav_rl_error_bound = params.uav_rl_error_bound

        fc = 800 # MHz
        hb = 100 # ft
        hm = 5.7 # ft

        hb *= 0.3048
        hm *= 0.3045

        a = hm -> 8.28*(log10(1.54*hm))^2 - 1.1 # large city with fc >= 400 MHz
        A = 69.55 + 26.16*log10(fc) - 13.82*log10(hb) - a(hm)
        B = 44.9 - 6.55*log10(hb)
        C = 5.4 + 2*(log10(fc/28))^2

        self.rss_params = [A, B, C]

        return self
    end
end


type ScenarioState

    uav_loc::Vector{Float64}

    uav_velocity::Vector{Float64}

    uav_waypoint_index::Int64
    uav_waypoint::Vector{Float64}

    uav_past_locs::Vector{Vector{Float64}}

    # for dead reckoning
    uav_loc_planned::Vector{Float64}
    uav_IMU_acc_bias::Vector{Float64}
    uav_IMU_gyr_bias::Vector{Float64}

    # for dead reckoning
    uav_loc_estimated::Vector{Float64}


    function ScenarioState(sc::Scenario)

        self = new()

        self.uav_loc = sc.uav_start_loc

        if sc.uav_nwaypoints > 0
            uav_phi = atand((sc.uav_waypoints[1][2] - sc.uav_start_loc[2]) / (sc.uav_waypoints[1][1] - sc.uav_start_loc[1]))
        else
            uav_phi = atand((sc.uav_end_loc[2] - sc.uav_start_loc[2]) / (sc.uav_end_loc[1] - sc.uav_start_loc[1]))
        end
        self.uav_velocity = [sc.uav_velocity * cosd(uav_phi), sc.uav_velocity * sind(uav_phi)]

        if sc.uav_nwaypoints > 0
            self.uav_waypoint_index = 1
            self.uav_waypoint = sc.uav_waypoints[self.uav_waypoint_index]
        else
            self.uav_waypoint = sc.uav_end_loc
        end

        self.uav_past_locs = (Float64, Float64)[]

        self.uav_loc_planned = sc.uav_start_loc
        self.uav_IMU_acc_bias = [0., 0.]
        self.uav_IMU_gyr_bias = [0.]

        self.uav_loc_estimated = sc.uav_start_loc

        return self
    end
end


function updateStateGPSINS(sc::Scenario, state::ScenarioState)

    delta = (state.uav_waypoint - state.uav_loc) / norm(state.uav_waypoint - state.uav_loc) * sc.uav_velocity * sc.dt

    if norm(delta) >= norm(state.uav_waypoint - state.uav_loc)
        delta_remained = norm(delta) - norm(state.uav_waypoint - state.uav_loc)
        state.uav_loc = state.uav_waypoint

        push!(state.uav_past_locs, state.uav_loc)

        if state.uav_loc != sc.uav_end_loc
            if state.uav_waypoint_index != sc.uav_nwaypoints
                state.uav_waypoint_index += 1
                state.uav_waypoint = sc.uav_waypoints[state.uav_waypoint_index]
            else
                state.uav_waypoint = sc.uav_end_loc
            end

            state.uav_loc += (state.uav_waypoint - state.uav_loc) / norm(state.uav_waypoint - state.uav_loc) * delta_remained
        end
    else
        state.uav_loc += delta
    end
end


function updateDRVelocityVector(sc::Scenario, state::ScenarioState, a_target::Vector{Float64}, w_target::Float64, dt::Float64)

    a_measured = a_target
    state.uav_IMU_acc_bias += rand(Normal(0., sqrt(sc.dt) * sc.uav_IMU_acc_instability), 2)
    a_actual = a_measured - (state.uav_IMU_acc_bias + rand(Normal(0., sc.uav_IMU_acc_VRW / sqrt(sc.dt)), 2))

    w_measured = w_target
    state.uav_IMU_gyr_bias += rand(Normal(0., sqrt(sc.dt) * sc.uav_IMU_gyr_instability))
    w_actual = w_measured - (state.uav_IMU_gyr_bias + rand(Normal(0., sc.uav_IMU_gyr_ARW / sqrt(sc.dt))))

    state.uav_velocity = [cosd(w_actual * dt) -sind(w_actual * dt); sind(w_actual * dt) cosd(w_actual * dt)] * state.uav_velocity

    phi = atand(state.uav_velocity[2] / state.uav_velocity[1])
    state.uav_velocity += [cosd(phi) -sind(phi); sind(phi) cosd(phi)] * a_actual * dt

    return a_actual, w_actual
end

function updateStateDR(sc::Scenario, state::ScenarioState)

    delta = (state.uav_waypoint - state.uav_loc_planned) / norm(state.uav_waypoint - state.uav_loc_planned) * sc.uav_velocity * sc.dt

    if norm(delta) >= norm(state.uav_waypoint - state.uav_loc_planned)
        delta_remained = norm(delta) - norm(state.uav_waypoint - state.uav_loc_planned)

        dt = norm(state.uav_waypoint - state.uav_loc_planned) / sc.uav_velocity
        dt_remained = sc.dt - dt

        a, w = updateDRVelocityVector(sc, state, [0., 0.], 0., dt)
        state.uav_loc += state.uav_velocity * dt + 1/2 * a * dt^2

        prev_uav_loc_planned = state.uav_loc_planned
        state.uav_loc_planned = state.uav_waypoint

        push!(state.uav_past_locs, state.uav_loc)

        if state.uav_loc_planned != sc.uav_end_loc
            prev_uav_waypoint = state.uav_waypoint

            if state.uav_waypoint_index != sc.uav_nwaypoints
                state.uav_waypoint_index += 1
                state.uav_waypoint = sc.uav_waypoints[state.uav_waypoint_index]
            else
                state.uav_waypoint = sc.uav_end_loc
            end

            dphi = atand((state.uav_waypoint[2] - prev_uav_waypoint[2]) / (state.uav_waypoint[1] - prev_uav_waypoint[1])) - atand((prev_uav_waypoint[2] - prev_uav_loc_planned[2]) / (prev_uav_waypoint[1] - prev_uav_loc_planned[1]))

            a, w = updateDRVelocityVector(sc, state, [0., 0.], dphi / dt_remained, dt_remained)
            state.uav_loc += state.uav_velocity * dt_remained + 1/2 * a * dt_remained^2
            state.uav_loc_planned += (state.uav_waypoint - state.uav_loc_planned) / norm(state.uav_waypoint - state.uav_loc_planned) * delta_remained
        end

    else
        state.uav_loc_planned += delta

        a, w = updateDRVelocityVector(sc, state, [0., 0.], 0., float(sc.dt))
        state.uav_loc += state.uav_velocity * sc.dt + 1/2 * a * sc.dt^2

    end
end


function RSSLoss(sc::Scenario, d::Float64)

    A, B, C = sc.rss_params

    return A + B * log10(d * 0.3048 / 1000) - C # dB, suburban area
end

function RSSdist(sc::Scenario, loss::Float64)

    A, B, C = sc.rss_params

    return 10^((loss - A + C) / B) * 1000 * 3.281 # m to ft
end

function RSSLossWithError(sc::Scenario, d::Float64)

    sigma_err = 8 # dB, 4-12dB (desert to dense urban)

    return RSSLoss(sc, d) + rand(Normal(0., sigma_err))
end

function EstimateLocationWithTowers(sc::Scenario, state::ScenarioState)

    cell_tower_indexes = [1, 2, 3]

    D = zeros(3)

    for i in cell_tower_indexes
        d = norm(state.uav_loc - sc.cell_towers[i])
        loss = RSSLossWithError(sc, d)
        D[i] = RSSdist(sc, loss)

        #println(d)
        #println(D[i])
    end 

    # trilateration
    # http://en.wikipedia.org/wiki/Trilateration

    P1 = [sc.cell_towers[cell_tower_indexes[1]], 0]
    P2 = [sc.cell_towers[cell_tower_indexes[2]], 0]
    P3 = [sc.cell_towers[cell_tower_indexes[3]], 0]

    r1 = D[1]
    r2 = D[2]
    r3 = D[3]

    ex = (P2 - P1) / norm(P2 - P1)
    i = dot(ex, P3 - P1)
    ey = (P3 - P1 - i*ex) / norm(P3 - P1 - i*ex)
    d = norm(P2 - P1)
    j = dot(ey, P3 - P1)

    x = (r1^2 - r2^2 + d^2) / (2 * d)
    y = (r1^2 - r3^2 + i^2 + j^2) / (2 * j) - i / j * x

    P = P1 + x*ex + y*ey

    state.uav_loc_estimated = P[1:2]
end

function updateStateRL(sc::Scenario, state::ScenarioState)

    EstimateLocationWithTowers(sc, state)

    #println(state.uav_loc)
    #println(state.uav_loc_estimated)

    delta = (state.uav_waypoint - state.uav_loc_estimated) / norm(state.uav_waypoint - state.uav_loc_estimated) * sc.uav_velocity * sc.dt

    #if norm(delta) >= norm(state.uav_waypoint - state.uav_loc_estimated)
    #    delta_remained = (norm(delta) - norm(state.uav_waypoint - state.uav_loc_estimated))

    #    state.uav_loc += state.uav_waypoint - state.uav_loc_estimated

    #    push!(state.uav_past_locs, state.uav_loc)

    #    if state.uav_waypoint != sc.uav_end_loc
    #        prev_uav_waypoint = state.uav_waypoint

    #        if state.uav_waypoint_index != sc.uav_nwaypoints
    #            state.uav_waypoint_index += 1
    #            state.uav_waypoint = sc.uav_waypoints[state.uav_waypoint_index]
    #        else
    #            state.uav_waypoint = sc.uav_end_loc
    #        end

    #        state.uav_loc += (state.uav_waypoint - prev_uav_waypoint) / norm(state.uav_waypoint - prev_uav_waypoint) * delta_remained
    #    end

    if norm(state.uav_loc_estimated - state.uav_waypoint) <= sc.uav_rl_error_bound
        if state.uav_waypoint != sc.uav_end_loc
            if state.uav_waypoint_index != sc.uav_nwaypoints
                state.uav_waypoint_index += 1
                state.uav_waypoint = sc.uav_waypoints[state.uav_waypoint_index]
            else
                state.uav_waypoint = sc.uav_end_loc
            end

            state.uav_loc += (state.uav_waypoint - state.uav_loc_estimated) / norm(state.uav_waypoint - state.uav_loc_estimated) * sc.uav_velocity * sc.dt
        end

    else
        state.uav_loc += delta

    end
end


function updateState(sc::Scenario, state::ScenarioState)

    push!(state.uav_past_locs, state.uav_loc)

    if sc.uav_localization == :GPS_INS
        updateStateGPSINS(sc, state)

    elseif sc.uav_localization == :deadreckoning
        updateStateDR(sc, state)

    elseif sc.uav_localization == :radiolocation
        updateStateRL(sc, state)

    end
end


function isEndState(sc::Scenario, state::ScenarioState)

    if sc.uav_localization == :GPS_INS
        if state.uav_loc == sc.uav_end_loc
            return true
        end
    elseif sc.uav_localization == :deadreckoning
        if state.uav_loc_planned == sc.uav_end_loc
            return true
        end
    elseif sc.uav_localization == :radiolocation
        if norm(state.uav_loc - sc.uav_end_loc) <= sc.uav_rl_error_bound
            return true
        end
    end

    (x, y) = state.uav_loc

    if x < 0 || x > sc.x || y < 0 || y > sc.y
        return true
    end

    return false
end


end


