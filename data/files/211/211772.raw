# Ian Martin(2013)EMCA
# replication of figures

# Monte Calro

tic()

require("price.jl")

# parameters which are not our focus
beta=1/1.05;
mu=.02+1;
sigma=sqrt(.1);

# parameters which I want to change
gamma=1;
s=.5; # share


# state variable share
xgridsize=100;
xmin=.01;
xmax=.99
x=linspace(xmin,xmax,xgridsize);

# Monte Calro iteration

N=1000;
alpha=0;

# pricing function iteration part

# asset 1

println("*****************************************")
println("Pricing function for asset 1 iteration starts")
println("*****************************************")

Pold1=ones(size(x))*20;
Pnew1=ones(size(x));
diff=10;
iteration=0;
while diff > .001
    #print(".")
    iteration=iteration+1;
    for k=1:xgridsize
        Pnext=zeros(N,1);
        for i=1:N
            randep1=1+mu+sigma*randn(1,1); ep1=randep1[1,1];
            randep2=1+mu+sigma*randn(1,1); ep2=randep2[1,1];
            x_prime=ep1 * x[k,1] / (x[k,1] * ep1 + (1-x[ k,1 ] )*ep2  );
            Pnext[i,1] = beta * (  x[ k,1 ] *  ep1 + (1-  x[ k,1 ]  ) * ep2   )^(-gamma) * ep1 * ( 1+Price(x_prime,Pold1,x) );
        end

        Pnew1[k,1]=sum(Pnext)/N;
   end

    diff=max(abs(Pnew1-Pold1));
#println("check")
    println("diff: ", diff)
    Pold1[:,1]=alpha*Pold1[:,1] + (1-alpha) * Pnew1[:,1];
end


P1=Pnew1;
println("\niteration :#5.0f times\n",iteration)

println("*****************************************")
#println("Pricing function for asset 2 iteration starts")





#----------------------------------------------------------
t=toc();
println("running tine: ",t)

























