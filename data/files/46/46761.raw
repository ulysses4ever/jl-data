using Plots
using Interact
plotlyjs()

unique_vehicle_ids(high_level) = sort(unique(high_level[:vehicle_ID]))

function plot_number_of_trips_per_vehicle(high_level)
    vehicles = unique_vehicle_ids(high_level)
    counts = map(id->sum(high_level[:vehicle_ID] .== id), vehicles)
    bar(collect(1:length(vehicles)), counts, size=(800,400), xlabel="vehicle", ylabel="number of trips")
end

function plot_histogram_per_vehcile(high_level, target)
    vehicles = unique_vehicle_ids(high_level)
    xlims = extrema(high_level[target])
    p1 = histogram(high_level[find(high_level[:vehicle_ID] .== vehicles[1]), target], title=1, xlims=xlims)
    p2 = histogram(high_level[find(high_level[:vehicle_ID] .== vehicles[2]), target], title=2, xlims=xlims)
    p3 = histogram(high_level[find(high_level[:vehicle_ID] .== vehicles[3]), target], title=3, xlims=xlims)
    p4 = histogram(high_level[find(high_level[:vehicle_ID] .== vehicles[4]), target], title=4, xlims=xlims)
    p5 = histogram(high_level[find(high_level[:vehicle_ID] .== vehicles[5]), target], title=5, xlims=xlims)
    plot(p1, p2, p3, p4, p5, size=(950, 600))
end

function scatter_targets(high_level, A, B)
    vehicles = unique_vehicle_ids(high_level)
    p = plot(xlabel=string(A), ylabel=string(B))
    for (i,id) in enumerate(vehicles)
        x = mean(high_level[find(high_level[:vehicle_ID] .== id), A])
        y = mean(high_level[find(high_level[:vehicle_ID] .== id), B])
        scatter!(p, Float64[x], Float64[y], lab=string(i))
    end
    p
end