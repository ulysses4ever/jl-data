module LabourDPOld

using Distributions

export LabourPortfolio, LabourPortfolio2, LabourPortfolioT
export TupleLabour, Shave, FuncTextOld, fFeas, fPort
export FeasibleChoices, FeasibleQnR

function LabourPortfolio(G::Int,N::Int,M_D::Float64,F_G::Float64)
    
    """Create all the Labour Portfolios
    a firm can have given the Economy

    Parameters
    ----------
    G  : Generations
    N  : Max Number of Workers hired in a Period 
    M_D: Maximum Demand
    F_G: Productivity of G Tenure Workers
    
    Output
    ----------
    L    : Matrix with S_L Labour Portfolio States with G different types of workers
    SizeL: Size of the State Space of Labourt Portfolios
    """
    
    N_G=ceil(M_D/F_G);
    
    LG=[0:1:N_G];
    Li=[0:1:N];
    
    SizeL=convert(Int,(N+1)^(G-1)*(N_G+1));
    
    L=zeros(Int,SizeL,G);
    
    Reps=div(SizeL,(N+1));
    
    for i=1:G-1
        
        innr=(N+1)^(i-1);
        outr=div(SizeL,(N+1)^i);
        
        L[:,i]=repeat(Li,inner=[innr],outer=[outr]);
        
    end
    
    innr=convert(Int,SizeL/(N_G+1));
    
    L[:,G]=repeat(LG,inner=[innr],outer=[1]);
    
    return L', SizeL
    
end

function LabourPortfolio2(G::Int,N::Int,M_D::Float64,F_G::Float64,f::Expr)
    
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
    SizeL: Size of the State Space of Labourt Portfolios 
    """
    
    N_G=ceil(M_D/F_G);
    
    global L_i=fill(N,G);
    
    L_i[G]=N_G;
    
    @eval L=collect($f);
    
    SizeL=length(L);
    
    return L, SizeL
    
end

function TupleLabour(L::Array{Int64,2},S::Int)
    
    """Convert the Labour Matrix into a Tuple

    Parameters
    ----------
    L : Matrix with Labour Portfolios
    S : Number of differente Labour Portfolios
    
    Output
    ----------
    Lt: Tuple with Labour Portfolios
    """
    
    Lt=ntuple(S,x->L[:,x]);
    
    return Lt
    
end

function LabourPortfolioT(G::Int,N::Int,M_D::Float64,F_G::Float64)
    
    """Create all the Labour Portfolios
    a firm can have given the Economy

    Parameters
    ----------
    G  : Generations
    N  : Max Number of Workers hired in a Period 
    M_D: Maximum Demand
    F_G: Productivity of G Tenure Workers
    
    Output
    ----------
    L    : Tuple with S_L Labour Portfolio States with G different types of workers
    SizeL: Size of the State Space of Labourt Portfolios 
    """
    
    N_G=ceil(M_D/F_G);
    
    LG=[0:1:N_G];
    Li=[0:1:N];
    
    SizeL=convert(Int,(N+1)^(G-1)*(N_G+1));
    
    L=zeros(Int,SizeL,G);
    
    Reps=div(SizeL,(N+1));
    
    for i=1:G-1
        
        innr=(N+1)^(i-1);
        outr=div(SizeL,(N+1)^i);
        
        L[:,i]=repeat(Li,inner=[innr],outer=[outr]);
        
    end
    
    innr=convert(Int,SizeL/(N_G+1));
    
    L[:,G]=repeat(LG,inner=[innr],outer=[1]);
    
    L=TupleLabour(L',SizeL);
    
    return L, SizeL
    
end

function Shave(L::(Any...),F::Array{Float64,1},M_D::Float64)
    
    """Reduce the number of Portfolio by deleting 
    those which are suboptimal due to their production 
    being above the Maximum Demand. (Tuple Method)

    Parameters
    ----------
    L  : Labour Portfolios (Tuple)
    F  : Productivity
    M_D: Maximum Demand
    
    Parameters
    ----------
    NewL : New Reduced Labour Portfolios (Tuple)
    SizeL: New Size of States of the Labour Portfolios
    """

    MaxF=M_D+maximum(F);
    
    NewL=L[reshape([L...],length(L[1]),length(L))'*F.<=MaxF];
    
    SizeL=length(NewL);
    
    return NewL, SizeL
    
end

function FuncText(f::Expr,G::Int)
    
    """Create a Text to display mathematically
    the function created by fFeas or fPort

    Parameters
    ----------
    f   : Function to Display
    G   : Number of Variables in the Function
    
    Output
    ----------
    Text: String used to Display Function

    """
    
    Text="[[";

    for i=1:G-1
    
        Param=f.args[1].args[i];
        Text=string(Text,Param,",");
    
    end

    Param=f.args[1].args[G];
    Text=string(Text,Param,"]~for~");

    for i=1:G-1
    
        Param=f.args[i+1].args[1];
        ParamN=f.args[i+1].args[2].args[2];
        Text=string(Text,Param,"=0:",ParamN,",~");
    
    end

    Param=f.args[G+1].args[1];
    ParamN=f.args[G+1].args[2].args[2];
    Text=string(Text,Param,"=0:",ParamN,"]");
    
    return Text
    
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
            
        x_i=symbol("x_$(i-1)");
        
        Feasf.args[i+1]=Expr(:(=), x_i, Expr(:(:),0,Expr(:ref,:L_i,i-1)));
        Feasf.args[1].args[i]=x_i;
        
    end
    
    Feasf.args[G+1]=Expr(:(=), :x_G, Expr(:(:),0,Expr(:call,:(+),Expr(:ref,:L_i,G-1),Expr(:ref,:L_i,G))));
    Feasf.args[1].args[G]=:x_G;
    
    return Feasf
    
end

function FeasibleChoices(f::Expr,L::Array{Any,1})
    
    """Returns the Array with the 
    Index Value of all Feasible future
    choices for Labour Portfolio i.

    Parameters
    ----------
    f : Function used to create Feasible Portfolios
    L : Labour Portfolios
    
    Parameters
    ----------
    H : List with all Feasible Portfolio indexes for each Portfolio
    """
    
    H=Array(Array{Int64,1},length(L))
    
    for i=1:length(L)

        global L_i=L[i];
    
        @eval FeasL=collect($f);
    
        H[i]=findin(L,FeasL);
        
    end

    return H
    
end

function FeasibleQnR(f::Expr,L::Array{Any,1})
    
    """Returns the Array with the 
    Index Value of all Feasible future
    Portfolios by Quits and Retirements.

    Parameters
    ----------
    f : Function used to create Feasible Portfolios
    L : Labour Portfolios
    
    Parameters
    ----------
    H : Array of Indexes of Possible Portfolios for tomorrow due to QnR
    """
    
    H=Array(Array{Int64,1},length(L))
    
    for i=1:length(L)

        global L_i=L[i];
    
        @eval FeasL=collect($f);
    
        H[i]=findin(L,FeasL);
        
    end

    return H
    
end

end
