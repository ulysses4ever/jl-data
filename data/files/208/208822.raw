# Methods for loading Bruker Binary Epr files

export eprload

function eprload(filename::String)
  descname = filename * ".DSC"
  binname = filename * ".DTA"
  
  keys = Dict{String,Any}()
  open(descname) do s
    loadDescription!(s, keys)
  end
  
  xlen = int(keys["XPTS"])
  ylen = haskey(keys,"YPTS") ? int(keys["YPTS"]) : 0
  
  i = open(binname) do s
    return loadBinary(s)
  end
  
  x = linspace(keys["XMIN"],keys["XMIN"]+keys["XWID"], xlen)
  
  if ylen != 0
    y = linspace(keys["YMIN"],keys["YMIN"]+keys["YWID"], ylen)
  else y = Array(Float32,0)
  end
  
  
  if keys["IKKF"] == "CPLX"
    d = reshape(i, xlen*2, ylen == 0 ? 1 : ylen)
    data = sub(d,1:2:xlen*2,:) + 1.0im*sub(d,2:2:xlen*2,:)
  else
    d = reshape(i, xlen, ylen == 0 ? 1 : ylen)
    data = complex(d)
  end
  
  EprData(ylen > 0 ? 1:2,x,y,data,keys)
end

function loadBinary(stream::IOStream)
  # Determine length
  seekend(stream)
  bytes = position(stream)
  seek(stream,0)
  arr = Array(Float64,int(bytes/8))
  
  for i = 1:length(arr)
    arr[i] = ntoh(read(stream,Float64))
  end
  
  return arr
end

# Doesn't close the stream.
function loadDescription!(stream::IOStream, keys::Dict{String,Any})
  for line = eachline(stream)
    parts = split(line)
    if length(parts) < 2 continue
    elseif beginswith(parts[1],'.') continue
    elseif beginswith(parts[1],'*') continue
    elseif beginswith(parts[1],'#') continue
    end
    
    # Try parsing it as an int
    try
      i = int(parts[2])
      keys[parts[1]] = i
      continue
    catch
    end 
    
    try # Perhaps a float?
      f = float32(parts[2])
      keys[parts[1]] = f
      continue
    catch
    
    end
    
    # Must just be a string, add it to the dict
    keys[parts[1]] = parts[2]
  end
  
  return keys
end
