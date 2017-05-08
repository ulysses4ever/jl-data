using Clustering
using DataFrames
using PyPlot
using Distances

df = readtable("usefuldataWithSAPSscoresAndOverUnder.csv",separator = ',', header = false) #read table
#remove NANs
[df[df[nm].== "nothing",nm] = NA for nm in names(df)]
#for nm in names(df)
#	df[isnan(df[nm]),nm]=NA
#end

df[~isna(df[:,symbol("x3")]),:]	
deleterows!(df,find(isna(df[:,symbol("x3")])))
deleterows!(df,find(isna(df[:,symbol("x4")])))
deleterows!(df,find(isna(df[:,symbol("x7")])))
#deleterows!(df,find(isna(df[:,symbol("x10")])))
#deleterows!(df,find(isna(df[:,symbol("x11")])))
#delete!(df, :x7) #delete 7th column that shouldn't exist

rename!(df, :x1, :subject_id)
rename!(df, :x2, :MSE)
rename!(df, :x3, :avgP)
rename!(df, :x4, :varianceP)
rename!(df, :x5, :avgHR)
rename!(df, :x6, :varianceHR)
rename!(df, :x7, :age)
rename!(df, :x8, :gender)
rename!(df, :x9, :SAPSscore)
rename!(df, :x10, :errorOverEstimates)
rename!(df, :x11, :errorUnderEstimates)
rename!(df, :x12, :percentOverEstimates)
rename!(df, :x13, :percentUnderEstimates)

#replace any ages greater than 110 with 110
df[df[:age].> 110, :age]=110

data = df[2:end] #remove first colum with IDs

delete!(data, :gender)
#delete!(data, :age)
delete!(data, :MSE)
#delete!(data, :avgHR)
delete!(data, :avgP)
delete!(data, :varianceHR)
delete!(data, :varianceP)
delete!(data, :percentOverEstimates)
delete!(data, :percentUnderEstimates)
delete!(data, :errorOverEstimates)
delete!(data, :errorUnderEstimates)
@show data
dataArray = transpose(convert(Array,data)) 

dist = pairwise(Euclidean(),dataArray)
maxclusters = 26
sumSilsArray = fill(1.0, 1,maxclusters+1)
PyCall.PyDict(matplotlib["rcParams"])["font.sans-serif"] = ["Helvetica"]
for j in range(2,maxclusters)
	close("all")
	R = kmeans(dataArray,j;maxiter=500, display=:iter)
	a = assignments(R)
	count = counts(R)
	sils = silhouettes(R,dist)
	centers = R.centers
	df[:assignment] = (a)
	df[:silhouettes] = sils
	sumSilsArray[j] = sum(df[:silhouettes])

	#draw(PDF(string(j, "clustersWithOnlyMSEandvariance.pdf"), 10inch, 10inch), plot(x =df[:varianceHR], y =df[:MSE], color = R.assignments, Geom.point, Guide.xlabel("varianceHR"), Guide.ylabel("MSE")))
	hold("on")
	s= scatter3D(df[:age], df[:SAPSscore], df[:avgHR], c = a, cmap = ColorMap("Greys"))
	#scatter3D(centers[1,:], centers[2,:], centers[3,:], color = "b")
	axis([0,120,0,100])
	xlabel("Age",fontsize=18)
	ylabel("SAPs Score",fontsize=18)
	zlabel("Average Heart Rate",fontsize=18)
	#colorbar(s)
	
	
	savefig(string("outputpic/justAgeSAPSavgHR/",j, "clusters.pdf"))
	offset = 0
	fig =figure()
	hold("on")
	for i in range(1,j)
		ith_clust_sil_val= df[df[:assignment].==i, :silhouettes]
		sort!(ith_clust_sil_val)
		x = range(offset+1,length(ith_clust_sil_val))
		#colorstr = [i/maxclusters, i/j, 1-i/maxclusters]
		colorstr = string(1-i/(maxclusters+1))
		#@show colorstr
		barh(x,ith_clust_sil_val, color=colorstr, edgecolor=colorstr)
		offset = offset + length(ith_clust_sil_val)
	end
	#savefig("outputpic/usingAgeAndSAPS/",j, "silhoutetteWithAgeAndSAPS.pdf")

	
	sort!(df, cols = [order(:assignment), order(:MSE), order(:SAPSscore)])
	writetable(string("outputdata/",j, "clustersAgeSAPSavgHR.csv"),df)
end

figure()
plot(range(2,maxclusters), sumSilsArray[2:end], "kx")
xlabel("Number of Clusters",fontsize=18)
ylabel("Sum of Silhouettes",fontsize=18)
savefig("outputpic/sumofsilhouettesasafunctionofclustersjustAgeSAPSavgHR.pdf")
