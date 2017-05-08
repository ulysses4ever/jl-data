module ParallelDP

export LiLarge!, FeasLoopP, PossLoopP, Rows!

function LiLarge!(Li::BitArray{1},L1::Array{Int64,1},L2::Array{Int64,1})
    
    """Return a boolean vector saying if the change of
    portfolio is feasible (ie if tomorrow number of
    workers is larger than todays

    Parameters
    ----------
    Li : Ready Boolean Vector
    L1 : Todays Labour Portfolio
    L2 : Vector with all possible portfolios
    
    Output
    ----------
    Li : Filled Boolean Vector
    """
    
    for i=1:length(Li)
        
        Li[i]=L1[rem(i-1,length(L1))+1]>=L2[i];
        
    end
    
end

function FeasLoopP(L::Array{Any,1},L2::Array{Int64,1})
    
    """Find the indexes of the Feasible Portfolios
    for each current Portfolio

    Parameters
    ----------
    L : Labour Portfolio
    L2 : Vector with all possible portfolios
    
    Output
    ----------
    C : List with all Feasible Portfolio indexes for each Portfolio
    """
    
    C=Array(Array{Int64,1},length(L));
    
    Li=BitArray(length(L2));
    
    for i=1:length(L)
        
        LiLarge!(Li,vcat(L[i][1:end-2],sum(L[i][end-1:end])),L2);       
        
        C[i]=find(prod(reshape(Li,length(L[1])-1,div(length(Li),length(L[1])-1)),1));       
        
    end
    
    return C
    
end

function PossLoopP(L::Array{Any,1},L2::Array{Int64,1})
    
    """Find the indexes of the Possible Portfolio QnR
    for each current Portfolio

    Parameters
    ----------
    L : Labour Portfolio
    L2 : Vector with all possible portfolios
    
    Output
    ----------
    C : List with all Feasible Portfolio indexes for each Portfolio
    """
    
    C=Array(Array{Int64,1},length(L));
    
    Li=BitArray(length(L2));
    
    for i=1:length(L)
        
        LiLarge!(Li,L[i],L2);   
        
        C[i]=find(prod(reshape(Li,length(L[1]),div(length(Li),length(L[1]))),1));       
        
    end
    
    return C
    
end

function Rows!(R::Array{Array{Int64,1},1})
    
    """Give the Indexes for Todays Portfolio
    for each feasible Portfolio Change. It does
    it by filling the Feasible portfolio Matrix
    with its coloumn value

    Parameters
    ----------
    R : Empty Array of Indexes of Today Portfolio by the Number of Feasible Portfolios
    
    Output
    ----------
    R : Array of Indexes of Today Portfolio by the Number of Feasible Portfolios
    """
    
    for i=1:length(R)
        
        fill!(R[i],i);                     
        
    end
    
end

end
