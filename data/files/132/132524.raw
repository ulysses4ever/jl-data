module MMA
export MMA_load_plotting, MMA_load_images

for x in LOAD_PATH
	println(x);
end

include("math.jl")

mma_plot_path = abspath("plot.jl")
println(mma_plot_path);
include("plot.jl")
println("done load");

#mma_image_path = abspath("image.jl")
#println(mma_image_path);

function __init__()
	println("loaded MMA")
	println("\tuse MMA_load_plotting() to load plotting")
	println("\tuse MMA_load_images() to load special image handling")
end

function MMA_load_plotting()
	println("loading MMA plotting (this can take a while)...")
	include(mma_plot_path)
	println("done")
end

function MMA_load_images()
	println("loading MMA image handling (this can take a while)...")
	include(mma_image_path)
	println("done")
end

end # module
