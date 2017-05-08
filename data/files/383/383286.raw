
using Mamba, Stan, ODE, PyPlot
function runModel()
	tic()
	old = pwd()
	ProjDir = normpath(homedir(), "Documents", "work", "ReducedOrderModelWPlatelets", "LumpedFXandFV_NewDetermineFVIIIFunction", "usingStan", "ODEPlatelets")
	cd(ProjDir)

	plateletmodel = "
	functions {
		real [] Balances(
			real t,
			real[] x,
			real[] control_parameter_vector,
			real[] kinetic_parameter_vector,
			real[] platelet_parameter_vector,
			real[] timing,
			real [] qualitative
			real ALEPH
			real FVIII_control
			){
				real dxdt[11];
				real dxdt_total[11];
				real control_vector[7];
				real rate_vector[7];
				FII	 <- x[1];
				FIIa	<- x[2];
				PC	  <- x[3];
				APC	 <- x[4];
				ATIII   <- x[5];
				TM	  <- x[6];
				TRIGGER <- x[7];
				Eps <- x[8]; //frac platelets acativated
				FV_FX <- x[9];
				FV_FXA <- x[10];
				PROTHOMBINASE_PLATELETS <- x[11];
				
				TFPI = qualitative[1];
				FVIII = qualitative[2];
				FIX = qualitative[3];
			
				alpha_trigger_activation <- control_parameter_vector[1];
				order_trigger_activation <- control_parameter_vector[2];
				alpha_trigger_inhibition_APC <- control_parameter_vector[3];
				order_trigger_inhibition_APC <- control_parameter_vector[4];
				alpha_trigger_inhibition_TFPI <- control_parameter_vector[5];
				order_trigger_inhibition_TFPI <- control_parameter_vector[6];
	
				// Amplification -
				alpha_amplification_FIIa <- control_parameter_vector[7];
				order_amplification_FIIa <- control_parameter_vector[8];
				alpha_amplification_APC <- control_parameter_vector[9];
				order_amplification_APC <- control_parameter_vector[10];
				alpha_amplification_TFPI <- control_parameter_vector[11];
				order_amplification_TFPI <- control_parameter_vector[12];
	
				// APC generation -
				alpha_shutdown_APC <- control_parameter_vector[13];
				order_shutdown_APC <- control_parameter_vector[14];

				//prothomibase complex
				alpha_FV_activation<-control_parameter_vector[15];
				order_FV_activation<-control_parameter_vector[16];
			 	alpha_FX_activation<-control_parameter_vector[17];
			    	order_FX_activation<-control_parameter_vector[18];
				alpha_FX_inhibition<-control_parameter_vector[19];
				order_FX_inhibition<-control_parameter_vector[20];
;
				kplatelts <- platelet_parameter_vector[1];//1 rate constant
				platelet_pwr <- platelet_parameter_vector[2];//2 power for control function
				platelet_denom <- platelet_parameter_vector[3]; //3 adjustment in denominator
				EpsMax0 <- platelet_parameter_vector[4]; //4 Epsmax0
				aida <- platelet_parameter_vector[5]; //5 aida
				koffplatelets <- platelet_parameter_vector[6];

				time_delay <- timing[1];
				time_coeff <- timing[2];

				k_trigger <- kinetic_parameter_vector[1];
				K_trigger <- kinetic_parameter_vector[2];
				k_amplification <- kinetic_parameter_vector[3];
				K_FII_amplification <- kinetic_parameter_vector[4];
				k_APC_formation <- kinetic_parameter_vector[5];
				K_PC_formation <- kinetic_parameter_vector[6];
				k_inhibition <- kinetic_parameter_vector[7];
				K_FIIa_inhibition <- kinetic_parameter_vector[8];
				k_inhibition_ATIII <- kinetic_parameter_vector[9];
				k_FV_X_activation <- kinetic_parameter_vector[10];
				K_FV_X_actiation <- kinetic_parameter_vector[11];
				k_complex <- kinetic_parameter_vector[14];
				k_amp_prothombinase <- kinetic_parameter_vector[15];
				K_FII_amp_prothombinase<-kinetic_parameter_vector[16];
				k_amp_active_factors<- kinetic_parameter_vector[17];
				K_amp_active_factors <- kinetic_parameter_vector[18];
				
				if(FIIa>ALEPH){
					ALEPH = FIIa
				}
				faleph <- aleph^platelet_pwr/(aleph^platelet_pwr + platelet_denom^platelet_pwr);
				EpsMax <- EpsMax0+(1+EpsMax0)*faleph;

				initiation_trigger_term <- ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation));
   				 initiation_TFPI_term <- 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
    
				    activation_term <- ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa));
				    inhibition_term <- ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC));
				    inhibition_term_TFPI <-  ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI));
				    factor_product <- FIX*FVIII*FV_FX/(nominal_FIX*nominal_FVIII*nominal_FV_X);
				    factor_amplification_term <- ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2));
				    shutdown_term <- ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC));
				    activation_FV_by_thrombin <- (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation);
				    activation_FX_by_trigger <- (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation);
				    inhibition_of_FX_by_ATIII<-1-(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition);

				    control_vector[1] <- min(initiation_trigger_term,initiation_TFPI_term);
				    control_vector[2] <- min(inhibition_term,inhibition_term_TFPI);
				    control_vector[3] <- shutdown_term;
				    control_vector[4] <- 1;
				    control_vector[5] <- 1;
				    control_vector[6] <- FVIII_control;
				    control_vector[7] <- min(1-max(inhibition_term,inhibition_term_TFPI));

				rate_vector[1] <- k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX));
				rate_vector[2] <- k_amplification*FIIa*(FII/(K_FII_amplification + FII));
				rate_vector[3] <- k_APC_formation*TM*(Float64(PC)/Float64(K_PC_formation + PC));
				rate_vector[4] <- Float64(k_inhibition_ATIII)*Float64(ATIII)*(Float64(FIIa)^1.26);
				rate_vector[5] <- k_complex*FV_FXA*aida/Eps;
				rate_vector[6] <- k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII);
				rate_vector[7] <- k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII);

				modified_rate_vector <- (rate_vector).*(control_vector);

				dxdt_total[1] <- -1*modified_rate_vector[2] -modified_rate_vector[7]-modified_rate_vector[6];	// 1 FII
				dxdt_total[2] <- modified_rate_vector[2] - modified_rate_vector[4]+modified_rate_vector[7]+modified_rate_vector[6];// 2 FIIa
				dxdt_total[3] <- -1*modified_rate_vector[3]; // 3 PC
				dxdt_total[4] <- 1*modified_rate_vector[3] ; // 4 APC
				dxdt_total[5] <- -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26);// 5 ATIII
				dxdt_total[6] <- 0.0 ;// 6 TM (acts as enzyme, so no change)
				dxdt_total[7] <- -0.0*TRIGGER;	// 7 TRIGGER
				dxdt_total[8] <- kplatelts*(EpsMax-Eps)-koffplatelets*Eps; //frac active platelets
				dxdt_total[9] <- -1*modified_rate_vector[1]; //FV_FX
				dxdt_total[10] <- modified_rate_vector[1] -modified_rate_vector[5];//FV_FXa
				dxdt_total[11] <- modified_rate_vector[5]; //Prothromibase_platelets
			
				tau <- time_coeff*(1-FIIa/aleph);
				time_scale <-1-1*exp(-tau*(t-time_delay));
				if(t<time_delay){
					time_scale = 0.0;
				}
				dxdt = dxdt_total*time_scale;
				return dxdt;
			}
	}

	data{
		int<lower=1> T;
		int<lower = 1> M;
		real t0;
		real ts[T];
		real x[T,M];

	}
	transformed data{
		real x_r[0];
		real x_i[0];
	}

	parameters{
		real x0[11];
		vector<lower=0>[11] sigma;
		real<lower = 0> control_parameter_vector[20];
		real<lower = 0>kinetic_parameter_vector[18];
		real<lower = 0> platelet_parameter_vector[6];
		real<lower = 0> timing[2];
		real<lower = 0> qualitative[3];
		real<lower=0> ALEPH;
		real<lower = 0> FVIII_control;
	}

	model {
		real x_hat[T,11];
		sigma ~cauchy(0,1);
		control_parameter_vector~normal(); //need to figure out how to create vector with different mean and std
		kinetic_parameter_vector~normal();
		platelet_parameter_vector~normal();
		timing~normal();
		qualitative~normal();
		ALEPH~normal(0,1);
		FVIII_control~normal(5.20895,1);
	
	}

	generated quatities{
		real x_hat[T,11];
		x_hat = integrate_ode_rk45(Balances, x0, t0,ts,control_parameter_vector,kinetic_parameter_vector,platelet_parameter_vector,timing,qualitative,ALEPH,FVIII_control)
	}

	"
	odedict = Dict(
		"T" =>size(collect(0:.01:60),1),
		"M"=> 11,
		"t0"=>0.0,
		"ts"=>collect(0:.01:60),
		"y"=>readdlm("../../../data/Luan2010Fig5A.csv", ',')[:,2]
		
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
