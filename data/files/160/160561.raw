function plot_wignerfunction(matrix)
	s1 = MSession()
	put_variable(s1, :wigner, matrix)
	put_variable(s1, :wignerSamples, convert(FloatingPoint,wignerSamples))
	eval_string(s1,"figure;surf(((1:wignerSamples)-wignerSamples/2)/10,((1:wignerSamples)-wignerSamples/2)/10,wigner,'EdgeColor', 'None', 'facecolor', 'interp');view(2);axis equal;caxis([-0.6366 0.6366]);colorbar;")
	eval_string(s1,"load('wignerColor','wignerColor');colormap(wignerColor);")
end