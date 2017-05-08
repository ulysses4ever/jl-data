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

function plot1PForm(rows,cols,xflow,yflow,dx,dy)
	(x,y,xvel,yvel) = form1PToVectorField(rows,cols,xflow,yflow,dx,dy);
	quiver(x,y,xvel,yvel);
end

function plot2PForm(rows,cols,scalar,dx,dy)
	(x,y) = meshGrid(rows,cols,dx,dy);
	pcolormesh(x,y,scalar / (dx * dy));
	colorbar();
end

function getD1(rows,cols)
	res = zeros(Float64,(rows,cols));

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


function plot1PFormDiv(rows,cols,xflow,yflow,dx,dy)
	p1Form = [reshape(xflow',length(xflow));reshape(yflow',length(yflow))];
	d1 = getD1(rows,cols);
	p2Form = d1 * p1Form;
	scalarField = reshape(p2Form,(rows,cols))';

	plot2PForm(rows,cols,scalarField,dx,dy)
end