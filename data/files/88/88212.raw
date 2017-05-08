importall Base;
#using Winston;
using JavaCall;
JavaCall.init(["-verbose:jni", "-verbose:gc","-Djava.class.path=$(joinpath(Pkg.dir(), "View5D\\AllClasses"));$(joinpath(Pkg.dir(), "loci_tools.jar"))"]);
include("mjcall.jl");

name = "resolution_fine.tif";

jChannelFiller		= @jimport "loci.formats.ChannelFiller";
jChannelSeparator		= @jimport "loci.formats.ChannelSeparator";
jIFormatReader		= @jimport "loci.formats.IFormatReader";
jReaderWrapper		= @jimport "loci.formats.ReaderWrapper";
jFormatTools			= @jimport "loci.formats.FormatTools";
jDataTools			= @jimport "loci.common.DataTools";
#jByte				= @jimport "java.lang.Byte";


myChannelFiller     = jChannelFiller((),);
myIFormatReader	  = convert(jIFormatReader,myChannelFiller);
myChannelSeparator  = jChannelSeparator((jIFormatReader,), myIFormatReader);
myReaderWrapper	  = convert(jReaderWrapper,myChannelSeparator);

myFormatTools      = jFormatTools((),);

jcall(myChannelSeparator, "setId", Void, (JString,),name);
nSeries = jcall(myReaderWrapper, "getSeriesCount", (jint), (),);
print("Number of series ",nSeries,"\n");
imageseries = 0;
#for imageseries = 0:nSeries-1
	print(" Reading series ",imageseries,"\n");
	jcall(myChannelSeparator, "setSeries",Void,(jint,),imageseries);
    # Find out info on the image
	sz = [ convert(Int64,jcall(myChannelSeparator, "getSizeX",jint,(),)) , convert(Int64,jcall(myChannelSeparator, "getSizeY",jint,(),))];
	
	imsz = (sz[2],sz[1],convert(Int64,jcall(myChannelSeparator, "getSizeZ",jint,(),)),convert(Int64,jcall(myChannelSeparator, "getSizeC",jint,(),)),convert(Int64,jcall(myChannelSeparator, "getSizeT",jint,(),)));
	pixelType = jcall(myChannelSeparator, "getPixelType",jint,(),);
	bpp = jcall(jFormatTools, "getBytesPerPixel",jint,(jint,),pixelType);	
	fp  = jcall(jFormatTools, "isFloatingPoint",jboolean,(jint,),pixelType);	
	sgn = jcall(jFormatTools, "isSigned",jboolean,(jint,),pixelType);	
	little = jcall(myReaderWrapper, "isLittleEndian",jboolean,(),);
	numImages = jcall(myChannelSeparator, "getImageCount",jint,(),);

   if numImages != prod(imsz[3:end])
      error("Assertion failed: number of planes in the image file not as expected!")
   end
   
   if bpp==1
	    if (sgn==0) 
			cls = Uint8;
		else
			cls = Int8;
		end
   elseif bpp==2
		if (sgn==0) 
			cls = Uint16;
		else
			cls = Int16;
		end
	elseif bpp==4
		if fp
            cls = Float32;
        else
            if (sgn==0) 
				cls = Uint32;
			else
				cls = Int32;
			end
        end
   elseif bpp==8
		if fp
            cls = Float64;
        else
            error("Unexpected number of bytes per pixel");
        end   
   else
        error("Unexpected number of bytes per pixel");
   end
  	  
	#Allocate space and read all image planes
   image = zeros(cls,imsz);
   
   ii = zero(jint);
  # for ii = 0:numImages-1
   #need at least a version of JavaCall of 09 mai 2014
   plane = jcall(myChannelSeparator, "openBytes",Array{jbyte,1},(jint,),ii);
   if(little != 0)
		arr = plane;
   else
		arr = hton(plane);
   end
   reinterpret(cls,arr);
   
   arr = jcall(jDataTools,"makeDataArray2D",JObject,(Array{jbyte,1},jint,jboolean,jboolean,jint),plane,bpp,fp,little,convert(Int32,sz[2]));
	
	
	buf = jcall(jDataTools,"allocate",Array{jbyte,1}, (Array{jint,1},), [4,4,4]);
	
	    byte[] buf =
      DataTools.allocate(w, h, FormatTools.getBytesPerPixel(getPixelType()));
	
	
   plane = r.openBytes(ii);
   arr = loci.common.DataTools.makeDataArray2D(plane,bpp,fp,little,sz(2));
      pos = r.getZCTCoords(ii);
      if ~sgn
         % Unsigned types are cast to signed types in Java...
         %arr = di_signtounsign(arr); %crashes matlab (BR)

         %this does not change the data - no copying of the data
         %but does only work on vectors not arrays!
         %arr = typecast(arr,'uint16');

         %this copies the data
         s = ['image(:,:,pos(1)+1,pos(2)+1,pos(3)+1)=' cls '(arr);'];
         eval(s);
      end
      image(:,:,pos(1)+1,pos(2)+1,pos(3)+1) = arr;
      %fprintf('(%d) %d %d %d\n',ii,pos);
   end

   
   

end


