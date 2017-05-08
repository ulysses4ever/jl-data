function form1PGridToArray(xflow,yflow)
	[reshape(xflow',length(xflow));reshape(yflow',length(yflow))];
end

function form1PArrayToGrid(rows,cols,p1Form)
	numXFlows = rows * (cols+1);

	xflow = p1Form[1:numXFlows];
	yflow = p1Form[(numXFlows+1):end];

	xflow = reshape(xflow,(cols+1,rows))';
	yflow = reshape(yflow,(cols,rows+1))';

	return (xflow,yflow);
end

function form1PToVectorField(rows,cols,xflow,yflow,dx,dy)
	xvel = zeros(Float64,(rows,cols));
	yvel = zeros(Float64,(rows,cols));
	x = zeros(Float64,(rows,cols));
	y = zeros(Float64,(rows,cols));

	for r in 1:rows
		for c in 1:cols
			xvel[r,c] = ( xflow[r,c] + xflow[r,c+1] ) / (2.0 * dy);
			yvel[r,c] = ( yflow[r,c] + yflow[r+1,c] ) / (2.0 * dx);

			x[r,c] = (c - 0.5) * dx;
			y[r,c] = (r - 0.5) * dy;
		end
	end

	return (x,y,xvel,yvel);
end

function meshGrid(rows,cols,dx,dy)
	x = zeros(Float64,(rows,cols));
	y = zeros(Float64,(rows,cols));

	for r in 1:rows
		for c in 1:cols
			x[r,c] = (c - 0.5) * dx;
			y[r,c] = (r - 0.5) * dy;
		end
	end

	return (x,y);
end

function plot0PForm(rows,cols,scalar,dx,dy)
	(x,y) = meshGrid(rows+1,cols+1,dx,dy);

	pcolormesh(x,y,scalar);
	colorbar();
end

function plot1PForm(rows,cols,xflow,yflow,dx,dy)
	(x,y,xvel,yvel) = form1PToVectorField(rows,cols,xflow,yflow,dx,dy);
	quiver(x,y,xvel,yvel);
end

function plot2PForm(rows,cols,scalar,dx,dy)
	(x,y) = meshGrid(rows,cols,dx,dy);

	pcolormesh(x,y,scalar / (dx * dy));
	colorbar();
end

function getD0(rows,cols)
	I = Int64[];
	J = Int64[];
	V = Float64[];

	xoffset = (cols+1) * rows;

	# register edges which are Y-axis aligned
	for r in 1:rows
		for c in 1:(cols+1)
			ridx = (r-1) * (cols+1) + c;

			# v0
			push!(I,ridx);
			push!(J, (r-1) * (cols+1) + c );
			push!(V,-1.0);

			# v1
			push!(I,ridx);
			push!(J, r * (cols+1) + c );
			push!(V,+1.0);

		end
	end

	# register edges which are X-axis aligned
	for r in 1:(rows+1)
		for c in 1:cols
			ridx = xoffset + (r-1) * cols + c;

			# v0
			push!(I,ridx);
			push!(J, (r-1) * (cols+1) + c );
			push!(V,-1.0);

			# v1
			push!(I,ridx);
			push!(J, (r-1) * (cols+1) + c + 1 );
			push!(V,+1.0);

		end
	end

	return sparse(I,J,V,(rows+1)*cols + rows*(cols+1),(rows+1)*(cols+1));
end

function getD1(rows,cols)
	I = Int64[];
	J = Int64[];
	V = Float64[];

	xoffset = (cols+1) * rows;

	for r in 1:rows
		for c in 1:cols
			ridx = (r-1) * cols + c;

			# left x-flow
			push!(I,ridx);
			push!(J,(r-1) * (cols+1) + c);
			push!(V,+1.0);
			# right x-flow
			push!(I,ridx);
			push!(J,(r-1) * (cols+1) + c + 1);
			push!(V,-1.0);
			# top y-flow
			push!(I,ridx);
			push!(J,xoffset + (r-1) * cols + c);
			push!(V,-1.0);
			# bottom y-flow
			push!(I,ridx);
			push!(J,xoffset + r * cols + c);
			push!(V,+1.0);

		end
	end

	return sparse(I,J,V,rows*cols,(rows+1)*cols + rows*(cols+1));
end

function getS1(rows,cols,dx,dy)
	xoffset = (cols+1) * rows;
	yoffset = cols * (rows+1);

	s = dx / dy;

	return spdiagm([ones(Float64,xoffset) * s; ones(Float64,yoffset)*2] * (1.0 / s) );
end

function getS1Inv(rows,cols,dx,dy)
	xoffset = (cols+1) * rows;
	yoffset = cols * (rows+1);

	s = dx / dy;

	return spdiagm([ones(Float64,xoffset) * (1.0 / s); ones(Float64,yoffset)*2] * s );
end

function plot1PFormDiv(rows,cols,xflow,yflow,dx,dy)
	p1Form = form1PGridToArray(xflow,yflow);
	d1 = getD1(rows,cols);
	p2Form = d1 * p1Form;
	scalarField = reshape(p2Form,(rows,cols))';

	plot2PForm(rows,cols,scalarField,dx,dy)
end

function plot1PFormRot(rows,cols,xflow,yflow,dx,dy)
	p1Form = form1PGridToArray(xflow,yflow);
	d0 = getD0(rows,cols);
	s1inv = getS1Inv(rows,cols,dx,dy);
	p0Form = (d0') * s1inv * p1Form;

	tmp = zeros(Float64,(rows+1) * (cols+1));
	for r in 1:(rows+1)
		for c in 1:(cols+1)
			tmp[(r-1) * (cols+1) + c] = r;
		end
	end

	scalarField = reshape(p0Form,(cols+1,rows+1))';

	plot0PForm(rows,cols,scalarField,dx,dy)
end