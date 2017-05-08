# ISN fft implementation

# Consider the following signal
# x = [0  8  4  5  8  4  9  3  7  9  8  4  7  2  0  6];
# y = fft(x)
# y =  [     84.0+0.0im
#   -14.7273-5.77644im
#  -0.221825-10.7782im
#    3.88163+2.30803im
#        1.0-5.0im
#   0.503142+7.3791im
#   -15.7782-4.77817im
#   -17.6575+3.29463im
#        2.0+0.0im
#   -17.6575-3.29463im
#   -15.7782+4.77817im
#   0.503142-7.3791im
#        1.0+5.0im
#    3.88163-2.30803im
#  -0.221825+10.7782im
#   -14.7273+5.77644im
#  ];

@everywhere include( "bit_reversal.jl")

@everywhere function bf(k,N,x_0,x_1)
	Wk0_N =  exp(-im*2*pi* k[1]/N);
	Wk1_N =  exp(-im*2*pi*k[2]/N);
	F_0 = x_0 + Wk0_N*x_1;
	F_1 = x_0 + Wk1_N*x_1;
	return round(F_0,12), round(F_1,12)
end

function test_for_Shared_Mem_NO_RACECONDITIONS(x)
	N = length(x);
	P = nprocs();
	sx =  SharedArray(Float64, (N,2));
	@sync(
	for k=2:P
		@spawnat k (
			begin
				sx[myid(),1] = myid();
				for k=1:100
					sx[myid(),1] =sx[myid(),1] +1; 
				end
			end
			);
	end
	);
	return sx	
end

@everywhere function butterfly(sx,m,index)
	P = nprocs();
	N = length(sx[:,1]);
	k = myid()-1;
	ini_ind = Int((k-1)*N/(P-1) + 1);
	end_ind = Int((k)*N/(P-1));
	#if m==8
	#println("$(sx[ini_ind:end_ind,:]), ini_ind=$ini_ind , end_ind=$end_ind");
	#end
	for lind = ini_ind : 2 : end_ind
		x_0 = complex(sx[lind  , 1] + sx[lind  , 2]*im);
		x_1 = complex(sx[lind+1, 1] + sx[lind+1, 2]*im);
		#println("@ini: x_0= $x_0, x_1=$x_1")
		x_0,x_1 = bf(mod(index[lind:(lind+1)],m),m,x_0,x_1);
		
		sx[lind  ,1] = real(x_0);
		sx[lind  ,2] = imag(x_0);
		sx[lind+1,1] = real(x_1);
		sx[lind+1,2] = imag(x_1);
		#if m==8
		#	println("@bf:  x_0= $x_0, x_1=$x_1, lind = $(lind-1), ind = $(mod(lind-1,m))")
		#end
	end
	#println("$(sx[ini_ind:end_ind,:])");
end

@everywhere function gen_indexes(stage, N, P)	
	ini = 2;
	l = Int64(log2(N));
	orig = zeros(2^(l-2),1);
	dest = zeros(2^(l-2),1);
	Grouplength = 2^(stage-1);
	dist_groups = 2^(stage+1);
	dist_orig_dest = 2^stage -1;
	gl = 0;
	orig[1] = ini;
	dest[1] = orig[1] + dist_orig_dest;
	for k= 2: 2^(l-2)
		gl = gl + 1;
		if (gl == Grouplength)
			gl = 0; 
			orig[k] = ini + dist_groups;
			ini = orig[k];
		else
			orig[k] = orig[k-1] + 2;
		end
		dest[k] = orig[k] + dist_orig_dest;
	end
	#println("orig = $(orig'), dest = $(dest'), stage = $stage")
	return orig, dest
end

@everywhere function swap(a,b)
	temp = a;
	a = b;
	b = temp;
	return a,b;
end

@everywhere function swap_all(orig, dest, sx, index)

	P = nprocs()-1;
	Pid = myid()-1; 
	for k=Pid:P:length(orig)
		indA = Int(orig[k]);
		indB = Int(dest[k]);
		sx[indA,1], sx[indB,1] = swap(sx[indA,1], sx[indB,1]);
		sx[indA,2], sx[indB,2] = swap(sx[indA,2], sx[indB,2]);
		index[indA], index[indB] = swap(index[indA], index[indB]);
	end

end

function isn_fft(x)
	N = length(x);
	sx =  SharedArray(Float64, (N,2));
	index =  SharedArray(Float64, (N,1));
	for i=1:N
		sx[i,1]=x[i];
		index[i]=i-1;
	end
	@sync(
	for k=2:nprocs()
		@spawnat procs()[k] (
			begin
				butterfly(sx,2,index);				
			end
		);
	end
	);
	 for stage = 1: Int(log2(N)-1)
	 		@sync(
	 			for k=2:nprocs()
	 				@spawnat procs()[k] (
	 					begin
	 						P = nprocs()-1;
	 						N = length(sx[:,1])
	 						l = Int64(log2(N));
	 						orig = zeros(2^(l-2),1);
	 						dest = zeros(2^(l-2),1);
	 						orig, dest = gen_indexes(stage, N, P);
							#println("orig = $(orig'), dest = $(dest'), l=$l, stage = $stage")
	 						swap_all(orig,dest,sx,index);
	 					end
	 				);
	 			end
	 		);
	 	@sync(
	 		for k=2:nprocs()
	 			@spawnat procs()[k] (
	 				begin
	 					butterfly(sx,2^(stage+1), index);
	 					#println("orig = $(orig'), dest = $(dest'), l=$l, stage = $stage")
	 					end
	 			);
	 		end
	 	);
	 end
	 
	
	
	#println("at the end\n \tsx = $sx, \t index = $index");
	temp_low =  complex( sx[1:2:end,1] + im*sx[1:2:end,2]);
	temp_high =  complex( sx[2:2:end,1] + im*sx[2:2:end,2]);
	#println(size(reshape(temp_low,(1,length(temp_low)) ) ))
	
	return reshape([temp_low; temp_high],(2*length(temp_low),1) )
end
	
function main()
	
	xlength2=parse(Int64,ARGS[1]);
	x = [0:(2^xlength2-1);]#[0  8  4  5  8  4  9  3  7  9  8  4  7  2  0  6];
	x1 = bitrev(x,Int(log2(length(x))));
	#println("input\n \tx = $x");
	#println("after bit reversal\n \tx = $x1");
	y=isn_fft(x1);
	#println("isn_fft(x)= \n \ty = $y")
end


t = zeros(31,1);
for k=1:31
	tic()
	main();
	t[k]=toq();
end
println("proc= $(nprocs()-1), xsize = $(2^parse(Int64,ARGS[1])), \t\t avg = $(mean(t[2:end])), std = $(std(t[2:end]))")


				# 				 [28.0 + 0.0im
				#                  0.0 + 0.0im
				#                  -2.0 + 2.0im
				#                  0.0 - 8.0im
				#                  23.313708498985 - 11.313708498985im
				#                  0.0 + 0.0im
				#                  6.828427124746 + 3.313708498985im
				#                  -4.0 - 9.656854249492im]



#
# TotalDataSize = length(x)
# NumofProcessors = 4
# localsize = TotalDataSize/NumofProcessors;
#
# for i =1:log2(TotalDataSize)
# 	if (i <= (log2(TotalDataSize)- log2(NumofProcessors) ) )
# 		p = 0
# 		for j=0:2:(localsize-1)
# 			if j!=(2^i)
# 				Rlt[p+1] = RlA[j^(2^i) +1 ];
# 			else
# 				Rlt[p+1] = RlA[(j+1)^(2^i) +1 ];
# 			end
# 			p = p+1;
# 		end
# 		for j=0:2:(localsize-1)
# 			if j!=(2^i)
# 				Rlt[p+1] = butterfly()
#
# 				#Rlt[p+1] = RlA[j^(2^i) +1 ];
# 				#Ilt[p+1] = IlA[j^(2^i) +1 ];
# 			else
# 				#Rlt[p+1] = RlA[(j+1)^(2^i) +1 ];
# 				#Ilt[p+1] = IlA[(j+1)^(2^i) +1 ];
# 			end
# 			p = p+1;
# 		end
# 	else
#
# 	end
# end
