# performance check

@debug let

maxit = 10;
A_gridsize=100;
H_gridsize = 100;
S_gridsize = 100;

tic()
a = 0;
for i = 1 : maxit

	for i_A = 1 : A_gridsize
		for i_H = 1 : H_gridsize
			for i_S = 1 : S_gridsize
				b = a;
				a = randn(1) + b;

			end
		end
	end

	print(".")
	if mod(i,100)==0
		println("")
	end    


end

toc()

end