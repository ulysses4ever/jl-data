using Gadfly;
using LinearLeastSquares;

println("function toeplitz(vect,n) ==>");
println("\tforms the toeplitz matrix as described in section 4.6.4 in textbook");
println("\tn is the size of the vector to convolve with");
println("\tselect the rows you need from this\n");
function toeplitz(vect,n)
	m = size(vect,1);
	T = zeros(m+n-1,n);
	for i in 1:n
		T[i:(i+m-1),i] = vect;
	end
return T
end

println("function plot_inputs(input1, the_rest...) ==>");
println("\tplots up to 3 inputs with color order blue, red, green");
println("\tto plot three call plot_inputs(u1,u2,u3) where u1, u2, u3 are all n-vectors\n");
function plot_inputs(input1, the_rest...)
	vect_size = size(input1,1);
	layers = {layer(y=input1, x=1:vect_size, Geom.line, Theme(default_color=color("blue")))};
	if(size(the_rest,1) > 0)
		append!(layers,layer(y=the_rest[1], x=1:vect_size, Geom.line, Theme(default_color=color("red"))))
	end
	if(size(the_rest,1) > 1)
		append!(layers,layer(y=the_rest[2], x=1:vect_size, Geom.line, Theme(default_color=color("green"))))
	end
	plot(layers...,Guide.XLabel("t"), Guide.YLabel("u"));
end

println("function plot_outputs(y_desired, output1, the_rest...) ==>");
println("\tplots y_desired as black line, and then up to 3 outputs");
println("\te.g. plot_outputs(my_y_desired, o1, o2, o3) where all arguments are 100-vectors\n");
function plot_outputs(y_desired, output1, the_rest...)
	vect_size = size(output1,1);
	layers = {
		layer(y=y_desired, x=1:vect_size, Geom.line, Theme(default_color=color("black"))),
		layer(y=output1, x=1:vect_size, Geom.line, Theme(default_color=color("blue")))
	};
	if(size(the_rest,1) > 0)
		append!(layers,layer(y=the_rest[1], x=1:vect_size, Geom.line, Theme(default_color=color("red"))))
	end
	if(size(the_rest,1) > 1)
		append!(layers,layer(y=the_rest[2], x=1:vect_size, Geom.line, Theme(default_color=color("green"))))
	end
	plot(layers...,Guide.XLabel("t"), Guide.YLabel("y"));
end

println("function plot_trade_off(tracking_cost,regularization_cost) ==>");
println("\tplots tracking_cost against regularization_cost");
println("\texpects arguments are vectors with the same length");
function plot_trade_off(tracking_cost,regularization_cost)
	vect_size = size(tracking_cost,1);
	plot(
		layer(y=regularization_cost, x=tracking_cost, Geom.line, Theme(default_color=color("blue"))),
		layer(y=regularization_cost, x=tracking_cost, Geom.point, Theme(default_color=color("blue"))),
		Guide.XLabel("tracking error"), Guide.YLabel("reg error")
	)
end
