module Jig

export @runtest

macro runtest(pkg, file...)
  for f in file
    print_with_color(:magenta, "**  ")
    print_with_color(:blue, string(f))
    println("")
    include(Pkg.dir("$pkg/test/$f.jl"))
  end
end

include("quant/Quant.jl")

end
