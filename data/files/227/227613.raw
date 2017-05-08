#using PyPlot
#addprocs(7)
using ProgressMeter
@everywhere using DataFrames

@everywhere type State
    current_state::Int64
    policy::Vector{Float64}
    nr_world_states::Int64
    nr_actions::Int64
    target_sequence::Vector{Int64}
    sum_of_rewards::Vector{Float64}
    nr_of_evaluations::Vector{Float64}
    value_function::Vector{Float64} # on the world state
    state_action_value_function::Matrix{Float64} # on the world state
    k::Int64
    value_history::Matrix{Float64}
end

@everywhere type Result
    experiment::State
    values::Matrix{Float64}
end

@everywhere function create_experiment(nr_world_states::Int64, nr_actions::Int64, target_actions::Int64, k::Int64)
    policy = rand(nr_actions)
    policy = policy / sum(policy)
    
    min = minimum([target_actions, nr_world_states])
    max = maximum([0, nr_world_states - nr_actions])
    
    sequence = vcat([1:min], int(ceil(rand(max) * nr_actions)))
    sequence = sequence[randperm(length(sequence))]
    
    return State(1, policy, nr_world_states, nr_actions, sequence, zeros(nr_world_states), zeros(nr_world_states), zeros(nr_world_states), zeros(nr_world_states, nr_actions), k, zeros(2,2))
end

@everywhere function run_episode(state::State, initial_state::Int64, T::Int64)
    state.current_state = initial_state
    for t = 1:T
        p = rand()
        s = 0
        action = state.nr_actions
        for i = 1:state.nr_actions
            s = s + state.policy[i]
            if p < s
                action = i
                break
            end
        end
        if action == state.target_sequence[state.current_state]
            state.current_state = state.current_state + 1
        else
            state.current_state = 1
        end
        if state.current_state >= state.nr_world_states
            return 1
        end
    end
    return 0
end

@everywhere function monte_carlo_estimation_of_world_state_function!(state::State, T::Int64, nr_of_episodes::Int64)
    for e = 1:nr_of_episodes
        initial_state                          = int64(ceil(rand()*state.nr_world_states))
        if initial_state == 1
          println("initial state: $(initial_state)")
        end
        reward                                 = run_episode(state, initial_state, T)
        state.sum_of_rewards[initial_state]    = state.sum_of_rewards[initial_state] + reward
        state.nr_of_evaluations[initial_state] = state.nr_of_evaluations[initial_state] + 1.0
        state.value_function[initial_state]    = state.sum_of_rewards[initial_state] / state.nr_of_evaluations[initial_state]
    end
end

@everywhere function calculate_world_state_action_function!(state::State)
    for i = 1:state.nr_world_states
        for action = 1:state.nr_actions
            if action == state.target_sequence[i]
                if i == state.nr_world_states
                    state.state_action_value_function[i,action] = 1.0
                else
                    state.state_action_value_function[i,action] = state.value_function[i+1]
                end
            else
                state.state_action_value_function[i,action] = state.value_function[1]
            end
        end
    end

    for action = 1:state.nr_actions
        if action == state.target_sequence[state.nr_world_states]
            state.state_action_value_function[state.nr_world_states,action] = 1.0
        else
            state.state_action_value_function[state.nr_world_states,action] = state.value_function[1]
        end
    end
end

@everywhere function prune_world_state_action_function!(state::State)
    nr_of_values = minimum([state.k, state.nr_actions])
    for i = 1:state.nr_world_states
        if sum(state.state_action_value_function[i,:]) > 0.0
            values = DataFrame(VALUES=[v for v in state.state_action_value_function[i,:]], INDICES=[1:state.nr_actions])
            sort!(values, cols = (:VALUES), rev=true)

            values = values[1:nr_of_values,:]
            for a = 1:state.nr_actions
                state.state_action_value_function[i,a] = 0.0
            end

            for a = 1:size(values)[1]
                state.state_action_value_function[i,values[:INDICES][a]] = values[:VALUES][a]
            end
        else
            indices = randperm(state.nr_actions)[1:nr_of_values]
            for a in indices
                state.state_action_value_function[i, a] = 0.001
            end
        end
    end
end

@everywhere function update_policy_from_world_state_action_function!(state::State)
    sum_of_values = zeros(state.nr_actions)
    for a = 1:state.nr_actions
        sum_of_values[a] = sum(state.state_action_value_function[:,a])
    end
    
    s = sum(sum_of_values)
    for a = 1:state.nr_actions
        state.policy[a] = sum_of_values[a] / s
    end
end

@everywhere function update_policy!(state::State)
    calculate_world_state_action_function!(state)
    prune_world_state_action_function!(state) 
    update_policy_from_world_state_action_function!(state)
end

@everywhere function scan_over_k(k::Int64, N::Int64, episode_length::Int64, nr_of_episodes::Int64)
    nr_world_states   = k + 1
    nr_of_actions     = k
    exp               = create_experiment(nr_world_states, nr_of_actions, nr_of_actions, k)
    exp.value_history = zeros(N, nr_world_states)
    pm = Progress(N, 1)
    for i = 1:N
        monte_carlo_estimation_of_world_state_function!(exp, (episode_length+1) * k, nr_of_episodes)
        update_policy!(exp)
        exp.value_history[i,:] = exp.value_function
        next!(pm)
    end
    return exp
end

#= N               = 1000000 =#
#= nr_world_states = 5 =#
#= nr_of_actions   = 5 =#
#= k               = 5 =#
#= v,r = scan_over_k(k, N, nr_world_states, nr_of_actions) =#

#= println("policy") =#
#= println(r.policy) =#

#= println("state action value function") =#
#= println(r.state_action_value_function) =#
