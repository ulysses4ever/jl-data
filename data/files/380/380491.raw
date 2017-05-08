function g4()
    s = Vertex(1, flow=30)
    u = Vertex(2)
    v = Vertex(3)
    t = Vertex(4, flow=-30)
    vrts = Vertex[s, u, v, t]

    e1 = Edge(s, u, cap=20)
    e2 = Edge(s, v, cap=10)
    e3 = Edge(u, t, cap=10)
    e4 = Edge(v, t, cap=20)
    e5 = Edge(u, v, cap=30)
    edgs = Edge[e1, e2, e3, e4, e5]

    Graph(vrts, edgs)
end

function testmaxflow()
    println("Testing maxflow, simple graph")
    g = g4()
    maxflow!(g)
    isfeasibleflow(g) || error("maxflow fail!")    
    g
end

function testmaxflow8()
    println("Testing maxflow, big8 graph")
    g = netg("data/big8.net")
    makest!(g)
    maxflow!(g)
    resetst!(g)
    isfeasibleflow(g) || error("maxflow fail!")    
    g
end

function testmaxflowdata()
    println("Testing maxflow, netg graphs")
    folder = "data"
    for f in readdir(folder)
        endswith(f, ".net") || continue
        path = "data/$f"
        print("Processing $path... ")
        g = netg(path)
        makest!(g)
        maxflow!(g)
        resetst!(g)
        if isfeasibleflow(g)
            println("PASS")
        else
            println("FAIL")
        end
    end
end

function g6()
    a = Vertex(1)
    b = Vertex(2)
    c = Vertex(3)
    d = Vertex(4)
    e = Vertex(5)
    t = Vertex(6)
    vrts = Vertex[a,b,c,d,e,t]
    
    e1 = Edge(a, b, cost=-4)
    e2 = Edge(a, t, cost=-3)
    e3 = Edge(b, d, cost=-1)
    e4 = Edge(b, e, cost=-2)
    e5 = Edge(c, b, cost=8)
    e6 = Edge(c, t, cost=3)
    e7 = Edge(d, a, cost=6)
    e8 = Edge(d, t, cost=4)
    e9 = Edge(e, c, cost=-3)
    e10 = Edge(e, t, cost=2)

    edgs = Edge[e1,e2,e3,e4,e5,e6,e7,e8,e9,e10]
    
    Graph(vrts,edgs)
end

function g4neg()
    v1 = Vertex(1, flow=4)
    v2 = Vertex(2)
    v3 = Vertex(3)
    v4 = Vertex(4, flow=-4)
    vrts = Vertex[v1, v2, v3, v4]
    
    e1 = Edge(v1, v2, cost=2,cap=4)
    e2 = Edge(v1, v3, cost=2,cap=2)
    e3 = Edge(v2, v3, cost=1,cap=2)
    e4 = Edge(v2, v4, cost=3,cap=3)
    e5 = Edge(v3, v4, cost=1,cap=5)
    edgs = Edge[e1, e2, e3, e4, e5]
    
    Graph(vrts, edgs)
end

function testmincost_cyclecanceling()
    println("Testing mincost cycle-canceling, simple graph")
    g = g4neg()
    maxflow!(g)
    mincost_cyclecanceling!(g)
    isfeasibleflow(g) || error("mincost cycle-canceling fail!")    
    cost(g)
end

function testmincost_cyclecanceling6()
    println("Testing mincost cycle-canceling, stndrd6 graph")
    g = netg("data/stndrd6.net")
    maxflow_castst!(g)
    mincost_cyclecanceling!(g)
    isfeasibleflow(g) || error("mincost cycle-canceling fail!")
    cost(g)
end

function testmincostdata_cyclecanceling()
    println("Testing mincost cycle-canceling, netg graphs")
    folder = "data"
    for f in readdir(folder)
        endswith(f, ".net") || continue
        !beginswith(f, "big") || continue
        path = "data/$f"
        print("Processing $path... ")
        g = netg(path)
        maxflow_castst!(g)
        mincost_cyclecanceling!(g)
        if isfeasibleflow(g)
            println("PASS (cost=$(cost(g)))")
        else
            println("FAIL")
        end
    end
end
