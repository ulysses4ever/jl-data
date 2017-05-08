
using Mamba, Stan, ODE, PyPlot
function runModel()
	tic()
	old = pwd()
	ProjDir = normpath(homedir(), "Documents", "work", "ReducedOrderModelWPlatelets", "LumpedFXandFV_NewDetermineFVIIIFunction", "usingStan", "ODEPlatelets")
	cd(ProjDir)

	plateletmodel = "
	functions {
		real[] Balances(
			real t,
			real[] x,
			real[] theta,
			real[] x_r,
			int[] x_i
			){
				real dxdt[11];
				vector[11] dxdt_total;
				vector[7] control_vector;
				vector[7] rate_vector;
				vector[11] modified_rate_vector;
				real FII=x[1];
				real FIIa=x[2];
				real PC= x[3];
				real APC=x[4];
				real ATIII =x[5];
				real TM=x[6];
				real TRIGGER= x[7];
				real Eps = x[8]; //frac platelets acativated
				real FV_FX =x[9];
				real FV_FXA =x[10];
				real PROTHOMBINASE_PLATELETS=x[11];
				
				real TFPI = theta[47];
				real FVIII = theta[48];
				real FIX = theta[49];

				real FVIII_control = theta[50];
				real ALEPH = theta[51];
			
				real alpha_trigger_activation= theta[19];
				real order_trigger_activation= theta[20];
				real alpha_trigger_inhibition_APC= theta[21];
				real order_trigger_inhibition_APC= theta[22];
				real alpha_trigger_inhibition_TFPI= theta[23];
				real order_trigger_inhibition_TFPI= theta[24];
	
				// Amplification -new c
				real alpha_amplification_FIIa= theta[25];
				real order_amplification_FIIa= theta[26];
				real alpha_amplification_APC= theta[27];
				real order_amplification_APC= theta[28];
				real alpha_amplification_TFPI= theta[29];
				real order_amplification_TFPI= theta[30];
	
				// APC generation -
				real alpha_shutdown_APC= theta[31];
				real order_shutdown_APC= theta[32];

				//prothomibase complex
				real alpha_FV_activation=theta[33];
				real order_FV_activation=theta[34];
			 	real alpha_FX_activation=theta[35];
			    	real order_FX_activation=theta[36];
				real alpha_FX_inhibition=theta[37];
				real order_FX_inhibition=theta[38];
				real kplatelts= theta[39];
				real platelet_pwr= theta[40];
				real platelet_denom= theta[41];
				real EpsMax0= theta[42]; 
				real aida= theta[43];
				real koffplatelets= theta[44];

				real time_delay= theta[45];
				real time_coeff= theta[46];

				real k_trigger= theta[1];
				real K_trigger= theta[2];
				real k_amplification= theta[3];
				real K_FII_amplification= theta[4];
				real k_APC_formation= theta[5];
				real K_PC_formation= theta[6];
				real k_inhibition= theta[7];
				real K_FIIa_inhibition= theta[8];
				real k_inhibition_ATIII= theta[9];
				real k_FV_X_activation= theta[10];
				real K_FV_X_actiation= theta[11];
				real k_complex= theta[14];
				real k_amp_prothombinase= theta[15];
				real K_FII_amp_prothombinase=theta[16];
				real k_amp_active_factors= theta[17];
				real K_amp_active_factors= theta[18];
				real local_aleph = ALEPH;
				real faleph;
				real EpsMax;
				real initiation_trigger_term;
				real initiation_TFPI_term;
				real activation_term;
				real inhibition_term;
				real inhibition_term_TFPI;
				real shutdown_term;
				real activation_FV_by_thrombin;
				real activation_FX_by_trigger;
				real inhibition_of_FX_by_ATIII;
				real term1[2];
				real term2[2];
				real tau;
				real time_scale;
				if(FIIa>local_aleph){
					local_aleph =FIIa;
				}
				faleph= local_aleph^platelet_pwr/(local_aleph^platelet_pwr+platelet_denom^platelet_pwr);
				EpsMax= EpsMax0+(1+EpsMax0)*faleph;

				initiation_trigger_term= ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation));
   				initiation_TFPI_term= 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI));
    
				    activation_term= ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa));
				    inhibition_term= ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC));
				    inhibition_term_TFPI=  ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI));
				    shutdown_term= ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC));
				    activation_FV_by_thrombin= (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation);
				    activation_FX_by_trigger= (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation);
				    inhibition_of_FX_by_ATIII=1-(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition);
					term1[1] = initiation_trigger_term;
					term1[2] =initiation_TFPI_term; 
					term2[1] = inhibition_term;
					term2[2] = inhibition_term_TFPI;
				    control_vector[1]= min(term1);
				    control_vector[2]= min(term2);
				    control_vector[3]= shutdown_term;
				    control_vector[4]= 1;
				    control_vector[5]= 1;
				    control_vector[6]= FVIII_control;
				    control_vector[7]= (1-max(term2));

				rate_vector[1]= k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX));
				rate_vector[2]= k_amplification*FIIa*(FII/(K_FII_amplification + FII));
				rate_vector[3]= k_APC_formation*TM*((PC)/(K_PC_formation + PC));
				rate_vector[4]= (k_inhibition_ATIII)*(ATIII)*((FIIa)^1.26);
				rate_vector[5]= k_complex*FV_FXA*aida/Eps;
				rate_vector[6]= k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII);
				rate_vector[7]= k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII);

				modified_rate_vector= (rate_vector).*(control_vector);

				dxdt_total[1]= -1.0*modified_rate_vector[2] -modified_rate_vector[7]-modified_rate_vector[6];	// 1 FII
				dxdt_total[2]= modified_rate_vector[2] - modified_rate_vector[4]+modified_rate_vector[7]+modified_rate_vector[6];// 2 FIIa
				dxdt_total[3]= -1*modified_rate_vector[3]; // 3 PC
				dxdt_total[4]= 1*modified_rate_vector[3] ; // 4 APC
				dxdt_total[5]= -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26);// 5 ATIII
				dxdt_total[6]= 0.0 ;// 6 TM (acts as enzyme, so no change)
				dxdt_total[7]= -0.0*TRIGGER;	// 7 TRIGGER
				dxdt_total[8]= kplatelts*(EpsMax-Eps)-koffplatelets*Eps; //frac active platelets
				dxdt_total[9]= -1*modified_rate_vector[1]; //FV_FX
				dxdt_total[10]= modified_rate_vector[1] -modified_rate_vector[5];//FV_FXa
				dxdt_total[11]= modified_rate_vector[5]; //Prothromibase_platelets
			
				tau= time_coeff*(1-FIIa/local_aleph);
				time_scale=1-1*exp(-tau*(t-time_delay));
				if(t<time_delay){
					time_scale = 0.0;
				}
				for(j in 1:11){
					dxdt[j] = dxdt_total[j]*time_scale;
				}
				return dxdt;
			}
	}

	data{
		int<lower=1> T;
		int<lower = 1> M;
		real t0;
		real x0[11];
		real ts[T];
		real x[T,M];
		real theta[51];

	}
	transformed data{
		real x_r[0];
		int x_i[0];
	}


	model {
	}

	generated quantities{
		real x_hat[T,11];
		x_hat = integrate_ode_rk45(Balances, x0, t0,ts,theta, x_r, x_i);
	}

	"
	odedict = Dict(
		"T" =>size(collect(0:.01:60),1),
		"M"=> 11,
		"t0"=>0.0,
		"x0"=>[1400,.001, 60, 0, 3400, 12, 1E-3, 0, 22, 0, 0],
		"ts"=>collect(0:.01:60),
		"theta"=>readdlm("../../parameterEstimation/NLoptCOBYLA_2017_02_10BestParams.txt", ','),
		"x"=>zeros(size(collect(0:.01:60),1),11)#readdlm("../../../data/Luan2010Fig5A.csv", ',')[:,2]
		
	)

	odedata = [
	  odedict,
	  odedict,
	  odedict,
	  odedict
	]

	stanmodel = Stanmodel(name="odePlatelets", model=plateletmodel, nchains=4);

	println("\nStanmodel that will be used:")
	stanmodel |> display
	println("Input observed data dictionary:")
	odedata |> display
	println()

	sim1 = stan(stanmodel, odedata, ProjDir, diagnostics=true, CmdStanDir=CMDSTAN_HOME);

	## Subset Sampler Output to variables suitable for describe().
	monitor = ["theta.1", "lp__", "accept_stat__"]
	sim = sim1[:, monitor, :]
	describe(sim)
	println()
	toc()
	cd(old)
	return sim1
end
