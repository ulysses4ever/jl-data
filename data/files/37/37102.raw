include("ADforward.jl")
Pkg.add("Gadfly")
using Gadfly;
f(x)=6*cos(x);
df=ADforward(f);
ddf=ADforward(df);
##show f ,df,ddf
plot1=plot(
  layer(
    #First layer
    f,0,2*pi,
    Theme(
      default_color=color("red"),
      line_width=3pt
      )
    ),
    layer(
    #Second layer
    df,0,2*pi,
    Theme(
      default_color=color("blue"),
      line_width=3pt,
      )
    ),
    layer(
    #Third layer
    ddf,0,2*pi,
    Theme(
      default_color=color("Green"),
      line_width=3pt
      )
    ),
  #background
  Theme(
    panel_fill=color("#FFFF00"),
    panel_opacity=0.1,
    panel_stroke=color("Black"),
    ),
  Guide.ylabel("y"),
  Guide.xlabel("x"),
  Guide.title("f(x) , f'(x) and f''(x)"),
  );
