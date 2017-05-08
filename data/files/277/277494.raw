module LabourDP

using Distributions

export Wages, Production, FiringCost, Demand, LabourPortfolio
export Shave!, fPort, ePort, eFeas, fFeas
export FeasibleChoices, FeasibleQnR, QnRTransition
export Profits, VFI
export ErrorCheck

function Wages(G::Int,Beta::Float64,Alpha::Float64)
    
    """Create the Wage Structure of an Economy.

    Parameters
    ----------
    G : Max Number of Tenure Workers
    Beta : Increase of wage each period of tenure 
    Alpha: Starting wage
    
    Parameters
    ----------
    W : Grid with the Wage of workers for each tenure
    """
    
    TGrid=[0:G-1];
    
    W=TGrid*Beta+Alpha;
    
    return W
    
end

function Production(G::Int,F0::Float64,FG::Float64,FK::Float64,GK::Int)
    
    """Create the Wage Structure of an Economy.
    It fits a second order polynomial for the three parameter values
    and extrapolates for the rest of the tenure values.

    Parameters
    ----------
    G : Max Number of Tenure Workers
    F0: Starting Production 
    FG: Last Tenure Production
    FK: Peak Production
    GK: Tenure of Peak Production
    
    Output
    ----------
    F : Grid with Production of each Tenure worker
    """
    
    V=ones(3,3);
    V[:,2]=[1,GK,G];
    V[:,1]=[1,GK^2,G^2];
    
    Y=[F0,FK,FG];
    
    Coef=V\Y;
    
    TGrid=[1:G];
    
    F=ones(G,1)*Coef[3];
    F+=TGrid*Coef[2];
    F+=TGrid.^2*Coef[1];
    
    return collect(F)
    
end

function FiringCost(G::Int,ϕ::Float64,S::Bool,W::Array{Float64,1})
    
    """Create a grid with the adjustment costs 
    paid by the firm for firing a worker for 
    each level of tenure.

    Parameters
    ----------
    G: Max Number of Tenure Workers
    ϕ: Firing Cost as Share of Wage 
    S: Seniority Dummy
    W: Wage Structure
    
    Output
    ----------
    FC: Grid with the Firing Cost of each Tenure Worker
    """
    
    TGrid=[-1:G-2]*S+1;
    
    FC=TGrid.*(ϕ*W);
    
    return FC
    
end

function Demand(M::Float64,m::Float64,ρ::Float64,N::Int,d::Float64)
    
    """Create the Demand Grid and the
    Markov Transition Matrix of the
    Demand Shock

    Parameters
    ----------
    M: Maximum Demand Shock
    m: Minimum Demand Shock 
    ρ: Autocorrelation
    N: Number of Demand Shocks
    d: Standard Deviation from the Mean to the Max/Min
    
    Output
    ----------
    D   : Grid with Demand Shock Realizations
    Tran: Transition Matrix for the Markov Process of the Demand Shock 
    """
    
    Mean=((M+m)/2);
    
    w=(M-m)/(N-1);
    
    stvy=(M-Mean)/d;
    
    sigma=sqrt(stvy^2*(1-ρ^2));

    D=[m:w:M];
    
    s=D-Mean;
    
    dNorm=Normal(0,sigma);
    
    Tran=zeros(N,N);
    
    for i=1:N
        
        Tran[i,1]=cdf(dNorm,s[1]-ρ*s[i]+w/2);
        
        for j=2:N-1
            
            Tran[i,j]=cdf(dNorm,s[j]-ρ*s[i]+w/2)-cdf(dNorm,s[j]-ρ*s[i]-w/2);
            
        end
        
        Tran[i,N]=1-cdf(dNorm,s[N]-ρ*s[i]-w/2);
        
        # Normalize
        
        Tran[i,:]=Tran[i,:]/sum(Tran[i,:]);
        
    end

    return D, Tran
    
end

function LabourPortfolio(G::Int,N::Int,N_G::Int,f::Function)
    
    """Create all the Labour Portfolios
    a firm can have given the Economy

    Parameters
    ----------
    G  : Generations
    N  : Max Number of Workers hired in a Period 
    N_G: Maximum Number of Workers in last Tenure Group
    f  : Function used to Create the Labour Portfolio
    
    Output
    ----------
    L    : Matrix with S_L Labour Portfolio States with G different types of workers
    """
    
    global L_i=fill(N,G);
    
    L_i[G]=N_G;
    
    L=f(L_i);
    
    return L
    
end

function LabourPortfolio(G::Int,N::Int,M_D::Float64,F_G::Float64,f::Function)
    
    """Create all the Labour Portfolios
    a firm can have given the Economy

    Parameters
    ----------
    G  : Generations
    N  : Max Number of Workers hired in a Period 
    M_D: Maximum Demand
    F_G: Productivity of G Tenure Workers
    f  : Function used to Create the Labour Portfolio
    
    Output
    ----------
    L    : Matrix with S_L Labour Portfolio States with G different types of workers
    """
    
    N_G=ceil(M_D/F_G);
    
    global L_i=fill(N,G);
    
    L_i[G]=N_G;
    
    L=f(L_i);
    
    return L
    
end

function Shave(L::Array{Any,1},F::Array{Float64,1},M_F::Float64)
    
    """Reduce the number of Portfolio by deleting 
    those which are suboptimal due to their production 
    being above the Maximum Demand. (Array Method)

    Parameters
    ----------
    L  : Labour Portfolio
    F  : Production
    M_D: Maximum Production a Portfolio can have 
    (Recommended to be above the maximum Demand in the Economy)
    
    Parameters
    ----------
    L : New Reduced Labour Portfolios
    """
    
    L=L[reshape([L...],length(L[1]),length(L))'*F.<=M_F];
    
    return L
    
end

function ePort(G::Int64)
    
    """Creates a Function which is used to create all
    possible combination of portfolios, given a 
    maximum number of workers for each G years of tenure.
    This Function is used to create all possible portfolios 
    in an economy, and the portfolios a portfolio can change 
    to due to a Quit and Retirement shocks.

    Parameters
    ----------
    G    : Number of Tenure Groups
    
    Output
    ----------
    Portf: Expression with Function that can Evaluate all Possible Portfolios
    
    Function Arguments
    ----------
    L_i  : Vector with the Maximum Number of Workers for each Tenure Group

    """
    
    Portf=Expr(:comprehension);
    
    Portf.args=Array(Any,G+1);
    
    Portf.args[1]=Expr(:vcat);
    
    Portf.args[1].args=Array(Any,G);
    
    for i=2:G+1
            
        x_i=symbol("x_$(i-1)");
        
        Portf.args[i]=Expr(:(=), x_i, Expr(:(:),0,Expr(:ref,:L_i,i-1)));
        Portf.args[1].args[i-1]=x_i;
        
    end
    
    return Portf
    
end

function fPort(G::Int64)
    
    """Creates a Function which is used to create all
    possible combination of portfolios, given a 
    maximum number of workers for each G years of tenure.
    This Function is used to create all possible portfolios 
    in an economy, and the portfolios a portfolio can change 
    to due to a Quit and Retirement shocks.

    Parameters
    ----------
    G    : Number of Tenure Groups
    
    Output
    ----------
    Portf: Function that can Evaluate all Possible Portfolios
    
    Function Arguments
    ----------
    L_i  : Vector with the Maximum Number of Workers for each Tenure Group

    """
    
    Portf2=Expr(:comprehension);
    
    Portf2.args=Array(Any,G+1);
    
    Portf2.args[1]=Expr(:vcat);
    
    Portf2.args[1].args=Array(Any,G);
    
    for i=2:G+1
            
        x_i=symbol("x_$(i-1)");
        
        Portf2.args[i]=Expr(:(=), x_i, Expr(:(:),0,Expr(:ref,:L_i,i-1)));
        Portf2.args[1].args[i-1]=x_i;
        
    end
    
    Portf3=:(L_i->collect(($Portf2)));
    
    Portf= @eval $Portf3;
    
    return Portf
    
end

function eFeas(G::Int64,N::Int64)
    
    """Creates an Expression which is used to create all
    possible combination of portfolios, given a 
    maximum number of workers for each G years of tenure.
    This Function is used to create all possible portfolios 
    in an economy, and the portfolios a portfolio can change 
    to due to a Quit and Retirement shocks.

    Parameters
    ----------
    G    : Number of Tenure Groups
    N    : Max Number of Workers Always available for first year of tenure
    
    Output
    ----------
    Feasf: Expression with Function that can Evaluate all Possible Portfolios
    
    Function Arguments
    ----------
    L_i  : Vector with the Maximum Number of Workers for each Tenure Group

    """
    
    Feasf=Expr(:comprehension);
    
    Feasf.args=Array(Any,G+1);
    
    Feasf.args[1]=Expr(:vcat);
    
    Feasf.args[1].args=Array(Any,G);
    
    Feasf.args[2]=Expr(:(=), :x_1, Expr(:(:),0,N));
    
    Feasf.args[1].args[1]=:x_1;
    
    for i=2:G-1
            
        x_i=symbol("x_$i");
        
        Feasf.args[i+1]=Expr(:(=), x_i, Expr(:(:),0,Expr(:ref,:L_i,i-1)));
        Feasf.args[1].args[i]=x_i;
        
    end
    
    Feasf.args[G+1]=Expr(:(=), :x_G, Expr(:(:),0,Expr(:call,:(+),Expr(:ref,:L_i,G-1),Expr(:ref,:L_i,G))));
    Feasf.args[1].args[G]=:x_G;
    
    return Feasf
    
end

function fFeas(G::Int64,N::Int64)
    
    """Creates a Function which is used to create all
    possible combination of portfolios, given a 
    maximum number of workers for each G years of tenure.
    This Function is used to create all possible portfolios 
    in an economy, and the portfolios a portfolio can change 
    to due to a Quit and Retirement shocks.

    Parameters
    ----------
    G    : Number of Tenure Groups
    N    : Max Number of Workers Always available for first year of tenure
    
    Output
    ----------
    Feasf: Function that can Evaluate all Possible Portfolios
    
    Function Arguments
    ----------
    L_i  : Vector with the Maximum Number of Workers for each Tenure Group

    """
    
    Feasf=eFeas(G,N);
    
    Feasf=:(L_i->collect(($Feasf)));
    
    Feasf= @eval $Feasf;
    
    return Feasf
    
end

function FeasibleChoices(f::Function,L::Array{Any,1})
    
    """Returns the Array with the 
    Index Value of all Feasible future
    choices for Labour Portfolio i.

    Parameters
    ----------
    f : Function used to create Feasible Portfolios
    L : Labour Portfolios
    
    Parameters
    ----------
    R : Array of Indexes of Today Portfolio by the Number of Feasible Portfolios
    C : List with all Feasible Portfolio indexes for each Portfolio
    """
    
    C=Array(Array{Int64,1},length(L))
    
    for i=1:length(L)

        L_i=L[i];
    
        FeasL=f(L_i);
    
        C[i]=findin(L,FeasL);
        
    end
    
    R=deepcopy(C);
    
    for i=1:length(L)
        
        fill!(R[i],i);
        
    end

    return R,C
    
end

function FeasibleQnR(f::Function,L::Array{Any,1})
    
    """Returns the Array with the 
    Index Value of all Feasible future
    Portfolios by Quits and Retirements.

    Parameters
    ----------
    f : Function used to create Feasible Portfolios
    L : Labour Portfolios
    
    Parameters
    ----------
    R : Array of Indexes of Today Portfolio by the Number of Possible Portfolios
    C : Array of Indexes of Possible Portfolios for tomorrow due to QnR
    """
    
    C=Array(Array{Int64,1},length(L))
    
    for i=1:length(L)

        L_i=L[i];
    
        FeasL=f(L_i);
    
        C[i]=findin(L,FeasL);
        
    end
    
    R=deepcopy(C);
    
    for i=1:length(L)
        
        fill!(R[i],i);
        
    end

    return R,C
    
end

function QnRTransition(L::Array{Any,1},F::(Array{Array{Int64,1},1},Array{Array{Int64,1},1}),δ::Float64,γ::Float64)
    
    """Returns a Transition Matrix 
    for shocks in Quit and Retirment

    Parameters
    ----------
    L : Labour Portfolios
    F : List of indexes of all Feasible QnR Shocks
    δ : Probability of a worker Quiting in the last tenure group
    γ : Probability of a worker Retiring in all but the last tenure group
    
    Parameters
    ----------
    Π : Transition Matrix of Quit and Retirment
    """
    
    G=length(L[1]);
    
    Pr=fill(δ,G);
    Pr[G]=γ;
    
    Fr=[F[1]...];
    Fc=[F[2]...];
    
    π=ones(length(Fr));
    
    for i=1:length(Fr)
        
        Chg=L[Fr[i]]-L[Fc[i]];
        
        for j=1:G
        
            π[i]*=pdf(Binomial(L[Fr[i]][j],Pr[j]),Chg[j])
            
        end
        
    end
    
    Π=sparse(Fr,Fc,π,length(L),length(L));
    
    Π[:,1]+=(1-sum(Π,2));       # Correct Rounding Error!
    
    return Π
    
end

function Profits(L::Array{Any,1},D::Array{Float64,1},W::Array{Float64,1},F::Array{Float64,1},FC::Array{Float64,1},M::(Array{Array{Int64,1},1},Array{Array{Int64,1},1}))
    
    """Creates a Sparse Matrix with all 
    the profits for each feasible change 
    in the Labour Portfolio.

    Parameters
    ----------
    L : Labour Portfolio
    D : Demand Shocks 
    W : Wages
    F : Production
    FC: Firing Cost
    M : Matrices with Feasibility Indexes
    
    Output
    ----------
    P : Matrix with Profits for each State
    """
    
    P=similar(M[1],Array{Float64,2});
    
    for i=1:length(L)
        
        P[i]=Array(Float64,length(D),length(M[1][i]));
        
    end
    
    P0=[M[1]...];
    P1=[M[2]...];
    
    Fl=[map(x->x'*F,L)...];
    Wl=[map(x->x'*W,L)...];
    
    f=similar(D);
    w=similar(D);
    fc=similar(D);
    
    for (i,x) in enumerate(P0)
        
        Fcl=(vcat(0,L[x][1:end-1])-L[P1[i]])'*FC;
        
        P[x][:,sum(P0[1:i].==x)]=min(D,fill!(f,Fl[P1[i]]))-fill!(w,Wl[P1[i]])-fill!(fc,Fcl[1]);
        
    end
    
    return P
    
end

function VFI(β::Float64,P::Array{Array{Float64,2},1},D::Array{Float64,2},Q::SparseMatrixCSC{Float64,Int64},M::Array{Array{Int64,1},1})
    
    """Solve the Dynamic Problem by 
    using Value Function Iteration.

    Parameters
    ----------
    β : Discount Factor
    P : Profits
    D : Transition Matrix of Demand Shocks 
    Q : Transition Matrix of
    M : Matrices with Feasibility Indexes
    
    Output
    ----------
    V : Value Function
    G : Optimal Policy
    """
    
    S_L=length(P);
    S_D=size(D,1);
    
    V0=zeros(S_D,S_L);
    V=ones(S_D,S_L);
    
    while norm(V-V0)>eps(Float32)
        
        V0=deepcopy(V);
        
        Vt=β*D*V0*Q';
        
        for i=1:S_L, j=1:S_D
            
            V[j,i]=max(P[i][j,:]+Vt[j,M[i]]...);
            
        end
        
    end
    
    G=zeros(Int,S_D,S_L);
    
    Vt=β*D*V0*Q';
    
    for i=1:S_L, j=1:S_D
        
        g=findmax([P[i][j,:]+Vt[j,M[i]]...]);
            
        G[j,i]=M[i][g[2]];
            
    end
    
    return V, G
    
end

function ErrorCheck(x;β=0.9,N=3,G=3,α₁=0.0,β₁=0.0,Ĝ=2,ϕ=0.0,S=true,δ=0.5,γ=0.5,M_D=10.0,m_D=5.0,ρ=0.0,N_D=2,d=3.0)
    
    """Create the Wage Structure of an Economy.

    Parameters
    ----------
    β  : Firm's intertemporal discount rate
    G  : Number of different heterogenous tenure workes  
    N  : Max Number of Workers hired during one period
    α₁ : Entry level wage  
    β₁ : Period Wage Increase with tenure 
    Ĝ  : Tenure for Peaked Production
    ϕ  : Percentage of Wage Paid as Firing Cost 
    S  : Boolean for Tenure increase in Firing Cost
    δ  : Probability of a worker Quiting in the last tenure group  
    γ  : Probability of a worker Retiring in all but the last tenure group  
    M_D: Maximum Demand Shock 
    m_D: Minimum Demand Shock 
    ρ  : Autocorrelation of Demand Shock  
    N_D: Number of Demand Shocks  
    d  : Standard Deviation from the Mean to the Max/Min 
    
    Parameters
    ----------
    Error : Error Message
    """
    
    0<β<1           || error("\u03B2 \u2209 (0,1)");                              # Check if β is between 0 and 1
    
    isa(N,Int)      || error("N is not and Interger");                            # Check if N is an Interger
    isa(G,Int)      || error("G is not and Interger");                            # Check if G is an Interger
    N>0             || error("N \u226F 0");                                       # Check if N is greater than zero  
    G>0             || error("G \u226F 0");                                       # Check if G is greater than zero
    
    α₁>=0           || error("Starting Wage is Negative");                        # Check if Wages are negative
    α₁+(β₁*(G-1))>=0|| error("Slope of Wage Function creates Negative Wages");    # Check if Wages are negative
    
    isa(Ĝ,Int)      || error("G\u0302 is not an Interger");                       # Check if Ĝ is an Interger
    1<Ĝ<G           || error("G\u0302 \u2209 (0,G)");                             # Check if Ĝ is a Valid Tenure Year
    
    ϕ>=0            || error("Firing Cost must not be negative");                 # Check if ϕ>0
    isa(S,Bool)     || error("Seniority (S) is not Boolean");                     # Check S is Boolean
    
    0<=δ<=1         || error("\u03B4 \u2209 [0,1]");                              # Check if δ is between 0 and 1
    0<=γ<=1         || error("\u03B3 \u2209 [0,1]");                              # Check if γ is between 0 and 1
    
    -1<ρ<1          || error("\u03C1 \u2209 (-1,1) No Unit Root Allowed");        # Check if ρ has a Unit Root
    M_D>m_D         || error("Maximum Demand is not larger than Minimum Demand"); # Check of M_D>m_D
    m_D>0           || error("Minimum Demand must be Positive");                  # Check of M_D>m_D
    N_D>1           || error("Number of Demand Shocks must be larger than 1");    # Check if N_D>1
    isa(N_D,Int)    || error("Number of Demand Grid is not an Interger");         # Check N_D is Interger
    d>0             || error("Standard Deviation of Max is not Positive");        # Check if d>0
    
end

end
