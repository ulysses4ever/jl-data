module Jig

export @runtest, 
       @jtest, 
       @context

macro runtest(pkg, file...)
  for f in file
    print_with_color(:magenta, "**  ")
    print_with_color(:blue, string(f))
    println("")
    include(Pkg.dir("$pkg/test/$f.jl"))
  end
end

macro jtest(ex...)
  for e in ex
    eval(:($e))?
    print_with_color(:green, ".") :
    print_with_color(:red, "x")
  end
  println("")
end

macro context(s)
  print_with_color(:magenta,s)
  print("  ")
end

include("quant/Quant.jl")

end
