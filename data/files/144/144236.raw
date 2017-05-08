
##
# Externe pakketten aanroepen.
# Deze geven extra functionaliteit.
##

using Dates					# Voor het opslaan van de datum waarop de berekening gedaan is
using PyPlot				# Voor het maken van grafieken
using PyCall				# Om @pyimport te kunnen uitvoeren
using JSON					# Opslaan en teruglezen van eerdere berekeningen
using NumericExtensions		# Efficientere bereken-functies

@pyimport matplotlib.patches as patch	# Voor het maken van de stabiliteits-cirkel in eigenwaarde-plots
@pyimport matplotlib.pyplot as plt		# Voor het maken van de stabiliteits-cirkel in eigenwaarde-plots

import Base.convert			# Om de convert()-functie te kunnen uitbreiden voor eigen types, zodat we JSON-data kunnen converteren naar type-instanties

# Haal alle andere bestanden binnen
include("types.jl")
include("files.jl")
include("plot.jl")
include("calc.jl")
include("extraplots.jl")

##
# fractDeriv()
# De functie die we aanroepen om een berekening te starten
##

function fractDeriv(;dx=0.0005, dt=0.05, T=8, imgX=100, imgT=100, bwp=Fisher(chi=5e-7, gamma=1), disc=L2C(), a=1.5, silent=true, trackMiddle=false)
	tic();
    result = BerekenFisher(dx, dt, T, imgX, imgT, bwp, disc, a, trackMiddle);
	toc();

	if(!silent)
		makeFiles(dx, dt, T, bwp, disc, a)
	end
	
	result
end

##
# BerekenFisher()
# Berekening van Fisher-varianten (EvwVgl, AdvecDiff, Fisher)
##

function BerekenFisher(dx::Float64, dt::Float64, T::Float64, Nx_img::Integer, Nt_img::Integer, bwp::BWP, disc::DiscMethode, a::Float64, trackMiddle::Bool)
	
	# De tijd- en plaats-intervallen
    const ts = 0:dt:T;
    const Nt=length(ts)-1;
    const xs = 0:dx:bwp.L;
    const Nx=length(xs)-1;
    
	# Initialiseer de color mesh
	const dx_img = ceil(Nx/Nx_img)*dx;
	const dt_img = ceil(Nt/Nt_img)*dt;
	const xs_img = 0:dx_img:bwp.L;
	const ts_img = 0:dt_img:T;
	Nx_img = length(xs_img)-1;
	Nt_img = length(ts_img)-1;
	u_xt = zeros(Nx_img+1, Nt_img+1);
	const sampleFactor_x = Nx/Nx_img;
	const sampleFactor_t = Nt/Nt_img;
	nextSaveT = 0;
	
	# Maak result container
	result = ResultSet(
		zeros(Nt+1),
		zeros(Nt+1),
		zeros(Nt+1),
		zeros(Nt+1),
		zeros(10, Nx+1),
		zeros(Nx_img+1, Nt_img+1),
		trackMiddle,
		trackMiddle ? zeros(Nt+1) : zeros(1),
		dx, dt, T, Nx_img, Nt_img, a,
		bwp, disc
		);
	
	# Bereken stabiliteits-eis
	println("> eta = ", (dt * bwp.chi / (dx ^ a)), ", max = ", gamma(3-a)/(3-2^(2-a)));
    
	# De tijdstippen waarop geplot wordt
    plotNts = [0, 0, T/8, 2*T/8, 3*T/8, 4*T/8, 5*T/8, 6*T/8, 7*T/8, T];
    #plotNts = [0, 0, 0.005, 0.0185, 0.0365, 0.0585, 10.0, 10.0, 10.0, 10.0];	# Lynch fig 5
    
	# Genereer de W-matrix
	tic();
	const Wred = berekenWReduced(disc, Nx, a, dx);
	const Wimpl = berekenWimpl(disc, Wred, Nx, dt, bwp.chi)
	const eye = Tridiagonal(zeros(Nx-2),ones(Nx-1),zeros(Nx-2));
	const IWimpl = eye + Wimpl
	toc();
    
	# Beginvoorwaarden
	u_t = beginOpl(bwp, xs, a);

    # Plot de begin-oplossing
    plotNt_i = 1;
	if(bwp.analyticSol)
		RS_savePlot!(result, plotNt_i, exact(bwp, xs, a));
	end
    plotNt_i = 2;
	RS_savePlot!(result, plotNt_i, u_t);
	RS_saveMesh!(result, 0, u_t, sampleFactor_x);
    plotNt_i = 3;
    
	result.maxVals[1], result.maxValsPos[1] = findmax(u_t);
	result.maxValsPos[1] = xs[result.maxValsPos[1]];
    
	# If we have an exact solution available, we compute it to check against later
	if(bwp.analyticSol)
		u_exact = exact(bwp, xs, a)
		u_exactSqSum = sumsq(u_exact)
	end
    
	# Julia works significantly faster when we use temporary arrays for intermediate values
	temp1 = ones(Nx-1);
	temp2 = ones(Nx-1);
	temp3 = ones(Nx-1);
	implCorr = ones(Nx-1);

    for n = 2:Nt+1
        t = (n-1)*dt;
        
        # If we're modelling semi-implicit, we keep track of a 'implicit correction'.
		if disc.imex == "im"
			implCorr = Wimpl*u_t[2:Nx];
		end
		
		# Calculate the explicit derivative
		Dalpha!(Wred, u_t-u_t[1], Nx, temp1, disc) #temp1 = W*(u_t-u_t[1]);
		temp2 = inhom(bwp, u_t[2:Nx],xs[2:Nx],a);
		temp3 = dt*bwp.chi*temp1 + dt*temp2;
		u_t[2:Nx] += temp3;
		
		# If we're moddeling semi-implicit, we now apply the correction, for what we've calculated explicitly, what we should have done implicitly.
		# After that, we solve the system of equalities with the \-operator.
		if disc.imex == "im"
			u_t[2:Nx] = IWimpl\(u_t[2:Nx] + implCorr)
		end
		
		# Apply the boundery conditions for the specific boundery value problem
		randVW!(bwp, u_t, t, a)
		
		# We log some information in our result-set
		result.followUpDiff[n] = sqrt(sumsq(temp3)/sumsq(u_t));
		result.maxVals[n], result.maxValsPos[n] = findmax(u_t);
		result.maxValsPos[n] = xs[result.maxValsPos[n]];
		
		# Track x(t) for which u(x, t) = 0.5
		if(trackMiddle)
			for i = 2:Nx+1
				if(u_t[i] >= 0.5)
					result.xsMiddle[n] = xs[i-1] + (0.5-u_t[i-1])/(u_t[i]-u_t[i-1])*dx;
					break;
				end
			end
		end
		
		# If we have an exact solution available, we check our result against it
		if(bwp.analyticSol)
			result.exactError[n] = sqrt(sumsqdiff(u_t, u_exact) / u_exactSqSum);
		end

		# Save the mesh if needed
		if((n-1)%sampleFactor_t == 0)
			RS_saveMesh!(result, (n-1)/sampleFactor_t, u_t, sampleFactor_x);
		end
        
		# Save the plot if needed
        if(plotNts[plotNt_i] <= t)
            RS_savePlot!(result, plotNt_i, u_t);
            plotNt_i = plotNt_i + 1;
        end

		# We let the plot determine when we're done calculating
        if(plotNt_i >= length(plotNts)+1)
            break
        end
    end
    
	if(bwp.analyticSol)
		println("> Fout: ", result.exactError[end])
	end
    
    result
end


##
# fractGrayScott()
# De functie die we aanroepen om een berekening te starten
##

function fractGrayScott(;dx=0.01, dt=0.4, T=500.0, imgX=100, imgT=125, bwp=GrayScott(), disc1=L2(), disc2=L2())
	tic();
    result = BerekenGrayScott(dx, dt, T, imgX, imgT, bwp, disc1, disc2);
	toc();
	
	result
end

##
# BerekenGrayScott()
# Berekening van GrayScott
##

function BerekenGrayScott(dx::Float64, dt::Float64, T::Float64, Nx_img::Integer, Nt_img::Integer, bwp::GrayScott, disc1::DiscMethode, disc2::DiscMethode)
	
	# De tijd- en plaats-intervallen
    const ts = 0:dt:T;
    const Nt=length(ts)-1;
    const xs = 0:dx:bwp.L;
    const Nx=length(xs)-1;
    
	# Initialiseer de color mesh
	const dx_img = ceil(Nx/Nx_img)*dx;
	const dt_img = ceil(Nt/Nt_img)*dt;
	const xs_img = 0:dx_img:bwp.L;
	const ts_img = 0:dt_img:T;
	Nx_img = length(xs_img)-1;
	Nt_img = length(ts_img)-1;
	u_xt = zeros(Nx_img+1, Nt_img+1);
	const sampleFactor_x = Nx/Nx_img;
	const sampleFactor_t = Nt/Nt_img;
	nextSaveT = 0;
	
	trackMiddle = false;
	
	# Maak result container
	res_u = ResultSet(
		zeros(Nt+1),
		zeros(Nt+1),
		zeros(Nt+1),
		[0.0],
		zeros(10, Nx+1),
		zeros(Nx_img+1, Nt_img+1),
		trackMiddle,
		trackMiddle ? zeros(Nt+1) : zeros(1),
		dx, dt, T, Nx_img, Nt_img, bwp.a1,
		bwp, disc1
		);
	res_v = ResultSet(
		zeros(Nt+1),
		zeros(Nt+1),
		zeros(Nt+1),
		[0.0],
		zeros(10, Nx+1),
		zeros(Nx_img+1, Nt_img+1),
		trackMiddle,
		trackMiddle ? zeros(Nt+1) : zeros(1),
		dx, dt, T, Nx_img, Nt_img, bwp.a2,
		bwp, disc2
		);
	
	# Bereken stabiliteits-eis
	println("> eta = ", (dt * bwp.eps1 / (dx ^ bwp.a1)), ", max = ", gamma(3-bwp.a1)/(3-2^(2-bwp.a1)));
	println("> eta = ", (dt * bwp.eps2 / (dx ^ bwp.a2)), ", max = ", gamma(3-bwp.a2)/(3-2^(2-bwp.a2)));
    
	# De tijdstippen waarop geplot wordt
    plotNts = [0, T/8, 2*T/8, 3*T/8, 4*T/8, 5*T/8, 6*T/8, 7*T/8, T];
    
	# Genereer de W-matrix
	tic();
	const eye = Tridiagonal(zeros(Nx-2),ones(Nx-1),zeros(Nx-2));
	
	const Wred1 = berekenWReduced(disc1, Nx, bwp.a1, dx);
	const Wimpl1 = berekenWimpl(disc1, Wred1, Nx, dt, bwp.eps1)
	const IWimpl1 = eye + Wimpl1
	
	const Wred2 = berekenWReduced(disc2, Nx, bwp.a2, dx);
	const Wimpl2 = berekenWimpl(disc2, Wred2, Nx, dt, bwp.eps2)
	const IWimpl2 = eye + Wimpl2
	toc();
    
	# Beginvoorwaarden
	u_t = beginOpl1(bwp, xs);
	v_t = beginOpl2(bwp, xs);

    # Plot de begin-oplossing
    plotNt_i = 1;
	RS_savePlot!(res_u, plotNt_i, u_t);
	RS_saveMesh!(res_u, 0, u_t, sampleFactor_x);
	
	RS_savePlot!(res_v, plotNt_i, v_t);
	RS_saveMesh!(res_v, 0, v_t, sampleFactor_x);
    plotNt_i = 2;
    
	res_u.maxVals[1] = minimum(u_t);
	res_v.maxVals[1] = maximum(v_t);
    
	# Julia works significantly faster when we use temporary arrays for intermediate values
	temp1 = ones(Nx-1);
	temp2 = ones(Nx-1);
	temp3 = ones(Nx-1);
	temp4 = ones(Nx-1);
	implCorr1 = ones(Nx-1);
	implCorr2 = ones(Nx-1);
	
	print("t = 0.0                                       ");

    for n = 2:Nt+1
        t = (n-1)*dt;
        
        # If we're modelling semi-implicit, we keep track of a 'implicit correction'.
		if disc1.imex == "im"
			implCorr1 = Wimpl1*u_t[2:Nx];
		end
		if disc2.imex == "im"
			implCorr2 = Wimpl2*v_t[2:Nx];
		end
		
		# Calculate the explicit derivative
		Dalpha!(Wred1, u_t-u_t[1], Nx, temp1, disc1) #temp1 = W*(u_t-u_t[1]);
		temp2 = inhom1(bwp, u_t[2:Nx], v_t[2:Nx], xs[2:Nx]);
		temp3 = dt*bwp.eps1*temp1 + dt*temp2;
		
		Dalpha!(Wred2, v_t-v_t[1], Nx, temp1, disc2) #temp1 = W*(v_t-v_t[1]);
		temp2 = inhom2(bwp, u_t[2:Nx], v_t[2:Nx], xs[2:Nx]);
		temp4 = dt*bwp.eps2*temp1 + dt*temp2;
		
		u_t[2:Nx] += temp3;
		v_t[2:Nx] += temp4;
		
		# If we're modelling semi-implicit, we now apply the correction, for what we've calculated explicitly, what we should have done implicitly.
		# After that, we solve the system of equalities with the \-operator.
		if disc1.imex == "im"
			u_t[2:Nx] = IWimpl1\(u_t[2:Nx] + implCorr1)
		end
		if disc2.imex == "im"
			v_t[2:Nx] = IWimpl2\(v_t[2:Nx] + implCorr2)
		end
		
		# Apply the boundery conditions for the specific boundery value problem
		randVW1!(bwp, u_t, t)
		randVW2!(bwp, v_t, t)
		
		# We log some information in our result-set
		res_u.followUpDiff[n] = sqrt(sumsq(temp3)/sumsq(u_t));
		res_u.maxVals[n] = minimum(u_t);

		res_v.followUpDiff[n] = sqrt(sumsq(temp4)/sumsq(v_t));
		res_v.maxVals[n] = maximum(v_t);
		
		# Save the mesh if needed
		if((n-1)%sampleFactor_t == 0)
			RS_saveMesh!(res_u, (n-1)/sampleFactor_t, u_t, sampleFactor_x);
			RS_saveMesh!(res_v, (n-1)/sampleFactor_t, v_t, sampleFactor_x);
		end
        
		# Save the plot if needed
        if(plotNts[plotNt_i] <= t)
			print("\rt = $t                                       ");
            RS_savePlot!(res_u, plotNt_i, u_t);
            RS_savePlot!(res_v, plotNt_i, v_t);
            plotNt_i = plotNt_i + 1;
        end

		# We let the plot determine when we're done calculating
        if(plotNt_i >= length(plotNts)+1)
            break
        end
    end
    print("\n");
    
    res_u, res_v
end

# Als er niets is misgegaan, geven we maar even een mooie succes-melding
"Load successful"
