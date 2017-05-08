cd(splitdir(@__FILE__)[1])
pwd()
include("improcess.jl")

const im_folders = ("3-11-15", "3-23-15", "3-25-15")

function run_improc(folder_list)
  i = 0
  result_array = fluor_test(setdir(folder_list[1]),
                            "signal", "back", "bgsub", ".tif",
                            0:9, 4, 0:9, 4)
  for subfolder in folder_list[2:end]
    result_array = vcat(result_array,
                        fluor_test(setdir(subfolder),
                                   "signal", "back", "bgsub", ".tif",
                                   0:9, 4, 0:9, 4))
  end
  return [["Image names" "I_B" "I_S" "I_BS" "I_max, rel" "I_max, rel fit" "I_decay"];
          result_array]
end


cd(splitdir(@__FILE__)[1])
pwd()

results = run_improc(im_folders)
writecsv(pwd()*"\\results.csv",results)

