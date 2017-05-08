importall Base;
using Winston;
using JavaCall;
JavaCall.init(["-verbose:jni", "-verbose:gc","-Djava.class.path=$(joinpath(Pkg.dir(), "View5D\\AllClasses"));$(joinpath(Pkg.dir(), "loci_tools.jar"))"]);

V = @jimport "View5D";

#loci_tools.jar
#=
#type ModInt{n} <: Integer
#	k::Int	
#	ModInt(k) = new(mod(k,n))
#end

#show{n}(io::IO, k::ModInt{n}) = print(io, "$(k.k) mod $n");

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

function setindex!{N<:Integer}(a::Img{Array{Float64,N}}, x...)
	#a.data[x,y,z,k,l] = i;
	x
	a.data[x,y,z,k,l] = i;
end
#myArray= rand(64,64,3,2,2)  # this is the 5D-Array to display




importall Base;
#using Winston;
using JavaCall;
JavaCall.init(["-verbose:jni", "-verbose:gc","-Djava.class.path=$(joinpath(Pkg.dir(), "View5D\\AllClasses"));$(joinpath(Pkg.dir(), "loci_tools.jar"))"]);
include("mjcall.jl");

jChannelFiller     = @jimport "loci.formats.ChannelFiller";
jChannelSeparator  = @jimport "loci.formats.ChannelSeparator";
jIFormatReader  = @jimport "loci.formats.IFormatReader";
jReaderWrapper = @jimport "loci.formats.ReaderWrapper";

myChannelFiller     = jChannelFiller((),);
myIFormatReader	  = convert(jIFormatReader,myChannelFiller);
#myChannelSeparator  = jChannelSeparator((), );
#myChannelSeparator  = jChannelSeparator((jChannelFiller), myChannelFiller);

myChannelSeparator  = jChannelSeparator((jIFormatReader,), myIFormatReader);

getMethod(myChannelSeparator,"setId");

jcall(myChannelSeparator, "setId", Void, (JString,),"cou");
jcall(myChannelSeparator, "setSeries",Void,(jint,),0);

r=jcall(myChannelSeparator, "getIndex", (jint), (jint,jint,jint),1,2,3);




