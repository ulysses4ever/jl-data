include("dec.jl")

function computeDivergence(rows,cols,xflow,yflow)
	p1Form = form1PGridToArray(xflow,yflow);

	# create laplace operator
	d1 = getD1(rows,cols);
	L = d1 * d1';
	rhs = d1 * p1Form;

	d0Form = \(L,rhs);
	println("Accuracy: ",norm(L*d0Form-rhs,2) / norm(rhs,2));

	return form1PArrayToGrid(rows,cols,d1' * d0Form);
end

function computeRot(rows,cols,xflow,yflow)
	p1Form = form1PGridToArray(xflow,yflow);

	# create laplace operator
	d0 = getD0(rows,cols);
	L = d0' * d0;
	rhs = (d0') * p1Form;

	p0Form = \(L,rhs);
	println("Accuracy: ",norm(L*p0Form-rhs,2) / norm(rhs,2));

	return form1PArrayToGrid(rows,cols,d0 * p0Form);
end

function helmholzDecomposition(rows,cols,xflow,yflow)
	(divVecFlowX,divVecFlowY) = computeDivergence(rows,cols,xflow,yflow);
	(rotVecFlowX,rotVecFlowY) = computeRot(rows,cols,xflow,yflow);

	hFlowX = xflow - divVecFlowX - rotVecFlowX;
	hFlowY = yflow - divVecFlowY - rotVecFlowY;

	return (divVecFlowX,divVecFlowY,rotVecFlowX,rotVecFlowY,hFlowX,hFlowY);
end

function plotHelmholzDecomposition(rows,cols,dx,dy,xflow,yflow)
	(divVecFlowX,divVecFlowY,rotVecFlowX,rotVecFlowY,hFlowX,hFlowY) = helmholzDecomposition(rows,cols,xflow,yflow);

	(x,y,xvel,yvel) = form1PToVectorField(rows,cols,xflow,yflow,dx,dy);
	(x,y,xDivvel,yDivvel) = form1PToVectorField(rows,cols,divVecFlowX,divVecFlowY,dx,dy);
	(x,y,xRotvel,yRotvel) = form1PToVectorField(rows,cols,rotVecFlowX,rotVecFlowY,dx,dy);
	(x,y,xHvel,yHvel) = form1PToVectorField(rows,cols,hFlowX,hFlowY,dx,dy);

	figure();
	title("Vectorfield");
	quiver(x,y,xvel,yvel);

	figure();
	title("Divergence");
	quiver(x,y,xDivvel,yDivvel);

	figure();
	title("Rotation");
	quiver(x,y,xRotvel,yRotvel);

	figure();
	title("Harmonic");
	quiver(x,y,xHvel,yHvel);

	println("Norm H-Field : ",norm(xHvel,2)+norm(yHvel,2));
end