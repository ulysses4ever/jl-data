module train
using DataFrames
using ArgParse

##function export list
#export train

function import_data()
    s = ArgParseSettings()
    @add_arg_table s begin
	"--source", "-s"
	help = "the relative path to the training set. defaults to ../data/train.csv"
	arg_type = String
	default = "../data/train.csv"
    end

    passengers = readtable(s.source)
    (num, len) = size(passengers)
    println("%d passengers", num)
end

end
