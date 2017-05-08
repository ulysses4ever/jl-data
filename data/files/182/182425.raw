# ASYBC.M
# This function does bias-correction based on the formula by Pope (1990)
# Luca Brugnolini 2014
# Based on Kilian

function  asybc(A,SIGMA,t,K,p)

# Input: Slope parameter estimates in compaion form,
#        variance of estimated residuals in companion form,
#        sample length, number of variables, lag order
# Output: Bias-corrected slope parameter estimates
T = t-p;
# vecSIGMAY=inv(eye((K*p)^2)-kron(A,A))*vec(SIGMA);  % Lutkepohl p.29 (2.1.39)
# SIGMAs = sparse(SIGMA[:]); As = sparse(A); eyes = sparse(eye((K*p)^2));
# vecSIGMAY = (eyes - kron(As, As))\SIGMAs; #***

vecSIGMAY = (eye((K*p)^2)-kron(A,A))\vec(SIGMA);
SIGMAY = reshape(vecSIGMAY, K*p, K*p);
I = eye(K*p, K*p);
B = A';

# There are K*p eigenvalues by construction
peigen = eigvals(A);
sumeig = zeros(K*p, K*p);

    for h = 1:K*p
        sumeig = sumeig + (peigen[h].\(I - peigen[h]*B)); #***

    end;

bias = SIGMA*(inv(I - B) + B/(I-B^2) + sumeig)/(SIGMAY); #***

Abias = - bias/T;

#############################################################

bcstab = 9;         # Arbitrary default value > 1
delta = 1;            # Adjustment factor

while bcstab >= 1

# Adjust bias-correction proportionately
global bcA = A-delta*Abias;
bcmod = abs(eigvals(bcA));

if  any(bcmod.>= 1)
    bcstab = 1;

else
    bcstab = 0;

end

delta += - 0.01;

if delta <= 0
   bcstab = 0;

end

end



return bcA

end
