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
    "anMean_estPoint" => report.analysis.mean.point,
    "anMean_estConfidenceLevel" => report.analysis.mean.confidence_level,
    "anMean_estLowerBound" => report.analysis.mean.lbound,
    "anMean_estUpperBound" => report.analysis.mean.ubound,
    "anOutlierVar_ovDesc" => report.analysis.outlier_variance.effect,
    "anOutlierVar_ovFraction" => report.analysis.outlier_variance.frac,
    "stdlb" => report.analysis.std.lbound,
    "stdpt" => report.analysis.std.point,
    "stdub" => report.analysis.std.ubound}
end

function report(reports::Vector{Report5})
    report_dicts = Dict[]
    for r in reports
	push!(report_dicts, report_to_dict(r))
    end
 
    tmpl = Mustache.template_from_file("../templates/report.tpl")
    fh = open("testreport.html","w")
    Mustache.render(fh, tmpl, {"name" => "test",
                      "include" => [{"dir" => string("file://",abspath("../templates/")),
				     "css" => readall(abspath("../templates/criterion.css"))}],
		  "report" => report_dicts})
    close(fh)
end
