using Rewrite
using Base.Test

# write your own tests here
@test 1 == 1

expr1 = :(destroy(1)*create(1))
expr2 = :(destroy(2)*create(1))


p1 = :(q_ * r_)
p2 = :(q_ * create(r_))
p3 = :(destroy(r_)*create(r_))
p4 = :(destroy(r_)*create(s_))

@test xmatch(p1, expr1) == XMatch(true, [:q_=>:(destroy(1)), :r_=>:(create(1))])
@test xmatch(p2, expr1) == XMatch(true, [:q_=>:(destroy(1)), :r_=>1])
@test xmatch(p3, expr1) == XMatch(true, [:r_=>1])
@test xmatch(p3, expr2) == XMatch(false)
@test xmatch(p4, expr2) == XMatch(true, [:r_=>2, :s_=>1])
@test xmatch(p4, expr1) == XMatch(true, [:r_=>1, :s_=>1])

@test xsub(expr1, [:destroy=>:create]) == :(create(1)*create(1))
@test xsub(expr1, [1=>2]) == :(destroy(2)*create(2))


normal_order1 = [
    :(destroy(j_)*create(l_))=>:(create(l_)*destroy(j_) + (l_==j_))
  ]


function aad(;j_=0, l_=0)
  commutator = (l_== j_? 1:0)
  :(create($l_)*destroy($j_) + $commutator)
end

function evalex(; e_)
  eval(e_)
end

normal_order2 = [
    :(destroy(j_)*create(l_))=> aad,
  ]

normal_order3 = [
  :(destroy(j_)*create(l_)) => :(create(l_)*destroy(j_) + eval((l_== j_? 1:0))),
  :(eval(e_)) => evalex,
  ]

@test rewrite(normal_order1, expr1) == :(create(1)*destroy(1) + (1 == 1))
@test rewrite(normal_order2, expr1) == :(create(1)*destroy(1) + 1)
@test flatten(:(a+b+(c+d)), [:+,:*], true) == :(a+b+c+d)


@test distribute_over(:((a+b)*c), [:(*)],:(+)) == :(a*c + b*c)
@test distribute_over(:((a+b)*c*(e+f*(g+h))), [:(*)],:(+)) == :(a*c*e + b*c*e + a*c*f*g + b*c*f*g + a*c*f*h + b*c*f*h)

# @time for k=1:1000; distribute_over(:((a+b)*c*(e+f*(g+h))), [:(*)],:(+)); end;
# --> ~ .1us per iteration
# This runs x200 faster than the following equivalent sympy code
# from sympy import *
# a,b,c,d,e,f,g,h = symbols("a,b,c,d,e,f,g,h")
# ((a+b)*c*(e+f*(g+h))).expand()
# %timeit ((a+b)*c*(e+f*(g+h))).expand()
# --> ~ 18us


