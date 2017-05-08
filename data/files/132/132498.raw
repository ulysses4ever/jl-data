using Images
export write_grayscale_image, load_grayscale_image

function write_grayscale_image(X, filename::String)
  img = convert(Images.Image, X)
  gray = convert(Images.Image{Images.Gray}, img)
  Images.imwrite(gray, filename)
end

function load_grayscale_image(filename::String)
  img = Images.imread(filename)
  gray = convert(Images.Image{Images.Gray{Float64}}, img)
  gray_mat = convert(Array, gray)
  gray_arr = convert(Array{Float64}, gray_mat)
  return gray_arr
end
