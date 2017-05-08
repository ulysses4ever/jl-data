using Mustache

function test(iter)
    [{"x" => x} for x in iter]
end

tmpl = Mustache.template_from_file("../templates/report.tpl")
fh = open("testreport.html","w")

# numbers need to be indexed by 0
render(fh, tmpl, {"name" => "test",
                  "include" => [{"dir" => string("file://",abspath("../templates/")),
				 "css" => readall(abspath("../templates/criterion.css"))}],
		  "report"  => [{"name" => "test1/test",
				 "number" => 0,
				 "times" => test(abs(randn(1000))),
				 "kdetimes" => test(1:3),
				 "kdepdf" => test(1:3),
				 "anMean_estPoint" => 1.0,
				 "anOutlierVar_ovDesc" => "severe",
				 "anOutlierVar_ovFraction" => 0.6,
				 "anMean_estConfidenceLevel" => 0.95,
				 "anMean_estLowerBound" => 2.2,
				 "anMean_estPoint" => 2.0,
				 "anMean_estUpperBound" => 2.3,
				 "stdlb" => 0.01,
				 "stdpt" => 0.02,
				 "stdub" => 0.03},
				 
				 {"name" => "test/test2",
				 "number" => 1,
				 "times" => test(abs(randn(1000))),
				 "kdetimes" => test(1:3),
				 "kdepdf" => test(1:3),
				 "anMean_estPoint" => 1.0,
				 "anOutlierVar_ovDesc" => "severe",
				 "anOutlierVar_ovFraction" => 0.6,
				 "anMean_estConfidenceLevel" => 0.95,
				 "anMean_estLowerBound" => 2.2,
				 "anMean_estPoint" => 2.25,
				 "anMean_estUpperBound" => 2.3,
				 "stdlb" => 0.01,
				 "stdpt" => 0.02,
				 "stdub" => 0.03},
				 
				 {"name" => "test2/aaa",
				 "number" => 2,
				 "times" => test(abs(randn(1000))),
				 "kdetimes" => test(1:3),
				 "kdepdf" => test(1:3),
				 "anMean_estPoint" => 1.0,
				 "anOutlierVar_ovDesc" => "severe",
				 "anOutlierVar_ovFraction" => 0.6,
				 "anMean_estConfidenceLevel" => 0.95,
				 "anMean_estLowerBound" => 2.2,
				 "anMean_estPoint" => 2.25,
				 "anMean_estUpperBound" => 2.3,
				 "stdlb" => 0.01,
				 "stdpt" => 0.02,
				 "stdub" => 0.03}]})
close(fh)
