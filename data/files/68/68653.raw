# Takes an output name which will be made into a directory
# The dataframe and associated information exported out
# and appropriate plots made
# possibly a web happy report made
# this is then zipped up
#s

include(Pkg.dir("BismarkSummary","src","bismark-report.jl"))
test_bismark_report1 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report.txt")
test_bismark_report2 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report1.txt")
test_bismark_report3 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report2.txt")
bismark_report_filenames = [test_bismark_report1,test_bismark_report2,test_bismark_report3]
sampleinfo_path = joinpath(Pkg.dir(), "BismarkSummary","testdata","datasource.tsv")
outputdir = Pkg.dir("BismarkSummary","testdata","bismarkreport1")
groupby_fields = ["strain"]

make_bismark_summary_report(outputdir, bismark_report_filenames, sampleinfo_path, groupby_fields)
