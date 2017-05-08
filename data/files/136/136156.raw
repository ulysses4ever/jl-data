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

"""
Speed of sound (m/s) for thigh tissue types
"""
speeds = Dict(
              0 => 1540.0, # PAA gel
              3 => 1562.0, # White matter
              4 => 1450.0, # Fat
              5 => 1585.0, # Muscle
              6 => 1660.0, # Muscle/skin
              7 => 2845.0, # Bone
              8 => 1584.0, # Vessels
              9 => 1522.0, # Around fat
              11 => 1540.0); # Bone marrow


"""
Proper names for tissue types
"""
tissue_types = Dict(
              0 => "PAA gel",
              3 => "White matter",
              4 => "Fat",
              5 => "Muscle",
              6 => "Muscle/skin",
              7 => "Bone",
              8 => "Vessels",
              9 => "Around fat",
              11 => "Bone marrow");

"""
Convert pixel ID's to inverse speeds (slowness), leaving the input array intact.
"""
function id2slowness(M::Array{Int, 2})
    id2slowness!(deepcopy(M))
end

"""
Convert pixel ID's to inverse speeds (slowness) in place, changing the input array.
"""
function id2slowness!(M::Array{Int, 2})
    for i in size(M)[1]
        for j in size(M)[2]
            M[i,j] = 1/speed[M[i,j]];
        end
    end
    M
end
