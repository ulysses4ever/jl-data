println("****************************************************")
println("************** Single tree asset pricing **************")
println("****************************************************")

# single tree case

# by monte calro

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
x=linspace(0,1,xgridsize);


# prepare variables for integration by discretization

# Monte Calro

N=1000;


##
# pricing function iteration part


Pold1=2;
Pnew1=1;
diff=10;
iteration=0;
while diff > .01
    print(".")
    iteration=iteration+1;
        Pnext=zeros(N,1);
        for i=1:N

            randep1=1+mu+sigma*randn(1,1);
            ep1=randep1[1,1]
            Pnext[i,1] = beta * ep1  ^(-gamma) * ep1 * ( 1+Pold1) ;

        end
        Pnew1=sum(Pnext)/N;
    diff=norm(Pnew1-Pold1,inf);
    #println("difference=",diff)
    Pold1=Pnew1;
end
P1=Pnew1;

println(" ")
println("iteration:", iteration)






#----------------------------------------------------------
t=toc();
println("running time:", t )
println("Eqm price: ", P1 )
























