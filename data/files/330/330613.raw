# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 03/09/2015

using UAV_
using Scenario_
using UTMVisualizer_


function generateParameters(model::ASCIIString)

    params = ScenarioParams()

    if model == "m0.1"
        params.x = 5000.    # ft
        params.y = 5000.    # ft

        params.dt = 1.      # seconds

        params.cell_towers = Vector{Float64}[[160., 200.], [2100., 4900.], [4800., 500.]]

    elseif model == "m1.0"
        params.x = 5000.    # ft
        params.y = 5000.    # ft

        params.dt = 1.      # seconds

        params.cell_towers = Vector{Float64}[[160., 200.], [2100., 4900.], [4800., 500.]]

        params.jamming_time = 0.
        params.jamming_center = [params.x / 2, params.y / 2]
        params.jamming_radius = 2500. * sqrt(2) + 1.

        params.sa_dist = 500. # ft

        params.bCAS = true

    elseif model == "m1.1"
        params.x = 10000.    # ft
        params.y = 10000.    # ft

        params.dt = 1.      # seconds

        params.cell_towers = Vector{Float64}[[320., 400.], [4200., 9800.], [9600., 1000.]]

        params.jamming_time = 0.
        params.jamming_center = [params.x / 2, params.y / 2]
        params.jamming_radius = 2500. * sqrt(2) + 1.

        params.sa_dist = 500. # ft

        params.bCAS = true

    elseif model == "m2.0"
        params.x = 10000.    # ft
        params.y = 10000.    # ft

        params.dt = 1.      # seconds

        params.cell_towers = Vector{Float64}[[320., 400.], [4200., 9800.], [9600., 1000.]]

        params.landing_bases = Vector{Float64}[[4000., 7000.], [8000., 2000.]]

        params.jamming_time = 0.
        params.jamming_center = [params.x / 2, params.y / 2]
        params.jamming_radius = 2500. * sqrt(2) + 1.

        params.sa_dist = 500. # ft

        params.bCAS = true

    elseif model == "m3.0"
        params.x = 20000.    # ft
        params.y = 20000.    # ft

        params.dt = 1.      # seconds

        params.cell_towers = Vector{Float64}[[7660., 7700.], [9600., 12400.], [12300., 8000.]]

        params.jamming_time = 0.
        params.jamming_center = [params.x / 2, params.y / 2]
        params.jamming_radius = 2500. * sqrt(2) + 1.

        params.sa_dist = 500. # ft

        params.bCAS = true

    end

    return params
end


function generateUAVList(UAVs)

    UAVList = UAV[]

    for i = 1:length(UAVs)
        uav_info = UAVs[i]

        uav = UAV()

        uav.number = i

        uav.start_loc = uav_info[1]
        if length(uav_info) > 2
            uav.waypoints = Vector{Float64}[]
            uav.nwaypoints = length(uav_info) - 2
        end
        for j = 2:length(uav_info)-1
            push!(uav.waypoints, uav_info[j])
        end
        uav.end_loc = uav_info[end]

        uav.velocity = 40.

        # nav or base
        uav.GPS_loss_policy = :nav

        # GPS_INS, deadreckoning or radiolocation
        uav.localization = :GPS_INS

        # deadreckoning
        uav.IMU_acc_instability = 6.e-6
        uav.IMU_acc_VRW = 0.06
        uav.IMU_gyr_instability = 4.e-5
        uav.IMU_gyr_ARW = 0.75

        # radiolocation
        uav.rl_error_bound = 50.

        push!(UAVList, uav)
    end

    return UAVList
end


function translateUAVs(UAVs, x, y)

    UAVs_ = Any[]

    for uav_info in UAVs
        uav_info_ = Any[]

        for waypoint in uav_info
            push!(uav_info_, [waypoint[1] + x, waypoint[2] + y])
        end

        push!(UAVs_, uav_info_)
    end

    return UAVs_
end


function generateUAVs(model::ASCIIString)

    if model == "m0.1" || model == "m1.0"
        UAVs = {{[100., 2500.], [2000., 2000.], [3600., 3000.], [5500., 3000.]},
                {[4000., 4900.], [2000., 3000.], [1500., -500.]},
                {[400., 4900.], [2700., 4200.], [5500., 4000.]},
                {[3200., 100.], [4400., 1800.], [3800., 3900.], [4400., 5500.]},
                {[4900., 2200.], [1600., 1200.], [-500., 900.]}}

    elseif model == "m1.1" || model == "m2.0"
        UAVs = {{[100., 2500.], [2000., 2000.], [3600., 3000.], [5500., 3000.], [7100., 1500.]},
                {[4000., 4900.], [2000., 3000.], [1500., -500.], [-100., -2000.]},
                {[400., 4900.], [2700., 4200.], [5100., 4000.], [7100., 4400.]},
                {[3200., 100.], [4400., 1800.], [3800., 3900.], [4400., 5500.], [4700., 7000.]},
                {[4900., 2200.], [1600., 1200.], [-500., 900.], [-1600., 500.]}}
        UAVs = translateUAVs(UAVs, 2500, 2500)

    elseif model == "m3.0"
        UAVs = {{[100., 2500.], [2000., 2000.], [3600., 3000.], [5500., 3000.], [7100., 1500.], [9000., 1000.], [11600., -500.]},
                {[4000., 4900.], [2000., 3000.], [1500., -500.], [-100., -2000.], [-2000., -3200.], [-3200., -5000.]},
                {[400., 4900.], [2700., 4200.], [5100., 4000.], [7100., 4400.], [8300., 5200.], [10500., 5800.]},
                {[3200., 100.], [4400., 1800.], [3800., 3900.], [4400., 5500.], [4700., 7000.], [3900., 8200.], [3500., 11000.]},
                {[4900., 2200.], [1600., 1200.], [-500., 900.], [-2600., 100.], [-4200., -100.], [-6000., 300.]}}
        UAVs = translateUAVs(UAVs, 7500, 7500)
        append!(UAVs, {{[500., 18000.], [2500., 16000.], [5000., 15000.], [7000., 15000.], [10000., 17000.], [12500., 18000.], [17000., 16000.]},
                       {[17000., 1400.], [14000., 1000.], [12500., 800.], [10000., 1200.], [9000., 2000.], [7000., 3200.], [4000., 3000.], [1600., 2800.]}})

    end

    return generateUAVList(UAVs)
end


function generateScenario(model::ASCIIString; localization::Union(Symbol, Nothing) = nothing, bCAS::Union(Bool, Nothing) = nothing, GPS_loss_policy::Union(Symbol, Nothing) = nothing)

    params = generateParameters(model)

    UAVList = generateUAVs(model)

    params.UAVs = UAV[]
    params.nUAV = length(UAVList)

    for i = 1:params.nUAV
        uav = UAVList[i]

        if GPS_loss_policy != nothing
            uav.GPS_loss_policy = GPS_loss_policy
        end

        if localization != nothing
            uav.localization = localization
        end

        push!(params.UAVs, uav)
    end

    sc = Scenario(params)

    if bCAS != nothing
        sc.bCAS = bCAS
    end

    return sc
end


function simulate(sc::Scenario; draw::Bool = false, wait::Bool = false)

    state = ScenarioState(sc)

    if draw
        vis = UTMVisualizer(wait = wait)

        visInit(vis, sc)
        visUpdate(vis, sc)
        updateAnimation(vis)
    end

    t = 0

    sa_violation = zeros(Bool, sc.nUAV, sc.nUAV)
    sa_violation_count = 0

    while !isEndState(sc, state)
        updateState(sc, state, t)

        for i = 1:sc.nUAV-1
            for j = i+1:sc.nUAV
                state1 = state.UAVStates[i]
                state2 = state.UAVStates[j]

                if state1.status == :flying && state2.status == :flying
                    if norm(state1.curr_loc - state2.curr_loc) < sc.sa_dist
                        if !sa_violation[i, j]
                            sa_violation[i, j] = true
                            sa_violation_count += 1
                        end
                    else
                        if sa_violation[i, j]
                            sa_violation[i, j] = false
                        end
                    end
                end
            end
        end

        if draw
            visInit(vis, sc)
            visUpdate(vis, sc, state, t)
            updateAnimation(vis)
        end

        t += 1
    end

    if draw
        println("# of SA violations: ", sa_violation_count)

        saveAnimation(vis, repeat = true)
    end

    return sa_violation_count
end


if true
    srand(uint(time()))

    sc = generateScenario("m2.0", localization = :radiolocation, bCAS = false, GPS_loss_policy = :base)

    simulate(sc, draw = true, wait = false)
end


if false
    srand(uint(time()))

    sc = generateScenario("m1.0", localization = :radiolocation)

    N = 1000

    va = zeros(N)
    y = 0.

    for i = 1:N
        x = simulate(sc)
        y += (x - y) / i
        va[i] = y
    end

    println("mean: ", va[end], ", std: ", std(va))
end


