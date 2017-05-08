require("point.jl")
using RW
using ArgParse

function parse_commandline()
  settings = ArgParseSettings()
  @add_arg_table settings begin
    "--num", "-n"
      arg_type = Int
      default = 1024
      range_tester = x->x>0
    "--steps", "-s"
      arg_type = Int
      default = 1024
      range_tester = x->x>0
    "--dim", "-d"
      arg_type = Int
      default = 1
      range_tester = x-> x>0 && x<4
    "--continuous", "-c"
      action = :store_true
  end
  return parse_args(settings)
end

function main()
  pargs = parse_commandline()

  N  = pargs["num"]
  T  = pargs["steps"]
  d  = pargs["dim"]

  if d == 1
    if pargs["continuous"]
      typealias PT CPoint1D{Float64}
    else 
      typealias PT DPoint1D{Float64}
    end
  elseif d == 2
    if pargs["continuous"]
      typealias PT CPoint2D{Float64}
    else 
      typealias PT DPoint2D{Float64}
    end
  else
    if pargs["continuous"]
      typealias PT CPoint3D{Float64}
    else 
      typealias PT DPoint3D{Float64}
    end
  end

  ps = zeros(PT,N)
  for t in 0:T
    println("$t $(abs(mean(ps))) $(mean(map(abs2,ps)))")
    update!(ps)
  end
end

main()

