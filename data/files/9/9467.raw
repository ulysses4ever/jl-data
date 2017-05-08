function ScatterMatrixPlot2(olddf::DataFrame;colorido=[],filepath::AbstractString="scattermatrix",mime::AbstractString="svg",xwidth=0cm,ywidth=0cm,legenda::Bool=false)
  pl=ScatterMatrix2(olddf, colorido, legenda)

   if(xwidth==0cm)
	xwidth=((size(olddf)[2]+1)*5)cm
   end
   if(ywidth==0cm)
	ywidth=((size(olddf)[2]+1)*5)cm
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
