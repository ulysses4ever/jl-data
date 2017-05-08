# Simulate Discrete Markov Decision Process
import MDP: SimpleMDP, valueiteration
using Distributions

function simulate(mdp::SimpleMDP, n, start; burnin=0)
  # convert markov decision process to markov chain
  val, policy = valueiteration(mdp)
  mc = mdp.P[policy,:]
  cat = Categorical[]
  for i=1:size(mc,1)
    p = vec(full(mc[i,:]))
    push!(cat, Categorical(p))
  end

  # use Markov Chain probabilities to simulate values
  path = Array(Int64, n+1)
  path[1] = start
  for i=2:(n+1)
    path[i] = rand(cat[path[i-1]])
  end
  path
end
