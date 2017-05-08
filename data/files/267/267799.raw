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

        self.sa_dist = params.sa_dist

        self.UAVs = params.UAVs
        self.nUAV = params.nUAV

        return self
    end
end


type ScenarioState

    UAVStates::Vector{UAVState}

    sa_violation_count::Int64


    function ScenarioState(sc::Scenario)

        self = new()
        self.UAVStates = UAVState[]

        for uav in sc.UAVs
            push!(self.UAVStates, UAVState(uav))
        end

        self.sa_violation_count = 0

        return self
    end
end


function updateState(sc::Scenario, state::ScenarioState)

    for i = 1:sc.nUAV
        UAV_.updateState(sc.UAVs[i], state.UAVStates[i])
    end

    for i = 1:sc.nUAV-1
        for j = i+1:sc.nUAV
            state1 = state.UAVStates[i]
            state2 = state.UAVStates[j]

            if state1.status == :flying && state2.status == :flying
                if norm(state1.curr_loc - state2.curr_loc) < sc.sa_dist
                    state.sa_violation_count += 1
                end
            end
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


end


