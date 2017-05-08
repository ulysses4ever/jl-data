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
# now we radiate out... and stop at the closest pixel in dest with the same color as the pixel in source
# this, too, is massively parallel, since all we need to do is read, and we do it for every pixel
# need to compute for both source to dest and dest to source.
# we are going to travel along a discretized archemedian spiral:
# http://cnr.lwlss.net/RasterArchimedes/

function spiral_point(theta, alpha)
    int((alpha*theta/(2*pi))*[cos(theta), sin(theta)])
end

function delta(theta, alpha, omega)
    (2*pi*omega)/sqrt(alpha^2*(1+theta^2))
end

circle_location(1/sqrt(2), 1/sqrt(2))
function distance(a,b)
    diff = a-b
    sqrt(dot(diff,diff))
end

function get_next_point(theta, alpha, omega, focus_point)
    # return tuple containing next sample point [x,y] AND next theta
    delta_new = delta(theta, alpha, omega)
    theta_new = theta + delta_new
    (focus_point + spiral_point(theta_new, alpha), theta_new)
end

function in_rectangle(point, top_left, bottom_right)
    top_left[1] <= point[1] <= bottom_right[1] && top_left[2] <= point[2] <= bottom_right[2]
end

function sample_spiral(focus_point, halt_fn, top_left, bottom_right)
    # Sample pixels along a spiral radiating out from `focus_point`
    # along rectangular grid bounded by `top_left` and `bottom_right`
    # halting on the condition that `halt_fn` returns true for
    # the current point.
    # Algorithm based on: http://cnr.lwlss.net/RasterArchimedes/
    alpha = 1/sqrt(2)
    omega = 1/sqrt(2)
    theta = 0

    corners = [[top_left[1], top_left[2]], [bottom_right[1], top_left[2]],
               [bottom_right[1], bottom_right[2]], [top_left[1], bottom_right[2]]]
    distances = map(corner -> distance(focus_point, corner), corners)
    farthest_corner = corners[indmax(distances)]

    # initialize current x, y
    current_point = focus_point
    while current_point != farthest_corner
        current_point, theta = get_next_point(theta, alpha, omega, focus_point)
        if in_rectangle(current_point, top_left, bottom_right) && halt_fn(current_point)
            return current_point
        end
    end
    false
end
