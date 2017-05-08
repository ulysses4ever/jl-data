using Gadfly
using Compose
## counts = map(zip(-1:0.5:0.5, -0.5:0.5:1)) do x
##     a, b = x
##     count(v-> a < v && v <= b, diffs[:P])
## end
counts = [0, 16, 21, 11]
histoP = plot(y=counts,
              x=["(-1, -.5]", "(-.5, 0]", "(0, .5]", "(.5, 1]"],
              Geom.bar,
              Theme(major_label_font_size=7pt),
              Guide.ylabel("Number of seizures"),
              Guide.xlabel("(postictal-ictal) / (postictal+ictal)"),
              Guide.title("Change in number of peaks"))
## counts = map(zip(-1:0.5:0.5, -0.5:0.5:1)) do x
##     a, b = x
##     count(v-> a < v && v <= b, diffs[:T])
## end 
counts = [0, 11, 26, 11]
histoT = plot(y=counts,
              x=["(-1, -.5]", "(-.5, 0]", "(0, .5]", "(.5, 1]"],
              Geom.bar,
              Theme(major_label_font_size=7pt),
              Guide.ylabel(nothing),
              Guide.xlabel("(postictal-ictal) / (postictal+ictal)"),
              Guide.title("Change in number of troughs"))


draw(PS("results/offset_histo.ps", 6inch, 3inch), hstack(histoP, histoT))
draw(PDF("results/offset_histo.pdf", 6inch, 3inch), hstack(histoP, histoT))
draw(PNG("results/offset_histo.png", 6inch, 3inch), hstack(histoP, histoT))

