import Mustache
import Distributions


type Report
   num::Integer
   name::String
   times::Vector{Float64}
   analysis::SampleAnalysis
   outliers::Outliers
end


function render_iter(s::String, iter)
    [{s => x} for x in iter]
end


function report_to_dict(report::Report5)
   kde_times = Distributions.kde(report.times)
   {"name" => report.name,
    "number" => report.num,
    "times" => render_iter("x", report.times),
    "kdetimes" => render_iter("x", kde_times.x),
    "kdepdf" => render_iter("x", kde_times.density),
    "mean_point" => report.analysis.mean.point,
    "mean_confidence_level" => report.analysis.mean.confidence_level,
    "mean_lbound" => report.analysis.mean.lbound,
    "mean_ubound" => report.analysis.mean.ubound,
    "outlier_effect" => report.analysis.outlier_variance.effect,
    "outlier_fraction" => report.analysis.outlier_variance.frac,
    "std_lbound" => report.analysis.std.lbound,
    "std_point" => report.analysis.std.point,
    "std_ubound" => report.analysis.std.ubound}
end


function read_css(template_dir::String)
    readall(abspath(joinpath(template_dir, "criterion.css")))
end


function report(rfile::String, reports::Vector{Report5})
    report_dicts = {report_to_dict(r) for r in reports}
    tmpl = Mustache.template_from_file("../templates/report.tpl")
    template_dir = abspath("../templates/")
    fh = open(rfile,"w")
    Mustache.render(fh, tmpl, {"name" => "test",
                    "include" => [{"dir" => string("file://", template_dir), 
				   "css" => read_css(template_dir)}],
		    "report" => report_dicts})
    close(fh)
end

function report(rfile::String, r::Report)
    report(rfile, [r])
end

function report(rs::Vector{Report})
    report("criterion.html", rs)
end

function report(r::Report)
    report("criterion.html", [r])
end

