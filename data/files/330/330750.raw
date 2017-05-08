include("decomposition.jl")

using PyPlot;

function test1()
	rows = 16;
	cols = 32;

	dx = 1.0;
	dy = 1.0;

	xflow = ones(Float64,(rows,cols+1));
	yflow = zeros(Float64,(rows+1,cols));

	plot1PForm(rows,cols,xflow,yflow,dx,dy);
end

function simpleInt(rows,cols,dx,dy,fun)
	xflow = zeros(Float64,(rows,cols+1));
	yflow = zeros(Float64,(rows+1,cols));

	# x-flows
	for r in 1:rows
		for c in 1:(cols+1)
			(u,v) = fun((c-1.0) * dx,(r-0.5) * dy);
			xflow[r,c] = u * dy;
		end
	end

	# y-flows
	for r in 1:(rows+1)
		for c in 1:cols
			(u,v) = fun((c-0.5) * dx,(r-1.0) * dy);
			yflow[r,c] = v * dx;
		end
	end

	return (xflow,yflow);
end

function test2()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	fun = ( (x,y) -> (-y,x) );

	(xflow,yflow) = simpleInt(rows,cols,dx,dy,fun);

	plot1PForm(rows,cols,xflow,yflow,dx,dy);
end

function test3()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	fun = ( (x,y) -> (x * (1.0 + x),0) );

	(xflow,yflow) = simpleInt(rows,cols,dx,dy,fun);

	# plot divergence
	plot1PFormDiv(rows,cols,xflow,yflow,dx,dy);
end


function test4()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	fun = ( (x,y) -> (x * (1.0 + x),0) );

	(xflow,yflow) = simpleInt(rows,cols,dx,dy,fun);

	divVec = computeDivergence(rows,cols,xflow,yflow,dx,dy);

	plot1PFormDiv(rows,cols,xflow,yflow,dx,dy);
end
