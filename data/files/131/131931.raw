function coords!(xsi, x1, y1, x2, y2, orient, x, incx, y, incy)

    Np = length(xsi)
    s = orient?1.0:-1.0
    idx = 1; idy = 1
    for i = 1:Np
        xx = s * xsi[i] 
        x[idx] = (1-xx)/2 * x1 + (1+xx)/2 * x2
        y[idy] = (1-xx)/2 * y1 + (1+xx)/2 * y2
        idx += incx
        idy += incy
    end

end

function coords(xsi, x1, y1, x2, y2, orient=true)
    Np = length(xsi)
    x = zeros(Np)
    y = zeros(Np)
    coords!(xsi, x1, y1, x2, y2, orient, x, 1, y, 1)

    return x, y
end

coords(s::Segment, xsi, x1, y1, x2, y2, orient=true) = coords(xsi, x1, y1, x2, y2, orient)
coords!(s::Segment, xsi, x1, y1, x2, y2, orient, x, incx, y, incy) = coords!(xsi, x1, y1, x2, y2, orient, x, incx, y, incy)

function normal(x1, y1, x2, y2)

    dx = x2-x1
    dy = y2-y1

    len = hypot(dx, dy)

    return [dy/len, -dx/len]
end

    
normal(s::Segment, x, y) = normal(s.x1, s.y1, s.x2, s.y2)


function coords!(crc::Circle, xsi, x1, y1, x2, y2, orient, x, incx, y, incy)
    Np = length(xsi)
    const PI2 = 2*pi
    xc = crc.xc
    yc = crc.yc
    r = crc.rad
    inside = crc.inside

    xr1 = x1 - xc; yr1 = y1-yc
    xr2 = x2 - xc; yr2 = y2-yc

    th1 = atan2(yr1, xr1)
    th2 = atan2(yr2, xr2)

    if inside
        if th2 < th1
            th2 += PI2
        end
    else
        if th2 > th1
            th2 -= PI2
        end
    end
    
    s = orient?1.0:-1.0

    idx = 1; idy = 1
    for i = 1:Np
        xx = s * xsi[i]
        th = ( (1-xx)*th1 + (1+xx)*th2 ) / 2
        x[idx] = xc + r * cos(th)
        y[idy] = yc + r * sin(th)
        idx += incx
        idy += incy
    end
    
end


function normal(crc::Circle, x, y)

    theta = atan2(y, x)

    s = crc.inside?-1.0:1.0

    return [s*cos(theta), s*sin(theta)]
end

    
function coords(crc::Circle, xsi, x1, y1, x2, y2, orient=true)
    Np = length(xsi)
    x = zeros(Np)
    y = zeros(Np)
    coords!(crc::Circle, xsi, x1, y1, x2, y2, orient, x, 1, y, 1)
    return x,y
end
    


function gordon_hall(x, y, xsi)
    Q = length(xsi)
    Q2 = Q*Q
    vx = zeros(Q,Q)
    vy = zeros(Q,Q)
    ex = zeros(Q,Q)
    ey = zeros(Q,Q)

    x0 = x[1,1]; x1 = x[Q,1]; x2 = x[Q,Q]; x3 = x[1,Q]
    y0 = y[1,1]; y1 = y[Q,1]; y2 = y[Q,Q]; y3 = y[1,Q]

    c = 1
    for j=1:Q, i=1:Q
        xi = xsi[i]
        xj = xsi[j]
	vx[c] = 0.25 * ( (1.0-xi)*(1.0-xj) * x0 + (1.0+xi)*(1.0-xj)*x1 +
		      (1.0+xi)*(1.0+xj)*x2 + (1.0-xi)*(1.0+xj)*x3)
	vy[c] = 0.25 * ( (1.0-xi)*(1.0-xj) * y0 + (1.0+xi)*(1.0-xj)*y1 +
		      (1.0+xi)*(1.0+xj)*y2 + (1.0-xi)*(1.0+xj)*y3);
        c += 1
    end
    c = 1
    for j=1:Q, i=1:Q
        xi = xsi[i]
        xj = xsi[j]
	ex[c] = vx[c] + 0.5*( (1.0-xi)*(x[1,j] - vx[1,j]) +
			     (1.0+xi)*(x[Q,j] - vx[Q,j]) +
			     (1.0-xj)*(x[i,1] - vx[i]) +
			     (1.0+xj)*(x[i,Q] - vx[i,Q]))
	
	ey[c] = vy[c] + 0.5*( (1.0-xi)*(y[1,j] - vy[1,j]) +
			     (1.0+xi)*(y[Q,j] - vy[Q,j]) +
			     (1.0-xj)*(y[i,1] - vy[i]) +
			     (1.0+xj)*(y[i,Q] - vy[i,Q]))
        c += 1
    end

    for i = 1:Q2
        x[i] = ex[i]
        y[i] = ey[i]
    end
end



function node_coords(elem::Quad, xsi, crvs)

    Q = length(xsi)

    x = zeros(Q,Q)
    y = zeros(Q,Q)
    xv = xverts(elem)
    yv = yverts(elem)
    ic = elem.curve
    if ic[1] > 0
        x[:,1], y[:,1] = coords(crvs[ic[1]], xsi, xv[1], yv[1], xv[2], yv[2], true)
    else
        x[:,1], y[:,1] = coords(xsi, xv[1], yv[1], xv[2], yv[2], true)
    end

    if ic[2] > 0
        x[Q,:], y[Q,:] = coords(crvs[ic[2]], xsi, xv[2], yv[2], xv[3], yv[3], true)
    else
        x[Q,:], y[Q,:] = coords(xsi, xv[2], yv[2], xv[3], yv[3], true)
    end

    if ic[3] > 0
        x[:,Q], y[:,Q] = coords(crvs[ic[3]], xsi, xv[3], yv[3], xv[4], yv[4], false)
    else
        x[:,Q], y[:,Q] = coords(xsi, xv[3], yv[3], xv[4], yv[4], false)
    end

    if ic[4] > 0
        x[1,:], y[1,:] = coords(crvs[ic[4]], xsi, xv[4], yv[4], xv[3], yv[3], false)
    else
        x[1,:], y[1,:] = coords(xsi, xv[4], yv[4], xv[1], yv[1], false)
    end
    gordon_hall(Q, x, y, xsi)

    return x, y
end

        