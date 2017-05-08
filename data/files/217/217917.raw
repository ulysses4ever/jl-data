using Mustache

type Report
    num   :: Int
    name  :: String
    times :: Sample 
    analysis :: SampleAnalysis
    outliers :: Outliers
end

function test(iter)
    n = length(iter)
    out = {}
    for (i, val) in enumerate(iter)
        if i < n
           push!(out, {"x" => val})
        else
           push!(out, {"x" => string(val, "],")})
        end
    end
    out
end

tmpl = Mustache.template_from_file("../templates/report.tpl")
fh = open("testreport.html","w")
render(fh, tmpl, {"name" => "test",
                  "include" => [{"dir" => string("file://",abspath("../templates/")),
				 "css" => readall(abspath("../templates/criterion.css"))}],
		  "report"  => [{"name" => "test",
				 "number" => "1",
				 "times" => test([1:3]),
				 "kdetimes" => test([1:3]),
				 "kdepdf" => test([1:3]),
				 "anMean_estPoint" => 1.0,
				 "anOutlierVar_ovDesc" => "severe",
				 "anOutlierVar_ovFraction" => 0.6,
				 "anMean_estConfidenceLevel" => 0.95,
				 "anMean_estLowerBound" => 0.2,
				 "anMean_estPoint" => 0.25,
				 "anMean_estUpperBound" => 0.3,
				 "stdlb" => 0.01,
				 "stdpt" => 0.02,
				 "stdub" => 0.03}]})
close(fh)
