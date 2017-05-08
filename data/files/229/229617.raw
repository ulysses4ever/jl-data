module RW

export random_walk

include("RW_detail/point.jl")
include("RW_detail/parameter.jl")

function random_walk(;
              num :: Integer = 1024,
              steps :: Integer = 1024,
              dim :: Integer = 1,
              continuous :: Bool = false,
              output :: String = ""
              )

  if dim == 1
    PT = continuous?CPoint1D{Float64}:DPoint1D{Int}
  elseif dim == 2
    PT = continuous?CPoint2D{Float64}:DPoint2D{Int}
  else
    PT = continuous?CPoint3D{Float64}:DPoint3D{Int}
  end

  if isempty(output)
    rw_detail(STDOUT, zeros(PT,num), steps)
  else
    open(output, "w") do io; rw_detail(io, zeros(PT,num),steps); end
  end
end

function rw_detail(output,ps,steps)

  println(output, "# 1 : number of steps")
  println(output, "# 2 : norm of mean of points")
  println(output, "# 3 : mean of norm^2 of points")
  println(output, "# 4 : min of norm of points")
  println(output, "# 5 : max of norm of points")
  println(output, "# 6-: coordinates of mean of points")
  println(output, "")

  for t in 0:steps
    m = mean(ps)
    n2s = map(norm2,ps)
    println(output, t, " ",  
                    norm(m), " ",
                    mean(n2s), " ",
                    sqrt(min(n2s)), " ",   
                    sqrt(max(n2s)), " ",
                    to_plot_str(m) 
                  )
    update!(ps)
  end
end

function random_walk{T}(params::Dict{String,T})
  params2 = Dict{Symbol,T}()
  for p in params
    params2[symbol(p[1])] = p[2]
  end
  random_walk(;params2...)
end

end # module RW
