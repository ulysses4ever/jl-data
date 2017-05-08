cd(splitdir(@__FILE__)[1])
const topdir = pwd()
include("improcess.jl")

const im_folders = ("3-11-15", "3-23-15", "3-25-15", "tergitol")

function run_improc(folder_list)
  #i = 0
  result_array = fluor_test(setdir(folder_list[1]),
                            "signal", "back", "bgsub", ".tif",
                            0:9, 4, 0:9, 4)
  for subfolder in folder_list[2:end]
    result_array = vcat(result_array,
                        fluor_test(setdir(subfolder),
                                   "signal", "back", "bgsub", ".tif",
                                   0:9, 4, 0:9, 4))
  end
  Imax_idx = indmax(result_array[:,5])
  I_max = maximum(imread(topdir*"\\gfx\\unscaled\\$(result_array[Imax_idx,1]).tif"))
  i = 0
  for imgname in result_array[:,1]
    i += 1
    img = imread(topdir*"\\gfx\\unscaled\\$(imgname).tif")
    I_max_img = maximum(img)
    println(I_max_img)
    imwrite(img/I_max_img, topdir*"\\gfx\\autoscaled\\$(imgname)autosc.tif",
            mapi=mapinfo(Clamp,img))
    imwrite(img/I_max,topdir*"\\gfx\\maxscaled\\$(imgname)maxsc.tif",
            mapi=mapinfo(Clamp,img))
  end

  return [["Image names" "I_B" "I_S" "I_BS" "I_max, rel" "I_max, rel fit" "I_decay"];
          result_array]
end



results = run_improc(im_folders)
cd(splitdir(@__FILE__)[1])
writecsv(pwd()*"\\results.csv",results)
