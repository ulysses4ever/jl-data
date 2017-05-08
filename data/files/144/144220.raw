# Coefficienten-berekening door Shen & Liu


function g(k, a)
	pow0(k+1, 2-a) - pow0(k, 2-a)
end


function w_LS(i, j, a, dx)
	if j == 1
		if i == 1
			ww = -1;
		elseif i == 2
			ww = 1-g(1, a);
		else
			ww = g(i-2, a) - g(i-1, a)
		end
	else
		if j <= i-2
			ww = g(i-j-1, a) - 2 * g(i - j, a) + g(i-j+1, a)
		elseif j == i - 1
			ww = 1 - 2*g(1, a) + g(2, a)
		elseif j == i
			ww = g(1, a) - 2
		elseif j == i + 1
			ww = 1
		end
	end
	ww = ww / (gamma(3-a)*dx^a);
	ww
end

function berekenW_LS(n, a, dx)
	W = zeros(n-1, n-1);
	for i = 1:n-1
		for j = 1:min(i+1, n-1)
			W[i, j] = w_LS(i, j, a, dx);
		end
    end
	W[n-1, n-1] = (g(1.0, a) - 1) / (gamma(3-a)*dx^a);
	W
end
