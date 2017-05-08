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
Given an Int matrix of pixel ID's, return a Float64 matrix of inverse speeds (slowness).
"""
function id2slowness(M::Array{Int, 2})
    V = Array{Float64}(size(M));
    for i in size(M)[1]
        for j in size(M)[2]
            V[i,j] = 1/speeds[M[i,j]];
        end
    end
end

"""
Rectangular section A of phantom thigh. A rectangular section, is defined by the coordinates of its four corners and specifies the positions of two contralateral probes. Corners are listed in counter-clockwise order from the upper left. Probe coordinates can be calculated using function `GenS.probPos`.
"""
section_A = [8.243810336540204  91.17893727910730;
             16.075381869743303  31.69224559667868;
             190.887988558032134  54.70676187695501;
             183.056417024829045 114.19345355938363];
"""
Rectangular section B of phantom thigh.
"""
section_B = [52.10302297389187  15.380882068250578;
             108.48458022104636  -5.140326531289552;
             171.08420521598575 166.850729608633742;
             114.70264796883131 187.371938208173901];
