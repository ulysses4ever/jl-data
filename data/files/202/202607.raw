using Sundials
include("regimen.jl")

function onecmptiv(t, a, adot, p)
	# p1 = KEL	
        adot[1] = -p[1]*a[1]
end



function sim_ind(f, regimen, sample_times)
conc = Array(Float64,0)
time = Array(Float64,0)

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
		y =Sundials.cvode(f, [amt], time_slice)
		else
		y =Sundials.cvode(f, [conc[end] + amt], time_slice)
		end
		append!(conc, y[1:end])
		append!(time, time_slice)
		
	end
return (time, conc)
end

reg = regimen(100., 5., interval = 12)
p = [0.1] # KEL
test_onecmpt(t, a, adot) = onecmptiv(t, a, adot, p)
sample_times = [0.:0.016:reg[1][end]+24.]

sim_ind(test_onecmpt, reg, sample_times)

#must redefine sampling times and such since modifying in place
reg = regimen(100., 5., interval = 12)
p = [0.1] # KEL
test_onecmpt(t, a, adot) = onecmptiv(t, a, adot, p)
sample_times = [0.:0.016:reg[1][end]+24.]
@time sim =sim_ind(test_onecmpt, reg, sample_times)


using DataFrames
df = DataFrame(TIME = sim[1], CONC = sim[2])

function all_sims()
 for i in 1:100
reg = regimen(100., 5., interval = 12)
p = [0.1] # KEL
test_onecmpt(t, a, adot) = onecmptiv(t, a, adot, p)
sample_times = [0.:0.016:reg[1][end]+24.]

sim =sim_ind(test_onecmpt, reg, sample_times)

df = DataFrame(TIME = sim[1], CONC = sim[2])
df[:i] = i
println(head(df))
	end
end
all_sims()
@time all_sims()
# need y is coming out as a 2dim array so this is hack to get it to 1dim so can be a df

# in order to take advantage of parallelization need to launch julia via
# julia -p 4 (or however many processors on that comp)
#M = [regimen(100., 5, interval = 12)for i=1:100]
#@time pmap(sim_ind, M)
