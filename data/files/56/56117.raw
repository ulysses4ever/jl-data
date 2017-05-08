module Jig

export @runtest, 
       @context,
       jtest 

macro runtest(pkg, file...)
  for f in file
    print_with_color(:blue, string(f))
    print_with_color(:blue, ":")
    println("")
    include(Pkg.dir("$pkg/test/$f.jl"))
  end
end

macro context(s)
  print("      ")
  print_with_color(:magenta,s)
  print("  ")
end

function jtest(ex...)
  fails = 0
  for e in ex
    if eval(:($e))
      print_with_color(:green, ".") 
    else
      print_with_color(:red, "x") 
      fails += 1
    end
  end
  println("")
  fails
end

end
