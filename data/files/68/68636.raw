using DataFrames
using Gadfly
# Read the datasource
include(Pkg.dir("BismarkSummary","src","bismark-report.jl"))
#using BismarkSummary

sampleinfo_path = joinpath(Pkg.dir(), "BismarkSummary","testdata","datasource.tsv")
pipeline_name = nothing
run_number = nothing

# Get filenames of bismark reports

test_bismark_report1 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report.txt")
test_bismark_report2 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report1.txt")
test_bismark_report3 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report2.txt")
bismark_report_filenames = [test_bismark_report1,test_bismark_report2,test_bismark_report3]

bismark_report_filenames
sampleinfo = readtable(sampleinfo_path)
report_dict=parse_bismark_reports( bismark_report_filenames)

methods(parse_bismark_reports)

append_report_info_to_sampleinfo!(sampleinfo,report_dict)
report_dict
sampleinfo
Gadfly.plot(sampleinfo,x="sex",y="Mapping efficiency", Geom.boxplot)


