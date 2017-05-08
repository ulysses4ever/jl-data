using Images
using ImageView
using Iterators
using Color

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

    sorted_keys = sort(collect(keys(results)), by = (k -> -1*results[k]))
    final_results = Set{Array{Uint8, 1}}(take(sorted_keys, color_count))
end

function normalize_rgb(color)
    # convert hex rgb(a) to gamma-corrected float color in [0..1]
    rgb = (float32(color[1:3])./255.0).^(1.0/2.2)
end

function closest_primary_color(color, primaries)
    norm_color = normalize_rgb(color)
    rgb_color = RGB(norm_color[1], norm_color[2], norm_color[3])
    min_dist = Inf32
    closest_color = [0x00,0x00,0x00,0xFF]
    for primary in primaries
        norm_primary = normalize_rgb(primary)
        rgb_primary = RGB(norm_primary[1], norm_primary[2], norm_primary[3])
        distance = colordiff(rgb_color, rgb_primary)
        if distance < min_dist
            min_dist = distance
            closest_color = primary
        end
    end
    closest_color
end

primaries = primary_colors(source, 2)
#closest_primary_color([0x01,0x01,0xff,0xff], primaries)

#I should not do the silly iterator. I should define a function which does an operation for every pixel
#... this is a massively parallelizable operation... just tweaking colors.
#... imfilter exists...
function convert_to_primaries(image, primaries)
    im_size = size(image)
    result = zeros(Uint8, im_size[1], im_size[2], im_size[3])
    for i = 1:im_size[2], j = 1:im_size[3]
        color = image[:,i,j]
        if !in(color, primaries)
            result[:,i,j] = closest_primary_color(color, primaries)
        else
            result[:,i,j] = color
        end
    end
    result
end

primary_source = convert_to_primaries(source, primaries)

colorim(primary_source, "RGBA")
