using Graphs
using GraphPlot
using Compose

function drawNetwork(networkPath, compartment_name_array, compartment_connection_name_array)
	vertexList = ExVertex[] #store vertices
	edgeList = ExEdge[] #store edges
	nodeLabels = AbstractString[]
	nodeDic = Dict()
	
	adjMatrix = float(open(readdlm,networkPath));
	num_compartments = size(adjMatrix,1)
	poss_edges = size(adjMatrix,2)

	overflowcounter = 0; #for counting comparments that are just used for degreatation

	#create all of the nodes and label them
	for j = 1:num_compartments
		currName = compartment_name_array[j]
		currVertex = ExVertex(j, string(currName))
		push!(vertexList, currVertex)
		push!(nodeLabels, currName)
	end

	#construct dictionary for looking up nodes by name
	for(n, f) in enumerate(nodeLabels)
		nodeDic[f] = n
	end
	#println(nodeDic)

	for j = 1:length(compartment_connection_name_array)
		currConnection = compartment_connection_name_array[j]
		#println(currConnection)
		indexFirstUnderscore = search(currConnection, '_')
		indexSecondUnderscore = search(currConnection, '_', indexFirstUnderscore+1)

		
		fromCompartment = currConnection[1:indexFirstUnderscore-1]
		toCompartment = currConnection[indexSecondUnderscore+1:end]
	
		#println(fromCompartment)
		#println(toCompartment)

		#there's a chance we have degreatation or stuff leaving the system, so need to create node for that
		if((fromCompartment in nodeLabels)==false)
			overflowcounter = overflowcounter+1
			currName = fromCompartment
			currVertex = ExVertex(num_compartments+overflowcounter, currName)
			push!(vertexList, currVertex)
			push!(nodeLabels, currName)
			
			nodeDic[currName] = num_compartments+overflowcounter
		elseif((toCompartment in nodeLabels)==false)
			overflowcounter = overflowcounter+1
			currName = toCompartment
			currVertex = ExVertex(num_compartments+overflowcounter, currName)
			push!(vertexList, currVertex)
			push!(nodeLabels, currName)
			nodeDic[currName] = num_compartments+overflowcounter
		end
		#create edges
		#println(nodeDic)
		println(nodeDic[fromCompartment])
		println(typeof((vertexList[nodeDic[fromCompartment]])))
		currEdge = ExEdge(j,vertexList[nodeDic[fromCompartment]],vertexList[nodeDic[toCompartment]])
		#currEdge=ExEdge(j, fromCompartment, toCompartment)
		push!(edgeList, currEdge)

	end
	g = edgelist(vertexList, edgeList, is_directed = true)
	println(edges(g))
	println("-")
	println(vertices(g))
	println("-")
	println(g)
	#plot(g)
	draw(PDF("PBPKLayout.pdf", 10cm, 10cm),gplot(g, nodelabel=nodeLabels))
end

drawNetwork("/home/rachel/Desktop/KWateeServer-v1.0/ReducedOrderModel/network/Connectivity.dat", ["vein", "lungs", "artery", "heart", "kidney", 
"wound"], ["vein_to_lungs","lungs_to_artery","artery_to_heart","heart_to_vein","artery_to_kidney","kidney_to_vein","artery_to_wound","wound_to_artery","wound_to_[]"])

