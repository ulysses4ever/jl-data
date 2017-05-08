using DataFrames
using Gadfly
include("../Libs/catrows.jl")
include("../Libs/getQuery.jl")
include("nugget.jl")

############################
# ---- Original sizes ----
#
# t_D = 7764
# sizeOfD = 22057845
# t_D_r = 7764
# sizeOfD_r = 153608
#
# sizeOfA = 97566250
# t_A = 2246
# t_A_r = 483
#
# sizeOfP = 1098988
############################
# ---- Julia Org Data -----
# ----! DO NOT CHANGE !----

const org_sizeOfD = 153608
const org_t_D = 7764
const org_t_A = 483
const amountOfEmptyValues = 72357775
const nuggetDimensions = 2:2 

const sparseness= amountOfEmptyValues/(org_sizeOfD*org_t_A)

############################

const nugget_dist = 0.2
const nugget_radius = 0.1

function find_rand_unique(Arr::Array, Amount::Int64)

	p_indexes=[1:length(Arr)]
	indexes=Int64[]

	for i=1:Amount
		foundElement=p_indexes[rand(1:length(p_indexes))]
		splice!(p_indexes,foundElement)
		push!(indexes, foundElement);
	end
	Arr[indexes]
end

include("nugget.jl")

function generatePlot(W::DataFrame, nugget)
	diag, dims = nugget
	y=by(W, "id", df -> if df["t_D"][1] == diag diag else "Other" end)
	Wy=join(W,y, on="id", kind = :left)

	plot(Wy[getAndQuery(dims), [dims[1], dims[2], "x1"]], x=dims[1], y=dims[2], color="x1", Geom.point)
end

function createPlots(W::DataFrame, Nuggets::Array)

	file=open("index.html", "w+")

	html="<script src=\"../Libs/js/d3.min.js\"></script><script src=\"../Libs/js/gadfly.js\"></script>"

	for i=1:length(Nuggets)
		plot=generatePlot(W,Nuggets[i])
		id="nugget$i"
		draw(D3("Data/$id.js", 8inch, 8inch), plot)
		html=string(html, "<div id=\"$id\"></div><script src=\"Data/$id.js\"></script><script>draw(\"#$id\");</script>")
	end

	write(file,html)
	close(file)
end

const def_sizeOfD = 300000

const min_nugget_size = 20
const nuggets = 1000

function generate_nonnugget_synthetic_data()
def_t_A = int(round((org_t_A/org_sizeOfD)*def_sizeOfD))

sparnessPostNuggets= sparseness-(min_nugget_size*nuggets)/(def_sizeOfD*def_t_A)

def_t_D = int(round((org_t_D/org_sizeOfD)*def_sizeOfD))

W = DataFrame()

W["id"] = [ 1:def_sizeOfD ]

W["t_D"] = [ string("d", rand(1:def_t_D)) for i=1:def_sizeOfD ]

 for i=1:def_t_A
 	W[string("f",i)] = [ if rand() > sparnessPostNuggets rand() else NA end for i=1:def_sizeOfD ]
 end
 writetable("output1.csv", W)
 readtable("output1.csv")
end

W=generate_nonnugget_synthetic_data()

#W = readtable("output1.csv")

features=colnames(W)[3:end]

Nuggets=createNuggets(W,features,nuggets)

writetable("nuggets.csv", Nuggets)

#createPlots(W,Nuggets)