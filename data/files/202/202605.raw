
using Sundials
include("regimen.jl")

@everywhere function onecmptiv(t, a, adot, p)
	# p1 = KEL	
        adot[1] = -p[1]*a[1]
end
testing = [1., 2., 3.]
testing
testing2 = splice!(testing, 1:2)
testing2
testing
@everywhere function sim_ind(regimen)
p = [0.1] # KEL
test_onecmpt(t, a, adot) = onecmptiv(t, a, adot, p)
conc = Array(Float64,0)
time = Array(Float64,0)
sample_times = [0.:0.016:regimen[1][end]+24.]

	for (j,amt) in enumerate(regimen[2])
		dtime = (j == length(regimen[2]) ? sample_times[end] : regimen[1][j+1])
		
		time_slice = Float64[] # must define outside for loop or time_slice only defined inside will not be available ever in global scope
		for i in  1:length(sample_times) 
			if sample_times[i] .< dtime 
				continue
			else 
				time_slice = splice!(sample_times, 1:i-1) # as loop will go 1 past the last element we want only want to splice to i-1
				push!(time_slice, dtime)
				break
			end
		end
		if j == 1	
		y =Sundials.cvode(test_onecmpt, [amt], time_slice)
		else
		y =Sundials.cvode(test_onecmpt, [conc[end] + amt], time_slice)
		end
		append!(conc, y[1:end])
		append!(time, time_slice)
		
	end
return (time, conc)
end
regimen(100., 5, interval = 12)
sim_ind(regimen(100., 5, interval = 12))
function all_sims()
 for i in 1:100
		sim_ind(regimen(100., 5, interval = 12))
	end
end
all_sims()
@time sim_ind(regimen(100., 5, interval = 12))
@time all_sims()
# need y is coming out as a 2dim array so this is hack to get it to 1dim so can be a df
df = DataFrame(TIME = time, CONC = conc)
# in order to take advantage of parallelization need to launch julia via
# julia -p 4 (or however many processors on that comp)
M = [regimen(100., 5, interval = 12)for i=1:100]
@time pmap(sim_ind, M)
