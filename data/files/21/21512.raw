#https://code.google.com/codejam/contest/11214486/dashboard
using DataStructures

a = [1 0 0 0;
     1 1 1 0;
     1 0 0 1;
     0 0 1 0]

function get_active_around(g, i, j)
    active_arounds = []
    i != 1 && g[i-1, j] == 1 && push!(active_arounds, (i-1, j))
    i != size(g, 1) && g[i+1, j] == 1 && push!(active_arounds, (i+1, j))

    j != 1 && g[i, j-1] == 1 && push!(active_arounds, (i, j-1))
    j != size(g, 2) && g[i, j+1] == 1 && push!(active_arounds, (i, j+1))
    return active_arounds
end

function get_connected_graph!(g, i, j, cg)
    active_arounds = get_active_around(g, i, j)
    for e in active_arounds
        if !in(e, cg)
            push!(cg, e)
            get_connected_graph!(g, e..., cg)
        end
    end
    return cg
end

cg = []
#println(get_connected_graph!(a, 2, 1, []))

function get_num_connected_graph(g)
    cgs = []
    for e in zip(1:size(g, 1), 1:size(g, 2))
        if !any(map(cg -> in(e, cg), cgs))
            push!(cgs, get_connected_graph!(g, e..., []))
        end
    end
    return length(cgs)
end

#println(get_num_connected_graph(a))

function set_zero_to_around(g, i, j, a)
    if i != 1 && !in((i-1, j), a)
        g[i-1, j] = 0
        push!(a, (i-1, j))
        set_zero_to_around(g, i-1, j, a)
    elseif i != size(g, 1) && !in((i+1, j), a)
        g[i+1, j] = 0
        push!(a, (i+1, j))
        set_zero_to_around(g, i+1, j, a)
    end
    if j != 1 && !in((i, j-1), a)
        g[i, j-1] = 0
        push!(a, (i, j-1))
        set_zero_to_around(g, i, j-1, a)
    elseif j != size(g, 2) && !in((i, j+1), a)
        g[i, j+1] = 0
        push!(a, (i, j+1))
        set_zero_to_around(g, i, j+1, a)
    end
end

function get_num_connected_graph2(g)
    g2 = deepcopy(g)
    i, j = 1, 1
    c = 0
    for e in g2
        if e != 0
            set_zero_to_around(g2, i, j, [])
            c += 1
        end
        if i < size(g2, 1)
            i += 1
        else
            i = 1
            j += 1
        end
    end
    c
end

function alter!(g, i, j, m, n)
    if g[i, j] == 1
        g[i, j] = 0
        i != m && alter!(g, i+1, j, m, n)
        i != 1 && alter!(g, i-1, j, m, n)
        j != n && alter!(g, i, j+1, m, n)
        j != 1 && alter!(g, i, j-1, m, n)
    end
end

"""
function alter!(g, i, j, m, n)
    if g[i, j] == 1
        g[i, j] = 0
        if i != m
            alter!(g, i+1, j, m, n)
            j != n && alter!(g, i, j+1, m, n)
            j != 1 && alter!(g, i, j-1, m, n)
        end
        if i != 1
            alter!(g, i-1, j, m, n)
            j != n && alter!(g, i, j+1, m, n)
            j != 1 && alter!(g, i, j-1, m, n)
        end
    end
end
function alter!(g, i, j, m, n)
    if g[i, j] == 1
        g[i, j] = 0
        if i == m
            alter!(g, i-1, j, m, n)
            j != n && alter!(g, i, j+1, m, n)
            j != 1 && alter!(g, i, j-1, m, n)
        elseif i == 1
            alter!(g, i+1, j, m, n)
            j != n && alter!(g, i, j+1, m, n)
            j != 1 && alter!(g, i, j-1, m, n)
        else
            alter!(g, i+1, j, m, n)
            alter!(g, i-1, j, m, n)
            j != n && alter!(g, i, j+1, m, n)
            j != 1 && alter!(g, i, j-1, m, n)
        end
    end
end
"""

function get_num_connected_graph3(g)
    m = size(g, 1)
    n = size(g, 2)
    es = deepcopy(g)
    c = 0
    for i in 1:m
        for j in 1:n
            if es[i, j] == 1
                alter!(es, i, j, m, n)
                c += 1
            end
        end
    end
    return c
end



#println(get_num_connected_graph(a))

println("function3")
println(@time get_num_connected_graph3(a))
println("function2")
println(@time get_num_connected_graph2(a))
println("function1")
println(@time get_num_connected_graph(a))

b = [1 0 0 0;
     1 1 1 0;
     1 0 0 1;
     0 0 1 0]

#set_zero_to_around(b, 2, 2, [])

#println(b)
