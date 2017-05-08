# EXPLANATION
# The model is explained in housing_aiyagari_note.pdf.
#This code is for computing the equilibrium for Dias Parado (10).
# This code is written in Julia.
#
# Basic features are the same as Aiyagari except for
# (1) agents cannot borrow at all if they don't have a house, which is a collateral;
# (2) if a household own a house, then they can borrow up to theta * q.
# (3) housing demand is binary. You can buy or not.
# In the future, add more
# (4) aggregate shock
# (5) elastic labor supply
# (6) multiple quality choise
# (7) fixed cost to buy or sell a house


##-------------------------------------------------------
## Code starts from here
##-------------------------------------------------------

## Housekeeping
@debug let  # make the code local
#let
##-------------------------------------------------------
## Parameters
##-------------------------------------------------------

beta        = .99; # discount rate
rho         = 0.4; # persistency
alpha       = .3; # capital ratio
gamma       = .5; # elastic supply
delta_h     = .05; # depreciation
rho_h       = .02;
delta       = .05;
sigma_c     = 2;
sigma_h     = 2;
sigma_f     = 2;
L       = 1; # labor supply
epsi    = 6; 
markup  = epsi/(epsi-1);

# Key parameter
b       = 0; # Borrowing limit
theta   = .2; # LTV
##-------------------------------------------------------

##-------------------------------------------------------
# State
##-------------------------------------------------------


# housing
H_lower_bar     = 0;
H_upper_bar     = 5;
H_gridsize      = 20;
H               = linspace(H_lower_bar,H_upper_bar,H_gridsize); # column vector
F               = H;
F_gridsize      = length(F);



# B : Bond choice . B>0 : lending. B<0 : borrowing
a_upper_bar     = 4;
a_lower_bar     = -theta*H_upper_bar;
A_gridsize      = 20;
A               = linspace(a_lower_bar,a_upper_bar,A_gridsize);
# Productivity (Earning process)
# Earning process
S = [1 1.9 2.82 4.05 6.05 13.11 78.65]';
S_gridsize = length(S);
Pi =
[0.910833 0.088657 0.000010 0.000000 0.000000 0.000000 0.008250;
0.088657 0.781730 0.128927 0.000186 0.000000 0.000000 0.008250;
0.000010 0.128927 0.729050 0.141327 0.000186 0.000000 0.008250;
0.000000 0.000186 0.141327 0.729050 0.128927 0.000010 0.008250;
0.000000 0.000000 0.000186 0.128927 0.781730 0.088657 0.008250;
0.000000 0.000000 0.000000 0.000010 0.088657 0.910833 0.008250;
0.0005 0.0005 0.0005 0.0005 0.0005 0.0005 0.9505];

Pi = Pi'; # Pi(i,j) = Prob( i to j ).

# Total number of the states
S_total = A_gridsize*S_gridsize*H_gridsize;


# staionary distribution for the states
lambda = ones(size(S))/length(S);
Pi_stat = Array(Float64,length(S));
for i = 1 : 10000

	lambda_new = Pi'*lambda;

	if norm(lambda_new-lambda,Inf)<1e-10
		lambda=lambda_new;
		Pi_stat = lambda;    
		break
	end
	lambda = lambda_new;
	if i == 10000
		println("The transition does not converge... Check Pi and S.")
	end

    # art
    # print(".")
    # if mod(i,50)==0
    # 	println("")
    # end
end


# Draw the stationary distribution
# myplot = plot(x=S,y=lambda,Geom.line,Geom.point )
# draw(PDF("stat_distri_earning.pdf",6inch,3inch),myplot)


##-------------------------------------------------------
# Index
##-------------------------------------------------------
A_ind = repmat(1:A_gridsize,H_gridsize*S_gridsize,1);
A_ind = A[A_ind];

H_ind  = repmat(transpose(1:H_gridsize),A_gridsize,1);
H_ind  = vec(H_ind);
H_ind  = repmat(H_ind,S_gridsize);
H_value= H[H_ind];

S_ind = repmat(transpose(1:S_gridsize),A_gridsize*H_gridsize,1);
S_ind = vec(S_ind);
S_value = S[S_ind];

##-------------------------------------------------------
# Implementation
##-------------------------------------------------------

# (1) interest rate is guessed, and verified.
R = 1/beta-.01; # initial guess

# (2) k L w
L = L*S'*Pi_stat;
K = L*(R+delta/alpha)^(1/(alpha-1));
w = (1-alpha) * (K/L)^alpha;
# (3) Compute the transfers
T = 0;
# (4) No arbitrage
r_f = R+delta;
# (5) q = 1
q = 1;

## DP OUTLINE


# some parameters for optimization
maxit = 1000;
tol = 1e-5;

## DP part
# initial guess
V = ones(A_gridsize,H_gridsize,S_gridsize);
V = V .* L^(1-sigma_c)/(1-sigma_c)/(1-beta);

# Boxes
C       = 0;
policy  = cell(A_gridsize,H_gridsize,S_gridsize);
V_new   = -Inf * ones(A_gridsize,H_gridsize,S_gridsize);
EV      = 0;

tic()
a = 0;
for i = 1 : maxit
    W = -Inf;

	# Value from having a house
	for i_A = 1 : A_gridsize
		for i_H = 1 : H_gridsize

            # assign minus infinity to the states not reached 
            if A[i_A,1] < theta * q * H[i_H,1]
                break;
            end

			for i_S = 1 : S_gridsize

				# maximization part
				for i_H_prime = 2 : H_gridsize

                    # adjustment cost
					tau = rho_h * (1-delta_h) * H[i_H] * ( H[i_H] - H[i_H_prime] );

                    # violation of financial constraints
                    A_index_start = getindex_matlab(A,theta * q * H[i_H_prime]); 
                    for i_A_prime = A_index_start : A_gridsize 
#                        @bp i>1
                        C = R * A[i_A] + w * S[i_S] + (1-delta_h) * H[i_H] - tau - q*H[i_H_prime] - A[i_A_prime] ;

                        if C[1]<0 # non-nagativity constraints on consumption
                            break;
                        end
                        EV_pointwise = squeeze(V[i_A_prime,i_H_prime,:],1:2);
                        EV = beta * Pi[i_S,:] * EV_pointwise;
						W_new =  C^(1-sigma_c)/(1-sigma_c) + H[i_H_prime]^(1-sigma_h)/(1-sigma_h) + EV;

#                         # concave in the assets
#                         if W[1]>W_new[1]
# #                            @bp
#                             break
#                         end

                        # take max
                        W = max(W,W_new);
                    end
                end
                # println(W_new[1])
                # updates the value
                V_new[i_A,i_H,i_S]=W_new[1];
			end
		end
	end
    @bp i>1
    ind = V_new.>-Inf;
    dist = norm(V[ind]-V_new[ind]);
#    println(dist)
#    @bp
    V = V_new;
    if dist[1]<1e-10
        println("DP converged...")
        break;
    end

    # art
    # print(".")
    # if mod(i,50)==0
    #   println("")
    # end


    # home owners
    # for j = 2 : H_gridsize # home owners don't choose h = 0.
    #     const = -theta * q * h(j);
    #     ind = const>B;
    #     B_min = sum(ind)+1; # finacial constraints

    #     # adjustment cost
    #     tau = rho_h * (1-delta_h)*H_value;
    #     ind = h(j) ~= H_value;
    #     tau = ind.*tau;

    #     for l = B_min : A_gridsize # B(l) is restricted...

    #         c = R * A_ind + w * S_value + (1-delta_h)*H_value - tau -q * h(j) - B(l) ;
    #         c(c<0)=0;
    #         sc=sum(c<0);

    #         if sc>0 # check
    #             # might be correct, but check again...
    #             keyboard
    #         end

    #         EV = Pi(S_ind,:)*squeeze(V(l,j,:));
    #         W_new = c.^(1-sigma_c)/(1-sigma_c) + h(j)^(1-sigma_h)/(1-sigma_h) + beta * EV;

    #         if exist('W','var')
    #             W = max(W_new,W);                
    #         else
    #             # set the initial choice
    #             W = W_new;
    #         end



    #     end

    # end


    # small check
    # if sum(isinf(W))>0
    # 	error('choice set is empty for some states...')
    # end
    # W_owners = W;
    # clear W;
    

    #----------------------------------------------------
    # renters
    #----------------------------------------------------

    # for j = 2 : f_gridsize # renters don't choose f=0.

    #     B_min = B0_ind;        
    #     for l = B_min : A_gridsize # B(l) is restricted...            
    #         c = R * B_value + w * S_value + (1-delta_h)*H_value -r_f*f(j) - B(l) ;
    #         # eliminate non-feasible allocations.
    #         c(c<0)=0;

    #         # small check
    #         sc=sum(c<0);            
    #         if sc>0
    #             keyboard
    #         end

    #         EV = Pi(S_ind,:)*squeeze(V(l,1,:)); # since they choose h'=0.
    #         W_new = c.^(1-sigma_c)/(1-sigma_c) + f(j)^(1-sigma_f)/(1-sigma_f) + beta * EV;

    #         if exist('W','var')
    #             W = max(W_new,W);
    #         else
    #             # set the initial choice
    #             W = W_new;
    #         end
    #     end

    # end
    # # small check
    # if sum(isinf(W))>0
    #     error('choice set is empty for some states...')
    # end
    # W_renters = W;
    # clear W;
    
    # # renter/owner choice
    # V_new = max(W_owners,W_renters);
    # V_new = reshape(V_new,A_gridsize,H_gridsize,S_gridsize
    # );



    # dist = norm(V(:)-V_new(:),inf);
    # if dist<tol
    #     V=V_new;

    #     clc
    #     fprintf('\nDP converged...\n')
    #     break
    # end
    
    # # updata
    # V = V_new;
    
    # fprintf('.')
    # # art
    # if mod(i,50)==0
    #     fprintf('.')
    #     #    dist
    # end
    
    # # non convergence
    # if i == maxit
    #     error('not converged...')
    # end



    # art
    # print(".")
    # if mod(i,50)==0
    # 	println("")
    # end    
end
toc()
#---------
end # make the file local.





