function reducedFibrinModel(t,x,kV,cV,qV)


#-------------------------------------------
#SPECIES
#-------------------------------------------

#Fibrin formation and fibrinolysis constants
FII                = x[1];
FIIa               = x[2]; 
PC                 = x[3];
APC                = x[4];
ATIII              = x[5];
TM                 = x[6];
TRIGGER            = x[7];

Fibrin             = x[8];
Plasmin            = x[9];
Fibrinogen         = x[10];
Plasminogen        = x[11];
tPA                = x[12];
uPA                = x[13];
Fibrin_monomer     = x[14];
Protofibril        = x[15];
antiplasmin        = x[16];
PAI_1              = x[17];
Fiber              = x[18]; 

TAT                = x[19];  #Thrombin-AntiThrombin complex
PAP                = x[20];  #Plasmin-AntiPlasmin complex

TFPI    = qV[1];
FV      = qV[2];
FVIII   = qV[3]
FIX     = qV[4];
FX      = qV[5];

fXIII   = qV[6];
TAFI    = qV[7];

#-------------------------------------------
#PARAMETERS
#-------------------------------------------

#-----Kinetic parameters for thrombin generation and regulation---------------
k_trigger=kV[1];
K_FII_trigger=kV[2];
k_amplification=kV[3];
K_FII_amplification=kV[4];
k_APC_formation=kV[5];
K_PC_formation=kV[6];
k_inhibition_ATIII=kV[7];

#-----Kinetic parameters for fibrin generation---------------
k_cat_Fibrinogen=kV[8];
Km_Fibrinogen=kV[9];
k_fibrin_monomer_association=kV[10];
k_protofibril_association=kV[11];
k_protofibril_monomer_association=kV[12];

#-----Kinetic parameters for fibrinolysis---------------
k_cat_plasminogen_Fibrin_tPA =kV[13];
Km_plasminogen_Fibrin_tPA=kV[14];
k_cat_plasminogen_Fibrin_uPA=kV[15];
Km_plasminogen_Fibrin_uPA=kV[16];

k_cat_Fibrin=kV[17];
Km_Fibrin=kV[18];

k_inhibit_plasmin=kV[19];

#-----Kinetic parameter for fibrin formation---------------
k_inhibit_PAI_1_APC=kV[20];

#-----Kinetic parameters for fibrinolysis---------------
k_inhibit_tPA_PAI_1=kV[21];
k_inhibit_uPA_PAI_1=kV[22];

#-----Kinetic parameter for fibrin formation---------------
k_fibrin_formation=kV[23];

#-----A few more kinetic parameters for fibrinolysis---------------

#Protofibril degradation
#k_cat_protofibril=kV(24];
#Km_protofibril=kV(25];

#Fiber degradation
k_cat_fiber=kV[24];
Km_fiber=kV[25];

#Plasmin activation
Ka_plasminogen_Fibrin_tPA =kV[26];
K_plasminogen_Fibrin_tPA =kV[27];



#-------Control Parameters-------------

#Initiation  
alpha_trigger_activation        = cV[1];
order_trigger_activation        = cV[2];
alpha_trigger_inhibition_TFPI   = cV[3];
order_trigger_inhibition_TFPI   = cV[4];
    
# Amplification -
alpha_amplification_APC         = cV[5];
order_amplification_APC         = cV[6];
alpha_amplification_TFPI        = cV[7];
order_amplification_TFPI        = cV[8];
    
# APC generation -
alpha_shutdown_APC              = cV[9];
order_shutdown_APC              = cV[10];


alpha_fib_inh_fXIII             = cV[11];
order_fib_inh_fXIII             = cV[12];
alpha_fib_inh_TAFI              = cV[13];
order_fib_inh_TAFI              = cV[14];

#Control constants for plasmin activation term
alpha_tPA_inh_PAI_1             = cV[15];
order_tPA_inh_PAI_1             = cV[16];
alpha_uPA_inh_PAI_1             = cV[17];
order_uPA_inh_PAI_1             = cV[18];

#alpha_APC_inh_PAI_1             = cV(19];
#order_APC_inh_PAI_1             = cV(20];


#--------Control Terms-----------------

# Initiation model -
initiation_trigger_term   =  (alpha_trigger_activation*TRIGGER.^order_trigger_activation)/(1 + (alpha_trigger_activation*TRIGGER.^order_trigger_activation));
initiation_TFPI_term      =  1 - (alpha_trigger_inhibition_TFPI*TFPI.^order_trigger_inhibition_TFPI)/(1 + (alpha_trigger_inhibition_TFPI*TFPI.^order_trigger_inhibition_TFPI));

# Amplification model -
inhibition_term           = 1 - (alpha_amplification_APC*APC.^order_amplification_APC)/(1 + (alpha_amplification_APC*APC.^order_amplification_APC));
inhibition_term_TFPI      = 1 - (alpha_amplification_TFPI*TFPI.^order_amplification_TFPI)/(1 +(alpha_amplification_TFPI*TFPI.^order_amplification_TFPI));
factor_product            = FV*FX*FVIII*FIX;
factor_amplification_term = (0.1*factor_product.^2)/(1+(0.1*factor_product.^2));
    
# Shutdown phase -
shutdown_term             = (alpha_shutdown_APC*FIIa.^order_shutdown_APC)/(1 + (alpha_shutdown_APC*FIIa.^order_shutdown_APC));



# Control terms for factor fXIII and TAFI 
Control_term_fibrinolysis_fXIII = 1-((alpha_fib_inh_fXIII.*fXIII).^order_fib_inh_fXIII)./(1+((alpha_fib_inh_fXIII.*fXIII).^order_fib_inh_fXIII)) ; 
Control_term_fibrinolysis_TAFI = 1-((alpha_fib_inh_TAFI.*TAFI).^order_fib_inh_TAFI)./(1+((alpha_fib_inh_TAFI.*TAFI).^order_fib_inh_TAFI)) ;

Control_term_tPA_PAI_1 = 1-((alpha_tPA_inh_PAI_1.*PAI_1).^order_tPA_inh_PAI_1)./(1+((alpha_tPA_inh_PAI_1.*PAI_1).^order_tPA_inh_PAI_1));
Control_term_uPA_PAI_1 = 1-((alpha_uPA_inh_PAI_1.*PAI_1).^order_uPA_inh_PAI_1)./(1+((alpha_uPA_inh_PAI_1.*PAI_1).^order_uPA_inh_PAI_1));


#-------------------------------------------
#REACTIONS
#-------------------------------------------
rV = fill(1.0,17,1)

#----------- Thrombin formation and regulation-------------

rV[1] = k_trigger*TRIGGER*(FII/(K_FII_trigger + FII));
rV[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII));
rV[3] = k_APC_formation*TM*(PC/(K_PC_formation + PC));    
rV[4] = k_inhibition_ATIII*(ATIII)*(FIIa.^1.26);    


#----------- Fibrin formation and regulation---------------

#-----------------------------------
#Formation of fibrin from fibrinogen
#-----------------------------------
rV[5] = (((FIIa)*k_cat_Fibrinogen*(Fibrinogen)./(Km_Fibrinogen+Fibrinogen))); #Cleavage of fibrinopeptides A and/or B to form fibrin monomer
rV[6] = k_fibrin_monomer_association.*(Fibrin_monomer.^2);  #Protofibril formation through association of fibrin monomers  
rV[7] = k_protofibril_association.*(Protofibril.^2); #Association of protofibril-protofibril to form fibers
rV[8] = k_protofibril_monomer_association*(Protofibril)*(Fibrin_monomer);  # Fibril association with monomer forms protofibril again
rV[9] = k_fibrin_formation*(Fiber); #Fibrin growth

#-----------------------------------
#Plasmin activation from plasminogen
#-----------------------------------

F=Fibrin+Fiber;

k_cat_plasminogen_tPA=(k_cat_plasminogen_Fibrin_tPA.*(F))./(K_plasminogen_Fibrin_tPA+(F));
Km_plasminogen_tPA=Km_plasminogen_Fibrin_tPA*(Ka_plasminogen_Fibrin_tPA+F)./((K_plasminogen_Fibrin_tPA+(F)));


#rV(10] = ((tPA)*k_cat_plasminogen_Fibrin_tPA*(Plasminogen))/(Km_plasminogen_Fibrin_tPA+Plasminogen);
rV[10] = ((tPA)*k_cat_plasminogen_tPA*(Plasminogen))/(Km_plasminogen_tPA+Plasminogen);
rV[11] = ((uPA)*k_cat_plasminogen_Fibrin_uPA*(Plasminogen))/(Km_plasminogen_Fibrin_uPA+Plasminogen);

#------------
#Fibrinolysis
#------------
rV[12] = ((Plasmin)*k_cat_Fibrin*(Fibrin))/(Km_Fibrin+Fibrin);
#rV[12] = (Plasmin)*k_cat_Fibrin*(Fibrin)^1.005;

#-----------------------------------
#Inhibition of antiplasmin
#-----------------------------------
rV[13] = k_inhibit_plasmin*Plasmin*(antiplasmin);

#----------------------
#PAI_1 APC interactions
#----------------------
rV[14] = k_inhibit_PAI_1_APC*(APC)*(PAI_1);

#----------------------
#t-PA,u-PA PAI_1 interactions
#----------------------
rV[15]= k_inhibit_tPA_PAI_1*(tPA)*PAI_1;
rV[16]= k_inhibit_uPA_PAI_1*(uPA)*PAI_1;


#----------------------
#Some more fibrinolysis
#----------------------
# rV(17] = ((Plasmin)*k_cat_protofibril*(Protofibril))/(Km_protofibril+Protofibril);
# rV(18] = ((Plasmin)*k_cat_fiber*(Fiber))/(Km_fiber+Fiber);
rV[17] = ((Plasmin)*k_cat_fiber*(Fiber))/(Km_fiber+Fiber);

rV_modified = fill(1.0,12,1)

rV_modified[1]=rV[1].*min(initiation_trigger_term,initiation_TFPI_term);
rV_modified[2]=rV[2].*min(inhibition_term,inhibition_term_TFPI,factor_amplification_term);
rV_modified[3]=rV[3].*shutdown_term;

if ((Control_term_fibrinolysis_TAFI)>0.0009)
    #rV_modified(10]=rV(10].*min([Control_term_fibrinolysis_TAFI Control_term_tPA_PAI_1]);
    rV_modified[10]=rV[10].*Control_term_fibrinolysis_TAFI;
else
    rV_modified[10]=rV[10];
end
#rV_modified(10]=rV(10].*0.01;
#rV_modified(10]=rV(10].*1;

if (Control_term_fibrinolysis_TAFI>0.0009)
    #rV_modified(11]=rV(11].*min([Control_term_fibrinolysis_TAFI Control_term_uPA_PAI_1]);
    rV_modified[11]=rV[11].*Control_term_fibrinolysis_TAFI;
else
    rV_modified[11]=rV[11];
end
    
if(Control_term_fibrinolysis_fXIII>0.0009)
    rV_modified[12]=rV[12].*Control_term_fibrinolysis_fXIII;
else
    rV_modified[12]=rV[12];
end
#mFibrin=Fibrin.*Control_term_fibrinolysis_fXIII;
#rV_modified(12]=((Plasmin)*k_cat_Fibrin*(mFibrin)^5)/(Km_Fibrin^0.5+mFibrin^0.5);


#-------------------------------------------
#MASSBALANCES
#-------------------------------------------
dxdt = fill(1.0,20,1)

dxdt[1]  = -rV_modified[2]-rV_modified[1]; #ProThrombin FII
dxdt[2]  = rV_modified[2]+rV_modified[1]-rV[4]; #Thrombin FIIa 
dxdt[3]  = -rV_modified[3] ; #PC
dxdt[4]  = rV_modified[3]-rV[14]; #APC
dxdt[5]  = -k_inhibition_ATIII*(ATIII)*(FIIa.^1.26); #ATIII
dxdt[6]  = 0.0; #TM acts as an enzyme
dxdt[7]  = 0.0; #Trigger

dxdt[8]  = rV[9]-rV_modified[12]; #Fibrin
dxdt[9]  = rV_modified[10]+rV_modified[11]-rV[13]; #Plasmin
dxdt[10] = -rV[5]; #Fibrinogen
dxdt[11] = -rV_modified[10]-rV_modified[11]; #Plasminogen
dxdt[12] = -rV[15]; #tPA
dxdt[13] = -rV[16]; #uPA
dxdt[14] = rV[5]-rV[6]; #Fibrin monomer
dxdt[15] = rV[6]+rV[8]-rV[7]; #Protofibril
#dxdt(15] = rV(6]+rV(8]-rV(7]; #Protofibril
dxdt[16] = -rV[13]; #antiplasmin
dxdt[17] = -rV[14]-rV[15]-rV[16]; #PAI_1
dxdt[18] = rV[7]-rV[9]-rV[17]; #Fibers
dxdt[19] = k_inhibition_ATIII*(ATIII)*(FIIa.^1.26); #TAT
dxdt[20] = rV[13]; #PAP

return dxdt;
end
