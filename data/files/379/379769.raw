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
    a.y+= 1.0/a.y
    a.z+= 1.0/a.z
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

function calcTestIterative(val::Float64,limit)
  a =val
  while a < limit
    a= a+1.0/a
  end
  return(a)
end


function runTest(fct,nRuns,start,limit)
  result = 0.0
  for i=1:nRuns
    result = fct(start,limit)
  end
  print(result)
end


#println(eField)
#runTestOpt(100000)
#Profile.clear()
#Profile.init()
#@profile runTestOpt(100000
nRuns = 10000
limit = 100.0
@time runTest(calcTestIterativeArray,nRuns,[1.0],limit)
@time runTest(calcTestRecursiveArray,nRuns,[1.0],limit)
@time runTest(calcTestIterative,nRuns,1.0,limit)
@time runTest(calcTestRecursive,nRuns,1.0,limit)
@time runTest(calcTestIterativeVector,nRuns,Vector3d(1.0,0.0,0.0),limit)
@time runTest(calcTestRecursiveVector,nRuns,Vector3d(1.0,0.0,0.0),limit)
#@time runTestRecursive(nRuns,limit)

limit = 100.0

println("----------------")
@time runTest(calcTestIterativeVector,nRuns,Vector3d(1.0,2.0,3.0),limit)
@time runTest(calcTestRecursiveVector,nRuns,Vector3d(1.0,1.0,1.0),limit)
val = Vector3d(1.0,1.0,1.0)
@time runTest(calcTestRecursiveVector2!,nRuns,val,limit)
print(val)
println("----------------")
@time runTest(calcTestIterativeArray,nRuns,[1.0],limit)
@time runTest(calcTestRecursiveArray,nRuns,[1.0],limit)
println("----------------")
@time runTest(calcTestIterative,nRuns,1.0,limit)
@time runTest(calcTestRecursive,nRuns,1.0,limit)


#@time runTestIterative(nRuns,limit)
#@time runTestRecursive(nRuns,limit)