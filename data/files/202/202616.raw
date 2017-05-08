
function regimen(amt,
	n = 0.; # after ; all are named args
	interval = 0.) 
    dose_times = [0.:n-1]*interval
    if(length(amt) != 1 && length(amt) != length(dose_times))
	    error("Please supply only one amount or amounts for each dose")
    end
    if(length(amt) == 1)
	amts = fill(amt, length(dose_times))
    else 
	amts = amt
    end
    
   return (dose_times, amts) 
end

#=
reg1 = regimen(100., 3., interval= 12.)
reg2 = regimen([100., 150.], 2., interval = 12.)	
reg2[1]
reg2[2]
reg2[1][1]
#should fail
regimen([100., 100.], 3., interval = 12.)
=#
