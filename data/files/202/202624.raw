using Sundials

function onecmptiv(t, a, adot, p)
	# p1 = KEL	
        adot[1] = -p[1]*a[1]
end

t = [0.:0.2:10. ]
p = [1.]
a0 = [10.]
f1test2(t, a, adot) = onecmptiv(t, a, adot, p)

Sundials.cvode(f1test2, a0, t)
