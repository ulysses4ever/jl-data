# Author: Youngjun Kim, youngjun@stanford.edu
# Date: 03/09/2015

using UAV_
using UAVList_
using Scenario_
using UTMVisualizer_


function generateScenario()

    params = ScenarioParams()

    params.x = 5000.    # ft
    params.y = 5000.    # ft

    params.dt = 1.      # seconds

    params.cell_towers = Vector{Float64}[[160., 200.], [2100., 4900.], [4800., 500.]]

    params.sa_dist = 500 # ft

    params.UAVs = UAV[]
    params.nUAV = length(UAVList)

    for i = 1:params.nUAV
        uav = UAVList[i]

        uav.x = params.x
        uav.y = params.y
        uav.dt = params.dt

        push!(params.UAVs, uav)
    end

    sc = Scenario(params)

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

    if draw
        visInit(vis, sc)
        visUpdate(vis, sc, state, t)
        updateAnimation(vis)
    end

    while !isEndState(sc, state)
        t += 1

        updateState(sc, state)

        if draw
            visInit(vis, sc)
            visUpdate(vis, sc, state, t)
            updateAnimation(vis)
        end
    end

    println("# of SA violations: ", state.sa_violation_count)

    if draw
        saveAnimation(vis, repeat = true)
    end
end


srand(uint(time()))

sc = generateScenario()

simulate(sc, draw = true, wait = false)


