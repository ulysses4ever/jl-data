
##
# plot.jl
# Functies waarmee we de resultaten kunnen bijhouden en grafisch kunnen weergeven
##

##
# RS_savePlot
# Sla een tussentijdse oplossing op
##
function RS_savePlot!(result::ResultSet, plotNt_i, u_t)
	
	result.plotSamples[plotNt_i,:] = u_t;
	
	nothing
end

##
# RS_makePlot
# Plot (x, u)
##
function RS_makePlot(result::ResultSet; newfigure=true, selfSimVelocities=false, legendLoc="center right", label_x=L"x", label_y=L"u")
	xs = 0:result.dx:result.BWP.L;

	T = result.T;
	ts = [0, T/8, 2*T/8, 3*T/8, 4*T/8, 5*T/8, 6*T/8, 7*T/8, T];
	labels = map(t -> string(L"t = ", t), ts);
	colours = map(t -> (0, 0.8*(1-t/T), t/T), ts);
	if(result.BWP.analyticSol)
		prepend!(labels, ["Exact"]);
		prepend!(colours, [(1, 0, 0)])
		i_start = 1;
	else
		i_start = 2;
	end

	if(selfSimVelocities == false)
		selfSimVelocities = 0*ts;
	end
	selfSimOffsets = cumsum(selfSimVelocities*T/8);
	
	if(newfigure)
		figure()
	end
	for i = i_start:length(result.plotSamples[:,1])
		plot(xs+selfSimOffsets[i-1], result.plotSamples[i,:]', c=colours[i-i_start+1]);
	end
	
	xlabel(label_x);
	ylabel(label_y);
	legend(labels, loc=legendLoc, fontsize="small", labelspacing = 0.1);
	
	nothing
end
function RS_makePlot(filename::String)
	RS_makePlot(RS_open(filename))
end

##
# RS_makeLogLog
# Plot (x, u) in log-log schaal
##
function RS_makeLogLog(result::ResultSet; newfigure=true, legendLoc="lower left")
	xs = 0:result.dx:result.BWP.L;

	T = result.T;
	ts = [0, T/8, 2*T/8, 3*T/8, 4*T/8, 5*T/8, 6*T/8, 7*T/8, T];
	labels = map(t -> string(L"t = ", t), ts);
	colours = map(t -> (0, 0.8*(1-t/T), t/T), ts);
	
	if(newfigure)
		figure()
	end
	for i = 2:length(result.plotSamples[:,1])
		loglog(xs[2:end], result.plotSamples[i,2:end]', c=colours[i-1]);
	end
	
	#axis([5e-4, 1.5, 5e-8, 1.5]);
	axis([1e-3, 1.0, 1e-7, 1.5]);
    xlabel(L"x");
    ylabel(L"u");
	legend(labels, loc=legendLoc, fontsize="small", labelspacing = 0.1);
	
	nothing
end
function RS_makeLogLog(filename::String)
	RS_makeLogLog(RS_open(filename))
end

##
# RS_saveMesh
# Sla een monster van een tussentijdse oplossing op
##
function RS_saveMesh!(result::ResultSet, t, u, sampleFactor_x)
	
	for i = 0:result.Nx_mesh-1
		result.meshSamples[i+1, t+1] = u[round(sampleFactor_x*i)+1]
	end
	
	nothing
end

##
# RS_makeMesh
# Teken een pattern plot
##
function RS_makeMesh(result::ResultSet)
	xs_mesh = 0:(1/result.Nx_mesh):1
	ts_mesh = 0:(result.T/result.Nt_mesh):result.T
	
	figure()
	pcolormesh(ts_mesh, xs_mesh, result.meshSamples, cmap="bwr", vmin=minimum(result.meshSamples), vmax=maximum(result.meshSamples))
	title(L"Tijdsevolutie van $u$")
	axis([ts_mesh[1], ts_mesh[end], xs_mesh[1], xs_mesh[end]])
	colorbar()
    xlabel("t");
    ylabel("x");
	
	nothing
end
function RS_makeMesh(filename::String)
	RS_makeMesh(RS_open(filename))
end

function RS_makeMesh2(result::ResultSet)
	xs_mesh = 0:(1/result.Nx_mesh):1
	ts_mesh = 0:(result.T/result.Nt_mesh):result.T
	
	figure()
	pcolormesh(xs_mesh, ts_mesh, result.meshSamples', cmap="bwr", vmin=minimum(result.meshSamples), vmax=maximum(result.meshSamples))
	title(L"Tijdsevolutie van $u$")
	axis([xs_mesh[1], xs_mesh[end], ts_mesh[1], ts_mesh[end]])
	colorbar()
    xlabel("x");
    ylabel("t");
	
	nothing
end
function RS_makeMesh2(filename::String)
	RS_makeMesh2(RS_open(filename))
end


##
# W_plotEV
# Plot eigenwaarden van W-matrix
##
function W_plotEV(W)
	ev = eigvals(W)
	scatter(real(ev), imag(ev))
	
	nothing
end

function plotEV(disc::DiscMethode, dt)
	cs = [
		(0.0, 0.0, 1.0), (0.0, 0.5, 1.0), (0.0, 1.0, 1.0), (0.0, 1.0, 0.5),
		(0.0, 1.0, 0.0), (0.5, 1.0, 0.0), (1.0, 1.0, 0.0), (1.0, 0.5, 0.0),
		(1.0, 0.0, 0.0), (1.0, 0.0, 0.5), (1.0, 0.0, 1.0), (0.5, 0.0, 1.0)
		];
	
	as = [1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0];
	cs = cs[1:length(as)];
	
	Nx = 200;
	
	figure();
	grid(true);
	

	#julia> using PyCall
	#julia> @pyimport matplotlib.patches as patch
	#julia> @pyimport matplotlib.pyplot as plt

	c = patch.Circle((-1,0), 1, alpha=0.2);
	plt.gca()[:add_patch](c)
	
	
	for i = 1:length(as)
		ev = eigvals(dt*berekenW(disc, Nx, as[i], 1.0, 1.0))
		
		#Wred = berekenWReduced(disc, Nx, as[i], 1.0);
		#Wimpl = berekenWimpl(disc, Wred, Nx, dt, 1.0)
		#ev = eigvals(berekenW(disc, Nx, as[i], 1.0, 1.0) - Wimpl)
		
		scatter(real(ev), imag(ev), c=cs[i])
	end
	
	loc = (typeof(disc) == L2C)?"center left":"upper left"
	
	legend( unshift!(map( a -> string(L"$\alpha = $", a), as), "Stab."), loc=loc, fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);
	title("Eigenwaarden van $(disc.toString)")
    xlabel("Re(z)");
    ylabel("Im(z)");
    
    if typeof(disc) == L2
		axis([-5, 1, -1, 1])
		axis([-2, 0.1, -0.5, 0.5])
    else
		axis([-1, 0.2, -1.5, 1.5])
		axis([-0.11, 0.01, -0.15, 0.15])
    end
	
	nothing
end

function plotL2StabBound()
	a = 1:0.01:2;
	b = gamma(3-a)./(3-2.^(2-a))
	
	figure();
	grid(true);
	
	plot(a, b);
	
	xlabel(L"$\alpha$");
	ylabel(L"$f(\alpha)$");
	title(L"$f(\alpha) = \Gamma(3-\alpha)/(3-2^{2-\alpha})$");
	
	axis([1, 2, 0.4, 1])
	
	nothing
end

function lynchFig2_load()
	L2 = [
		"evwVgl1_L2_1.0"
		"evwVgl1_L2_1.1"
		"evwVgl1_L2_1.2"
		"evwVgl1_L2_1.3"
		"evwVgl1_L2_1.4"
		"evwVgl1_L2_1.5"
		"evwVgl1_L2_1.6"
		"evwVgl1_L2_1.7"
		"evwVgl1_L2_1.8"
		"evwVgl1_L2_1.9"
		#"evwVgl1_L2_2.0"
	]
	L2C = [
		"evwVgl1_L2C_1.0"
		"evwVgl1_L2C_1.1"
		"evwVgl1_L2C_1.2"
		"evwVgl1_L2C_1.3"
		"evwVgl1_L2C_1.4"
		"evwVgl1_L2C_1.5"
		"evwVgl1_L2C_1.6"
		"evwVgl1_L2C_1.7"
		"evwVgl1_L2C_1.8"
		"evwVgl1_L2C_1.9"
		#"evwVgl1_L2C_2.0"
	]
	
	#=
	L2 = [
		"../resultaten3_evwVgl_lager_T2_im/evwVgl1_L2_1.3"
		"../resultaten3_evwVgl_lager_T2_im/evwVgl1_L2_1.5"
		"../resultaten3_evwVgl_lager_T2_im/evwVgl1_L2_1.7"
	]
	L2C = [
		"../resultaten3_evwVgl_lager_T2_im/evwVgl1_L2C_1.3"
		"../resultaten3_evwVgl_lager_T2_im/evwVgl1_L2C_1.5"
		"../resultaten3_evwVgl_lager_T2_im/evwVgl1_L2C_1.7"
	]
	=#
	#=L2 = [
		"../resultaten1/evwVgl1_L2_1.3"
		"../resultaten1/evwVgl1_L2_1.5"
		"../resultaten1/evwVgl1_L2_1.7"
	]
	L2C = [
		"../resultaten1/evwVgl1_L2C_1.3"
		"../resultaten1/evwVgl1_L2C_1.5"
		"../resultaten1/evwVgl1_L2C_1.7"
	]
	L2 = [
		"evwVgl1_L2_1.1"
		"evwVgl1_L2_1.3"
		"evwVgl1_L2_1.5"
		"evwVgl1_L2_1.7"
		"evwVgl1_L2_1.9"
	]
	L2C = [
		"evwVgl1_L2C_1.1"
		"evwVgl1_L2C_1.3"
		"evwVgl1_L2C_1.5"
		"evwVgl1_L2C_1.7"
		"evwVgl1_L2C_1.9"
	]=#

	exErr_L2 = zeros(length(L2));
	exErr_L2C = zeros(length(L2C));

	for i in 1:length(L2)
		result = RS_open("../resultaten1/$(L2[i])");
		exErr_L2[i] = result.exactError[end]
		
		#=
		figure()
		RS_makePlot(result);
		savefig("resultaten/plots/plot_$(L2[i]).png");
		close()
		
		figure()
		RS_makeMesh(result);
		savefig("resultaten/plots/mesh_$(L2[i]).png");
		close()
		
		result = 0
		=#
	end

	for i in 1:length(L2C)
		result = RS_open("../resultaten1/$(L2C[i])");
		exErr_L2C[i] = result.exactError[end]
		
		#=
		figure()
		RS_makePlot(result);
		savefig("resultaten/plots/plot_$(L2C[i]).png");
		close()
		
		figure()
		RS_makeMesh(result);
		savefig("resultaten/plots/mesh_$(L2C[i]).png");
		close()
		
		result = 0
		=#
	end

	
	exErr_L2, exErr_L2C

end


function lynchFig2_draw(exErr_L2, exErr_L2C)
	as = 1.0:0.1:1.9;
	#as = [1.3 ; 1.5 ; 1.7]
	#as = [1.1; 1.3 ; 1.5 ; 1.7; 1.9]
	
	figure();
	semilogy(as, exErr_L2);
	semilogy(as, exErr_L2C);
	
	xlabel(L"\alpha");
	ylabel(L"\delta u");
	legend(["L2","L2C"], loc="upper center")
	
	nothing
end

function lynchFig3_params(imex="ex")
	[
		(L2(imex), 400, 0.04, "lynchFig3_L2_400_004"),
		(L2(imex), 800, 0.02, "lynchFig3_L2_800_002"),
		(L2(imex), 1600, 0.01, "lynchFig3_L2_1600_001"),
		(L2C(imex), 400, 0.04, "lynchFig3_L2C_400_004"),
		(L2C(imex), 800, 0.02, "lynchFig3_L2C_800_002"),
		(L2C(imex), 1600, 0.01, "lynchFig3_L2C_1600_001")
	]
end

function lynchFig3_calc(imex="ex")
	params = lynchFig3_params(imex);

	for i = 1:length(params)
		result = fractDeriv(dx=1.0/params[i][2], dt=params[i][3], T=10.0, bwp=AdvecDiff(chi=0.05,W=0.1), disc=params[i][1], a=1.0);
		RS_save(result, params[i][4])
		result = 0
	end
	

	nothing
end

function lynchFig3_draw(imex="ex")
	params = lynchFig3_params(imex);
	
	
	for i = 1:length(params)
		result = RS_open(params[i][4])
		plot(0:params[i][3]:10, result.maxVals)
	end

	xlabel(L"t");
	ylabel(L"u_{\max}");
	legend( map( p -> string(L"N = ", p[2], L", \Delta_t = ", p[3], ", ", p[1].toString), params), loc="lower left", fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);

end

function lynchFig3_drawVelocity(imex="ex")
	params = lynchFig3_params(imex);
	
	figure();
	for i = 1:length(params)
		result = RS_open(params[i][4])
		
		ts = 0.0:result.dt:result.T;
		vs = zeros(length(ts));
		
		vs[2:5:end] = (result.maxValsPos[6:5:end] - result.maxValsPos[1:5:end-5]) / result.dt / 5;
		
		plot(ts[2:5:end], vs[2:5:end])
	end

	xlabel(L"t");
	ylabel(L"v");
	legend( map( p -> string(L"N = ", p[2], L", \Delta_t = ", p[3], ", ", p[1].toString), params), loc="lower left", fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);

end

function lynchFig4_draw(a)
	result = fractDeriv(dx=1.0/400, dt=5e-4, T=1.0, BWP=AdvecDiff(chi=0.05,x0=0.5,W=0.003), disc=L2C("im"), a=a)
	
	RS_makePlot(result)
	
	xs = 0:result.dx:result.BWP.L;
	
	figure()
	for i = 2:length(result.plotSamples[:,1])
		t = (i-2.0)*result.T/8.0
		fact = (result.BWP.chi * t)^(1/a);
		plot((xs-xs[indmax(result.plotSamples[i,:])])/fact, fact*result.plotSamples[i,:]');
	end
	
	xlabel(L"(x-x_0)/(\chi t)^{1/\alpha}");
	ylabel(L"u (\chi t)^{1/\alpha}");
	
	nothing
end


function lynchFig5_draw()
	result = fractDeriv(dx=1.0/1000, dt=5e-4, T=0.06, BWP=AdvecDiff(chi=1.0,W=2e-3), disc=L2("im"), a=1.5);

	RS_makePlot(result)

	nothing
end

#=
function RS_velocityPlot(result::ResultSet)
	xs = 0.0:result.BWP.L/result.Nx_mesh:result.BWP.L
	
	x05s = zeros(result.Nt_mesh+1); # indices of 0.5 values
	
	for t = 1:result.Nt_mesh+1
		i05 = -1; # index of lowest value above 0.5
		for i = 1:result.Nx_mesh
			if(result.meshSamples[i, t] >= 0.5)
				if(i >= 2)
					# xs[i-1] + (0.5 - u[i-1])/du*dx
					x05s[t] = xs[i-1] + (0.5-result.meshSamples[i-1, t])/(result.meshSamples[i, t]-result.meshSamples[i-1, t])*(xs[i]-xs[i-1]);
					#x05s[t] = xs[i-1] + 0.5 * (
					#			  (0.5-result.meshSamples[i-1, t])/(result.meshSamples[i, t]-result.meshSamples[i-1, t])*(xs[i]-xs[i-1])
					#			+ (xs[i]-xs[i-1]) - (result.meshSamples[i, t]-0.5)/(result.meshSamples[i, t]-result.meshSamples[i-1, t])*(xs[i]-xs[i-1])
					#		);
				end
				break;
			end
		end
		
	end
	
	ts = 0.0:result.T/result.Nt_mesh:result.T;
	vs = zeros(result.Nt_mesh+1);
	
	#for t = 2:result.Nt_mesh+1
	#	vs[t] = (x05s[t] - x05s[t-1]) / (result.T/result.Nt_mesh);
	#end
	
	vs[2:end] = (x05s[2:end] - x05s[1:end-1]) / (result.T/result.Nt_mesh);
	
	figure()
	plot(ts, x05s)
	figure()
	plot(ts[2:end], vs[2:end])
	
	x05s, vs, (x05s[2:end] - x05s[1:end-1])

end
=#

function RS_velocityPlot(result::ResultSet)
	if(!result.trackMiddle)
		return
	end
	
	xs = 0.0:result.dx:result.BWP.L
	ts = 0.0:result.dt:result.T;

	vs = zeros(length(result.xsMiddle));
	
	#for t = 2:result.Nt_mesh+1
	#	vs[t] = (x05s[t] - x05s[t-1]) / (result.T/result.Nt_mesh);
	#end
	
	vs[2:end] = (result.xsMiddle[2:end] - result.xsMiddle[1:end-1]) / result.dt;
	
	figure()
	plot(ts, result.xsMiddle)
	xlabel(L"t");
	ylabel(L"x | u(x) = 0.5");

	figure()
	plot(ts[3:end], vs[3:end])
	xlabel(L"t");
	ylabel(L"v");
	
	#x05s, vs, (x05s[2:end] - x05s[1:end-1])

end

function velocityMultiPlot_vals()
	dxs = [0.6e-3, 1.0e-3, 1.25e-3, 1.6e-3, 2.5e-3, 5e-3, 1.0e-2];
	dts = [0.2, 0.1, 0.07, 0.04, 0.01, 0.006, 0.002];
	
	dxs, dts
end


function velocityMultiPlot_calc()
	dxs, dts = velocityMultiPlot_vals()
	
	Vs = zeros(length(dts), length(dxs));
	
	for ix in 1:length(dxs)
		for it in 1:length(dts)
			dx = dxs[ix];
			dt = dts[it];
			
			result = fractDeriv(dx=dx, dt=dt, T=30.0, bwp=Fisher(chi=5.0e-4,gamma=1.0/3, W=Wmin,x0=0.9), disc=L2C("im"), a=1.9, trackMiddle=true);

			vs = zeros(length(result.xsMiddle));
			vs[2:end] = (result.xsMiddle[2:end] - result.xsMiddle[1:end-1]) / result.dt;
			
			v = mean(vs[end-10:end]);

			Vs[it, ix] = v;
		end
	end
	
	Vs
end

function velocityMultiPlot_draw(Vs)
	dxs, dts = velocityMultiPlot_vals()
	
	figure();
	for it in 1:length(dts)
		plot(dxs, Vs[it,:]', marker="o");
	end
	
	axis([0.0, 1.1e-2, 0.0, 0.022]);
	xlabel(L"\Delta_x");
	ylabel(L"c_{\mathrm{eind}}");
	legend( map( dt -> string(L"\Delta_t = ", dt), dts), loc="lower right", fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);
	
end


function velocityMultiPlot_draw2(Vs)
	dxs, dts = velocityMultiPlot_vals()
	
	figure();
	for it in 1:length(dts)
		semilogx((dxs.^1.9)/(5.0e-4 * dts[it]), Vs[it,:]', marker="o");
	end
	
	xlabel(L"\Delta_x^\alpha/(\chi \Delta_t)");
	ylabel(L"c_{\mathrm{eind}}");
	legend( map( dt -> string(L"\Delta_t = ", dt), dts), loc="lower right", fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);
	
end

function ShenLiu_calc(T)
	Nx = 100.00000001; # We include a small number to avoid a problem which causes the range to create n-1 points instead of n points...
	result = fractDeriv(dx=pi/Nx, dt=1.0e-4, T=T, bwp=HeatPi(chi=0.4), disc=L2C("ex"), a=1.7);
	println([0.0:pi/Nx:pi][map(x->10*x+1, [0:10])]')
	println(result.plotSamples[end,map(x->10*x+1, [0:10])])
	result
end

function fisherSelfSim_calc(disc::DiscMethode)
	chi=5.0e-3;
	gamma=1.0/3;
	a=1.1;
	Wmin = ((a-1)*chi/gamma)^(1/a);
	cmin = a*gamma/(a-1)*Wmin;
	println("Wmin = ", Wmin, ", cmin= ", cmin);
	
	fractDeriv(dx=1/400, dt=0.001, T=70.0, bwp=Fisher(chi=chi,gamma=gamma, W=Wmin,x0=0.9), disc=disc, a=1.1, trackMiddle=true);
	
end

function fisherSelfSim_draw(result)

	vs = zeros(length(result.xsMiddle));
	vs[2:end] = (result.xsMiddle[2:end] - result.xsMiddle[1:end-1]) / result.dt;
	
	Nt = result.T/result.dt;
	ts = [0, Nt/8, 2*Nt/8, 3*Nt/8, 4*Nt/8, 5*Nt/8, 6*Nt/8, 7*Nt/8, Nt]
	v = map(it -> mean(vs[it-10:it]), ts[2:end]);
	prepend!(v, [v[1]]);
	
	figure();
	plot(vs[3:end]);
	
	RS_makePlot(result, legendLoc="center left");
	
	RS_makePlot(result, selfSimVelocities=abs(v), legendLoc="center left", label_x=L"x+ct");
	
end

function ShenLiu_plot()
	
end