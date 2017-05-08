using PyPlot
PyPlot.pygui(true)
include("gradientDescent.jl")

data = readcsv("C:\\Users\\Owner\\Documents\\GitHub\\mat258A\\Homework\ 2\\binary.csv")
names = data[1,:]

# convert the array type on the actual data so it works
data =convert(Array{Float64,2}, data[2:end,:])
# make a normalized set of data
rD = data./[1 800 4 4]

function LogRegress(x)
  # x must be vertical
  m = size(data)[1]
  linear = rD[:,2:3]*x[1:end-1,:]+ones(m,1).*x[end,:]
  obj = sum(-linear.*rD[:,1] + log(1+exp(linear)))
  gradf = [(sum((-rD[:,1] + e.^((linear))./(1+exp(linear))).*rD[:,2:3],1))', sum((-rD[:,1] + e.^(linear)./(1+exp(linear))),1)]
  return (obj, gradf)
end
(minn,path,err) = gradientDescent(LogRegress,[.5 .5 .5]')
minn
path

# Graph the path of the parameters
fV=path[:,end]
plot(path[1,:]',path[2,:]')
title("The path through parameter space")
ylabel("GPA");
xlabel("GRE");
PyPlot.show()

# Start graphing the separating line
bit = convert(BitVector, data[:,1])
bitc = convert(BitVector, 1-bit)
# make a vector of probabilities
m = size(data)[1]
linear = rD[:,2:3]*fV[1:end-1,:]+ones(m,1).*fV[end,:]
p = e.^(rD[:,1].*(linear))./(1+exp(linear))
# make a line representing ambivalence
t = [100:5:900]
s = -4/fV[2]*(fV[1]*t/800+.80*fV[3])
plot(t,s,color="k")
pos =PyPlot.scatter(data[bit,2], data[bit,3], s=1000*p[bit,:].^3, c=.5*p[bit,:],  marker="+", alpha=1)
neg =PyPlot.scatter(data[bitc,2], data[bitc,3], s=50*p[bitc,:].^3, c = .5*p[bitc,:], marker="o", alpha=0.5)
title("Scatter Plot of Admissions data with Boundary of Ambiguity");
ylabel("GPA");
xlabel("GRE");
legend((pos, neg),("Admitted","Not Admitted"), scatterpoints=1,loc="upper right");
axis([200,850,2,4.5]);
PyPlot.show()

