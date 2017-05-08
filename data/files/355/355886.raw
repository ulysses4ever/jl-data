using MatlabCompat, DataFrames, DataFramesMeta, Gadfly
using Color
include("minmaxnorm.jl")

#######################
#  Parameters
#######################
dataTablePath  = "U:\\Data\\150415-Francesca-Hela-Fucci-timelapse_Plate_15\\analysis\\all_timepoints\\csv\\col_8_trackedDataFiltered.csv";
folderPath = "U:\\Data\\150415-Francesca-Hela-Fucci-timelapse_Plate_15\\analysis\\all_timepoints\\plots\\";
figTitle = "aavcfpneo4000"
figFile = "aavcfpneo4000.svg"

dataFrame = readtable(dataTablePath);

minInfected = 0.4;

#######################
#  Normalize Local
#######################

dataFrame = @transform(dataFrame, normalized_mean_Intensity_Virus =  minmaxnorm(:mean_Intensity_Virus));


#######################
#  Group & Filter out non-infected cells defined as max < minInfected
######################

subDF = groupby(dataFrame, :nucleus_ID)
filteredDF = DataFrame(nucleus_ID = UTF8String[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = UTF8String[], site_ID = Int64[], time_Point = Float64[], distances = Float64[], normalized_mean_Intensity_GFP = Float64[], normalized_mean_Intensity_TRITC = Float64[], cell_cycle_score = Float64[], brightness_score = Float64[], normalized_mean_Intensity_Virus = Any[])
for iNuc in 1:length(subDF)
  maxInfection = maximum(subDF[iNuc][:normalized_mean_Intensity_Virus])
  println(maxInfection)
  if  maxInfection >= minInfected
    condition = "$(subDF[iNuc][:nucleus_ID][1])"
    println("condition found for $(condition)")
    selectedData = @where(dataFrame, :nucleus_ID .== condition);
    println("data selected")
    append!(filteredDF, selectedData)
    println("data appended")
  end
end
#######################
#  Plot
#######################

# for i in 1:length(subDF)
#   p = plot(x=subDF[i][:time_Point], y=subDF[i][:cell_cycle_score], color = subDF[i][:normalized_mean_Intensity_Virus], Scale.y_continuous(minvalue=-1, maxvalue=1), Scale.continuous_color(minvalue=0, maxvalue=1), Geom.line)
# end
#draw(SVG("myplot.svg", 4inch, 3inch), myplot)


subDF = groupby(filteredDF, :nucleus_ID)

# initialize the with the first cell
p = plot(
  layer(
    x = subDF[1][:time_Point],
    y = subDF[1][:cell_cycle_score],
    color = subDF[1][:normalized_mean_Intensity_Virus],
    Geom.point,
    Theme (
        default_point_size=2pt
      )
    ),
  layer(
    x = subDF[1][:time_Point],
    y = subDF[1][:cell_cycle_score],
    Geom.line(preserve_order=true),
    Theme(
      line_width=1pt,
      default_color=color("#C4C4C4")
      )
    ),
  Scale.y_continuous(minvalue=-1, maxvalue=1),
  Scale.x_continuous(minvalue=0, maxvalue=45),
  Scale.ContinuousColorScale(p -> RGB(0,p/1.5,p+0.01), minvalue=0, maxvalue=1),
  Guide.xlabel("Days Post Infection"),
  Guide.ylabel("Cell Cycle Score"),
  Guide.title(figTitle),
  Guide.colorkey("Infection"),
  Theme(
     panel_fill=color("#FFFFFF"),
     panel_opacity=0.1,
     panel_stroke=color("#CCCCCC"),
   )
  )
push!(p,  layer(  yintercept=[0],
  Geom.hline(color="orange", size=2pt),))
push!(p,  layer(  yintercept=[1],
  Geom.hline(color="green", size=2pt),))
push!(p,  layer(  yintercept=[-1],
  Geom.hline(color="red", size=2pt),))
# plot all the other cells
for i in 2:length(subDF)
  println("adding layer $(i) lines")
  push!(p,  layer(
            x = subDF[i][:time_Point],
            y = subDF[i][:cell_cycle_score],
            color = subDF[i][:normalized_mean_Intensity_Virus],
            Geom.point,
            Theme (
            default_point_size=2pt
              )
            )
        )
  println("adding layer $(i) points")
  push!(p, layer(
          x = subDF[i][:time_Point],
          y = subDF[i][:cell_cycle_score],
          Geom.line(preserve_order=true),
          Theme(
          line_width=1pt,
          default_color=color("#C4C4C4")
            )
          )
        )
end
draw(SVG(string(folderPath, figFile), 4inch, 3inch), p)
p

