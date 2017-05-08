#using ProgressMeter
using Base


type Memory
  mem::Array
  height::Int64
  size::Int64
  objFunc::Function
  length::Int64
  bounds::Array
  pitch::Float64
  pitchRate::Float64
  improvRate::Float64
  function Memory(size::Int64, bounds::Array)
    self = new()
    self.size = size
    self.mem = Array(Harmony, size)
    self.height = 1
    self.bounds=bounds
    return self
  end
end

function jam(memory::Memory)
  """
  Fills the memory with random harmonies.
  """
  for i = 1:memory.size
    harmony = Harmony(memory.bounds, true)
    listen(harmony, memory.objFunc)
    addHarmony(memory, harmony)
  end
end

function registerObjFunc(memory::Memory, func::Function)
  memory.objFunc = func
end

function configure(memory::Memory, pitch::Float64=.1, pitchRate::Float64=.9, improvRate::Float64=.9)
   memory.pitch = pitch
   memory.pitchRate = pitchRate
   memory.improvRate = improvRate
end

function introspect(memory::Memory)
  memory.length = length(memory.mem[1])
end

type Harmony
  params::Array
  sound::Float64
  function Harmony(bounds::Array, randomize::Bool=true)
    #println("Creating random Harmony.")
    self = new()
    self.params = [(bound[2]-bound[1])*rand()+bound[1] for bound in bounds]
    #self.params = rand(len,1)
    #self.sound = 0
    return self
  end
  function Harmony(parameters::Array)
    self = new()
    #println("Creating custom Harmony.")
    self.params = parameters
    #self.sound = 0
    return self
  end
end

function length(harmony::Harmony)
  return Base.length(harmony.params)
end

function listen(harmony::Harmony, delegate)
  #println("Listening to Harmony.")
  harmony.sound = delegate(harmony.params)
  #return harmony.sound
end

function value(harmony::Harmony)
  return harmony.sound
end


function play(memory::Memory)
  doModulate::Bool = rand() > memory.pitchRate
  doImprovise::Bool = rand() > memory.improvRate
  newParams = Array(Float64,memory.length)

  for i = 1:memory.length
    pick::Int64 = rand(1:memory.size)
    newParams[i] = memory.mem[pick].params[i]
  end
  newHarmony = Harmony(newParams)

  if doModulate
    modulate(newHarmony, memory)
  end
  if doImprovise
    improvise(newHarmony, memory)
  end
  listen(newHarmony, mean)
  addHarmony(memory, newHarmony)
end

function addHarmony(memory::Memory, harmony::Harmony)
  in = memory.height
  max = memory.size
  if in <= max
  #println("Adding new Harmony to memory: $in/$max")
  memory.mem[memory.height] = harmony
  memory.height += 1
  else
    #println("Memory full.")
    sort(memory)
    #println(value(memory.mem[1]))
    #println(value(memory.mem[2]))
    if value(harmony) < value(memory.mem[1])
      #println("Replacing worst harmony.")
      memory.mem[1] = harmony
    else
      #println("Rejecting new harmony.")
    end
  end
end

function sort(memory::Memory)
  sort!(memory.mem, by=value, rev=true)
end

function improvise(harmony::Harmony, memory::Memory)
  pos = rand(1:memory.length)
  bound = memory.bounds[pos]
  harmony.params[pos] = (bound[2]-bound[1])*rand()+bound[1]
end

function modulate(harmony::Harmony, memory::Memory)
  pos = rand(1:memory.length)
  harmony.params[pos] += (memory.pitch*(rand(0:1)*2-1))
  if harmony.params[pos] > memory.bounds[pos][2]
    harmony.params[pos] = memory.bounds[pos][2]
  end
  if harmony.params[pos] < memory.bounds[pos][1]
    harmony.params[pos] = memory.bounds[pos][1]
  end
end

function harvest(memory::Memory)
  sort(memory)
  return (value(memory.mem[1]), memory.mem[1].params)
end

function report(memory::Memory)
  size::Int64 = memory.size
  println("Reporting Memory:\nSize: $size")
  sort(memory)
  for harmony::Harmony in memory.mem
    report(harmony)
  end
end

function report(harmony::Harmony)
  """
  Prints the parameters of the harmony.
  """
  sound::Float64 = harmony.sound
  println("Sound: $sound")
end

function harmonize(objFunc::Function, memorySize::Int64, bounds::Array, iterations::Int64=1000000, pitch::Float64=0.1, pitchRate::Float64=.9, improvRate::Float64=.9)
"""
Interface for optimizing a model by finding the parameters that minimize
the objective Function 'objFunc' using Harmony Search.

:param objFunc::Function: Function accepting an Array of parameters and
returning a Float64. The algorithm tries to find the set of parameters that
minimizes this function's return value.

:param memorySize::Int64: Number of Harmony instances kept in memory. Warning:
Can greatly impact performance. Choose large values only if necessary.

:param bounds::Array: Contains a list of tuples each defining the lower/upper
bound of one parameter. The length of the Array is also the number of parameters.
Starting parameters are selected randomly from within these bounds.

:param iterations::Int64: Defining the number of iterations the algorithm will run.
Trying many iterations will not garantee better solutions. Usually a certain
configuration has a maximum accuracy associated with it. Finding better solutions
may require different configurations.

:param pitch::Float64: Defines the amount by which a paramter is changed whenever
the modulation criteria is met. This value is directly related to the maximum
accuracy that can be reached. However too small values can greatly increase
the necessary number of iterations in order to reach the best solution.

:param pitchRate::Float64: Defines how often a new Harmony is modulated: 1=never
0=always.

:param improvRate::Float64: Defines how often a new Harmony is improvised meaning
a new value is generated randomly within its bounds: 1=never 0=always.

:return Memory: Returns the memory in its final stage containing the 'memorySize' 
best solutions. Calling 'report' on the object returns a tuple containing the
the objective Function's return value for the best set of parameters and
a list of the corresponding parameters as a second value.


Example:

bounds = [(0,2),(0,1),(0,4),(0,1),(0,1),(-5,1),(0,1),(0,1),(0,1),(0,1)]
memory = harmonize(sum, 10, bounds, 1000000, .01)
report(memory)
println(harvest(memory))
"""
   memory = Memory(memorySize, bounds)
   registerObjFunc(memory, objFunc)
   configure(memory, pitch, pitchRate, improvRate)
   jam(memory)
   introspect(memory)
   for i=1:iterations
      play(memory)
   end
   return memory
end


