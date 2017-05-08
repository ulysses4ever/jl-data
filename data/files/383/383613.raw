function generateSampleData(numpatients, numtimepoints)
	#generate a matrix with numpatients row and numtimepoints colms
	data = 100.0+25.0*(.5-rand(numpatients,numtimepoints))
	@show typeof(data)
	return data

end

function doPCA(data)
	N = size(data,2)
	M = size(data,1)
	mn = mean(data,2)
	mnfilled= fill(mn, M, N)
	data =data-mnfilled #subtract off mean
	@show typeof(data)
	cov = 1./(N-1)*data*transpose(data)
	@show typeof(cov)
	d,v = eig(cov)
	@show v
	
end

function doPCAoverTime(data)
	for j in collect(1:size(data,1))
		currdata = data[:,j]
		doPCA(currdata)
	end
end

function main()
	sampleData = generateSampleData(10,100)
	@show typeof(sampleData)
	doPCA(sampleData)
end
