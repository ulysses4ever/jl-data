function ScatterMatrixPlot(olddf::DataFrame;colorido=[],filepath::AbstractString="scattermatrix",mime::AbstractString="svg",xwidth=0cm,ywidth=0cm,legenda::Bool=false)
  pl1=ScatterMatrix1(olddf, colorido, legenda)
  pl2=ScatterMatrix2(olddf, colorido, legenda)
  
  filepath1=string(filepath,"_1")
  filepath2=string(filepath,"_2")
  
   if(xwidth==0cm)
	xwidth=((size(olddf)[2]+1)*5)cm
   end
   if(ywidth==0cm)
	ywidth=((size(olddf)[2]+1)*5)cm
   end

    if( (mime=="svg"||mime=="SVG")==true)
        filepath1=string(filepath1,".svg")
        filepath2=string(filepath2,".svg")
        
        image1=draw(SVG(filepath1, xwidth, ywidth), pl1)
        image2=draw(SVG(filepath2, xwidth, ywidth), pl2)
    elseif ( (mime=="png"||mime=="PNG")==true)
        filepath1=string(filepath1,".png")
        filepath2=string(filepath2,".png")

        image1=draw(PNG(filepath1, xwidth, ywidth), pl1)
        image2=draw(PNG(filepath2, xwidth, ywidth), pl2)
    else
        filepath1=string(filepath1,".svg")
        filepath2=string(filepath2,".svg")

        image1=draw(SVG(filepath1, xwidth, ywidth), pl1)
        image2=draw(SVG(filepath2, xwidth, ywidth), pl2)
    end

    open_imagefile(filepath1)
    open_imagefile(filepath2)


end 
