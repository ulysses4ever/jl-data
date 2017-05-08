module ImageSeam

using Images
import FixedPointNumbers
import ColorTypes
import Base.size


# brightness of a color is the sum of the r,g,b values (stored as float32's)
brightness(c)        =  c.r + c.g + c.b

# brightness of an image bordered with zeros
function brightness(I::Image)
  w, h = size(I)
  b = Array(Float32, w+2, h+2)
  for x = 1:w
    for y = 1:h
      b[x+1, y+1] = brightness(I[x, y])
    end
  end
  b[:,1] = 0
  b[:,h+2] = 0
  b[1,:] = 0
  b[w+2,:] = 0
  b
end

function xenergy(b::Array{Float32, 2}, x::Int64, y::Int64)
  b[x-1, y] + 2b[x, y] + b[x+1, y]
end         

function yenergy(b::Array{Float32, 2}, x::Int64, y::Int64)
  b[x, y-1] + 2b[x, y] + b[x, y+1]
end

function energy(xenergy::Array{Float32}, yenergy::Array{Float32}, x::Int64, y::Int64)
  sqrt((xenergy[x, y-1] - xenergy[x, y+1])^2 + (yenergy[x-1, y] - yenergy[x+1, y])^2)
end


# CarvableImage serves as a workspace for the image seam computations. By
# allocating space for the image data, energy data, cost-to-go, and
# directions, we can avoid re-allocating those arrays each time we want to
# remove another seam. The process is:
# 1. Generate a single CarvableImage from the source image
# 2. To remove one seam, call the (mutating) function carve!(obj)
# 3. To extract the result, call get_image(obj)
type CarvableImage
  img::Image{ColorTypes.RGB4{FixedPointNumbers.UfixedBase{UInt8,8}}, 2, Array{ColorTypes.RGB4{FixedPointNumbers.UfixedBase{UInt8,8}}, 2}}
  width::Int32
  height::Int32
  brightness::Array{Float32, 2}
  xenergy::Array{Float32, 2}
  yenergy::Array{Float32, 2}
  energy::Array{Float32, 2}
  cost_to_go::Array{Float32, 2}
  directions::Array{Int8, 2}
  seam::Array{Int64, 1}

  CarvableImage(img::Image) = (
    img = copy(img);
    (w, h) = size(img);
    b = brightness(img);
    xe = zeros(Float32, size(b, 1), size(b, 2));
    ye = zeros(Float32, size(b, 1), size(b, 2));
    e = zeros(Float32, size(b, 1), size(b, 2)-2);
    c = zeros(Float32, size(b, 1), size(b, 2)-2);
    dirs = zeros(Int8, size(b, 1)-2, size(b, 2)-3);
    seam = zeros(Int64, size(b, 2)-2);
    obj = new(img, w, h, b, xe, ye, e, c, dirs, seam);
    @inbounds update_xenergy!(obj);
    @inbounds update_yenergy!(obj);
    @inbounds update_energy!(obj);
    obj.cost_to_go[1,:] = Inf32;
    @inbounds update_cost_to_go!(obj);
    @inbounds compute_seam!(obj);
    obj
    )
end

# We only have to update the energies for pixels which are to the right of the seam
function update_xenergy!(obj::CarvableImage)
  s::Int64 = 0
  for y = 2:obj.height+1
    s = obj.seam[y-1]
    for x = max(s - 2, 2):obj.width+1
      obj.xenergy[x,y] = xenergy(obj.brightness, x, y)
    end
  end
end

function update_yenergy!(obj::CarvableImage)
  s::Int64 = 0
  for y = 2:obj.height+1
    s = obj.seam[y-1]
    for x = max(s - 2, 1):obj.width+2
      obj.yenergy[x,y] = yenergy(obj.brightness, x, y)
    end
  end
end

function update_energy!(obj::CarvableImage)
  obj.energy[1,:] = Inf32
  obj.energy[obj.width+2,:] = Inf32
  for y = 2:obj.height+1
    s = obj.seam[y-1]
    for x = max(s - 2, 2):obj.width+1
      obj.energy[x, y-1] = energy(obj.xenergy, obj.yenergy, x, y)
    end
  end
end

# Updating the cost-to-go requires keeping track of the fact that a change in
# the cost-to-go at pixel [x, y] can affect all the pixels from [x-1, y-1] to
# [x+1, y-1]. So we maintain an "unknown_frontier" which expands the set of
# pixels which need updates for each row.
function update_cost_to_go!(obj::CarvableImage)
  obj.cost_to_go[:,end] = obj.energy[:,end]
  obj.cost_to_go[obj.width+2,:] = Inf32
  unknown_frontier = obj.seam[obj.height]
  search_directions = Int64[-1, 0, 1]
  for y = obj.height-1:-1:1
    for x = max(unknown_frontier-1, 2):obj.width+1
      # s_min, obj.directions[x-1,y] = findmin(obj.cost_to_go[x+[-1, 0, 1], y+1]) # findmin gets the min and the index
      s_min = obj.cost_to_go[x-1, y+1]
      obj.directions[x-1,y] = 1
      for i = 2:3

        s = obj.cost_to_go[x + search_directions[i], y+1]
        if s < s_min
          s_min = s
          obj.directions[x-1,y] = i
        end
      end
      obj.cost_to_go[x,y] = obj.energy[x,y] + s_min
    end
    unknown_frontier -= 1 
  end
end

function compute_seam!(obj::CarvableImage)
  s = indmin(obj.cost_to_go[2:obj.width+1, 1])
  obj.seam[1] = s
  for y=2:obj.height
    s += obj.directions[s, y-1] - 2
    obj.seam[y] = s
  end
end

# Rather than actually shrinking any of the contained arrays, we just shuffle
# the image and brightness data around and then reduce the stored width. That
# avoids any need to reallocate the data arrays.
function remove_seam!(obj::CarvableImage)
  for y = 1:obj.height
    for x = obj.seam[y]:obj.width-1
      obj.img.data[x, y] = obj.img.data[x+1, y]
      obj.brightness[x+1, y] = obj.brightness[x+2, y]
    end
  end
  obj.width -= 1
end

# Extract the image after seam removal
function get_image(obj::CarvableImage)
  # shareproperties(obj.img, obj.img.data[1:obj.width, :])
  obj.img[1:obj.width,:]
end

# Mutates a CarvableImage to remove one lowest-energy seam
function carve!(obj::CarvableImage)
  @inbounds remove_seam!(obj)
  @inbounds update_xenergy!(obj)
  @inbounds update_yenergy!(obj)
  @inbounds update_energy!(obj)
  @inbounds update_cost_to_go!(obj)
  @inbounds compute_seam!(obj)
end

function precompute_all_sizes(img::Image)
  # A=[img for i=1:1] # set up a vector of images
  A = Array(Image, size(img, 1))
  A[1] = img
  C = CarvableImage(img)
  for i=1:size(img,1)-1
    carve!(C)
    A[i+1] = get_image(C)
  end
  A
end


# Helper functions for unit testing
function save_expected_data()
  if ~isfile("320px-Broadway_tower_edit.jpg")
    run(`wget https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/Broadway_tower_edit.jpg/320px-Broadway_tower_edit.jpg`)
  end
  img = imread("320px-Broadway_tower_edit.jpg")
  A = precompute_all_sizes(img)
  outfile = open("tower_carves.dat", "w")
  serialize(outfile, A)
  close(outfile)
end

function verify(carved_images)
    infile = open("tower_carves.dat", "r")
    expected = deserialize(infile)
    close(infile)
    if length(carved_images) != length(expected)
        println("lengths don't match")
        return false
    end
    for i in 1:length(expected)
        if carved_images[i] != expected[i]
            println("images don't match at index ", i)
            return false
        end
    end
    true
end

end
