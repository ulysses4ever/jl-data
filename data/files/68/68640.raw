include(Pkg.dir("BismarkSummary","src","bismark-report.jl"))

test_bismark_report1 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report.txt")
test_bismark_report2 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report1.txt")
test_bismark_report3 = joinpath(Pkg.dir(), "BismarkSummary","testdata","bismark_report2.txt")
bismark_report_filenames = [test_bismark_report1,test_bismark_report2,test_bismark_report3]
datasource_path = joinpath(Pkg.dir(), "BismarkSummary","testdata","datasource.tsv")

plots = plot_bismark_summary(bismark_report_filenames,datasource_path,["seq-pairs","map-eff"],["sex"])

hstack(plots...)
