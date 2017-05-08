function ScatterMatrix2(olddf::DataFrame, colorido=[], legenda::Bool=true)
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
