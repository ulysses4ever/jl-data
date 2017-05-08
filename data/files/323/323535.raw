push!(LOAD_PATH, ".")

type Vector3d
  x::Float64
  y::Float64
  z::Float64
end

function +(a::Vector3d,b::Vector3d)
  Vector3d(a.x+b.x,a.y+b.y,a.z+b.z)
end

function /(a::Float64,b::Vector3d)
  Vector3d(a/b.x,a/b.y,a/b.z)
end


function calcTestIterativeVector(val::Vector3d,limit::Float64)
  a =val
  while a.x < limit
    a.x+= 1.0/a.x
    #a.y+= 1.0/a.y
    #a.z+= 1.0/a.z
  end
  return(a)
end

function calcTestIterative(a::Float64,limit::Float64)
  #a = val
  while a < limit
    a+= 1.0/a
  end
  return(a)
end

function calcTestRecursiveVector(val::Vector3d,limit::Float64)
  if val.x < limit
    nextVal = val+1.0/val
    calcTestRecursiveVector(nextVal,limit)
  else
    return(val)
  end
end

function calcTestRecursiveVector2!(val::Vector3d,limit::Float64)
  if val.x < limit
    val.x = val.x+1.0/val.x
    val.y = val.y+1.0/val.y
    val.z = val.z+1.0/val.z
    calcTestRecursiveVector2!(val,limit)
  end
end


function calcTestIterativeArray(val,limit)
  a =val
  while a[1] < limit
    a+= 1.0/a[1]
  end
  return(a)
end

function calcTestRecursiveArray(val,limit)
  if val[1] < limit
    nextVal = val+1.0/val[1]
    calcTestRecursiveArray(nextVal,limit)
  else
    return(val)
  end
end

function calcTestRecursive(val,limit)
  if val < limit
    nextVal = val+1.0/val
    calcTestRecursive(nextVal,limit)
  else
    return(val)
  end
end

function runTest(fct,nRuns,limit)
  #result = 0.0
  for i=1:nRuns
    start=1.0
    fct(start,limit)
  end
  #print(result)
end

function runTestVector(fct,nRuns,limit)
  #result = 0.0
  for i=1:nRuns
    start = Vector3d(1.0,0.0,0.0)
    fct(start,limit)
  end
  #print(result)
end


function testBool(nRuns)
  #result = 0.0
  A = true
  j = 0
  for i=1:nRuns
    if !A == false
      j=i
    end
  end
  return j
end

function testNull(nRuns)
  #result = 0.0
  A = Nullable{Int64}(1)
  j = 0
  for i=1:nRuns
    if !isnull(A)
      j=i
    end
  end
  return j
end

nRuns = 10000000
@time testBool(nRuns)
@time testNull(nRuns)
@time testBool(nRuns)
@time testNull(nRuns)


nRuns = 1000
limit = 200.0
#@time runTest(calcTestIterativeArray,nRuns,[1.0],limit)
#@time runTest(calcTestRecursiveArray,nRuns,[1.0],limit)
#@time runTest(calcTestIterative,nRuns,limit)
#@time runTest(calcTestRecursive,nRuns,1.0,limit)
#@time runTestVector(calcTestIterativeVector,nRuns,limit)
#@time runTest(calcTestRecursiveVector,nRuns,Vector3d(1.0,0.0,0.0),limit)
#@time runTestRecursive(nRuns,limit)

limit = 200.0

println("----------------")
#@time runTestVector(calcTestIterativeVector,nRuns,limit)
#@time runTest(calcTestRecursiveVector,nRuns,Vector3d(1.0,1.0,1.0),limit)
#val = Vector3d(1.0,1.0,1.0)
#@time runTest(calcTestRecursiveVector2!,nRuns,val,limit)
#println(val)
#println("----------------")
#@time runTest(calcTestIterativeArray,nRuns,[1.0],limit)
#@time runTest(calcTestRecursiveArray,nRuns,[1.0],limit)
println("----------------")
#@time runTest(calcTestIterative,nRuns,limit)
#@time runTest(calcTestRecursive,nRuns,1.0,limit)


#code_typed(calcTestIterativeVector,(Vector3d,Float64))
#code_typed(calcTestIterative,(Float64,Float64))

#@time runTestIterative(nRuns,limit)
#@time runTestRecursive(nRuns,limit)
