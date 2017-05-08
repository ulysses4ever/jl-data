module MathematicaPalette

using Colors: @colorant_str
using Gadfly: Theme, get_stroke_vector
using Measures: pt

export MathematicaRed, MathematicaYellow, MathematicaOrange, MathematicaBrick
export MathematicaLightGreen, MathematicaGreen, MathematicaDarkGreen
export MathematicaLightTeal, MathematicaTeal, MathematicaDarkTeal
export MathematicaLightBlue, MathematicaBlue, MathematicaDarkBlue
export MathematicaLightPurple, MathematicaPurple, MathematicaDarkPurple
export MathematicaBeige, MathematicaTan, MathematicaGrey
export MathematicaRedTheme, MathematicaGreenTheme, MathematicaTealTheme
export MathematicaBlueTheme, MathematicaPurpleTheme

const MathematicaRed = colorant"#e70033"
const MathematicaYellow = colorant"#ffcb00"
const MathematicaOrange = colorant"#ef8200"
const MathematicaBrick = colorant"#c05131"
const MathematicaLightGreen = colorant"#77b800"
const MathematicaGreen = colorant"#003a3d"
const MathematicaDarkGreen = colorant"#00694e"
const MathematicaLightTeal = colorant"#30cdd7"
const MathematicaTeal = colorant"#0098aa"
const MathematicaDarkTeal = colorant"#006784"
const MathematicaLightBlue = colorant"#34b6e4"
const MathematicaBlue = colorant"#0063be"
const MathematicaDarkBlue = colorant"#002e5f"
const MathematicaLightPurple = colorant"#a5a4df"
const MathematicaPurple = colorant"#651f76"
const MathematicaDarkPurple = colorant"#1e0576"
const MathematicaBeige = colorant"#d7d3c8"
const MathematicaTan = colorant"#c7be71"
const MathematicaGrey = colorant"#6c6f70"

const _default_theme = Theme(
  # If the color aesthetic is not mapped to anything, this is the color that
  # is used.
  default_color=MathematicaRed,

  # Default size when the size aesthetic is not mapped.
  default_point_size=3pt,

  # Width of lines in the line geometry.
  line_width=2pt,

  # type of dash style (a Compose.StrokeDash object which takes a vector of sold/missing/solid/missing/...
   # lengths which are applied cyclically)
  line_style=get_stroke_vector(:solid),

  # Background color of the plot.
  panel_fill=MathematicaBeige,

  # Border color of the plot panel.
  panel_stroke=nothing,

  # Opacity of the plot background panel.
  panel_opacity=1.0,

  # Background of the entire plot
  background_color=nothing,

  # Padding around the entire plot
  plot_padding=6pt,

  # Grid line color.
  grid_color=MathematicaGrey,
  grid_strokedash=get_stroke_vector(:solid),

  # Grid lines for focused item.
  grid_color_focused=MathematicaGrey,

  # Width of grid lines
  grid_line_width=0.5pt,

  # Font name, size, and color used for tick labels, entries in keys, etc.
  minor_label_font="'Arial','Liberation Sans',sans-serif",
  minor_label_font_size=8pt,
  minor_label_color=colorant"black",

  # Font name, size and color used for axis labels, key title, etc.
  major_label_font="'Arial','Liberation Sans',sans-serif",
  major_label_font_size=11pt,
  major_label_color=colorant"black",

  # Font name, size and color used for labels on plot elements.
  point_label_font="'Arial','Liberation Sans',sans-serif",
  point_label_font_size=8pt,
  point_label_color=colorant"black",

  # Font name, size and color used for key titles
  key_title_font="'Arial','Liberation Sans',sans-serif",
  key_title_font_size=11pt,
  key_title_color=colorant"black",

  # Font name, size and color used for key entries.
  key_label_font="'Arial','Liberation Sans',sans-serif",
  key_label_font_size=8pt,
  key_label_color=colorant"black",

  # How many gradations to show in a continuous color key.
  key_color_gradations=10,

  # Spacing between bars for Geom.bar.
  bar_spacing=0pt, #-0.05mm?

  # Spacing between boxplots in Geom.boxplot.
  boxplot_spacing=3pt,

  # Length of caps on error bars
  errorbar_cap_length=6pt,

  # Lines are drawn in a slightly different color than fills, e.g. to
  # differentiate histogram bars from error bars.
  #stroke_color=default_stroke_color,

  # Points, etc, are highlighted by stroking in slightly different color. This
  # is the stroke width.
  highlight_width=0.5pt,

  # A function mapping fill color to stoke color for highlights.
  #discrete_highlight_color=default_discrete_highlight_color
  #continuous_highlight_color=default_continuous_highlight_color,

  # A function mapping fill color to a duller background fill color. Used for
  # Geom.ribbon in particular so lines stand out against it.
  #lowlight_color=default_lowlight_color,

  # Opacity of geometry filled with lowlight_color
  lowlight_opacity=0.6,

  # A function mapping base fill color to the color of the median marker in a
  # boxplot.
  #middle_color=default_middle_color,

  # Width of the middle line in a boxplot.
  middle_width=1pt,

  # Horizontal position of the title of color key guides. One of :left,
  # :right, :center.
  guide_title_position=:left,

  # Shape used in color keys for color swatches. Either :square or :circle.
  colorkey_swatch_shape=:circle,

  # One of :left, :right, :top, :bottom, :none determining where color keys
  # and the like should be placed.
  key_position=:right,

  # True if bars in bar plots should be stroked. Stroke color is
  bar_highlight=nothing,

  # Symbol forms used for the shape aesthetic
  #shapes=[circle, square, diamond, cross, xcross, utriangle, dtriangle, star1, star2, hexagon, octagon]

  # Qua?  Something to do with the minimum height of things and clipping...
  rug_size=6pt

  # TODO: This stuff is too incomprehensible to be in theme, I think. Put it
  # somewhere else.

  # Number of annealing iterations.
  #label_placement_iterations=1000,

  # Penalty for a label not being contained within the plot frame.
  #label_out_of_bounds_penalty=10.0,

  # Penalty for making a label hidden to avoid overlaps.
  #label_hidden_penalty=0.5,

  # Probability of proposing a visibility flip during label layout.
  #label_visibility_flip_pr=0.2,

  # Number of columns in key
  #key_max_columns=4

)
const MathematicaRedTheme = _default_theme
const MathematicaGreenTheme = _default_theme
MathematicaGreenTheme.default_color=MathematicaGreen
const MathematicaTealTheme = _default_theme
MathematicaTealTheme.default_color=MathematicaTeal
const MathematicaBlueTheme = _default_theme
MathematicaBlueTheme.default_color=MathematicaBlue
const MathematicaPurpleTheme = _default_theme
MathematicaPurpleTheme.default_color=MathematicaPurple

end # module
