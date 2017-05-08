
function regimen(amt,
	n = 0.; # after ; all are named args
	interval = 0.) 
    dose_times = [0.:n-1]*interval
    if(length(amt) != 1 && length(amt) != length(dose_times))
	    error("Please supply only one amount or amounts for each dose")
    end
   return dose_times 
end

regimen(100., 3., interval= 12.)
	
#should fail
regimen([100., 100.], 3., interval = 12.)
