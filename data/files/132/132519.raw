module MMA
export MMA_load_plotting, MMA_load_images

include("math.jl")

mma_plot_path = abspath("plot.jl")
mma_image_path = abspath("plot.jl")

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
