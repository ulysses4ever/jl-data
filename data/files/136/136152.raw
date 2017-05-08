# I/O for phantom thigh

"""
Read phantom thigh data at one of 4 pixel sizes, 1 being the coarsest (3.76 mm,) 4 the finest (0.47 mm.) 
"""
function readPhantom(pixel_size::Int)
    if(!(1 <= pixel_size  <= 4))
        error("Pixel size must be one of 1, 2, 3, or 4.");
    end
    path = joinpath(Pkg.dir("ThighDemo"), "data",
                    "thigh_"*string(pixel_size)*".txt");
    readdlm(path, ',', Int);
end
