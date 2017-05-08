#Originally produced by Joseph Vavra and David Berger
#Yale University

# modified to make this code compatible with julia
# by Yuta Takahashi
#
# Northwestern University 2013

# *** NOTE ***
# See the Berger's note.
# Dropbox/PDF/Berger/note
# QuantitiveSs.pdf


#---------------------------------------------------------
# Parameter(economic parameters)
#---------------------------------------------------------

beta=0.96^(1.0/12.0);   #discount factor
theta=7;  #Elasticity of substitution (implies markup = 7/6-1)
omega=(theta-1)/theta;  #Disutility of leisure

#If you want 1/3 labor supply, set disutility to 3
#but then you'll need lots of 3's floating around
#the program because log prices won't have mean 0
#If you also multiply menu cost by 1/3, nothing is
#changed

# shocks

# log(S')=log(S) mu + Normal (0,sigma_eps)
mu=.002;  #money growth rate
sigma_eps=.0037;  #standard deviation of money growth rate


# log(z')= rho_z log(z)+ Normal( 0 , sigma_z)
rho_z = .7;  #Persistence of productivity
sigma_z=.04;  #Standard deviation of idiosyncratic productivity

fmenu=.045*2;  #Menu cost


# toleramce

difftranstol=.01;  #Krusell-Smith tolerance
policytol = 10e-6;

#---------------------------------------------------------
# Grid related parameters
#---------------------------------------------------------
npgridsize=181;   #price gridsize
zgridsize=23;   #idiosyncratic productivity grid size
moneygridsize=7; #Money shock grid size

# Aggregate state See p.42
# log(P/S)= a0 + a1 xi
# xi is a state variable(mean for each state)

xigridsize=12;  #Aggregate state grid size

truncation=2.0;  #Just scales grid size



#Min and max grid points:
zmin=-truncation*((1.55*.04)^2/(1-rho_z^2))^.5;
zmax=truncation*((1.55*.04)^2/(1-rho_z^2))^.5;
npmin=-mu*(npgridsize-1)/2;
npmax=mu*(npgridsize-1)/2;
moneymin=-(moneygridsize-1)/2*mu;
moneymax=(moneygridsize-1)/2*mu;
ximin=-.025;
ximax=.025;

#*** NOTE ***
# gridside for money and np are the same, 0.02.
# This is useful when calculating the values since we don't care about the
# indexes


#---------------------------------------------------------
#Discritization of the states  by Tauchen(1986)
#---------------------------------------------------------

# money supply & idiosyncratic productivity & aggregate state


#Construct grids:
np=zeros(npgridsize,1);
for i=1:npgridsize
    np[i,1]=npmin+(npmax-npmin)/(npgridsize-1)*(i-1);
end
z=zeros(zgridsize,1);
for i=1:zgridsize
    z[i,1]=zmin+(zmax-zmin)/(zgridsize-1)*(i-1);
end

xi=zeros(xigridsize,1);
for i=1:xigridsize
    xi[i,1]=ximin+(ximax-ximin)/(xigridsize-1)*(i-1);
end

money=zeros(moneygridsize,1);
for i=1:moneygridsize
    money[i,1]=moneymin+(moneymax-moneymin)/(moneygridsize-1)*(i-1);
end

#---------------------------------------------------------
# Transition prpb of idiosyncratic risk
#---------------------------------------------------------

#  j is current idiosyncratic state, k is new state
# See p.16

#Calculate Density


w=z[2]-z[1];# grid width
Probz=zeros(zgridsize,zgridsize);
for j=1:zgridsize
    Probz[j,1]=normcdf (    (z[1]-rho_z*z[j]+w/2)/sigma_z    );
    Probz[j,zgridsize]=1-normcdf (   ( z[zgridsize]-rho_z*z[ j ]-w/2)/sigma_z);
    for k=2:zgridsize-1
        Probz[j,k]=normcdf(    (z [ k ]-rho_z* z [ j ]+w/2)/sigma_z  )  - normcdf(   (z[k]-rho_z*z[j]-w/2)/sigma_z);
    end
end

#Calculate CDF:
Probzcum=zeros(zgridsize , zgridsize);
for j=1:zgridsize
    for k=1:zgridsize
        Probzcum[j,k]=sum(Probz[j,1:k]);
    end
end

#---------------------------------------------------------
# Transition of money supply
#---------------------------------------------------------


#***NOTE***
# Assume iid. log(St)= mu + Normal( 0 , sigma_eps)
# Then no rho component
# in Berger's note, log(St+1)= log(St) + mu + Normal( 0 , sigma_eps)
# in this case, use Tauchen

w=money[2]-money[1]; # this is equal to  money(3)-money(2)

Probmoney=zeros(moneygridsize,1);
Probmoney[1,1]=normcdf((money[1]+w/2)/sigma_eps);
Probmoney[moneygridsize,1]=1-normcdf((money[moneygridsize]-w/2)/sigma_eps);

for j=2:moneygridsize-1
    Probmoney[j,1]=normcdf((money[j]+w/2)/sigma_eps)-normcdf((money[j]-w/2)/sigma_eps);
end
Probmoneycum=zeros(moneygridsize,1);
for j=1:moneygridsize
    Probmoneycum[j,1]=sum(Probmoney[1:j]);
end

#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
