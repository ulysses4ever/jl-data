#= Note: if packages have not yet been installed, uncomment & execute:
for pkg in ("Images", "Color", "FixedPointNumbers", "ImageView", "LsqFit", "Winston")
  Pkg.add(pkg)
end
=#
using ProgressMeter
# Import image processing routines
using Images, Color, FixedPointNumbers, ImageView
# Import curve-fitting and plotting functions
using LsqFit, Winston

#= readbasenames(dir::String, ignore_len::Int)
Inputs:
  dir: the absolute path to a directory which contains one or more sets of .tif
      image files which are differentiated by an iterated index of fixed length
      (e.g. img_001, img_002, ...)
  ignore_len: the length of the iterated index
      (for the above example,ignore_len = 3)
Output:
  A vector of base filenames (for the above example, ["img_"])
=#
function readbasenames(dir, idx_len)
  fnames = readdir(dir) # Read list of files from directory
  # Filter out files without .tif extension from list
  csvnames = filter(fname -> splitext(fname)[2] == ".tif", fnames)
  # Return vector of unique base image names
  return convert(Vector{ASCIIString},
                 unique([csvname[1:end-(4+idx_len)] for csvname in csvnames]))
end

#= set_dir(workdir_str::String)
Inputs:
  workdir_str: the folder name of a subdirectory of the directory
    containing this script.
  The folder should have three subfolders:
    * Background images
    * Signal images
    * An output folder for processed images
  All the images in the folder must have been taken under similar
    lab conditions.
Output:
  The absolute path of the working directory
=#
function setdir(workdir_str)
  dir = splitdir(@__FILE__)[1]
  workdir = joinpath(dir,workdir_str)
  cd(workdir)
  return pwd()
end

# imname_gen generates image filename for an image within an iterated list
function imname_gen(imgbasename, idx, id_len, ext)
  return imgbasename*lpad("$idx", id_len, "0")*ext
end

#= imgavg(...)
Averages a set of images with a common base name and an iterated fixed-length
  index, returning a subimage of the region of interest
Input examples given for a folder containing
  img0001.tif, img0002.tif, img0003.tif
Inputs:
  imgdir: absolute path to directory containing images to be averaged
  imgbasename: e.g. "img"
  range: <minimum index>:<maximum index>, e.g. 1:3
  num_id_len: length of fixed-length index, e.g. 4
  ext: image extension, e.g. ".tif"
  xrange, yrange: horizontal and vertical ranges of pixels for region of
    interest (ROI)
=#
function imgavg(imgdir, imgbasename, range, num_id_len, ext,
                           xrange::Range, yrange::Range)
  println(num_id_len)
  img1name = imname_gen(imgbasename, range[1], num_id_len, ext)
  # Load subimage of ROI
  img1 = subim(imread(joinpath(rootdir,imgdir,img1name)), "x", xrange, "y", yrange)
  t = Gray{Float64} # Define type: grayscale double to prevent overflow when
                    # performing arithmetic on image sets
  imgout = map(MapNone(t),zeros(img1)) #
  xpx, ypx = size(img1)
  for img_num = range
    imgname = imgbasename*lpad("$(range[1])", num_id_len, "0")*ext
    img = subim(imread(joinpath(rootdir,imgdir,imgname)), "x", xrange, "y", yrange)
    imgout += map(MapNone(t), img)
  end
  imgout /= length(range)
  map(MapNone(typeof(img1[1,1])), imgout)
end

#= bgsub(img, bgimg)
Inputs:
  img, bgimg: two images of identical dimensions & data type
Output:
  A background-subtracted image
=#
function bgsub(img, bgimg)
  imgout = similar(img)
  imzero = zero(typeof(img[1,1]))
  npx, npy = size(img)
  for j in 1:npy
    for i in 1:npx
      diff = img[i,j] - bgimg[i,j]
      # Note: <bool> ? expr_1 : expr2 is shorthand for if <bool> expr1; else expr2.
      imgout[i,j] = diff > imzero ? diff : imzero
    end
  end
  return imgout
end

# Given a data type and image, creates a blank image the same size as img,
# with data type t.
imzeros(t, img) = map(MapNone(t),zeros(img))

#==============================================================================#
#= fluor_test: main test function for fluorescence measurements
Inputs:
  rootdir: absolute path to root directory
  **NOTE**: imgdir, bgdir, outdir must be subdirectories of rootdir.
  imgdir: name of folder containing test images
  bgdir: name of folder containing background images
  outdir: name of folder where processed images are to be output
  range, bgrange: range of image number indices to read
    (e.g. for img001.png ... img005.png, range = 1:5)
  num_id_len, bg_num_id_len: number of characters in fixed-size index
    (for the above example, num_id_len = 3)
Output:
  An array with fluorescence intensity results
=#

function fluor_test(rootdir, imgdir, bgdir, outdir, ext,
                    range, num_id_len, bgrange, bg_num_id_len)
  # Read arrays of signal and background image base names
  imgbasenames = readbasenames(joinpath(rootdir,imgdir), 4)
  bgbasename =   readbasenames(joinpath(rootdir,bgdir),  4)
  n_imgs = length(imgbasenames) # Determine number of signal images collected

  # xrange, yrange: location of cuvette within image
  # xbox, ybox: location of maximum-intensity region within cuvette subimage
  xrange = 5:142#525:670
  yrange = 1:450
  xbox = 100:135
  ybox = 230:270
  xboxdim = 8.78  # mm, width of cuvette window
  bgavg = imgavg(joinpath(rootdir, bgdir),
                 bgbasename, bgrange, bg_num_id_len, ext,
                 xrange, yrange)

  imwrite(bgavg, joinpath(rootdir, outdir, bgbasename*"avg"*ext))
  bgmean = mean(bgavg[xbox, ybox])

  # Initialize output arrays
  imgmean = zeros(typeof(bgmean),n_imgs)
  imgmax = zeros(imgmean)
  I_bar_BS = zeros(imgmean)
  bgsubmean = zeros(imgmean)
  bgsubmax = zeros(imgmean)
  bgsub_curvefit_max = zeros(imgmean)
  bgsub_curvefit_eps = zeros(imgmean)

  scalefac = 2^15 - 1 # For scaling float #s to counts per second

  im_num = 0

  for imgbasename in imgbasenames
    im_num += 1
    img = imgavg(joinpath(rootdir, imgdir),
                          imgbasename, range, num_id_len, ext, xrange, yrange)
    imgmean[im_num] = mean(img[xbox, ybox])
    I_bar_BS[im_num] = imgmean[im_num] - bgmean
    imgmax[im_num] = maximum(img)
    gfilt(image) = imfilter_gaussian(image, [1., 1.])
    bgsubimg = bgsub(gfilt(img), gfilt(bgavg))
    #bgsubimg = imfilter_gaussian(bgsub(img, bgavg), [1., 1.])
    bgsubimg = map(MapNone(typeof(img[1,1])), bgsubimg)
    bgsubmean[im_num] = mean(bgsubimg[xbox, ybox])
    imax, jmax = ind2sub(size(img), indmax(img))
    println("$imgbasename: maximum intensity = $(bgsubmean[im_num]) at [$imax, $jmax]")
    bgsubmax[im_num] = img[imax, jmax]
    imwrite(img, joinpath(rootdir, outdir, imgbasename*"avg"*ext))
    imwrite(bgsubimg, joinpath(rootdir, outdir, imgbasename*"bgsub"*ext))

    # Curve fit exponential model; find max
    model(x, p) = p[1]*exp(x.*p[2])
    ydata = Float64[convert(Float64, img[i,j]) for i = xbox, j = ybox]
    ydatavec = reverse(vec(mean(ydata, 2)))
    xdata = linspace(0, xboxdim, length(ydatavec))
    fit = LsqFit.curve_fit(model, xdata, ydatavec, [0.5, 0.5])
    bgsub_curvefit_max[im_num] = fit.param[1]
    bgsub_curvefit_eps[im_num] = fit.param[2]

    # Plot curve fit
    p = FramedPlot(xlabel = "x-location (mm)",
                   ylabel = "Background-subtracted intensity\n(counts per second)")
    points = Points(xdata, scalefac*ydatavec)
    fitvals = model(xdata, fit.param)
    fitline = Curve(xdata, scalefac*fitvals)
    add(p, points, fitline)
    savefig(p, joinpath(rootdir, outdir, imgbasename*"fit.svg"))
  end

  # Convert from fixed-point 16-bit representation to integer counts per second
  bgmean = convert(Int64, round(bgmean*scalefac))
    for imgstat in [imgmean, bgsubmean, bgsubmax, bgsub_curvefit_max,
                    bgsub_curvefit_eps]
    println("$imgstat: $(typeof(imgstat))")
    println(round(imgstat*scalefac))
      imgstat = convert(Array{Int64,1}, round(imgstat*scalefac))
    end
   #imgmean = convert(Array{Int64,1}, round(imgmean*scalefac))
#   bgsubmean = convert(Array{Int64,1}, round(bgsubmean*scalefac))
#   bgsubmax = convert(Array{Int64,1}, round(bgsubmax*scalefac))
#   bgsub_curvefit_max = convert(Array{Int64,1}, round(bgsub_curvefit_max*scalefac))
#   bgsub_curvefit_eps = convert(Array{Int64,1}, round(bgsub_curvefit_eps*scalefac))
  header_txt = ["Image names" "I_B" "I_S" "I_BS" "I_max, rel" "I_max, rel fit" "I_decay"]

  println(typeof(imgbasenames))

  I_data = hcat(imgbasenames, fill(bgmean,n_imgs), imgmean, bgsubmean,
                  bgsubmax, bgsub_curvefit_max, bgsub_curvefit_eps)
  println(size(imgmean))
    data_table = [header_txt; I_data]
    writecsv(joinpath(rootdir, outdir, "Intensity_data.csv"), data_table)

#   df = DataFrame(Img_Names = imgbasenames[:], I_B = fill(bgmean,n_imgs)[:],
#                  I_S = imgmean[:], I_BS = bgsubmean[:],
#                  Imax_rel = bgsubmax[:], Imax_rel_fit = bgsub_curvefit_max[:],
#                  I_decay = bgsub_curvefit_eps[:])
#   writetable(joinpath(rootdir, outdir, "Intensity_data.csv"), df)
  return data_table #df
end

@time fluor_test(setdir("3-23-15"), "signal", "back", "bgsub", ".tif",
           0:9, 4,
           0:9, 4)


#testim = subim(imread(joinpath(workdir,"back\\back_1_0000.tif")), "x",525:670, "y", 1:450)

#testim2 = imfilter_gaussian(testim, [1, 1])
#testim3 = map(MapNone(typeof(testim[1,1])), testim2)
