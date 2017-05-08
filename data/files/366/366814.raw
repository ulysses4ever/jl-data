#Plot tools using Gadfly library for Julia

#Pkg.add("Gadfly")
#Pkg.add("DataFrames")
#Pkg.add("Color")

#using Gadfly

"""Matrix plot
Input : M matrix, zeros boolean
Output : plotting of M with colored squares, zeros can be hidden by setting zeros=false"""
function matplot(M;zeros=true,
    col1=Color.RGB(234/255,234/255,246/255), col2=Color.RGB(105/255,165/255,255/255))
    #col1=color("lavender"), col2=color("blue"))
    I,J = size(M)
    if !zeros
        is, js, values = findnz(M)
    else
        is, js, values = repeat([1:I], outer=[J]), repeat([1:J], inner=[I]), vec(M)
    end
    df = DataFrames.DataFrame(i=is-0.5, j=js-0.5, value=values)
    plot(df, x="j", y="i", color="value",
        Coord.cartesian(yflip=true, fixed=true),
        #Scale.color_continuous,
        Scale.ContinuousColorScale(Scale.lab_gradient(col1, col2)),
        Scale.x_continuous, Scale.y_continuous,
        Guide.xticks(ticks=[0,J]), Guide.yticks(ticks=[0,I]),
        Theme(grid_line_width=0mm),
        Geom.rectbin)
end