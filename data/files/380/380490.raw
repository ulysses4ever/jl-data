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
