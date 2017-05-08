f = readdlm("output.xyz")


k = size(f)

dt = zeros(0)
dx = zeros(0)

for i in 1:5:k[1]
	H = [f[i+3,2],f[i+3,3],f[i+3,4]]
	O = [f[i+2,2],f[i+2,3],f[i+2,4]]
	md_iter = f[i+1,3]
	d = norm(H-O)
	push!(dx,d)
	push!(dt,md_iter)
	
end

writedlm("tvb",[dt dx],'\t')

using Gadfly

p = plot(x=dt, y=dx,Coord.Cartesian(xmin=0.0,xmax=1000.0),Guide.xlabel("Time (ps)"), Guide.ylabel("Bond length (Angstrom)"),Guide.title("Bond length as a function of time in the canonical ensemble"))
draw(SVG("tvb_pic.svg", 18cm, 9cm), p)
