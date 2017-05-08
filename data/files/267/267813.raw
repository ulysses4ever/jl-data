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
        uav.cell_towers = params.cell_towers

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

    sa_violation = zeros(Bool, sc.nUAV, sc.nUAV)
    sa_violation_count = 0

    while !isEndState(sc, state)
        t += 1

        updateState(sc, state)

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
    end

    println("# of SA violations: ", sa_violation_count)

    if draw
        saveAnimation(vis, repeat = true)
    end
end


srand(uint(time()))

sc = generateScenario()

simulate(sc, draw = true, wait = false)


