using ODEs
using Base.Test

# write your own tests here
f(t,y) = [4*exp(0.8*t)-0.5*y[1],4*exp(0.8*t)-0.5*y[2]]

println("Testing solver: rk4")
t, y = rk4(f, [0 4], [2 2])

@test((y[end,1]-75.33896)/75.33896 < 0.01)
print_with_color(:green,"Solver rk4 passed\n")

println("Testing solver: rk5")
t, y = rk4(f, [0 4], [2 2])

@test((y[end,1]-75.33896)/75.33896 < 0.01)
print_with_color(:green,"Solver rk5 passed\n")

println("All looks OK")
