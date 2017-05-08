function optimizeODE(opt,edat,p)

pnum = length(p)

finalP = p
finalf = 1e10

#--- Design inital latin hyper cube---

lhc = designLHC(opt.iters,pnum,opt.space)

#---Save parameters for plotting parameter space---

all_param = Array(Float64,opt.iters*opt.spcrd,pnum+1)
all_param[:,pnum+1] = all_param[:,pnum+1].*finalf

for v = 1:opt.spcrd

	for i = 1:opt.iters	
		all_param[opt.iters*(v-1) + i,:] = paramSearch(opt,edat,lhc[:,i])	
		print(' ',i)		
	end

	idxmin = indmin(all_param[1:opt.iters*v,pnum+1])

	if all_param[idxmin,pnum+1] < finalf

		finalf = all_param[idxmin,pnum+1]
		finalP = all_param[idxmin,1:end-1]
		print('\n',"Found better parameters! Function value is:  ",finalf,'\n',"Parameters are:  ",finalP)

	end

	error_temp = copy(all_param[1:opt.iters*v,pnum+1])
	best_param = Array(Float64,int(opt.iters/10),pnum)

	print('\n',"Best 10%:" ,'\n')

	for i = 1:int(opt.iters/10)
		idx = indmin(error_temp)		
		best_param[i,:] = all_param[idx,1:end-1]

		print(minimum(error_temp),'\n')
		error_temp[idx] = maximum(error_temp)

	end
	#---construct lhc from logspace of previous bounds---

	lhc = designLHC(opt.iters,best_param)

end

writedlm("All_sampled_parameters.csv",all_param,',')

print('\n',"final value      ", finalf)
print('\n',"final parameters      ", abs(finalP))

return(0)
end






