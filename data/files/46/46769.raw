using Plots
using Interact
# plotlyjs()
pyplot()

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

function plot_drive(index::Int; scatter::Bool=false)
    utmx = Float64[]
    utmy = Float64[]
    path = anon_paths[index]["utm"]
    for pt in path
        push!(utmx, pt[1])
        push!(utmy, pt[2])
    end
    lox, hix = extrema(utmx)
    loy, hiy = extrema(utmy)
    max_sep = max(hix - lox, hiy - loy)
    midx = (hix + lox)/2
    midy = (hiy + loy)/2
    half_sep = max_sep/2*1.1
    xlims = (midx-half_sep, midx+half_sep)
    ylims = (midy-half_sep, midy+half_sep)
    p = plot(utmx, utmy, xlabel="x position [m]", ylabel="y position [m]", xlims=xlims, ylims=ylims, size=(800,800))

    if scatter == true
        scatter!(p, utmx, utmy)
    end

    p
end