using GeneralizedMaps: polygon!, GeneralizedMap, collectcelldarts, Dart

# Initialized empty GMap.
g = GeneralizedMap(Dict{Int64, Dart{Int64, Int64}}());

n = 4
# Create four independent polygons in g.
for i in 1:n
    polygon!(g, 1, 4);
end

# Show the return of collect cell darts using both darts in the
# 0-cell as the start dart. Repeat for one 0-cell on each of the
# four polygons to see patterns (or the lack thereof).
for i in 1:n
    println("Ploygon: ", i)
    print("Dart ", i*8-7, " traversal:\n")
    for d in collectcelldarts(g.darts[i*8-7], 0)
        print(d.index, " ")
    end
    println()
    print("Dart ", i*8, " traversal:\n")
    for d in collectcelldarts(g.darts[i*8], 0)
        print(d.index, " ")
    end
    println()
end
