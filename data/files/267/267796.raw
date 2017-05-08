# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 04/02/2015

module UAV_

export UAV, UAVState
export updateState, isEndState


using Distributions


type RSSParams

    A::Float64
    B::Float64
    C::Float64

    sigma_err::Float64


    function RSSParams()

        self = new()

        # XXX fc, hb, hm, and sigma_err are global parameters
        fc = 800 # MHz
        hb = 100 # ft
        hm = 5.7 # ft

        hb *= 0.3048
        hm *= 0.3045

        a = hm -> 8.28*(log10(1.54*hm))^2 - 1.1 # large city with fc >= 400 MHz
        self.A = 69.55 + 26.16*log10(fc) - 13.82*log10(hb) - a(hm)
        self.B = 44.9 - 6.55*log10(hb)
        self.C = 5.4 + 2*(log10(fc/28))^2

        self.sigma_err = 2 # dB, 4-12dB (desert to dense urban)

        return self
    end
end


type UAV

    sc::Any

    number::Int64

    start_loc::Union(Vector{Float64}, Nothing)
    end_loc::Union(Vector{Float64}, Nothing)

    waypoints::Union(Vector{Vector{Float64}}, Nothing)
    nwaypoints::Int64

    velocity::Float64

    GPS_loss_policy::Symbol
    localization::Symbol

    # for dead reckoning
    IMU_acc_instability::Union(Float64, Nothing)
    IMU_acc_VRW::Union(Float64, Nothing)
    IMU_gyr_instability::Union(Float64, Nothing)
    IMU_gyr_ARW::Union(Float64, Nothing)

    # for radiolocation
    rss_params::RSSParams
    rl_error_bound::Float64


    function UAV()

        self = new()

        self.sc = nothing

        self.number = 0

        self.start_loc = nothing    # [x:ft, y:ft]
        self.end_loc = nothing      # [x:ft, y:ft]

        self.waypoints = nothing    # list of [x:ft, y:ft]
        self.nwaypoints = 0

        self.velocity = 0.          # ft/s

        self.GPS_loss_policy = :nav
        self.localization = :GPS_INS

        self.IMU_acc_instability = nothing
        self.IMU_acc_VRW = nothing
        self.IMU_gyr_instability = nothing
        self.IMU_gyr_ARW = nothing

        self.rss_params = RSSParams()
        self.rl_error_bound = 0.    # ft

        return self
    end
end


type UAVState

    number::Int64

    status::Symbol

    curr_loc::Vector{Float64}
    past_locs::Vector{Vector{Float64}}

    waypoint_index::Int64
    waypoint::Vector{Float64}

    velocity::Vector{Float64}

    bAdvisory::Bool
    advisory::Union((Union(Int64, Nothing), Vector{Float64}), Nothing)
    loss_loc::Union(Vector{Float64}, Nothing)

    base_loc::Union(Vector{Float64}, Nothing)

    # for dead reckoning
    loc_planned::Vector{Float64}
    IMU_acc_bias::Vector{Float64}
    IMU_gyr_bias::Vector{Float64}

    # for radiolocation
    cell_towers::Union(Vector{Vector{Float64}}, Nothing)
    loc_estimated::Vector{Float64}
    P::Array{Float64, 2}    # Kalman error covariance matrix


    function UAVState(uav::UAV)

        self = new()

        self.number = uav.number

        self.status = :flying

        self.curr_loc = uav.start_loc
        self.past_locs = (Float64, Float64)[]

        if uav.nwaypoints > 0
            self.waypoint_index = 1
            self.waypoint = uav.waypoints[self.waypoint_index]

            phi = atan2(uav.waypoints[1][2] - uav.start_loc[2], uav.waypoints[1][1] - uav.start_loc[1]) * 180/pi
        else
            self.waypoint = uav.end_loc

            phi = atan2(uav.end_loc[2] - uav.start_loc[2], uav.end_loc[1] - uav.start_loc[1]) * 180/pi
        end

        self.velocity = [uav.velocity * cosd(phi), uav.velocity * sind(phi)]

        self.bAdvisory = false
        self.advisory = nothing
        self.loss_loc = nothing

        self.base_loc = nothing

        self.loc_planned = uav.start_loc
        self.IMU_acc_bias = [0., 0.]
        self.IMU_gyr_bias = [0.]

        self.cell_towers = uav.sc.cell_towers
        self.loc_estimated = uav.start_loc
        self.P = zeros(2, 2)

        return self
    end

end


function updateStateGPSINS(uav::UAV, state::UAVState)

    delta = (state.waypoint - state.curr_loc) / norm(state.waypoint - state.curr_loc) * uav.velocity * uav.sc.dt

    if state.status == :flying
        end_loc = uav.end_loc
    elseif state.status == :base
        end_loc = state.base_loc
    end

    if norm(delta) >= norm(state.waypoint - state.curr_loc)
        delta_remained = norm(delta) - norm(state.waypoint - state.curr_loc)
        state.curr_loc = state.waypoint

        push!(state.past_locs, state.curr_loc)

        if state.curr_loc != end_loc
            if state.waypoint_index < uav.nwaypoints
                state.waypoint_index += 1
                state.waypoint = uav.waypoints[state.waypoint_index]
            else
                state.waypoint = end_loc
            end

            state.curr_loc += (state.waypoint - state.curr_loc) / norm(state.waypoint - state.curr_loc) * delta_remained
        end
    else
        state.curr_loc += delta
    end
end


function updateDRVelocityVector(uav::UAV, state::UAVState, a_target::Vector{Float64}, w_target::Float64, dt::Float64)

    a_measured = a_target
    state.IMU_acc_bias += rand(Normal(0., sqrt(uav.sc.dt) * uav.IMU_acc_instability), 2)
    a_actual = a_measured - (state.IMU_acc_bias + rand(Normal(0., uav.IMU_acc_VRW / sqrt(uav.sc.dt)), 2))

    w_measured = w_target
    state.IMU_gyr_bias += rand(Normal(0., sqrt(uav.sc.dt) * uav.IMU_gyr_instability))
    w_actual = w_measured - (state.IMU_gyr_bias + rand(Normal(0., uav.IMU_gyr_ARW / sqrt(uav.sc.dt))))

    state.velocity = [cosd(w_actual * dt) -sind(w_actual * dt); sind(w_actual * dt) cosd(w_actual * dt)] * state.velocity

    phi = atan2(state.velocity[2], state.velocity[1]) * 180 / pi
    state.velocity += [cosd(phi) -sind(phi); sind(phi) cosd(phi)] * a_actual * dt

    return a_actual, w_actual
end


function updateStateDR(uav::UAV, state::UAVState)

    delta = (state.waypoint - state.loc_planned) / norm(state.waypoint - state.loc_planned) * uav.velocity * uav.sc.dt

    if state.status == :flying
        end_loc = uav.end_loc
    elseif state.status == :base
        end_loc = state.base_loc
    end

    if norm(delta) >= norm(state.waypoint - state.loc_planned)
        delta_remained = norm(delta) - norm(state.waypoint - state.loc_planned)

        dt = norm(state.waypoint - state.loc_planned) / uav.velocity
        dt_remained = uav.sc.dt - dt

        a, w = updateDRVelocityVector(uav, state, [0., 0.], 0., dt)
        state.curr_loc += state.velocity * dt + 1/2 * a * dt^2

        prev_loc_planned = state.loc_planned
        state.loc_planned = state.waypoint

        push!(state.past_locs, state.curr_loc)

        if state.loc_planned != end_loc
            prev_waypoint = state.waypoint

            if state.waypoint_index < uav.nwaypoints
                state.waypoint_index += 1
                state.waypoint = uav.waypoints[state.waypoint_index]
            else
                state.waypoint = end_loc
            end

            dphi = (atan2(state.waypoint[2] - prev_waypoint[2], state.waypoint[1] - prev_waypoint[1]) - atan2(prev_waypoint[2] - prev_loc_planned[2], prev_waypoint[1] - prev_loc_planned[1])) * 180/pi

            a, w = updateDRVelocityVector(uav, state, [0., 0.], dphi / dt_remained, dt_remained)
            state.curr_loc += state.velocity * dt_remained + 1/2 * a * dt_remained^2
            state.loc_planned += (state.waypoint - state.loc_planned) / norm(state.waypoint - state.loc_planned) * delta_remained
        end

    else
        state.loc_planned += delta

        a, w = updateDRVelocityVector(uav, state, [0., 0.], 0., float(uav.sc.dt))
        state.curr_loc += state.velocity * uav.sc.dt + 1/2 * a * uav.sc.dt^2

    end
end


function RSSLoss(uav::UAV, d::Float64)

    A = uav.rss_params.A
    B = uav.rss_params.B
    C = uav.rss_params.C

    return A + B * log10(d * 0.3048 / 1000) - C # dB, suburban area
end


function RSSdist(uav::UAV, loss::Float64)

    A = uav.rss_params.A
    B = uav.rss_params.B
    C = uav.rss_params.C

    return 10^((loss - A + C) / B) * 1000 * 3.281 # m to ft
end


function RSSLossWithError(uav::UAV, d::Float64)

    return RSSLoss(uav, d) + rand(Normal(0., uav.rss_params.sigma_err))
end


function EstimateLocationWithTowers(uav::UAV, state::UAVState)

    D = zeros(3)

    for i in 1:3
        d = norm(state.curr_loc - state.cell_towers[i])
        loss = RSSLossWithError(uav, d)
        D[i] = RSSdist(uav, loss)

        #println(d)
        #println(D[i])
    end 

    # trilateration
    # http://en.wikipedia.org/wiki/Trilateration

    P1 = [state.cell_towers[1], 0]
    P2 = [state.cell_towers[2], 0]
    P3 = [state.cell_towers[3], 0]

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

    state.loc_estimated = P[1:2]
end


function updateStateRL(uav::UAV, state::UAVState; bKalmanFilter::Bool = false)

    if bKalmanFilter
        # + Model
        # x_k = F_k x_{k-1} + B_k u_k + w_k, w_k \sim N(0, Q_k) ; process noise
        # z_k = H_k x_k + v_k, v_k \sim N(O, R_k) ; observation noise
        #
        # + Prediction
        # Predicted (a priori) state estimate
        # \hat{x}_{k|k-1} = F_k \hat{x}_{k-1|k-1} + B_k u_k
        # Predicted (a priori) esitmate covariance
        # P_{k|k-1} = F_k P_{k-1|k-1}F^T_k + Q_k
        #
        # + Update
        # Innovation or measurement residual
        # \tilde{y}_k = z_k - H_k \hat{x}_{k|k-1}
        # Innovation (or residual) covariance
        # S_k = H_k P_{k|k-1} H^T_k + R_k
        # Optimal Kalman gain
        # K_k = P_{k|k-1} H^T_k S^{-1}_k
        # Updated (a posteriori) state estimate
        # \hat{x}_{k|k} = \hat{x}_{k|k-1} + K_k \tilde{y}_k
        # Updated (a posteriori) estimate covariance
        # P_{k|k} = (I - K_k H_k) P_{k|k-1}

        F = eye(2)
        B = uav.velocity * uav.sc.dt
        Q = [100^2 0; 0 100^2]

        H = eye(2)
        R = [500^2 0; 0 500^2]

        x = state.loc_estimated
        u = (state.waypoint - state.loc_estimated) / norm(state.waypoint - state.loc_estimated)
    end


    delta = (state.waypoint - state.loc_estimated) / norm(state.waypoint - state.loc_estimated) * uav.velocity * uav.sc.dt

    if state.status == :flying
        end_loc = uav.end_loc
    elseif state.status == :base
        end_loc = state.base_loc
    end

    #if norm(delta) >= norm(state.waypoint - state.loc_estimated)
    #    delta_remained = (norm(delta) - norm(state.waypoint - state.loc_estimated))

    #    state.curr_loc += state.waypoint - state.loc_estimated

    #    push!(state.past_locs, state.curr_loc)

    #    if state.waypoint != end_loc
    #        prev_waypoint = state.waypoint

    #        if state.waypoint_index < uav.nwaypoints
    #            state.waypoint_index += 1
    #            state.waypoint = uav.waypoints[state.waypoint_index]
    #        else
    #            state.waypoint = end_loc
    #        end

    #        state.curr_loc += (state.waypoint - prev_waypoint) / norm(state.waypoint - prev_waypoint) * delta_remained
    #    end

    if norm(state.loc_estimated - state.waypoint) <= uav.rl_error_bound
        if state.waypoint != end_loc
            if state.waypoint_index < uav.nwaypoints
                state.waypoint_index += 1
                state.waypoint = uav.waypoints[state.waypoint_index]
            else
                state.waypoint = end_loc
            end

            state.curr_loc += (state.waypoint - state.loc_estimated) / norm(state.waypoint - state.loc_estimated) * uav.velocity * uav.sc.dt
        end

    else
        state.curr_loc += delta

    end

    EstimateLocationWithTowers(uav, state)


    if bKalmanFilter
        z = state.loc_estimated

        P = state.P

        x_ = F*x + B*u
        P_ = F*P*F' + Q

        K = P_ * H' * inv(H*P_*H' + R)

        x = x_ + K * (z - H * x_)
        P = (eye(2) - K * H) * P_

        state.loc_estimated = x
        state.P = P
    end
end


function updateState(uav::UAV, state::UAVState, t::Int64)

    if state.status == :flying || state.status == :base
        push!(state.past_locs, state.curr_loc)

        if state.bAdvisory
            if state.advisory[1] != nothing
                state.waypoint_index = state.advisory[1]
            else
                state.waypoint_index = uav.nwaypoints
            end
            state.waypoint = state.advisory[2]

            phi = atan2(state.waypoint[2] - state.curr_loc[2], state.waypoint[1] - state.curr_loc[1]) * 180/pi
            state.velocity = [uav.velocity * cosd(phi), uav.velocity * sind(phi)]

            state.bAdvisory = false
        else
            if t >= uav.sc.jamming_time && norm(state.curr_loc - uav.sc.jamming_center) <= uav.sc.jamming_radius
                if uav.GPS_loss_policy == :base
                    index = nothing
                    dist = Inf

                    for j = 1:length(uav.sc.landing_bases)
                        dist_ = norm(state.curr_loc - uav.sc.landing_bases[j])
                        if  dist_ < dist
                            index = j
                            dist = dist_
                        end
                    end

                    state.waypoint_index = uav.nwaypoints
                    state.waypoint = uav.sc.landing_bases[index]

                    phi = atan2(state.waypoint[2] - state.curr_loc[2], state.waypoint[1] - state.curr_loc[1]) * 180/pi
                    state.velocity = [uav.velocity * cosd(phi), uav.velocity * sind(phi)]

                    state.base_loc = uav.sc.landing_bases[index]

                    state.status = :base
                end
            end
        end

        localization = uav.localization

        if uav.sc.jamming_time != Inf
            localization = :GPS_INS

            # XXX check whether the current location is in jamming area. this code should be in Scenario. please check cross-reference in Julia
            if t >= uav.sc.jamming_time && norm(state.curr_loc - uav.sc.jamming_center) <= uav.sc.jamming_radius
                localization = uav.localization
            end
        end

        if state.status == :flying
            end_loc = uav.end_loc
        elseif state.status == :base
            end_loc = state.base_loc
        end

        if localization == :GPS_INS
            updateStateGPSINS(uav, state)

            if state.curr_loc == end_loc
                state.status = :done
            end

        elseif localization == :deadreckoning
            updateStateDR(uav, state)

            if state.loc_planned == end_loc
                state.status = :done
            end

        elseif localization == :radiolocation
            updateStateRL(uav, state, bKalmanFilter = true)

            if norm(state.curr_loc - end_loc) <= uav.rl_error_bound
                state.status = :done
            end

        end

        (x, y) = state.curr_loc

        if x < 0 || x > uav.sc.x || y < 0 || y > uav.sc.y
            state.status = :done
        end
    end
end


function isEndState(uav::UAV, state::UAVState)

    if state.status == :done
        return true
    else
        return false
    end
end


end


