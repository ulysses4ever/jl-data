function smoothlife()
    nx = 256
    ny = 256
    ra = 14
    ri = ra/3
    b  = 1
    b1 = 0.278
    b2 = 0.365
    d1 = 0.267
    d2 = 0.445
    alphan = 0.028
    alpham = 0.147

    kd = zeros(NY,NX)
    kr = zeros(NY,NX)
    for iy in 1:NY
        for ix in 1:NX
            x = ix - 1 - NX/2
            y = iy - 1 - NY/2
            r = hypot(x,y)
            kd[iy,ix] = 1-func_linear(r, ri, b)
            kr[iy,ix] = func_linear(r, ri, b)*(1-func_linear(r, ra, b))
        end
    end
    kflr = sum(kd)
    kfld = sum(kd)
    krf  = fft2(fftshift(kr))
    kdf  = fft2(fftshift(kd))

    aa = initaa(NY,NX,ra)
	while true
		aaf = fft2(aa)
		nf = aaf.*krf
		mf = aaf.*kdf
		n = real(ifft2(nf))/kflr
		#figure imagesc(n)
		m = real(ifft2(mf))/kfld
		#figure imagesc(m)
		aa = snm (n, m, alphan, alpham, b1, b2, d1, d2)
        #imagesc(aa) colormap(gray) caxis([0 1]) colorbar pause (0.1)
	end
end

function func_linear(x, a, b)
    if x < (a-b)//2
        return 0
    elseif x > (a+b)//2
        return 1
    else
        return (x -1(a+b)//2)/b
end

sigmoid_a(x, a, b) =  1 ./(1+exp(-4(x-a)/b))

sigmoid_b(x, b, eb) = 1 - sigmoid_a(x, b, eb)

sigmoid_ab(x, a, b, ea, eb) = sigmoid(x, a, ea) .* sigmoid(x, b, eb)

function sigmoid_mix (x, y, m, em)
	return x.*(1-sigmoid_a(m, 0.5, em)) + y.*sigmoid_a(m, 0.5, em)
end

function snm(n, m, en, em, b1, b2, d1, d2)
	return sigmoid_ab(n, sigmoid_mix(b1, d1, m, em), sigmoid_mix(b2, d2, m, em), en, en)
end

function splat(aa, ny, nx, ra)
	x = fix(rand()*nx)+1;
	y = fix(rand()*ny)+1;
	c = rand()>0.5;

	for dx in -ra:ra
        for dy in -ra:ra
            ix = x+dx
            iy = y+dy
            if ix>=1 && ix<=nx && iy>=1 && iy<=ny
                aa[iy,ix] = c
            end
        end
	end
    return aa
end
