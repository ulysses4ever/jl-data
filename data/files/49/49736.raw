# plotfile.jl
#
# Description: Function to Plot a csv File
#
# amousam@dewberry.com



#---Load Packages
using PyPlot

#---Function to Plot a csv File

function plotfile(file)
    df=readdlm(file,',', header=false, skipstart=1)
    data=df[:,6:7]                                    #---Read in columns [(rows),column_1:column_n]
    datasort=sortrows(data, by=x->(x[2],x[1]))        #---Sort
    v=datasort[:,1]
    f=sum(v)
    p=cumsum(v)
    g=p/f
    j=datasort[:,2]
    plot(j,g)
	plt = PyPlot
	plt.ylabel("Normalized Length");
	plt.xlabel("Elevation (ft)");
	plt.grid("on")
	plt.title("Characteristic Levee Crest Elevation")
	savefig(replace(file,"csv","png"))
	close()
end
