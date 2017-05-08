module TKMisc

export argrelmax

function argrelextrema(data::Vector, comperator::Function, order=1)
  N = length(data)

  map = zeros(Bool,N)
  for l=order+1:N-order-1
    map[l] = true
    for k=1:order
      if !( comperator(data[l],data[l+k]) && comperator(data[l],data[l-k]) )
        map[l] = false
        break;
      end
    end
  end

  return find(map)
end

argrelmax(data::Vector, order=1) = argrelextrema(data, >, order)

end # module
