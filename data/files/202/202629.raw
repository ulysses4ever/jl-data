using Sundials

function onecmptiv(t, a, adot, p)
	# p1 = KEL	
        adot[1] = -p[1]*a[1]
end

t = [0.:0.2:10. ]
p = [0.1]
a0 = [10.]
f1test2(t, a, adot) = onecmptiv(t, a, adot, p)

Sundials.cvode(f1test2, a0, t)


# 'manual' use of multiple doses

t1 = [0.:0.1:5.]
a01 = [10.]

y1 =Sundials.cvode(f1test2, a01, t1)
y1[end]

t2 = [5.:0.1:15.]
a02 = [10. + y1[end]] 
y2 =Sundials.cvode(f1test2, a02, t2)
ally
y1[1]

using DataFrames
allt = [t1, t2]
ally = [y1, y2]
# need y is coming out as a 2dim array so this is hack to get it to 1dim so can be a df
df = DataFrame(TIME = allt, CONC = ally[1:length(ally)])

using Gadfly

plot(df, x = "TIME", y = "CONC", Geom.line)


include("pauc.jl")
pauc(df[:TIME], df[:CONC], [0., 15.])
