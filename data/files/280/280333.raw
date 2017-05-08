arcs=readcsv("C:/Users/adm/Desktop/Book2.csv",Int)
non= maximum(arcs[:,1:2])
function AdjList(arcs,non)
  A=Array(Array{Int},non)
  for i=1:non A[i]=[] end
  for i=1:size(arcs,1)
    a,b,c=arcs[i,:]
    get=[b,c]
    println("nooooooooooooo")
    println(get)
A[a]=get
   # push!(A[a],(b,c))
    #push!(A[arcs[i,1]],arcs[i,3])
  end
  return A
end
println("finalllll")
adj=AdjList(arcs,non)
println(adj)


arcs=readcsv("C:/Users/adm/Desktop/Book2.csv",Int)
non= maximum(arcs[:,1:2])

function adjMatrix (arc,non)
  matrix = zeros (Int,non,non)
  for i = 1: size(arcs,1)
    node1=arcs[i,1]
    node2=arcs[i,2]
    node3=arcs[i,3]
    matrix[node1,node2]=node3
  end
  return matrix
end

a=adjMatrix(arcs,non)

