__precompile__()
module ScatterMatrixPlots

# package code goes here
using Gadfly, Compose, DataFrames
export ScatterMatrixPlot,ScatterMatrix,open_imagefile

function ScatterMatrix(olddf, colorido=[], legenda=true)
    df = olddf[complete_cases(olddf),:]
    n = size(df, 2)
    nomes = names(df)
    if colorido!=[]
        n = n-1
        splice!(nomes,findfirst(x -> string(x) == colorido, nomes))
    end
    M = Array(Compose.Context, (n,n))

    for (i,indexi) in zip(nomes,1:length(nomes))
        nowcor = false
        for (j,indexj) in zip(nomes,1:length(nomes))
            gdplot = Geom.point
            xTickMarks=yTickMarks=false
            xName=yName=""
            kps=:none
            if j == nomes[1]
                yName=string(i)
                yTickMarks=true
            end
            if i == nomes[end]
                xName=string(j)
                xTickMarks=true
            end
            if nowcor#Cor Info
                index1 = complete_cases(df[:,[i,j]])
                text0 = "Corr: "*string(trunc(cor(df[index1,i],df[index1,j]),4))
                M[indexi,indexj] = compose(context(),
                (context(), text(0.5, 0.5, text0, hcenter)),
                (context(0.1w, 0.1h, 0.8w, 0.8h), rectangle(), fill("white"), stroke("black")))#))
            elseif i == j #histogram
                gdplot = Geom.histogram
                if legenda
                    kps=:right
                end
                M[indexi,indexj] = render(plot(df, x=string(j), y=string(i), color=colorido, gdplot(maxbincount=20),
                Guide.xlabel(xName), Guide.ylabel(yName), Guide.xticks(label=xTickMarks), Guide.yticks(label=yTickMarks), 
                Theme(grid_line_width=1pt, panel_stroke=colorant"black", key_position=kps)))
                nowcor=true
            else #scatterplots
		kps=:none
                M[indexi,indexj] = render(plot(df, x=string(j), y=string(i), color=colorido, gdplot,
                Guide.xlabel(xName), Guide.ylabel(yName), Guide.xticks(label=xTickMarks), Guide.yticks(label=yTickMarks), 
                Theme(panel_stroke=colorant"black", key_position=kps)))
            end
        end
    end
    return gridstack(M)
end

function open_imagefile(filename)
    if OS_NAME == :Darwin
        run(`open $(filename)`)
    elseif OS_NAME == :Linux || OS_NAME == :FreeBSD
        run(`xdg-open $(filename)`)
    elseif OS_NAME == :Windows
        run(`$(ENV["COMSPEC"]) /c start $(filename)`)
    else
        warn("Showing plots is not supported on OS $(string(OS_NAME))")
    end
end


function ScatterMatrixPlot(olddf, colorido=[],filepath::AbstractString="scattermatrix",mime::AbstractString="svg",xwidth=15cm,ywidth=15cm,legenda::Bool=true)
    pl=ScatterMatrix(olddf, colorido, legenda)

    if( (mime=="svg"||mime=="SVG")==true)
        image=draw(SVG(filepath, xwidth, ywidth), pl)
    elseif ( (mime=="png"||mime=="PMG")==true)
            image=draw(PNG(filepath, xwidth, ywidth), pl)
    else
            image=draw(SVG(filepath, xwidth, ywidth), pl)
    end

    open_imagefile(filepath)

end

end # module
