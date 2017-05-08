function OMP_plus_1_mod(X::Matrix,mu::Vector,nu::Real=.01,I::Integer=100)

# X, mu, nu and I -> These are defined in the Algorithm 1 of the SEK manuscript
# gamma <- The 'gamma' vector as defined in the Algorithm 1 of the
# manuscript
# it <- number of iterations the algorithm does

## Comment
# Question: How to set nu and I ?
# Answer: This is bit arbitrary. Default values can be as follows. 
# nu can be set to a small number, such as # nu=0.00001; 
# I can be set as I = int ( (1/3) * dim (mu) ). Note that dim(mu)= number of rows in X = 4^k.



## Algorithm 1 starts here


## Finding the l_2 norms of columns of X

ColNorms = zeros(Real,size(X,2),1);
for i=1:length(ColNorms);
    ColNorms[i]=norm(X[:,i]);
end


## System parameters

M,N = size(X);   # Note that M = 4^k, where k is the value of k-mers; We have used k=4 so far in the manuscript. However, the choice of k depends on the user


## Intialization
gamma = zeros(N,1);
r = mu;
T = [];
it=0;


## Iterations
Xtrans=X';#pre-compute transpose
while ( (abs(sum(gamma)-1) > nu)  && (it < I) )
    
    # Step 3 of the 'Iterations of Algorithm 1'
    e = Xtrans*r;
    e[T]=0;

    for index=1:length(e) #e[find(e <= zeros(size(e)))]=0;
        if e[index]<=0
            e[index]=0
        end
    end

    e = [e[i] / ColNorms[i] for i=1:length(e)];
    dummy,j0=findmax(e);

    # Step 4 of the 'Iterations of Algorithm 1'
    T = [T; j0];
    
    # Step 5 of the 'Iterations of Algorithm 1'
    Xp = X[:,T];
    (gamma_temp,dummy,dummy) = lsqnonneg(Xp,mu);
    for index=1:length(T)
        gamma[T[index]] = gamma_temp[index]
    end
    r = mu - Xp*gamma[T];
    
    # Increment of iterations count
    it=it+1;

end


## Output

# Step 2 of the 'Output of Algorithm 1'
gamma = gamma / sum(gamma);  # Enforcing ||gamma||_1 = 1.
return gamma
end


