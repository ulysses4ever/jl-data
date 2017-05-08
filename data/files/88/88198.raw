importall Base;
using JavaCall;
#using Winston;
JavaCall.init(["-verbose:jni", "-verbose:gc","-Djava.class.path=$(joinpath(Pkg.dir(), "View5D\\AllClasses"))"])
#JavaCall.init([" -verbose:jni", " -verbose:gc"," -Djava.class.path=$(joinpath(Pkg.dir(), "View5D\\AllClasses")):$(joinpath(Pkg.dir(), "loci_tools.jar"))"]);
V = @jimport "View5D";

type Img{T} 
	data::Array{T}
	Img(x::Array{T}) = new(x)
end

Img{T}(x::Array{T}) = Img{T}(x);

Img{T}() = Img{T}(rand(T,100,100));

#keyTrans = [ :Int8=> :jbyte, :Int16=> :jshort, :Int32=> :jint, :Float64=> :jdouble];

#for typ in [:Int8,:Int16,:Int32,:Int64,:Float32,:Float64,:Complex64,:Complex128]
#m = quote
	function show{T<:Real}(io::IO, k::Img{T}) 		
		println("real");
		tempData = reshape(k.data,prod(size(k.data)));
		myviewer=jcall(V, "Start5DViewer", JavaObject{:View5D}, (Array{T,1}, jint, jint, jint, jint, jint), tempData, size(k.data,1), size(k.data,2), size(k.data,3), size(k.data,4),size(k.data,5));
	end
	
	function show{T<:Complex}(io::IO, k::Img{T}) 		
		println("complex");
		re = reshape(real(k.data),prod(size(k.data)));
		im = reshape(imag(k.data),prod(size(k.data)));
		tempArray = [re;im];
		myviewer=jcall(V, "Start5DViewerC", JavaObject{:View5D}, (Array{Float32,1}, jint, jint, jint, jint, jint), tempArray, size(k.data,1), size(k.data,2), size(k.data,3), size(k.data,4),size(k.data,5));
	end


a = Img(rand(10,10));


		re = reshape(real(d),prod(size(d)));
		im = reshape(imag(d),prod(size(d)));
		tempArray = [re;im];



function show{T}(io::IO, k::Img{T}) 
	imagesc( k.data )
end



function setindex!{N<:Integer}(a::Img{Array{Float64,N}}, x...)
	#a.data[x,y,z,k,l] = i;
	x
	a.data[x,y,z,k,l] = i;
end
#myArray= rand(64,64,3,2,2)  # this is the 5D Array to display



JavaCall.destroy()
















type Img{T<:Array{Float64}}
  	data::T
  	Img(x::T) = new(x)
  end
  
  Img{T<:Array{Float64}}(x::T) = Img{T}(x);
  
  
  function show{T<:Array{Float64}}(io::IO, k::Img{T}) 
  	#print(io, "coucou\n")
  	#print(io, k.data)
  	#imagesc( k.data )
  	jfloatArr=Array{Float32,1};
  	myJArr=Array(jfloat,prod(size(k.data)));
  	myJArr[:]=k.data[:];
  	myviewer=jcall(V, "Start5DViewer", JavaObject{:View5D}, (jfloatArr, jint, jint, jint, jint, jint), myJArr, size(k.data,1), size(k.data,2), size(k.data,3), size(k.data,4),size(k.data,5));
  end
  

