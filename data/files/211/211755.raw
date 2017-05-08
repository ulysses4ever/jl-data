function VF_iteration(dffmax,npgridsize,zgridsize,xigridsize,theta,beta,a0,a1,z,xi,np)


    while diffmax>0        # stop when the policies converge.


        #*** NOTE ***
        # NICE OVSEBATION

        #iterate until policy function unchanged
        #You could also iterate on value function convergence
        #but I find that the policy function has completely
        #converged somewhat before the value function has


        # prepare the boxes
        Vnoadjustnew=zeros(npgridsize,zgridsize,xigridsize);
        Vadjustnew=zeros(zgridsize,xigridsize);


        #----------------------------------------------------------
        # Computing Value function (Calculate expectations & continuation values)
        #----------------------------------------------------------


        #----------------------------------------------------------
        # Not adjusted value V^A
        #----------------------------------------------------------

        # Computing value function which is not adjusted
        # this part does not involve any optimization
        # Integration is just sum: int(f)= sum_i f_i *width

        for i=1:npgridsize
            for j=1:zgridsize
                for k=1:xigridsize

                    # Flow profit

                    # np = log( p/S ).  p/S = exp(np);
                    # (p/S - omega/productivity) * exp((a0 +a1*xi(k))*(theta-2))  * p/S ^-theta

                    Vnoadjustnew[i,j,k]=( exp(        np[i]  )-omega/exp(z[j] ) )*(exp( (a0 +a1*xi[k] )*(theta-2) )*exp(-theta*np[i]  ));

                    # Add continuation

                    for n=1:zgridsize # n for integration

                        for r=1:moneygridsize # r for integration

                            # Prepare SDF
                            #  Q=beta*exp(-(a0+a1*xi(k)))/exp(-(a0+a1*xi(Xiprime(k,r))));
                            # function of k(zgrid) and r(moneygrid)
                            #Drop a0 in common

                            #If the money shock would push price off grid need to make sure it stays on grid

                            # (1+(r-(moneygridsize+1)/2)) means
                            # mu +epsilonS
                            # adding mu is the same as shifting 1 index
                            # since the grid width = mu




                            # in each step, in the last sentence
                            # calculate Vnoadjustnew(i,j,k)=Vnoadjustnew(i,j,k)+Probmoney(r)*Q*Probz(j,n)*Vold;
                            # where
                            # Q=beta*exp(-(a0+a1*xi(k)))/exp(-(a0+a1*xi(Xiprime(k,r))))
                            # SDF

                            if 1<=i-(1+(r-(moneygridsize+1)/2)) && npgridsize>=i-(1+(r-(moneygridsize+1)/2)) # when log(p/S) is in the bounds

                                #Vold=max(  Vnoadjustold(   i-1-(r-(moneygridsize+1)/2),n,Xiprime(k,r)  ),  Vadjustold(n,Xiprime(k,r))   );

                                Vnoadjustnew[i,j,k]=Vnoadjustnew[i,j,k]+Probmoney[r] * beta * exp(    -(a0+a1*xi [ k ]  ) )/exp(-(a0+a1* xi[ Xiprime [ k , r ]  ]    ))* Probz[ j , n ]*max(  Vnoadjustold[   i-1-(r-(moneygridsize+1)/2 ) , n , Xiprime[k,r]  ],  Vadjustold[n,Xiprime[k,r] ]   );

                            elseif 1>i-(1+(r-(moneygridsize+1)/2)) # when log(p/S') is out of the grid (too small)

                                #Vold=max(  Vnoadjustold( 1 , n,Xiprime(k,r)  ),  Vadjustold(n,Xiprime(k,r))   );

                                Vnoadjustnew[i,j,k]=Vnoadjustnew[i,j,k] + Probmoney[r]*  beta*   exp(-(a0+a1*   xi[k]   ))/exp(-(a0+a1*      xi[Xiprime[k,r]]      ))*Probz[j,n]*    max(  Vnoadjustold[ 1 , n,Xiprime[k,r]  ],  Vadjustold[n,Xiprime[k,r]]   );

                            else # when log(p/S) is too big

                                # Vold=max(  Vnoadjustold(npgridsize ,  n,Xiprime(k,r)),  Vadjustold(n,Xiprime(k,r))    );

                                Vnoadjustnew[i,j,k]= Vnoadjustnew[i,j,k] + Probmoney[r]*beta*exp(-(a0+a1*  xi[k]  ))/exp(-(a0+a1*         xi[Xiprime[k,r]]    ))*Probz[j,n]*max(  Vnoadjustold[npgridsize ,  n,Xiprime[k,r]],  Vadjustold[n,Xiprime[k,r]]    );
                            end

                        end

                    end


                end
            end
        end
        #----------------------------------------------------------


        #----------------------------------------------------------
        # Adjusted value V^A
        #----------------------------------------------------------


        #*** NOTE ***
        # This is clever
        #************

        #The value of adjusting will be the value of not adjusting at the
        #computed at the highest value price, minus the cost of adjusting
        #to that price


        for j=1:zgridsize
            for k=1:xigridsize
                (  Vadjustnew[j,k], policyadjust[j,k]   )  =  findmax(  Vnoadjustnew[:,j,k]  );
                Vadjustnew[j,k]=Vadjustnew[j,k]-fmenu*omega*exp( -(a0+a1*xi[k]  ) ); # pay the fixed cost
            end
        end

        #Policy is max of adjusting and not adjusting:
        for i=1:npgridsize
            for j=1:zgridsize
                for k=1:xigridsize
                    if Vnoadjustnew[i,j,k]>Vadjustnew[j,k]
                        policy[i,j,k]=i;
                    else
                        policy[i,j,k]=policyadjust[j,k];
                    end
                end
            end
        end

        #Converged when policy function doesn't change:
        diffmax=max((abs(policy-policyold)));
        policyold=policy;
        Vnoadjustold=Vnoadjustnew;
        Vadjustold=Vadjustnew;
    end
Vnoadjust=Vnoadjustold
Vadjust    =Vadjustold
return [Vnoadjust,Vadjust, policy]
end
