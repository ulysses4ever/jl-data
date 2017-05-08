# Functions not ready for prime time

function append!(a::CountMinSketch, b::CountMinSketch)
    if shape(a) != shape(b)
        error("CountMinSketches must be of the exact same sketch dimensions")
    end
    a.sketch += b.sketch
end


function unappend!(a::CountMinSketch, b::CountMinSketch)
    if shape(a) != shape(b)
        error("CountMinSketches must be of the exact same sketch dimensions")
    end
    a.sketch -= b.sketch
end
