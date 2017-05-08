using Images, Color, FixedPointNumbers, ImageView
using DataFrames, LsqFit, Winston

dir = "C:\\Users\\Alex\\Dropbox\\College\\Research\\Shock tube"
workdir = dir*"\\3-11-15\\"
cd(workdir)
names = readcsv(workdir*"img_basenames.csv", ASCIIString)

function imgavg{s<:String}(rootdir::s, imgdir::s,
                           imgbasename::s, range, num_id_len, ext::s,
                           xrange::Range, yrange::Range)
  img1name = imgbasename*lpad("$(range[1])", num_id_len, "0")*ext
  img1 = subim(imread(joinpath(rootdir,imgdir,img1name)), "x", xrange, "y", yrange)
  t = Gray{Float64}
  imgout = map(MapNone(t),zeros(img1))#map(MapNone(t), img1)
  xpx, ypx = size(img1)
  for img_num = range
    imgname = imgbasename*lpad("$(range[1])", num_id_len, "0")*ext
    img = subim(imread(joinpath(rootdir,imgdir,imgname)), "x", xrange, "y", yrange)
    imgout += map(MapNone(t), img)
  end
  imgout /= length(range)
  map(MapNone(typeof(img1[1,1])), imgout)
end

function bgsub(img, bgimg)
  imgout = similar(img)
  imzero = zero(typeof(img[1,1]))
  npx, npy = size(img)
  for j in 1:npy
    for i in 1:npx
      diff = img[i,j] - bgimg[i,j]
      imgout[i,j] = diff > imzero ? diff : imzero
    end
  end
  return imgout
end

function fluor_test(rootdir, imgdir, bgdir, outdir, ext,
                    imgbasenames, range, num_id_len,
                    bgbasename, bgrange, bg_num_id_len)
  n_imgs = length(imgbasenames)

  xrange = 525:670
  yrange = 1:450
  xbox = 80:135
  ybox = 230:270
  xboxdim = 8.78  # mm

  bgavg = imgavg(rootdir, bgdir, bgbasename, bgrange, bg_num_id_len, ext)
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
    img = imgavg(rootdir, imgdir, imgbasename, range, num_id_len, ext, xrange, yrange)
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
    p = FramedPlot(xlabel = "Relative x-location",
                   ylabel = "Background-subtracted intensity\n(counts per second)")
    points = Points(xdata, scalefac*ydatavec)
    fitvals = model(xdata, fit.param)
    fitline = Curve(xdata, scalefac*fitvals)
    add(p, points, fitline)
    savefig(p, joinpath(rootdir, outdir, imgbasename*"fit.svg"))
  end

  # Convert from fixed-point 16-bit representation to integer counts per second
  bgmean = convert(Int64, round(bgmean*scalefac))
  imgmean = convert(Array{Int64,1}, round(imgmean*scalefac))
  bgsubmean = convert(Array{Int64,1}, round(bgsubmean*scalefac))
  bgsubmax = convert(Array{Int64,1}, round(bgsubmax*scalefac))
  bgsub_curvefit_max = convert(Array{Int64,1}, round(bgsub_curvefit_max*scalefac))
  bgsub_curvefit_eps = convert(Array{Int64,1}, round(bgsub_curvefit_eps*scalefac))

  df = DataFrame(Img_Names = imgbasenames[:], I_B = fill(bgmean,n_imgs)[:],
                 I_S = imgmean[:], I_BS = bgsubmean[:],
                 Imax_rel = bgsubmax[:], Imax_rel_fit = bgsub_curvefit_max[:],
                 I_decay = bgsub_curvefit_eps[:])
  writetable(joinpath(rootdir, outdir, "Intensity_data.csv"), df)
  return df
end

@time fluor_test(workdir, "signal", "back", "bgsub", ".tif",
           names, 0:9, 4,
           "back_2_", 0:9, 4)



testim = subim(imread(workdir*"back\\back_2_0000.tif"), "x",525:670, "y", 1:450)
view(testim)
testim2 = imfilter_gaussian(testim, [1, 1])
testim3 = map(MapNone(typeof(testim[1,1])), testim2)

