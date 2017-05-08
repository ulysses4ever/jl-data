t = [1971 
1972 
1974 
1978 
1982 
1985 
1989 
1993 
1997 
1999 
2000 
2002 
2003];

N = [2250
2500
5000
29000
120000
275000
1180000
3100000
7500000
24000000
42000000
220000000
410000000];

using Gadfly
function plot_log_fit(t, N, theta)
	xaxis=1970:2005;
	plot(
			 layer(y=log10(N), x=t, Geom.point, Theme(default_color=color("red"))),
			 layer(y=theta[1]+theta[2]*(xaxis-1970), x=xaxis, Geom.line, Theme(default_color=color("blue")))
	 )
end;
