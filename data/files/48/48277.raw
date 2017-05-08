using DataFrames
using DataFramesMeta
using DataStructures

# =======
# Helpers
# =======

function NS(data::DataFrame)
  @by(data, :state, count = size(:state, 1))
end

function NSA(data::DataFrame)
  @by(data, [:state, :action], count_sa = size(:state, 1))
end

function NSAS(data::DataFrame)
  @by(data, [:state, :action, :state_], count_sas = size(:state, 1))
end

function rewards(data::DataFrame)
  rew = @by(data, [:state, :action], reward = unique(:reward))

  {(x[:state], x[:action]) => x[:reward] for x in eachrow(rew)}
end

function next(data::DataFrame)
  nxt = @by(data, [:state, :action], next = Set{Any}(:state_))
  
  {(x[:state], x[:action]) => x[:next] for x in eachrow(nxt)}
end

function transitions(data::DataFrame)
  nSAS = NSAS(data)
  nSA  = NSA(data)
  joined = join(nSAS, nSA, on=[:state, :action])
  trans = @transform(joined, t_sas=:count_sas ./ :count_sa)
  
  {(x[:state], x[:action], x[:state_]) => x[:t_sas] for x in eachrow(trans)}
end

# ===========
# Loading MDP
# ===========

macro concat(data, col1, col2)
  :([(d[$col1], d[$col2]) for d in eachrow($data)])
end

function grid2standard(data::DataFrame) 
  data[:state] = @concat(data, :row, :col)
  data[:state_] = @concat(data, :row_, :col_)
  data = data[[:state, :action, :reward, :state_]]
end

function pendulum2standard(data::DataFrame) 
  data[:state] = @concat(data, :theta, :omega)
  data[:state_] = @concat(data, :theta', :theta')
  data[:action] = data[:f]
  data = data[[:state, :action, :reward, :state_]]
end
#=
function grid2standard(data::DataFrame) 
  function rowcol2state(theta, omega)
    row + 10*(col-1)
  end

 @transform(data, 
    state = rowcol2state(:row, :col),
    state_ = rowcol2state(:row_, :col_))
  data = data[[:state, :action, :reward, :state_]]
end
=#

function standard2grid(state)
  state % 10, div(state, 10) + 1
end

function getAttributes(data)
  S = array(unique(data[:state]))
  A = array(unique(data[:action]))
  nxt = next(data)
  T = transitions(data)
  R = rewards(data)

  S, A, nxt, T, R
end
