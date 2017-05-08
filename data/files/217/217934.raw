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


# JUnit Output
function junit(reports::Vector{Report})
    
    attr_esc = (esc) -> begin
        if     esc == '\'' "&apos;"
        elseif esc == '"'  "&quot;"
        elseif esc == '<'  "&lt;"
        elseif esc == '>'  "&gt;"
        elseif esc == '&'  "&amp;"
        else string(esc)
        end
    end
   
    esc_html = (str) -> join([attr_esc(c) for c in str], "")
    
    report_out = String[]
    ntests = length(reports)
    header = string("<?xml versions\"1.0\" encoding=\"UTF-8\"?>\n",
                    "<testsuite name=\"Criterion benchmarks\" tests=\"$ntests\">\n")
    push!(report_out, header)  
    for report in reports 
       name = esc_html(report.name)
       time = report.analysis.mean.point
       push!(report_out, "<testcase name=\"$name\" time=\"$time\"/>\n")
   end
   push!(report_out, "</testsuite>\n")
   join(report_out, "")
end


function junit(report::Report)
    junit([report])
end
