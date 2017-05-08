Module Traffic
using Graphs, Convex, SCS


"""
Returns a graph of type EdgeList with ExVertex and ExEdge edges and vertices.
The arguments it needs:

A - adjacency matrix
a - free flow cost vector
b - congestion cost vector
OD - OD matrix

The vertices have attributes "o" and "d", whose values are a list of labels of the 
flows for which they are either sources or sinks. Eg. if o=[1,3] for a vertex it is
an origin for journeys corresponding to OD pairs 1 and 3. OD pairs are ordered according
to when they appear by searching through the OD matrix as is done in the function...

Edges have attributes "a" and "b" which correspond to the constants for affine cost
functions with the form f(x) = a + bx (to be generalised later...)

Myabe OD should not be used here, but only when making the optimisation problem to solve...
this has to be decided later? but soon-ish.

This should probably be made into a constructor for a subtype of GenericGraph
so that the graph stores its own "a" and "b" vector... to be decided later...
"""
function make_urban_graph(A, a, b, OD)
    n = size(A)[1]
    
    #Generate vertex list and assing OD attributes
    vlist = [ExVertex(i, "") for i=1:n]
    
    for v in vlist
        v.attributes = AttributeDict([("O" ,Int[]), ("D", Int[])])
    end
    
#Assign OD values to nodes...    
    flows_counter = 1
    
    for i in 1:n
        for j in 1:n
            if OD[i,j] != 0
                
                push!(vlist[i].attributes["O"], flows_counter)
                push!(vlist[j].attributes["D"], flows_counter)
                flows_counter += 1
            end
        end
    end
    
    #Generate edge list and assign cost attributes
    elist = ExEdge[]
    e_counter = 1
    
    for i in 1:n
        for j in 1:n
            if A[i,j] != 0
                for k =1:A[i,j]
                    
                    push!(elist, ExEdge(e_counter, vlist[i], vlist[j]) )
                    e_counter += 1
                end
            end
        end
    end
    
    for i in 1:length(elist)
        
        elist[i].attributes = AttributeDict([("a" , a[i]), ("b" , b[i])])
    end
    
    g = graph(vlist, elist)
end


"""
Constructs and returns the incidence matrix of g. An n x m matrix where n is the nummber of 
nodes and m is the number of edges.

B[i,j] = 1 if edge j is incoming at node i; 
B[i,j] = 1 if edge j is incoming at node i
B[i,j] = 0 otherwiswe
"""
function incidence_matrix(g)
    n = num_vertices(g)
    m = num_edges(g)

    B = zeros(n,m)

    for i in 1:num_vertices(g)
        out_e = out_edges(g.vertices[i], g)
        for e in out_e
            j = edge_index(e)
            B[i,j] = -1
        end
    end

    for i in 1:num_vertices(g)
        in_e = in_edges(g.vertices[i], g)
        for e in in_e
            j = edge_index(e)
            B[i,j] = 1
        end
    end
    
    return B
end


"""
Generates convex optimisation problem from the graph g, the Origin-Destination matrix OD,
and the demand vector q. If only one OD pair, then q is a scalar. Regime is either "UE" (default)
which is "user equilibrium" or "SO": system optimal.

This should be a general method for multiple OD pairs, but it only works for 1 OD pair for now

This function uses Convex.jl
"""
function make_ta_problem(g, OD, q, regime="UE")
    
    #n = num_vertices(g)
    m = num_edges(g)

    a = Float64[g.edges[i].attributes["a"] for i=1:m]
    b = Float64[g.edges[i].attributes["b"] for i=1:m]
    
    x = Variable(m)
    B = incidence_matrix(g)

    d = zeros(m)

    for i in 1:num_vertices(g)
        #println("i = $i")
        for j in length(q)
            #println("j = $j")
            if j in g.vertices[i].attributes["O"]
                #println("flow $j has origin at node $i ")
                d[i] = -1*q[j]
            end
            if j in g.vertices[i].attributes["D"]
                #println("flow $j has destination at node $i ")
                d[i] = q[j]
            end
        end
    end

    equality_constraints = B*x == d # Flow conservation at nodes
    inequality_constraints = x >= 0 # Non-negative flows

    if regime == "UE"
        cost_function = dot(a, x) + 0.5*quadform(x,diagm(b))
    elseif regime == "SO"
        cost_function = dot(a,x) + quadform(x,diagm(b))
    else
        error("Regime must be either 'UE' or 'SO'...")
    end

    problem = minimize(cost_function, equality_constraints, inequality_constraints)
    
    return problem, x 
end


"""
Returns solutions to the traffic assignment problem for a given range of demands: q_range.
Calls function make_ta_problem
"""
function ta_solve(g, OD, q_range, regime="UE")
    println("Will solve $regime, TA problem  for $(length(q_range)) values of demand...\n")
    
    sols = Array{Float64}[]
    for q in q_range
        problem, x = make_ta_problem(g, OD, q, regime)
        solve!(problem)
        println("\n\nq = $q\nStatus: $(problem.status)\n\n")
        push!(sols, x.value)
    end
    return sols
end 

export make_urban_graph, incidence_matrix, ta_solve

end