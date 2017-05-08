using Images
using ImageView
using Iterators

cd(dirname(@__FILE__))
source = imread("examples/simple1.png")
dest = imread("examples/simple2.png")
source[:,103,103]
source[:,1,1]
function primary_colors(im, color_count)
    source_array = convert(Array, source)
    results = Dict{Array{Uint8, 1}, Int64}()
    for i = 1:size(im)[2], j = 1:size(im)[3]
        key = im[:,i,j]
        count = get!(results, key, 0)
        results[key] = count + 1
    end

    sorted_keys = sortby(collect(keys(results)), k -> -1*results[k])
    final_results = Set{Array{Uint8, 1}}(take(sorted_keys, color_count))
end

function closest_primary_color(color, primaries)
end
