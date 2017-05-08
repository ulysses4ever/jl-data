using Base.LinAlg.BLAS
using ArrayViews
using WAV
function performIACC()
files=readdir("./")
  for fileIterate=1:length(files)
    if contains(files[fileIterate],".wav")
      println(files[fileIterate]);
      fille=wavread(files[fileIterate]);
      fille=fille[1];
      iac = iacc(fille[:,1],fille[:,2],44100)
      writedlm("../files/"*files[fileIterate][1:end-3]*"iacc",iac);
    end
  end
end

function iacc{T<:Number}(leftChannel::AbstractVector{T},rightChannel::AbstractVector{T},ω::Int)
	@assert size(leftChannel,1)==size(rightChannel,1)
	sampleLength=size(leftChannel,1);
	korrN=zero(Float32);
	amp1N=zero(Float32);
	amp2N=zero(Float32);
	max=zero(Float32);
	tempKo =  zeros(Float32,sampleLength);
	#=iaccResult=zeros(Float32,sampleLength);=#
	korr = zeros(Float32,sampleLength);
	ampLeft = zeros(Float32,sampleLength);
	ampRight = zeros(Float32,sampleLength);
	windowSiSmall = div(ω,1000)*2; # small windwow ± 1ms
	windowSize = int(windowSiSmall*80); #window-size for the integration window: 80 ms
	windowSizeHalf = div(windowSize,2);
	for i=1:sampleLength
		ampLeft[i] = leftChannel[i]*leftChannel[i];
		ampRight[i] = rightChannel[i]*rightChannel[i];
	end	
	korrS=zeros(Float32,windowSiSmall*2);
##### Old version with averaged short window integration
	#=for i =div(windowSize,2):sampleLenght-div(windowSize,2)=#
			#=korrN=0;=#
			#=amp1N=0;=#
			#=amp2N=0;=#
			#=for  t=-div(windowSize,2):div(windowSize,2)=#
				#=korrN+= korr[i+t];=#
				#=amp1N+= ampLeft[i+t];=#
				#=amp2N+= ampRight[i+t];=#
			#=end=#
			#=tempKo[i]= korrN/sqrt(amp1N*amp2N);=#
	#=end=#

	#=for i =div(windowSize,2):sampleLenght-div(windowSize,2)=#
		#=max = -1;=#
		#=for  j = -div(windowSiSmall,2): div(windowSiSmall,2)=#
			#=if tempKo[i+j]>max=#
				#=max = tempKo[i+j];=#
			#=end=#
		#=iaccResults[i]=max;=#
		#=end	=#
	#=return iaccResults;=#
#=end=#
#######################################################

######New version with "correct" short window integration
for i=windowSizeHalf+windowSiSmall:div(windowSiSmall,2):sampleLength-windowSizeHalf-windowSiSmall-1
 	fill!(korrS,0.0)
	#=korrS=zeros(Float32,windowSiSmall*2);=#
  for τ= -windowSiSmall:windowSiSmall	-1,  t=-windowSizeHalf+1:windowSizeHalf
			korrS[τ+windowSiSmall+1]+=leftChannel[i+t]*rightChannel[i+t+τ]
	end
	amp1N=sum(view(ampLeft,i-windowSizeHalf-windowSiSmall+1:i+windowSizeHalf+windowSiSmall));
	amp2N=sum(view(ampRight,i-windowSizeHalf-windowSiSmall+1:i+windowSizeHalf+windowSiSmall));
	#=for ff=0:windowSiSmall-1=#
   #=tempKo[i+ff]=maximum(korrS)./sqrt(amp1N*amp2N);=#
	#=end=#
	fill!(view(tempKo,i:i+windowSiSmall),maximum(korrS)./sqrt(amp1N*amp2N));
end
return tempKo;
end
