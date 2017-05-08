

#Joseph Vavra & David Berger
#Yale University

#modified by Yuta Takahashi
#Northwestern University

# originally 20000
numfirms=2000;  #You get good approximations for 10,000 firms but it starts to get a bit slow


numsim=500;
burnin=50;  #Throw out an initial burnin before computing stats
#rand('twister', 5489);  #Initialize random sequence so always the same
#rng('default'); # this is recommended by Matlab


#----------------------------------------------------------
# Initialize state variables
#----------------------------------------------------------

currentfirmstate=zeros(numfirms,3);
newfirmstate=zeros(numfirms,3);

# initial values start from median. (ex ante the same agents)

currentfirmstate[:,1]=round(npgridsize/2);
currentfirmstate[:,2]=round(zgridsize/2);
currentfirmstate[:,3]=round(xigridsize/2);


numup=0;
numdown=0;
sizeup=0;
sizedown=0;

#----------------------------------------------------------
# Aggregate variables
#----------------------------------------------------------

Csim=zeros(numsim,1);  #Simulated demand
xisim=zeros(numsim,1);  #Simulated Krusell-Smith moment
eps=zeros(numsim,1); #Money shock

#-------------------------------------------------------------------------------
# Just some holders for calculating different statistics that could
# sometimes be of interest:
#-------------------------------------------------------------------------------

frequp_t=zeros(numsim,1);
freqdown_t=zeros(numsim,1);
sizeup_t=zeros(numsim,1);
sizedown_t=zeros(numsim,1);
size_t=zeros(numsim,1);

inflation=zeros(numsim-1,1);  #keeps track of implied inflation
logPoverMregression=zeros(numsim,3);  #Variable for Krusell-Smith regression = 1/Csim

#-------------------------------------------------------------------------------
#Initialize some moments for statistics
#-------------------------------------------------------------------------------

xsd=0;
xsdholder=zeros(numsim,1);
meanpricechange=zeros(numsim,1);

#--------------------------------------------------------------------------------------------------------------------------------------------------------------
# Simulation part
#--------------------------------------------------------------------------------------------------------------------------------------------------------------

for k=1:numsim+burnin

    numup2=0;
    numdown2=0;
    sizeup2=0;
    sizedown2=0;
    size2=0;

    #-------------------------------------------------------------------------------
    #Calculate money shock and thus money tomorrow:
    #-------------------------------------------------------------------------------
    moneyrand=rand(1,1); # draw from uniform distribution
    # inv(U)=d distribution(Money)
    # moneyholder = mu + epsilonS taking value in {-2,-1,...,}(index)

    if moneyrand<Probmoneycum(1) # moneyshock is 1-st grid
        moneyholder=1+(1-(moneygridsize+1)/2);
        moneyshockindex=1;
    else
        for j=1:moneygridsize-1
            if moneyrand>Probmoneycum [ j ] && moneyrand<=Probmoneycum[ j+1 ] # money shock is j+1
                moneyholder=1+(j+1-(moneygridsize+1)/2);
                moneyshockindex=j+1;
            end
        end
    end

    #--------------------------------------------------------------------------------------------------------------------------------------------------------------
    # Statistics about price
    #--------------------------------------------------------------------------------------------------------------------------------------------------------------
    pricetoday=zeros(numfirms,1); # for each firms

    # i is the index for firm

    for i=1:numfirms

        #Price today will be the price firms choose today (normalized by M)
        # policy: indexes
        pricetoday[i,1]=policy[currentfirmstate[i,1],currentfirmstate[i,2],currentfirmstate[i,3]];


        if k>burnin  #Calculate statistics:
            if pricetoday[i,1]>currentfirmstate[i,1] #<=> pricetoday(i,1)>price yesterday(i,1)
                numup=numup+1;
                numup2=numup2+1;
                sizeup=sizeup+np[ pricetoday [i,1] ] -np[ currentfirmstate[i,1 ] ];
                sizeup2=sizeup2+np[pricetoday[i,1]]-np[currentfirmstate[i,1]];
                size2=size2+np[pricetoday[i,1]]-np[currentfirmstate[i,1]];
            elseif pricetoday[i,1]<currentfirmstate[i,1]
                numdown=numdown+1;
                numdown2=numdown2+1;
                sizedown=sizedown+np[currentfirmstate[i,1]]-np[pricetoday[i,1]];
                sizedown2=sizedown2+np[currentfirmstate[i,1]]-np[pricetoday[i,1]];
                size2=size2+np[pricetoday[i,1]]-np[currentfirmstate[i,1]];
            end
        end

        #---------------------------------------------------
        # Transition for log(p-1/S)
        #---------------------------------------------------
        # Note that state = (log(p-1/S),log(z),xi)
        #Price tomorrow will be price today adjusted by money shock

        # newfirmstate(:,1)=log(p/S')= log(p/S) - (mu+epsilonS)
        newfirmstate [i,1]=pricetoday[i,1]-moneyholder;

        # Keep them stay in the grid
        if newfirmstate[i,1]<1
            newfirmstate[i,1]=1;
        elseif newfirmstate[i,1]>npgridsize
            newfirmstate[i,1]=npgridsize;
        end




        #-------------------------------------------------------------------------------
        # Transition for z
        #-------------------------------------------------------------------------------

        randz=rand(1,1);
        if randz<Probzcum[currentfirmstate[i,2],1]
            newfirmstate[i,2]=1;
        else
            for j=1:zgridsize-1
                if randz>Probzcum[currentfirmstate[i,2],j] && randz<=Probzcum[currentfirmstate[i,2],j+1]
                    newfirmstate[i,2]=j+1;
                end
            end
        end


    #--------------------------------------------------------------------------------------------------------------------------------------------------------------
    end



    #-------------------------------------------------------------------------------
    # Transition for xi : krusell-smith state (aggregate)
    #-------------------------------------------------------------------------------
    #Xiprime = function (xi,monetaryshock)
    # third element is an aggregate shock, which be common across the row.

    newfirmstate[:,3]=Xiprime[currentfirmstate[1,3],moneyshockindex];

    #-------------------------------------------------------------------------------
    # Calculate moments averaging across the agents
    #-------------------------------------------------------------------------------
    if k>burnin
        xsd=xsd+sum(            (        ( np[ pricetoday[:,1] ]  -np[ currentfirmstate[:,1] ] )     -    mean(    np[    pricetoday[:,1]   ]  -    np[    currentfirmstate[:,1]  ]  )         ).^2/numfirms)^.5;
        xsdholder[k-burnin]=sum(       (      (  np[pricetoday[:,1]]-np[currentfirmstate[:,1]]   )-mean (    np[pricetoday[:,1]] - np[currentfirmstate[:,1]]    )).^2/numfirms)^.5;
        meanpricechange[k-burnin]=mean(        np[pricetoday[:,1]]-np[currentfirmstate[:,1]]   );
    end






    #calculate simulated variables
    if k>burnin
        Csim[k-burnin]=1/ (sum(exp (  np[pricetoday[:,1]]  ).^(1-theta))/numfirms)^(1/(1-theta));
        xisim[k-burnin,1]=log((sum((exp(         np[currentfirmstate[:,1]]   )).^(1-theta))/numfirms)^(1/(1-theta)));
        eps[k-burnin,1]=moneyholder*mu;
        frequp_t[k-burnin,1]=numup2/numfirms;
        freqdown_t [k-burnin,1] =numdown2/numfirms;
        sizeup_t[k-burnin,1]=sizeup2/numup2;
        sizedown_t[k-burnin,1]=sizedown2/numdown2;
        size_t[k-burnin,1]=size2/(numup2+numdown2);
    end
    if k>burnin+1
        changemv=eps[k-burnin-1,1];
        changec=log(Csim[k-burnin]/Csim[k-burnin-1]);
        inflation[k-burnin]=changemv-changec;
    end

    currentfirmstate=newfirmstate;

end






#Setup matrix for krusell-smith regression
for k=1:numsim
    logPoverMregression[k,1]=log(1/Csim[k]);  #y variable
    logPoverMregression[k,2]=1;  #constant
    logPoverMregression[k,3]=xisim[k];  #x variable

end

#(X'X)^(-1)*X'Y:
coefficients=(logPoverMregression[:,2:3]'*logPoverMregression[:,2:3])\(logPoverMregression[:,2:3]'*logPoverMregression[:,1]);
a0new=coefficients[1];
a1new=coefficients[2];

yhat=logPoverMregression[:,2:3]*coefficients;

r2a=1-sum((logPoverMregression[:,1]-yhat).^2)/sum((logPoverMregression[:,1]-sum(logPoverMregression[:,1]/     max(  size (  logPoverMregression[:,1]  )       )      )).^2);
fracup=numup/(numup+numdown);
freq=(numup+numdown)/(numfirms*numsim);
avesizeup=sizeup/numup;
avesizedown=sizedown/numdown;

#fprintf('\n r2a: #5.3f  \n',r2a);
#fprintf('\n fraction up: #5.3f  \n',fracup);
#fprintf('\n frequency: #5.3f  \n',freq);
#fprintf('\n average size up: #5.3f  \n',avesizeup);
#fprintf('\n average size down: #5.3f  \n',avesizedown);
#xsd=xsd/numsim
#corrxsd_infl=corr(xsdholder,meanpricechange)



