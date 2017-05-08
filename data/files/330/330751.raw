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

function rotField(x,y,posx=0,posy=0)
	x -= posx;
	y -= posy;

	d = sqrt(x*x + y*y);

	if d > 0
		return (-y/d,x/d);
	else
		return (0,0);
	end

end

function test2()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	fun = (x,y) -> rotField(x,y,0.5,0.5);

	(xflow,yflow) = simpleInt(rows,cols,dx,dy,fun);

	plot1PFormRot(rows,cols,xflow,yflow,dx,dy);
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

	(divVecFlowX,divVecFlowY) = computeDivergence(rows,cols,xflow,yflow);

	diffX = xflow - divVecFlowX;
	diffY = yflow - divVecFlowY;

	plot1PFormDiv(rows,cols,diffX,diffY,dx,dy);
end


function test5()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	fun = (x,y) -> rotField(x,y,0.5,0.5);

	(xflow,yflow) = simpleInt(rows,cols,dx,dy,fun);

	(rotVecFlowX,rotVecFlowY) = computeRot(rows,cols,xflow,yflow);

	plot1PFormDiv(rows,cols,rotVecFlowX,rotVecFlowY,dx,dy);
end

function checkDivAndRot(xflow,yflow,d0,d1)
	p1Form = form1PGridToArray(xflow,yflow);

	# compute divergence
	div = d1 * p1Form;

	# compute rotation
	rot = (d0') * p1Form;

	return (norm(div,2),norm(rot,2));
end

function test6()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	d0 = getD0(rows,cols);
	d1 = getD1(rows,cols);

	# generate random vector field
	(xflow,yflow) = simpleInt(rows,cols,dx,dy,(x,y)->(rand(),rand()));

	# apply helmholz decomposition
	(divVecFlowX,divVecFlowY,rotVecFlowX,rotVecFlowY,hFlowX,hFlowY) = helmholzDecomposition(rows,cols,xflow,yflow);

	# check result
	(div,rot) = checkDivAndRot(divVecFlowX,divVecFlowY,d0,d1);
	println("Divergence : Div=",div," Rot=",rot);

	(div,rot) = checkDivAndRot(rotVecFlowX,rotVecFlowY,d0,d1);
	println("Rotation : Div=",div," Rot=",rot);

	(div,rot) = checkDivAndRot(hFlowX,hFlowY,d0,d1);
	println("Harmonic : Div=",div," Rot=",rot);

	plot1PForm(rows,cols,hFlowX,hFlowY,dx,dy);
end


function test7()
	rows = 32;
	cols = 32;

	dx = 1.0 / rows;
	dy = 1.0 / cols;

	#fun = (x,y) -> rotField(x,y,0.5,0.5);
	fun = (x,y) -> (1,0);

	(xflow,yflow) = simpleInt(rows,cols,dx,dy,fun);

	plotHelmholzDecomposition(rows,cols,dx,dy,xflow,yflow);
end