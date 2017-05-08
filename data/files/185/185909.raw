function sma_original(avect, numPer)
  numEle = length(avect)
  tout = Array(Float32, numEle)
  for ndx = 1:numEle
    tsum = 0.0
    begndx = max(1, ndx - numPer)
    for slicendx = begndx:ndx
      tsum += avect[slicendx]
    end
    tout[ndx] = tsum / float32(numPer)
  end
  return tout
end

function sma_improved(avect, numPer)
    numEle = length(avect)
    tout = Array(eltype(avect), numEle)
    @inbounds for ndx = 1:numEle
        tsum = zero(eltype(avect))
        begndx = max(1, ndx - numPer)
        @simd for slicendx in begndx:ndx
            tsum += avect[slicendx]
        end
        tout[ndx] = tsum / numPer
    end
    return tout
end

function tester()

  n = 700_000

  f32_data = rand(Float32, n)
  @time rand(Float32, n)
  #= @time sma_original(f32_data, 3) =#
  #= @time sma_original(f32_data, 14) =#
  #= @time sma_original(f32_data, 100) =#

  @time sma_improved(f32_data, 3)
  @time sma_improved(f32_data, 14)
  @time sma_improved(f32_data, 100)
  @time sma_improved(f32_data, 600)
end

tester()
