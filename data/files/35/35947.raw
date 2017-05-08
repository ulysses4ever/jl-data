function trianglenum_divisor_count()
    t = 0
    # memo = [1 => [1], 3 => [1,3], []]
    for i in 1:typemax(Int64)
      t += i 
      n = 0
      for j in 1:t
          if mod(t, j) == 0
              n += 1
          end
      end
      if n > 5
          return t
      end
    end
    return nothing
end

function remember_factor(fac :: Int64, facmemo :: Dict{Int64, Set{Int64}})
   j = 2
   factors = Set{Int64}()
   f = fac
   while j < f
      if mod(f, j) == 0
         f = div(f, j)
         if haskey(facmemo, f)
            
         end
         push!(factors, j)         
         j = 2
      end
      j += 1 
   end
   facmemo[fac] = factors 
end

function trianglenum_divisors(max_factors::Int64)
    triangle_nums = Dict{Int64, Vector{Int64}}()
    facmemo = Dict{Int64, Vector{Int64}}()
    
    t = 0
    for i in 1:typemax(Int64)
      t += i 
      n = 0
      factors = Int64[]
      fac = t
      while j <= fac
          if mod(fac, j) == 0
              n += 1
              fac = div(fac, j)
              if haskey(facmemo, fac)
                  append!(factors, facmemo[fac])
                  break                  
              end
              push!(factors, j)
          end
      end
      triangle_nums[t] = factors
      if n >= max_factors
          return triangle_nums
      end
    end
    return triangle_nums
end

