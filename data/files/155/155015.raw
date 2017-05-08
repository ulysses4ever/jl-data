
function countneighbors(prevstep,i::Int,j::Int) #prevstep is Array{Bool,2}
  kmax,mmax = size(prevstep)
  count = 0
  for k=(i-1):(i+1),m=(j-1):(j+1)
    #wrap out of bounds values
    k = (k < 1) ? kmax : k
    k = (k > kmax) ? 1 : k
    m = (m < 1) ? mmax : m
    m = (m > mmax) ? 1 : m

    #if not self, then count if live
    if (!(k==i && m==j)) && prevstep[k,m]
      count += 1
    end
  end
  return count
end

function isalive(count::Int,alreadyalive::Bool)
  if count < 2 || count > 3
    return false
  else
    return count == 3 ? true : alreadyalive
  end
end

function step(prevstep,newstep::Array{Bool,2},ri::Range1{Int},rj::Range1{Int})
  isz,jsz = size(prevstep)
  if isz + 1 < (ri.start + ri.len) || jsz + 1 < (rj.start + rj.len)
    error("ranges $ri,$rj are too big for prevstep array $(size(prevstep)) ")
  end

  for i=ri,j=rj
    liveneighbors = countneighbors(prevstep,i,j)
    newstep[i+1-ri.start,j+1-rj.start] = isalive(liveneighbors,prevstep[i,j])
  end
end

function step(prevstep,rangei::Range1{Int},rangej::Range1{Int})
  output = Array(Bool,rangei.len,rangej.len)
  step(prevstep,output,rangei,rangej)
  return output
end

function stepeverywhere(dprev)
  ps = procs(dprev)
  rs = Array(RemoteRef, length(ps))
  for i=1:(length(ps))
    rs[i] = @spawnat ps[i] (myindexes(dprev),step(dprev,myindexes(dprev)...))
  end
  println("+")
  result = [fetch(r) for r=rs]
  println("*")
  return result
end

function copyfrom(destarray,tuple,inputarray)
  r1,r2 = tuple
  destarray[r1,r2] = inputarray
end

function assemble(newarray,pieces)
  for i=pieces
    copyfrom(newarray,i...)
  end
end

function pretty_print(a::Array{Bool,2})
  imax,jmax = size(a)
  for i=1:imax
    for j=1:jmax
      c = a[i,j] ? 'X' : '.'
      print("$c")
    end
    print("\n")
  end
end

function step!(dprev,nextstep)
  dprev = distribute(nextstep)
  assemble(nextstep,stepeverywhere(dprev))
  #pretty_print(nextstep)
end
