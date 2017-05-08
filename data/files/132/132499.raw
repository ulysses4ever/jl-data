using Images
export write_grayscale_image, load_grayscale_image

# saves an image represented as a 2D or 3D array as a grayscale image
# color images are converted to grayscale
function write_grayscale_image(X, filename::String)
  img = convert(Images.Image, X)
  gray = convert(Images.Image{Images.Gray}, img)
  Images.imwrite(gray, filename)
end

# loads an image and converts it to grayscale
# returns an 2d array with each value from 0 (black) to 1 (white)
function load_grayscale_image(filename::String)
  img = Images.imread(filename)
  gray = convert(Images.Image{Images.Gray{Float64}}, img)
  gray_mat = convert(Array, gray)
  gray_arr = convert(Array{Float64}, gray_mat)
  return gray_arr
end
