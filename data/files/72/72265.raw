module ImageSeamReference

using Images

# brightness of a color is the sum of the r,g,b values (stored as float32's)
brightness(c)        =  c.r + c.g + c.b

# brightness of an image bordered with zeros
function brightness(I::Image)
  w, h = size(I)
  b = [brightness(I[x,y]) for x=1:w, y=1:h]
  # borders
  zv = fill(0f0,1,  h)  #  vertical zero 
  zh = fill(0f0,w+2,1)  #  horizontal zero 
  [zh  [zv; b; zv]  zh] 
 end

# the 3x3 stencil for energy
function stencil(b)
      xenergy = b[1,1]+2b[2,1]+b[3,1]-b[1,3]-2b[2,3]-b[3,3]
      yenergy = b[1,1]+2b[1,2]+b[1,3]-b[3,1]-2b[3,2]-b[3,3]
      √(xenergy^2 + yenergy^2)
end
    
# energy of an array of brightness values 
# input: assumed zero borders
# output: left and right set to ∞
function energy(b)
  w, h = size(b)
  e = [Float32(stencil( b[x-1:x+1, y-1:y+1] )) for x=2:w-1,y=2:h-1]
  infcol = fill(Inf32,1,h-2)
  [infcol; e; infcol]
end

#  e (row                  e[x,y] 
#  dirs:                ↙   ↓   ↘       <--directions naturally live between the rows
#  e (row y+1): e[x-1,y+1] e[x,y+1]  e[x+1,y+1]     
# Basic Comp:   e[x,y] += min( e[x-1,y+1],e[x,y],e[x+1,y])
#               dirs records which one from (1==SW,2==S,3==SE)


# Take an array of energies and work up from bottom to top accumulating least energy to bottom
function least_energy(e)
   # initialize dirs 
   w, h = size(e)
   dirs = fill(0, w-2, h-1) # w-2 because we don't need the infs, h-1 because arrows between rows
   # compute
   for y=h-1:-1:1, x=2:w-1          
        s, dirs[x-1,y] = findmin(e[x+[-1, 0, 1], y+1]) # findmin gets the min and the index
        e[x,y] += s   #  add in current energy +  smallest from below
   end
   e[2:w-1,1], dirs  # return top row without infinities and dirs
end

function get_seam(dirs,x)
  seam = fill(0,1+size(dirs,2))
  seam[1]=x
  for y=1:size(dirs,2)
    seam[y+1] = seam[y] + dirs[seam[y],y] - 2
  end
  seam
end

using Colors
#Mark a seam
function mark_seam(img, seam, color=RGB4{U8}(1,1,1))
    img2 = copy(img)
    for y=1:length(seam)
        img2[seam[y], y]=color
    end
    img2
end

function minseam(img)
  e, dirs = least_energy(energy(brightness(img)))
  x = indmin(e)
  seam = get_seam(dirs,x)
end
    
function carve(img,seam)
    w, h = size(img)

    newimg = copy(img)
     newimg.data  = newimg.data[1:w-1,:]         # one pixel less wide
    
   
    
    for y=1:h
        s=seam[y]
        
        newimg[:,y] = img[[1:s-1;s+1:end],y] # delete pixel x=s on row y
    end
    newimg
end
    
carve(img) = carve(img, minseam(img))  

function carve(img, n::Int)
  img2 = copy(img)
  for i=1:n
    img2 = carve(img2)
        
  end
  img2
end

function all_carvings(img)
  println("When we reach $(size(img,1)-1) we have carved the image down to 1 pixel wide:")
  A=[img for i=1:1] # set up a vector of images
  for i=1:size(img,1)-1
    push!(A,carve(A[end]))
    if(rem(i,5)==0) || i==size(img,1)-1 print(i, " ") end
  end
  A
end

function save_expected_data()
  if ~isfile("320px-Broadway_tower_edit.jpg")
    run(`wget https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/Broadway_tower_edit.jpg/320px-Broadway_tower_edit.jpg`)
  end
  img = imread("320px-Broadway_tower_edit.jpg")
  A = generate_all_carvings(img)
  outfile = open("tower_carves.dat", "w")
  serialize(outfile, A)
  close(outfile)
end

end
