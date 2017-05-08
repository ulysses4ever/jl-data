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

# xenergy(b) = [fill(Inf32, 1, size(b, 2));
#               [xenergy(b, x, y) for x=2:size(b, 1)-1, y=1:size(b, 2)];
#               fill(Inf32, 1, size(b, 2))]

function yenergy(b::Array{Float32, 2}, x::Int64, y::Int64)
  b[x, y-1] + 2b[x, y] + b[x, y+1]
end

# yenergy(b) = hcat(fill(Inf32, size(b, 1), 1),
#               [yenergy(b, x, y) for x=1:size(b, 1), y=2:size(b, 2)-1],
#               fill(Inf32, size(b, 1), 1))

function energy(xenergy::Array{Float32}, yenergy::Array{Float32}, x::Int64, y::Int64)
  sqrt((xenergy[x, y-1] - xenergy[x, y+1])^2 + (yenergy[x-1, y] - yenergy[x+1, y])^2)
end

# function energy(xenergy, yenergy)
#   e = Array(Float32, size(xenergy, 1), size(xenergy, 2)-2)
#   e[1,:] = Inf32
#   e[end,:] = Inf32
#   for x = 2:size(xenergy, 1)-1
#     for y = 2:size(xenergy, 2)-1
#       e[x,y-1] = energy(xenergy, yenergy, x, y)
#     end
#   end
#   e
# end

# # the 3x3 stencil for energy
# function stencil(b)
#       xenergy = b[1,1]+2b[2,1]+b[3,1]-b[1,3]-2b[2,3]-b[3,3]
#       yenergy = b[1,1]+2b[1,2]+b[1,3]-b[3,1]-2b[3,2]-b[3,3]
#       √(xenergy^2 + yenergy^2)
# end

# # energy of an array of brightness values 
# # input: assumed zero borders
# # output: left and right set to ∞
# function energy(b)
#   w, h = size(b)
#   e = [Float32(stencil( b[x-1:x+1, y-1:y+1] )) for x=2:w-1,y=2:h-1]
#   infcol = fill(Inf32,1,h-2)
#   [infcol; e; infcol]
# end


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
    compute_xenergy!(obj);
    compute_yenergy!(obj);
    compute_energy!(obj);
    obj.cost_to_go[1,:] = Inf32;
    compute_cost_to_go!(obj);
    compute_seam!(obj);

    # carve!(obj);
    # @assert size(obj.energy) == size(energy(obj.brightness));
    # @assert maximum(abs(obj.energy - energy(obj.brightness))) <= 1e-4;
    # (c_expected, dirs_expected) = least_energy(obj.energy);
    # x_expected = indmin(c_expected);
    # seam_expected = get_seam(dirs_expected,x_expected);
    # @assert size(obj.directions) == size(dirs_expected);
    # @assert obj.directions == dirs_expected;
    # @assert obj.seam == seam_expected;
    obj
    )
end

function compute_xenergy!(obj::CarvableImage)
  for y = 1:obj.height+2
    for x = 2:obj.width+1
      obj.xenergy[x,y] = xenergy(obj.brightness, x, y)
    end
  end
end

function update_xenergy!(obj::CarvableImage)
  s::Int64 = 0
  for y = 1:obj.height+2
    if y >= 2 && y <= obj.height
      s = obj.seam[y]
    else
      s = 1
    end
    for x = max(s - 2, 2):obj.width+1
      obj.xenergy[x,y] = xenergy(obj.brightness, x, y)
    end
  end
end

function compute_yenergy!(obj::CarvableImage)
  for y = 2:obj.height+1
    for x = 1:obj.width+2
      obj.yenergy[x,y] = yenergy(obj.brightness, x, y)
    end
  end
end

function update_yenergy!(obj::CarvableImage)
  s::Int64 = 0
  for y = 2:obj.height+1
    if y >= 2 && y <= obj.height
      s = obj.seam[y]
    else
      s = 1
    end
    for x = max(s - 2, 1):obj.width+2
      obj.yenergy[x,y] = yenergy(obj.brightness, x, y)
    end
  end
end

function compute_energy!(obj::CarvableImage)
  obj.energy[1,:] = Inf32
  obj.energy[obj.width+2,:] = Inf32
  for y = 2:obj.height+1
    for x = 2:obj.width+1
      obj.energy[x, y-1] = energy(obj.xenergy, obj.yenergy, x, y)
    end
  end
end

function update_energy!(obj::CarvableImage)
  obj.energy[1,:] = Inf32
  obj.energy[obj.width+2,:] = Inf32
  s::Int64 = 0
  for y = 2:obj.height+1
    if y >= 2 && y <= obj.height
      s = obj.seam[y]
    else
      s = one(s)
    end
    for x = max(s - 2, 2):obj.width+1
      obj.energy[x, y-1] = energy(obj.xenergy, obj.yenergy, x, y)
    end
  end
end

function compute_cost_to_go!(obj::CarvableImage)
  obj.cost_to_go[:,end] = obj.energy[:,end]
  obj.cost_to_go[obj.width+2,:] = Inf32
  search_directions = Int64[-1, 0, 1]
  for y = obj.height-1:-1:1
    for x = 2:obj.width+1
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

function remove_seam!(obj::CarvableImage)
  for y = 1:obj.height
    for x = obj.seam[y]:obj.width-1
      obj.img[x, y] = obj.img[x+1, y]
      obj.brightness[x+1, y] = obj.brightness[x+2, y]
    end
  end
  obj.width -= 1
end

function get_image(obj::CarvableImage)
  # shareproperties(obj.img, obj.img.data[1:obj.width, :])
  obj.img[1:obj.width,:]
end

function carve!(obj::CarvableImage)
  @inbounds remove_seam!(obj)
  @inbounds update_xenergy!(obj)
  @inbounds update_yenergy!(obj)
  @inbounds update_energy!(obj)
  @inbounds compute_cost_to_go!(obj)
  @inbounds compute_seam!(obj)
end

#  e (row                  e[x,y] 
#  dirs:                ↙   ↓   ↘       <--directions naturally live between the rows
#  e (row y+1): e[x-1,y+1] e[x,y+1]  e[x+1,y+1]     
# Basic Comp:   e[x,y] += min( e[x-1,y+1],e[x,y],e[x+1,y])
#               dirs records which one from (1==SW,2==S,3==SE)


# Take an array of energies and work up from bottom to top accumulating least energy to bottom
# function least_energy(e)
#    # initialize dirs 
#    w, h = size(e)
#    dirs = fill(0, w-2, h-1) # w-2 because we don't need the infs, h-1 because arrows between rows
#    # compute
#    for y=h-1:-1:1, x=2:w-1          
#         s, dirs[x-1,y] = findmin(e[x+[-1, 0, 1], y+1]) # findmin gets the min and the index
#         e[x,y] += s   #  add in current energy +  smallest from below
#    end
#    e[2:w-1,1], dirs  # return top row without infinities and dirs
# end

# function get_seam(dirs,x)
#   seam = fill(0,1+size(dirs,2))
#   seam[1]=x
#   for y=1:size(dirs,2)
#     seam[y+1] = seam[y] + dirs[seam[y],y] - 2
#   end
#   seam
# end

# using Colors
# #Mark a seam
# function mark_seam(img, seam, color=RGB4{U8}(1,1,1))
#     img2 = copy(img)
#     for y=1:length(seam)
#         img2[seam[y], y]=color
#     end
#     img2
# end

# function minseam(img)
#   e, dirs = least_energy(energy(brightness(img)))
#   x = indmin(e)
#   seam = get_seam(dirs,x)
# end
    
    
# function carve(img,seam)
#     w, h = size(img)



#     # newdata = Array(ColorTypes.RGB4{FixedPointNumbers.UfixedBase{UInt8,8}}, size(img.data, 2), size(img.data, 1) - 1)
#     # newimg = Image(newdata)
#     newimg = copy(img)
#     newimg.data = newimg.data[1:w-1, :]

#     for y=1:h
#         s=seam[y]
#         newimg[:,y] = img[[1:s-1;s+1:end],y] # delete pixel x=s on row y
#     end
#     newimg
# end
    
# carve(img) = carve(img, minseam(img))  

# function carve(img, n::Int)
#   for i=1:n
#     img2 = carve(img2)
        
#   end
#   img2
# end

function all_carvings(img::Image)
  # A=[img for i=1:1] # set up a vector of images
  A = Array(Image, size(img, 1))
  A[1] = img
  C = CarvableImage(img)
  for i=1:size(img,1)-1
    carve!(C)
    A[i+1] = get_image(C)
    # push!(A, get_image(C))
    # push!(A,carve(A[end]))
  end
  A
end

function save_expected_data()
  if ~isfile("320px-Broadway_tower_edit.jpg")
    run(`wget https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/Broadway_tower_edit.jpg/320px-Broadway_tower_edit.jpg`)
  end
  img = imread("320px-Broadway_tower_edit.jpg")
  A = all_carvings(img)
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
