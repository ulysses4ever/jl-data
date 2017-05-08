__precompile__()
module ScatterMatrixPlots

# package code goes here
using Gadfly, Compose, DataFrames

import Compose: draw, hstack, vstack, gridstack, isinstalled, parse_colorant, parse_colorant_vec

export ScatterMatrixPlot,ScatterMatrix,open_imagefile

# Re-export some essentials from Compose
export SVGJS, SVG, PGF, PNG, PS, PDF, draw, inch, mm, cm, px, pt, color, @colorant_str, vstack, hstack

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
		if(issubtype(eltype(df[index1,i]),Real)&&issubtype(eltype(df[index1,j]),Real)==true)
	                text0 = "Corr: "*string(trunc(cor(df[index1,i],df[index1,j]),4))
		else
			text0="can not calculation"
		end
                M[indexi,indexj] = compose(context(),
                (context(), text(0.5, 0.5, text0, hcenter)),
                (context(0.1w, 0.1h, 0.8w, 0.8h), rectangle(), fill("white"), stroke("black")))#))
            elseif i == j #histogram
                gdplot = Geom.histogram
                if legenda
                    kps=:right
                end
		if(issubtype(eltype(df[:,i]),String)&&issubtype(eltype(df[:,j]),String)==true)
			text0="can not plot"
			M[indexi,indexj] = compose(context(), (context(), text(0.5, 0.5, text0, hcenter)),
                	(context(0.1w, 0.1h, 0.8w, 0.8h), rectangle(), fill("white"), stroke("black")))#))
		else
       	        	 M[indexi,indexj] = render(plot(df, x=string(j), y=string(i), color=colorido, gdplot(maxbincount=20),
       	         	Guide.xlabel(xName), Guide.ylabel(yName), Guide.xticks(label=xTickMarks), Guide.yticks(label=yTickMarks), 
       	         	Theme(grid_line_width=1pt, panel_stroke=colorant"black", key_position=kps)))
		end
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
    if is_apple()
        run(`open $(filename)`)
    elseif is_linux() || is_bsd()
        run(`xdg-open $(filename)`)
    elseif is_windows()
        run(`$(ENV["COMSPEC"]) /c start $(filename)`)
    else
        warn("Showing plots is not supported on OS $(string(Compat.KERNEL))")
    end
end


function ScatterMatrixPlot(olddf;colorido=[],filepath::AbstractString="scattermatrix",mime::AbstractString="svg",xwidth=0cm,ywidth=0cm,legenda::Bool=false)
    pl=ScatterMatrix(olddf, colorido, legenda)

   if(xwidth==0cm)
	xwidth=(size(olddf)[2]*5.5)cm
   end
   if(ywidth==0cm)
	ywidth=(size(olddf)[2]*5.5)cm
   end

    if( (mime=="svg"||mime=="SVG")==true)
        image=draw(SVG(filepath, xwidth, ywidth), pl)
    elseif ( (mime=="png"||mime=="PNG")==true)
            image=draw(PNG(filepath, xwidth, ywidth), pl)
    else
            image=draw(SVG(filepath, xwidth, ywidth), pl)
    end

    open_imagefile(filepath)

end

end # module
