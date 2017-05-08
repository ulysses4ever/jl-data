using Gadfly
using Compose

include("lib/functions.jl")

f1 = 13
f2 = 59
A1 = 100
A2 = 10

function pimarker(x)
    multiple = x/pi
    r = rationalize(multiple)
    n = string(r.num == 0 ? string("0") :
               string(r.num == 1 ? "" : r.num, "π"))
    s = string(n, r.den == 1 ? "" : string("/", r.den))
    return s
end

using Color
theme = Theme(
              major_label_font_size=7pt
              )

x = 2pi*[0:0.00005:1]
plt(y, title, args...) = plot(x=x, y=y,
                              Geom.line, args..., Scale.x_continuous(format=pimarker),
                              Guide.title(string(title, sum(extrema(y)), " peaks")), theme);

y1 = A1 * sin(x*f1);
y2 = A2 * sin(x*f2);

col1 = vstack(
              plt(y1, string("A=", A1, " f=", f1, "Hz, "), Guide.xlabel(nothing), Guide.ylabel(nothing) ),
              plt(y2, string("A=", A2, " f=", f2, "Hz, "), Guide.xlabel(nothing), Guide.ylabel(nothing)),
              plt(y1+y2, string("superimposed, "),  Guide.xlabel(nothing), Guide.ylabel(nothing))
              );
              
y3 = A2 * sin(x*f1);
y4 = A1 * sin(x*f2);

col2 = vstack(
              plt(y3, string("A=", A2, " f=", f1, "Hz, "), Guide.xlabel(nothing), Guide.ylabel(nothing)),
              plt(y4, string("A=", A1, " f=", f2, "Hz, "), Guide.xlabel(nothing), Guide.ylabel(nothing)),
              plt(y3+y4, string("superimposed, "), Guide.xlabel(nothing), Guide.ylabel(nothing))
              );

figure = hstack(col1, col2);
draw(PS("results/simulation.ps",   4inch, 4inch), figure);
draw(PDF("results/simulation.pdf", 4inch, 4inch), figure);
draw(PNG("results/simulation.png", 4inch, 4inch), figure);
