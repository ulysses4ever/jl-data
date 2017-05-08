module MDPs
  using DataStructures

  export MDP, DiscreteMDP, actions, states, numActions, numStates, reward, transition, discount, locals
  export valueIteration, bestAction
  export nextStates, stateIndex, actionIndex

  abstract MDP

  actions(mdp::MDP) = error("$(typeof(mdp)) does not implement actions")
  states(mdp::MDP) = error("$(typeof(mdp)) does not implement states")
  numActions(mdp::MDP) = length(actions(mdp))
  numStates(mdp::MDP) = length(states(mdp))
  reward(mdp::MDP, s, a) = error("$(typeof(mdp)) does not implement reward")
  transition(mdp::MDP, s0, a, s1) = error("$(typeof(mdp)) does not implement transition")
  discount(mdp::MDP) = error("$(typeof(mdp)) does not implement discount")
  nextStates(mdp::MDP, s, a) = states(mdp)
  stateIndex(mdp::MDP, s) = error("$(typeof(mdp)) does not implement stateIndex")
  actionIndex(mdp::MDP, a) = error("$(typeof(mdp)) does not implement actionIndex")


  function locals(mdp::MDP)
    S = states(mdp)
    A = actions(mdp)
    T = (s0, a, s1) -> transition(mdp, s0, a, s1)
    R = (s, a) -> reward(mdp, s, a)
    gamma = discount(mdp)
    (S, A, T, R, gamma)
  end

  type DiscreteMDP <: MDP
    S::Vector
    A::Vector
    next::Dict{(Any, Any), Set{Any}}
    T::Dict{(Any, Any, Any), Float64}
    R::Dict{(Any, Any), Float64}
    discount::Float64
    function DiscreteMDP(S, A, next, T, R; discount=0.99)
      new(S, A, next, T, R, discount)
    end
  end

  actions(mdp::DiscreteMDP) = mdp.A
  states(mdp::DiscreteMDP) = mdp.S
  reward(mdp::DiscreteMDP, s, a) = mdp.R[s, a]
  transition(mdp::DiscreteMDP, s0, a, s1) = mdp.T[(s0, a, s1)]
  discount(mdp::DiscreteMDP) = mdp.discount
  stateIndex(mdp::DiscreteMDP, s) = mdp.stateIndex[s]
  actionIndex(mdp::DiscreteMDP, a) = mdp.actionIndex[s]
  nextStates(mdp::DiscreteMDP, s, a) = mdp.next[(s, a)]

  function difference(U::Dict, V)
    sum(s -> (U[s] - V[s])^2, keys(U))
  end

  function valueIteration(mdp::DiscreteMDP, ϵ=10^-3.)
    U  = {s => 0 for s in states(mdp)}
    U_ = DefaultDict(0)
    n = 0

    while true
      n += 1
      U_ = Dict()
      for s in states(mdp)
        U_[s] = maximum( 
          a -> reward(mdp, s, a) + 
            discount(mdp) * sum(
              s_ -> transition(mdp, s, a, s_) * U[s_], 
              nextStates(mdp, s, a)), 
          actions(mdp))
      end
      
      δ = difference(U, U_)  

      if n % 10 == 0
        @printf("Iteration %d, ϵ = %f\n", n, δ)
      end

      U = U_
      # stop when converged
      if δ < ϵ
        break
      end
    end
    (U, n)
  end

  macro argmax(f, iter)
    :(indmax([$f(x) for x in $iter]))
  end

  function bestAction(mdp::DiscreteMDP, U::Dict)
    A = Dict()
    for s in states(mdp)
      A[s] = @argmax(
        a -> reward(mdp, s, a) + 
          discount(mdp) * sum(
            s_ -> transition(mdp, s, a, s_) * U[s_], 
            nextStates(mdp, s, a)), 
          actions(mdp))
    end
    A
  end
end
