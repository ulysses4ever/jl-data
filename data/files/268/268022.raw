include("dec.jl")

function computeDivergence(rows,cols,xflow,yflow,dx,dy)
	p1Form = [reshape(xflow',length(xflow));reshape(yflow',length(yflow))];

	# create laplace operator
	d1 = getD1(rows,cols);
	L = d1 * d1';
	rhs = d1 * p1Form;

	d0Form = \(L,rhs);
	println("Accuracy: ",norm(L*d0Form-rhs,2) / norm(rhs,2));

	return d1' * d0Form;
end