# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 03/09/2015

using Scenario_
using UTMVisualizer_


function generateParams()

    params = ScenarioParams()

    params.x = 5000.    # ft
    params.y = 5000.    # ft

    params.dt = 1       # seconds

    params.uav_start_loc = nothing  # [x: ft, y: ft]
    params.uav_end_loc = nothing    # [x: ft, y: ft]
    params.uav_waypoints = nothing  # list of [x: ft, y: ft]
    params.uav_velocity = 0.        # ft/s

    # GPS_INS, deadreckoning or radiolocation
    params.uav_localization = :GPS_INS

    # deadreckoning
    params.uav_IMU_acc_instability = nothing
    params.uav_IMU_acc_VRW = nothing
    params.uav_IMU_gyr_instability = nothing
    params.uav_IMU_gyr_ARW = nothing

    # radiolocation
    params.cell_towers = nothing
    params.uav_rl_error_bound = 0.

    return params
end


function simulate(params::ScenarioParams; draw::Bool = false, wait::Bool = false)

    sc = Scenario(params)
    state = ScenarioState(sc)

    if draw
        vis = UTMVisualizer(wait = wait)

        visInit(vis, sc)
        visUpdate(vis, sc)
        updateAnimation(vis)
    end

    t = 0

    #println("t: ", t, ", uav_loc: ", state.uav_loc)

    if draw
        visInit(vis, sc)
        visUpdate(vis, sc, state, t)
        updateAnimation(vis)
    end

    while !isEndState(sc, state)
        t += 1

        updateState(sc, state)

        #println("t: ", t, ", uav_loc: ", state.uav_loc)

        if draw
            visInit(vis, sc)
            visUpdate(vis, sc, state, t)
            updateAnimation(vis)
        end
    end

    if draw
        saveAnimation(vis, repeat = true)
    end
end


srand(uint(time()))

params = generateParams()

params.uav_start_loc = [100., 2500.]
params.uav_end_loc = [4500., 3000.]
params.uav_waypoints = Vector{Float64}[[2000., 1000.], [4000., 3500.]]
params.uav_velocity = 40.

#params.uav_localization = :deadreckoning
#params.uav_IMU_acc_instability = 6.e-6
#params.uav_IMU_acc_VRW = 0.06
#params.uav_IMU_gyr_instability = 4.e-5
#params.uav_IMU_gyr_ARW = 0.75

params.uav_localization = :radiolocation
params.cell_towers = Vector{Float64}[[160., 200.], [2100., 4900.], [4800., 500.]]
params.uav_rl_error_bound = 300.

simulate(params, draw = true, wait = false)


