using Distributions

# How to generate a random sigma machine
# Select a random machine from a set of primitives

## ============
## Utils

flip = function(p) ifelse(rand(Bernoulli(p)) == 0,false,true) end

function rand_select(c::AbstractVector)
  c[rand(range(1, length(c)))]
end

# TODO, could be more efficient for large n
rand_select(c::AbstractVector, n::Integer) = [rand_select(c) for i=range(0, n)]

## ============
## Constructors

# Generates a vector of all the constructors signatures of a Datatype
function constructor_type(d::DataType)
  types::Vector{} = (DataType...)[]
  m = methods(d)
  if isa(methods(TTEST),MethodTable)
    for def in methods(d)
      push!(types,def.sig)
    end
  end
  types
end

one() = 1
two() = 2
three() = 3
four() = 4
five() = 5
six() = 6
seven() = 7
eight() = 8
nine() = 9
ten() = 10

## ==========
## Generation

# Gen should take a set of constructors
# Choose something from the list
# If To construct it we first need to construct other things
# -- Try to construct those other things, first
function gen(types::Vector{DataType})
  t = rand_select(types)
  t_constructor = constructor_type(t)
  nullary_constructors = filter(isempty, t_constructor)
  if length(nullary_constructors) == 1 && length(t_constructor) == 1
    t()
  elseif length(nullary_constructors) == 1 && length(t_constructor) > 1 && flip(0.5)
    t()
  else
    5
  end
end

function get_args(t::DataType, t::Vector{DataTypes})

type TTEST
  x
end
