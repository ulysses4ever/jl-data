using GeneralizedMaps: polygon!, GeneralizedMap, collectcelldarts, Dart
using FactCheck


# Initialized empty GMap.
g = GeneralizedMap(Dict{Int64, Dart{Int64, Int64}}());

# Create n independent squares in g.
n=4
dim_max=2
for i in 1:n
    polygon!(g, 1, dim_max);
end

facts("Check that traverse always returns the start dart first. (Uses collectcelldarts to call traverse.)") do
    for (i, dart) in g.darts
        for dim in 0:dim_max
            t = collectcelldarts(dart, dim)
            @fact dart => t[1]
        end
    end
end

# Show the return of collect cell darts using both darts in the
# 0-cell as the start dart. Repeat for one 0-cell on each of the
# four polygons to see patterns (or the lack thereof).
# for i in 1:n
#     println("Ploygon: ", i)
#     print("Dart ", i*8-7, " traversal:\n")
#     for d in collectcelldarts(g.darts[i*8-7], 0)
#         print(d.index, " ")
#     end
#     println()
#     print("Dart ", i*8, " traversal:\n")
#     for d in collectcelldarts(g.darts[i*8], 0)
#         print(d.index, " ")
#     end
#     println()
# end
