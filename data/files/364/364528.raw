module LDPC

export minvmod, bec, bsc, bdc, biawgn, ldpcH, calc_lamrho, calc_erasure_thresh, calc_H, calc_G, isCW, lc_end, swap_row, swap_col,calc_RU, ldpcRUenc, ell,bec_MPD, biawgn_MPD,bsc_MPD,calc_girth,calc_mcycle




using Distributions

#############################################################
#calculates matrix inverse modulo N
#############################################################
function minvmod{T<:Integer}(Arr::Array{T,2},N)
    A=copy(Arr)
    n=size(A)[1]
    Ainv=eye(T,n)
    for i=1:n
        k=i
        isz=true
        while isz 
            if gcd(A[k,i],N) == 1
                isz=false
                if k!=i
                    A[i,:],A[k,:]=A[k,:],A[i,:]
                    Ainv[i,:],Ainv[k,:]=Ainv[k,:],Ainv[i,:]
                end
            else
                k+=1
            end
            if k>n
                return false
            end
                
        end
        if N != 2
            tem=invmod(A[i,i],N)
            for j=1:n
                A[i,j]   =convert(T,mod(tem*A[i,j],N)) 
                Ainv[i,j]=convert(T,mod(tem*Ainv[i,j],N)) 
            end
        end
        
        for j=union(1:i-1,i+1:n)
            if A[j,i] != convert(T,0)
                tem=A[j,i]
                for k=1:n
                    A[j,k]   =convert(T,mod(A[j,k]-tem*A[i,k],N))
                    Ainv[j,k]=convert(T,mod(Ainv[j,k]-tem*Ainv[i,k],N))
                end
          
            end
        end
    
    end
    return Ainv
end

#########################################################################
#######Channels##########################################################

#Binary Erasure Channel
function bec(p::Float64,cws)
    n=length(cws)
    out=zeros(Float64,n,1)
    D=rand(Bernoulli(p),n)
    for i=1:n
        if D[i]==1
            out[i]=2
        else
            out[i]=cws[i]
        end
    end
    return out
end

#Binary Symmetric Channel
function bsc(p::Float64,cws)
    n=length(cws)
    out=zeros(Float64,n,1)
    D=rand(Bernoulli(p),n)
    for i=1:n
        if D[i]==1
            out[i]=mod(cws[i]+1,2)
        else
            out[i]=cws[i]
        end
    end
    return out
end



#Binary Deletion Channel
function bdc(d::Float64,cws,dpos)
    n=length(cws)
    D=rand(Bernoulli(d),n)
    L=n-sum(D)
    out=zeros(Float64,L,1)
    j=1
    for i=1:n
        dpos[i]=D[i]
        if D[i]==0
            out[j]= cws[i]
            j+=1    
        end
    end
        
    return out
end

#BIAWGN Channel , Note this take 0s and 1s and maps them to 1s and -1s, then adds noise
function biawgn(var::Float64,cws)
    n=length(cws)
    out=zeros(Float64,n)
    out=rand(Normal(0,sqrt(var)),n)
    for i=1:n
        out[i]+=(1.0-2*cws[i])
    end
    return out
end


##############################################################################
##############################################################################
####LDPC Type and Functions
##############################################################################
#Data Structure to hold LDPC Code for quick message passing decoding
type ldpcH
    n::Int #number of variable nodes 
    k::Int 
    m::Int #number of check nodes
    mdV::Int
    mdC::Int
    dV::Array{Uint8,1}
    dC::Array{Uint8,1}
    CtoV::Array{Uint32,3}
    VtoC::Array{Uint32,3}
    G::Array{Uint8,2} #T can store the generator matrix if desired
    phin::Array{Uint8,2} #phin can store phi^(-1) if in RU form
    ruperm::Array{Int64,1} #stores column permutation if in RU form
    htype::ASCIIString #what special form H is in( i.e. RU, LU, null)
    isG::Bool #whether the generator matrix has been calculated
    #CtoV(i,cnt,1)=j jth variable node connected to check node i
    #CtoV(i,cnt,2)   such that VtoC[ CtoV[i,cnt,1] , CtoV(i,cnt,2) ,1] = i
    #vice-versa for VtoC
    
    
    
    function ldpcH()
        T=new()
        T.n=0
        T.k=0
        T.m=0
        T.mdV=0
        T.mdC=0
        T.htype="null"
        T.isG==false
        
        return T
    end
    
    #generates a structure given the parity check Matrix H
    function ldpcH(H::Array) 
        T=new()
        T.n=size(H)[2]
        T.m=size(H)[1]
        T.k=T.n-T.m

        T.dV=zeros(Uint8,T.n)
        T.dC=zeros(Uint8,T.m)
        
        
        for i=1:T.n
            T.dV[i]=sum(H[:,i])
        end
        for i=1:T.m
            T.dC[i]=sum(H[i,:])
        end
        
        T.htype="null"
        T.isG==false
      
        T.mdC=maximum(T.dC)
        T.mdV=maximum(T.dV)
        
        
        
        T.CtoV=zeros(Uint32,T.m,T.mdC,2)
        T.VtoC=zeros(Uint32,T.n,T.mdV,2)
        #CtoV(i,cnt,1)=j jth variable node connected to check node i
        #CtoV(i,cnt,2)   such that VtoC[ CtoV[i,cnt,1] , CtoV(i,cnt,2) ,1] = i
        #vice-versa for VtoC
        
        for i=1:T.m #check node i
            count=1
            for j=1:T.n 
                if H[i,j]==1 #checking variable node j
                    T.CtoV[i,count,1]=j
                    temm=sum(H[1:i,j])
                    T.VtoC[j,temm,2]=count
                    count+=1
                end
            end
        end
        
         for j=1:T.n
            count=1
            for i=1:T.m
                if H[i,j]==1
                    T.VtoC[j,count,1]=i
                    temm=sum(H[i,1:j])
                    T.CtoV[i,temm,2]=count
                    count+=1
                end
            end
        end
        
        return T;
    end
    
    #randomly generates an LDPC code with given variable and check node degree distributions
    #does not always succeed, so might need ot be called multiple times
    #it works by randomly choosing variable node, based on the number of uninitialized edges
    #then we randomly choose a check node based on the number of uninitialized edges
    # but we make sure it does not result in a 4-cycle
    #it returns false if there are any issues, like having an even variable node degree, etc...
    
    function ldpcH(dV,dC) 
        T=new()
        T.n=size(dV)[1]
        T.m=size(dC)[1]
        T.k=T.n-T.m
        T.dV=copy(dV)
        T.dC=copy(dC)
  
        T.mdC=maximum(T.dC)
        T.mdV=maximum(T.dV)
        T.CtoV=zeros(Uint32,T.m,T.mdC,2)
        T.VtoC=zeros(Uint32,T.n,T.mdV,2)
        #CtoV(i,cnt,1)=j jth variable node connected to check node i
        #CtoV(i,cnt,2)   such that VtoC[ CtoV[i,cnt,1] , CtoV(i,cnt,2) ,1] = i
        #vice-versa for VtoC
        T.htype="null"
        T.isG==false
        #############randomly add edges and check if they are valid##############
        cnt=0
        pv=zeros(Int64,T.n,1)
        Cc=zeros(Int64,T.m,1)
        pc=zeros(Int64,T.m,1)
        #first we come up with a probability distribution(actually more like a CDF) for the check nodes,
        pv[1]=dV[1]
        for i=2:T.n
            pv[i]=dV[i]+pv[i-1]
        end
        
        #########################################################################
        totedges=pv[T.n] #T is the total # of edges to add
        ttem=zeros(Int64,T.n,1)
        i=1
        vn=0
        
        while i <= totedges
            rnv= rand(1:pv[T.n])  #first we choose a random edge to add
            nh=true
        
            for j=1:T.n   #here we randomly choose a variable node, by going through pv
                if rnv <= pv[j] && nh
                    vn=j 
                    nh=false
                    pv[j]-=1
                elseif rnv <= pv[j] && ~nh
                    pv[j]-=1
                end
            end
       
        
            tem=0
            for j=setdiff((1:T.m),T.VtoC[vn,:,1]) #cycle through all check nodes not connected to vn to find possible check nodes
                if (T.CtoV[j,dC[j],1] == 0) #make sure the check node does not have its max # of edges 
                    pc[j]=dC[j]-Cc[j]+tem
                    tem=pc[j]
                else
                    pc[j]=tem
                end
            end
            
            if pc[T.m] <  1
                println("We were unable to find a successful checknode, err(1)")
                return false
            end
            scn=true
            while scn #here we randomly select check nodes then check if they are 'good'
                rnc= rand(1:pc[T.m])
                j=1
                while rnc > pc[j]
                    j+=1
                end
                cn=j #now we have choosen a check node and must check if it is gives girth > 4
                gcn=true
                j=1
                cnt=1
                
                if T.VtoC[vn,1] != 0 #if vn is connected to any check nodes, we must check whether adding cn will introduce a 4-cycle
                    while j <= dV[vn]
                    
                        if T.VtoC[vn,j] == 0
                            cnt=j
                            j=dV[vn]+1
                        elseif length(setdiff(intersect(T.CtoV[cn,:,1], T.CtoV[T.VtoC[vn,j],:,1]  ),0))>0 #convoluted but works for now...
                            gcn=false
                            j=dV[vn]+1
                        else
                            j+=1
                        end
                    end 
                end
                
                
                
                if gcn==true #i.e. adding cn did not result in a 4-cycle
                    T.VtoC[vn,cnt,1]=cn
                    
                    Cc[cn]+=1
                    T.VtoC[vn,cnt,2]=Cc[cn]
                    T.CtoV[cn,Cc[cn],1]=vn
                    T.CtoV[cn,Cc[cn],2]=cnt
                    scn=false
                else
                    if cn==1
                        tem=pc[1]
                    else
                        tem=pc[cn]-pc[cn-1]
                    end
                    for j=cn:T.m
                        pc[j]-=tem
                    end
                    if pc[T.m] <  1
                        println("We were unable to find a successful check node resulting in a girth >4 code")
                        return false
                    end
                
                end
            
            end      
            i+=1
        end
        ##########################################################################
        return T;
    end

    
    #initialize LDPC structure using alist file format
    #http://www.inference.phy.cam.ac.uk/mackay/codes/alist.html
    #note: T does not guarantee that the rows are linearly independent.
    
    function ldpcH(fname::ASCIIString) 
        f=open(fname)
        a=readline(f)
        lar=readdlm(IOBuffer(a),Int)
        T=new()
        T.n=lar[1]
        T.m=m=lar[2]
        T.k=T.n-T.m
        
        T.dV=zeros(Uint8,T.n)
        T.dC=zeros(Uint8,T.m)

        a=readline(f)
        lar=readdlm(IOBuffer(a),Int)
        T.mdC=maximum(lar[2])
        T.mdV=maximum(lar[1])
        
        
        T.CtoV=zeros(Uint32,T.m,T.mdC,2)
        T.VtoC=zeros(Uint32,T.n,T.mdV,2)
        
        
        a=readline(f)
        lar=readdlm(IOBuffer(a),Int)
        for i=1:T.n
            T.dV[i]=lar[i]
        end
        
        
        a=readline(f)
        lar=readdlm(IOBuffer(a),Int)
        for i=1:T.m
            T.dC[i]=lar[i]
        end
                
        
        chkcnts=zeros(Int64,T.m,1) #keeps track of number of variable nodes connected in loop
        for i=1:T.n #references variable nodes
            a=readline(f)
            lar=readdlm(IOBuffer(a),Int)
            ns=T.dV[i]
            for j=1:ns #cycle through all connected check nodes
                
                chkcnts[lar[j]]+=1
                
                T.VtoC[i,j,1]=lar[j]
                T.VtoC[i,j,2]=chkcnts[lar[j]]
                
                
                T.CtoV[lar[j],chkcnts[lar[j]],1]=i
                T.CtoV[lar[j],chkcnts[lar[j]],2]=j
                   
            end
        
        end
        
        close(f)
        return T
    end
   
end

#ell function in Rudiger/Urbanke paper to determine necessary girth of Tanner graph
function ell(dv,dc,n)
    return (log(n)-log((dv*dc-dv-dc)/(2.0*dc)))/log((dc-1.0)*(dv-1.0))
    
end

##########################################################################

function calc_mcycle(LH::ldpcH,sv::Int64,maxc::Int64)
    #LH is a parity check matrix
    #sv is a source variable node
    #maxc is the maximum cycle length for which to search.
    n=LH.n
    m=LH.m
    
    #first n entries are variable node, 
    #next m entries are check nodes
    R=zeros(Int64,n+m) # stores two stages of traversing graph
    S=zeros(Int64,n+m) 
    Prnt=zeros(Int64,n+m) #parent node
    Dsv=zeros(Int64,n+m)
    mcyl=Inf #minimum cycle size 
    cylend=zeros(Int64, 2)#,cycle endpoint
    Nx=zeros(Int64,max(LH.mdC,LH.mdV)) #neighbors
    nxl=0
    R[sv]=1
    Prnt[sv]=-1

    Dsv[sv]=0
    x=0 # this is the current node
    isvar=true #this keeps track whether we are looking at variable or check nodes
    #it is either 0 or n
    sumr=sum(R[1:n])
    while sumr > 0
        if isvar #here we find an x in R
            i=1
            while i<=n #first we clear all entries in R due to variable nodes, then move on to check nodes
                if R[i]==1
                    x=i
                    S[i]=1
                    R[i]=0
                    i=n+1
                    Nx[:]=0
                    nxl=LH.dV[x]
                    Nx[1:nxl]=round(Int64,LH.VtoC[x,1:nxl,1])+n
                else
                    i+=1
                end
            end
        else
            i=n+1
            while i<=n+m
                if R[i]==1
                    x=i
                    S[i]=1
                    R[i]=0
                    i=n+m+1
                    Nx[:]=0
                    nxl=LH.dC[x-n]
                    Nx[1:nxl]=round(Int64,LH.CtoV[x-n,1:nxl,1])
                else
                    i+=1
                end
            end
        end
        
        if maxc >=4
            if  Dsv[x]+1 > maxc
                return maxc
            end
             
        end
        
        for y in setdiff(Nx[1:nxl],Prnt[x])
            
            if S[y]==0
                Prnt[y]=x
                Dsv[y]=Dsv[x]+1
                R[y]=1
                
            else
                tem=mcyl
                mcyl=round(Int64,min(mcyl,Dsv[x]+Dsv[y]+1))
                
                if tem != mcyl
                    cylend[1]=y
                    cylend[2]=x
                end
                if mcyl == 4 #if we find a 4-cycle, time to stop.
                    R[:]=0
                    break
                end
            end
        
        end
        
        if isvar
            sumr=sum(R[1:n])
            
        else
            sumr=sum(R[n+1:n+m])
        end
        
        if sumr==0
            isvar= ~isvar
            if isvar
                sumr=sum(R[1:n])
            else
                sumr=sum(R[n+1:n+m])
            end
        end
        
    end
    
    cycle=zeros(Int64,mcyl)
    tem=cylend[1]    
    for i=Dsv[cylend[2]]+2:(mcyl)
        cycle[i]=tem
        tem=Prnt[tem]
    end
    
    tem=cylend[2]
    for i=Dsv[tem]+1:-1:1
        cycle[i]=tem
        tem=Prnt[tem]
    end
    
    return cycle
    
end
function calc_mcycle(LH::ldpcH,sv::Int64)
    return calc_mcycle(LH,sv,LH.n)
    
end



function calc_girth(LH::ldpcH)
    n=LH.n
    cgirth=n*ones(Int64,LH.n+LH.m) # stores current shortest path for each variable node 
    minc=Inf
    for i=1:n
        tem=calc_mcycle(LH,i,cgirth[i])
        tg=length(tem)
        if tg != 1
        for j=1:tg
            cgirth[tem[j]]=min(tg,cgirth[tem[j]])
        end
        
        minc=min(tg,minc)
        end
    end
    return convert(Int64,minc)
    
end

#####calculate lambda and rho, i.e. degree distributions
function calc_lamrho{T<:Integer}(dV::Array{T,1})
    cur=1
    loc=1
    n=length(dV)
    tem=sort(dV)
    for i=2:n
        if tem[i]!= tem[i-1]
            cur+=1
        end
    end
    lam=zeros(Float64,cur,2)
    cur=1
    loc=1
    for i=2:n
        if tem[i] == tem[i-1]
            cur+=1
            if i==n
                lam[loc,1]=cur/n
                lam[loc,2]=tem[i-1]-1
            end
        else
            lam[loc,1]=cur/n
            lam[loc,2]=tem[i-1]-1
            cur=1     
            loc+=1
            
            if i==n
                lam[loc,1]=1/n
                lam[loc,2]=tem[i]-1
            end
        end
    end
    return lam
end

#calculates the erasure threshold given the degree distribution (lam,rho) 
# M. Luby, M. Mitzenmacher, and A. Shokrollahi, 
#“Analysis of random processes via and-or tree evaluation,” in Proc. 9th Annu. ACM-SIAM
# Symp. Discrete Algorithms, 1998, pp. 364–373.
#lam(x)= sum_{i >= 2}^{d_v(max) } lam_i x^{i-1}
#rho(x)= sum_{i >= 2}^{d_c(max) } pho_i x^{i-1}
#where lam_i and rho_i denote the fraction of edges incident to variable and check nodes with degree i, respectively
function calc_erasure_thresh(lam::Array{Float64,2},rho::Array{Float64,2},maxit,maxl)
    #lam[j,1]*x^{lam[j,2]} corresponds to lam_i*x^{i-1}
    #i.e. i-1= lam[j,2] and lam_i=lam[j,1], likewise for rho
    lv=size(lam)[1]
    lc=size(rho)[1]
    eps=1e-10
    lbound=0.0
    rbound=1.0
    mid=0.5
    alc=0.0
    alp=0.0
    tem=0.0
    inc=true
    for i=1:maxit
        cnt=0
        alp=mid
        alc=alp
        while alc > eps &&  cnt < maxl 
            
            tem=0.0
            for k=1:lc
                tem+=rho[k,1]*(1.0-alp)^(rho[k,2])
            end
            alc=0.0
            for k=1:lv
                alc+=lam[k,1]*(1.0-tem)^(lam[k,2])
            end
            alc*=mid   
            cnt+=1
            #println("$alc $(alp-alc)")
            if  alc >= alp
                cnt=maxl
            elseif cnt != maxl && alc > eps
                alp=alc
            end
           
        end
        if  alc > eps
            inc=false
        else
            inc=true
        end
        if inc
            lbound=mid
            mid=(lbound+rbound)/2.0
        else
            rbound=mid
            mid=(lbound+rbound)/2.0
        end
        
    end
    return mid
    
end



#given a ldpcH type, it returns the associated parity check matrix as a mxn array
function calc_H(LH::ldpcH)
    H=zeros(Uint8, LH.m,LH.n)
    for i=1:LH.n
        for j=1:LH.dV[i]
            H[LH.VtoC[i,j,1],i]=1     
        end 
    end
    return H
end
    



#finds a generator matrix for a given parity check matrix
function  calc_G{T<:Integer}(H::Array{T,2})
    #H is a mxn Parity check matrix
    #returns the generator Matrix G which is nxk, k=n-m
    m=size(H)[1]
    n=size(H)[2]
    k=n-m
    G=zeros(T,n,k)
    Hp=copy(H)
    colops=zeros(Int64,2*n,2)
    ncolo=0
    
    for i=m:-1:1#put H into systematic form , i references the current row
        findl=true
        j=i #iterates over rows
        col=n-m+i #references the column such that Hp[i,col] should eventually be the only 1 in that column
        kk=col #iterates over columns
        
        ######################################################################        
        while findl #search for a column then row with a 1 in the ith position
   
            if Hp[j,kk] == 1 
                findl=false
                if kk != col
                    ncolo+=1
                    colops[ncolo,1]=kk
                    colops[ncolo,2]=col 
                    for ii=1:m
                        tem=Hp[ii,kk]
                        Hp[ii,kk]=Hp[ii,col]
                        Hp[ii,col]=tem
                    end
                    kk=col        
                end
                
                
            elseif Hp[j,kk] ==0 
                if kk>1 #go to the left columnwise, as long as we are not in the first column
                    kk-=1
                    elseif j>1 #got up rowwise and 
                    kk=col    
                    j-=1
                else
                    return false
                end              
            else
                return false
            end
        end
        ######################################################################
        #swap row vectors
        if i != j
            for ii=1:col
                tem=Hp[i,ii]
                Hp[i,ii]=Hp[j,ii]
                Hp[j,ii]=tem
            end
        end
        for ii=union(1:(i-1),(i+1):m)
            if Hp[ii,col]==1     
                for iii=1:col
                    Hp[ii,iii]=Hp[ii,iii] $ Hp[i,iii]
                end
            end
        end
        ######################################################################
        
        
    end
    G= [eye(Int64,k) Hp[:,1:k]' ]
  
    
    for i=ncolo:-1:1
        tem=copy(G[:,colops[i,1]])
        G[:,colops[i,1]]=copy(G[:,colops[i,2]])
        G[:,colops[i,2]]=copy(tem)
    end
       println("$G")

    return G
    
    
end

#sets the generator matrix in LH::ldpcH very inefficiently...
function calc_G(LH::ldpcH)
    LH.G=calc_G(calc_H(LH))
    if LH.G != false
        LH.isG=true
    else
        LH.isG=false
    end
end

#check whether cw satisfies the parity check equations of LH
function isCW{T<:Integer}(LH::ldpcH,cw::Array{T,1})
    n=length(cw)
    t=0
    for i=1:LH.m
        t=0
        for j=1:LH.dC[i]
            if cw[LH.CtoV[i,j,1]]==1
                t+=1
            end
        end
        if mod(t,2)==1
            return 0
        end
    end
    return 1
end

#encoder for any linear code given a generator matrix by matrix multiplication
function lc_end(inp, G) 
    ni=length(inp)
    k=size(G)[1]
    n=size(G)[2]
    re=ni%k
    if re !=0 
        inp=vcat(inp,zeros(Float64,k-re,1))
        ni=length(inp)
    end
    ncw=int64(ni/k)
    cws=zeros(Float64,n*ncw,1)
    for i=1:ncw
        cws[(i-1)*n+1:n*i]=copy(inp[(i-1)*k+1:k*i]'*G %2) 
    end
    return cws
end




#swaps rows in ldpcH type
function swap_row(LH::ldpcH,i,j)
    for k=1:LH.dC[i]
        LH.VtoC[ LH.CtoV[i,k,1] , LH.CtoV[i,k,2] ,1] = j
        LH.VtoC[ LH.CtoV[i,k,1] , LH.CtoV[i,k,2] ,2] = k
    end
    for k=1:LH.dC[j]
        LH.VtoC[ LH.CtoV[j,k,1] , LH.CtoV[j,k,2] ,1] = i
        LH.VtoC[ LH.CtoV[j,k,1] , LH.CtoV[j,k,2] ,2] = k
    end
    LH.dC[i],LH.dC[j]= LH.dC[j],LH.dC[i]
    LH.CtoV[i,:,:],LH.CtoV[j,:,:]=LH.CtoV[j,:,:],LH.CtoV[i,:,:]
end
#swaps columns in ldpcH type
function swap_col(LH::ldpcH,i,j)
    for k=1:LH.dV[i]
        LH.CtoV[ LH.VtoC[i,k,1] , LH.VtoC[i,k,2] ,1] = j
            LH.CtoV[ LH.VtoC[i,k,1] , LH.VtoC[i,k,2] ,2] = k
    end
    for k=1:LH.dV[j]
        LH.CtoV[ LH.VtoC[j,k,1] , LH.VtoC[j,k,2] ,1] = i
        LH.CtoV[ LH.VtoC[j,k,1] , LH.VtoC[j,k,2] ,2] = k
    end
    LH.dV[i],LH.dV[j]= LH.dV[j],LH.dV[i]
    LH.VtoC[i,:,:],LH.VtoC[j,:,:]=LH.VtoC[j,:,:],LH.VtoC[i,:,:]
end



#puts LH into the Rudiger/Urbanke (RU) form specified in  Efficient Encoding of Low-Density Parity-Check Codes
############################################################################################
function calc_RU(LHo::ldpcH,tgap::Int64)
    LH=deepcopy(LHo)
    n=LH.n
    tem1=0.0
    tem2=0.0
    ldiag=0
    LH.ruperm=collect(1:n)

    #############first we estimate the expected gap########
    lam=calc_lamrho(LH.dV)
    rho=calc_lamrho(LH.dC)
        
    et=calc_erasure_thresh(lam,rho,30,10000)

    
    for i=1:size(rho)[1]
        tem1+= rho[i,1]/(rho[i,2]+1)
    end
    for i=1:size(lam)[1]
        tem2+= lam[i,1]/(lam[i,2]+1)
    end
    maxit=5 #this is the maximum #of iterations before increasing tgap
    #i.e. say you put tgap =0, it is is possible this program would run for years to come
    #thus after maxit, we do tgap+=1, eventually it will stop
    its=0
    gap=floor((1.0-et -(1-tem1/tem2))*LH.n)
    ######################################################
    
    ##############################################
    ###Greedy Algorithm A
    ##############################################
    ##########
    g=2*tgap
    ulA=0
    te=0
    while g > tgap
        #[0] Initialization
        #start of the A~ in initialization step
        icols=rand(Bernoulli((1.0-et)*0.95),n)
        ulA=sum(icols)+1
        k=0
        for i=1:n
            if icols[i]==1
                k+=1
                swap_col(LH,k,i)
                    
                c1=k
                c2=i
                fc1=find(LH.ruperm .== c1)
                fc2=find(LH.ruperm .== c2)
                        
                LH.ruperm[fc1],LH.ruperm[fc2]=LH.ruperm[fc2],LH.ruperm[fc1]
            end
        end
        #now after each iteration A~ (in LH) starts at column ulA + ldiag and row ldiag+1
        ldiag=0 #length of the diagonal of found ones 
        kcnt=1 #of known columns
        k=1
            
            
        ##############################################
        while kcnt >0 && (ulA + ldiag) <=n 
            kcnt=0
            for i=(ulA+ldiag):n #find "known" columns, i.e. columns with only one 1, to the right of (ulA+ldiag)
                k=1

                tem=sort(LH.VtoC[i,1:LH.dV[i],1],2)
                while k <= LH.dV[i] 
                    #for column i, see if row tem[k] has one 1 to the right of ulA+ldiag-1
                    if length(find( LH.CtoV[ tem[k],:,1] .>= (ulA+ldiag))  ) == 1 
                        kcnt+=1
         
                        
                        #now we have a known column and must do row and column permutations
                        c1=(kcnt-1)+(ulA+ldiag)
                        c2=i
                        
                        fc1=find(LH.ruperm .== c1)
                        fc2=find(LH.ruperm .== c2)
                        LH.ruperm[fc1],LH.ruperm[fc2]=LH.ruperm[fc2],LH.ruperm[fc1]

                        swap_col(LH,c1,c2)
                        swap_row(LH, kcnt + ldiag, tem[k] ) 
                        k=LH.dV[i]+1

                    else
                        k+=1
                    end
                end
            end
            ldiag+=kcnt 
        end
        
            
        g=LH.m- ldiag
        if g >tgap
            LH=deepcopy(LHo)
            LH.ruperm=collect(1:n)

        end
        its+=1
        if its > maxit
            its=0
            tgap+=1
        end
        te+=1
    end
    
    println("The theoretically achievable gap is $gap, and the resulting gap is $(LH.m- ldiag).")

    #here we check if the diagonal of ones makes it all the way to the last column, 
    #if not, we send the columns on the far right of the matrix to a "happy place"
    if ldiag-1+ulA < n
        cnt=0
        for i=ldiag-1+ulA:-1:ulA
            swap_col(LH,i,n-cnt)
            
            c1=i
            c2=n-cnt
                    
            fc1=find(LH.ruperm .== c1)
            fc2=find(LH.ruperm .== c2)
                    
            LH.ruperm[fc1],LH.ruperm[fc2]=LH.ruperm[fc2],LH.ruperm[fc1]
            
            cnt+=1
        end
    end
    gap=LH.m- ldiag
    #######################################################################################
    #now we use Gaussian Elimination to clear E
    kcnt=0
    phin=zeros(Uint8, gap, n)
    #first we initialize the matrix [C D E]
    for i=1:gap
        #look at row LH.m-gap+i
        for k=1:LH.dC[LH.m-gap+i]
            phin[i,LH.CtoV[ LH.m-gap+i,k,1]]=1
        end
    end
    
    for j=n:-1:(n-LH.m+gap+1) #column j
        for i=(LH.m-gap+1):LH.m  #row i
            if phin[i-LH.m+gap,j]==1 #if this is true we must clear this 1 by adding row j-(n-LH.m+gap)
                for k=1:LH.dC[j-(n-LH.m+gap)]
                    phin[ i-LH.m+gap,LH.CtoV[j-(n-LH.m+gap),k,1] ] =mod( phin[ i-LH.m+gap,LH.CtoV[j-(n-LH.m+gap),k,1] ]+1 ,2)
                end
            end
        end
            
    end
    
    # now we use gaussian elimination and column permutations to make -ET^{-1}B + D invertible
    #we also make a copy so we can return phi^(-1) as a precomputation
    phin=phin[:,1:(n-LH.m+gap)]
    work=copy(phin)
    for i=1:gap
        if work[i,i+n-LH.m] != 1
            k=1
            while k <= (n-LH.m+gap)
                if work[i,k]==1 #we found a 1, and need to swap columns
                    tem=work[:,k]
                    work[:,k]=work[:,i+n-LH.m]
                    work[:,i+n-LH.m]=tem
                    tem=phin[:,k]
                    phin[:,k]=phin[:,i+n-LH.m]
                    phin[:,i+n-LH.m]=tem
                    
                    swap_col(LH,k,i+n-LH.m)
                    
                    c1=k
                    c2=i+n-LH.m
                    
                    fc1=find(LH.ruperm .== c1)
                    fc2=find(LH.ruperm .== c2)
                    
                    LH.ruperm[fc1],LH.ruperm[fc2]=LH.ruperm[fc2],LH.ruperm[fc1]
                    
                    k+=(n-LH.m+gap)
                end

                k+=1
            end
            if  work[i,i+n-LH.m] != 1
                println("We were unable to make -ET^{-1}B + D invertible ")
                return false
            end
        end
        for k=i+1:gap
            if  work[k,i+n-LH.m] == 1
                work[k,:]=mod(work[k,:]+work[i,:],2)
            end
        end
    end
    phin=phin[:,n-LH.m+1:end]
    
    LH.htype="RU"
    LH.phin=minvmod(phin,2) #we set phi^(-1) as a precomputation
    return LH
end

############################################################################################

#given a ldpcH in RU form and phi^(-1) it encodes sk using the RU method
function ldpcRUenc{T<:Integer}(LH::ldpcH,sk::Array{T,1})
    if LH.htype!= "RU"
        println("The parity check matrix is not in RU form, please run calc_RU first.")
    end
    
    n=LH.n
    m=LH.m
    k=LH.k
    g=size(LH.phin)[1]
    p1=zeros(T,g)
    p2=zeros(T,m-g)
    #computation of p1
    #AsT : n-m -> m-g
    ast = zeros(T,m-g)
    for i=1:m-g
        for k=1:LH.dC[i]
            if LH.CtoV[i,k,1] <= n-m
                ast[i]=mod(ast[i]+sk[LH.CtoV[i,k,1]],2)
            end
            
        end
        p2[i]=ast[i]
    end
    
    #T^-1 [As^t] : m-g -> m-g
    #calculate by back substitution
    for i=1:m-g
        for k=1:LH.dC[i]
            tem=LH.CtoV[i,k,1]
            if tem > (n-m+g) && tem < (n-m+g +i)
                ast[i]=mod( ast[i] + ast[tem-n+m-g]  ,2)  
            end
        end
    end
    #-E[T^-1 [As^t] ] : m-g -> g
    for i=1:g
        for k=1:LH.dC[m-g+i]
            tem=  LH.CtoV[m-g+i,k,1]
            if tem> n-m+g
                p1[i]=mod(p1[i]+ast[tem-(n-m+g)],2) 
            end
        end
        
    end
    #Cs^t : n-m -> g 
    #-E[T^-1 [As^t] ] + Cs^t : g -> g
    for i=1:g
        for k=1:LH.dC[m-g+i]
            tem=  LH.CtoV[m-g+i,k,1]
            if tem <= n-m
                p1[i]=mod(p1[i] +  sk[tem]  ,2) 
            end
        end
        
    end
    #-Phin[ -E[T^-1 [As^t] ] + Cs^t ] : g-> g
    temp=copy(p1)
    for i=1:g
        p1[i]=0
        for j=1:g
            p1[i]=mod(p1[i]+temp[j]*LH.phin[i,j],2)
        end
    end
    
    #As^t - done
    #Bp1^t
    #As^t+Bp1^t
    for i=1:m-g
        for k=1:LH.dC[i]
            tem=LH.CtoV[i,k,1]
            if tem >(n-m) && tem <= (n-m+g)
                p2[i]=mod(p2[i]+ p1[tem-(n-m)] ,2)
            end
        end
        
        
    end
    #-T^(-1)[ As^t+Bp1^t ]
    for i=1:m-g
        for k=1:LH.dC[i]
            tem=LH.CtoV[i,k,1]
            if tem > (n-m+g) && tem < (n-m+g +i)
                p2[i]=mod(p2[i]+p2[tem-(n-m+g)],2)  
            end
        end
    end
    tem=[sk ;p1 ;p2]
    xn=zeros(T,n)
    for i=1:n
        xn[i]=tem[LH.ruperm[i]]
    end
    return xn
end

##############################################################################
##############################################################################
#########Message Passing Functions############################################
##############################################################################

#Message Passing for the Binary Erasure Channel
function bec_MPD(xn,LH::ldpcH,maxi)
    #xn binary vector, received message
    #p BEC probability
    #H parity check matrix
    #maxi max iterations
    n=LH.n
    m=LH.m
    
    u0=zeros(Float64,n,1) # set the llr messages
    gdcm=ones(Uint8,m,1)
    jj=0
 
    u0=copy(xn)
    tcnt=0
    msum=0
    tloc=0
    for iter=1:maxi
        #start with check messages
       
        for i=1:m #look at check node i
            tcnt=0
            msum=0
            if gdcm[i]==1
                for j=1:(LH.dC[i]) #look at all variable nodes connected to i
                    jj=LH.CtoV[i,j,1]
                    if u0[jj]==2
                        tcnt+=1
                        tloc=jj
                    else
                        msum=mod(msum+u0[jj],2)
                    end
                end
                if tcnt==0
                    gdcm[i]=0
                elseif tcnt==1
                    gdcm[i]=0
                    u0[tloc]=msum  
                end
                
            end
            
        end       
    end
    return u0
end

#message passing for the Binary Symmetric Channel
function bsc_MPD(xn,p,LH::ldpcH,maxi)
    #xn binary vector, transmitted message
    #p BSC probability
    #H parity check matrix
    #maxi max iterations
   
    n=LH.n
    m=LH.m
    k=LH.k
    u0=ones(Float64,n)*log((1.0-p)/p) # set the llr messages
    mn=zeros(Float64,n) #llr decoded message
    bn=zeros(Int64,n) #bits decode message
   
    jj=0
    tem=0.0
    temm=0
    for i=1:n
        if xn[i]==1
            u0[i]*=-1
        end
    end
    
    mVtoC=zeros(Float64,n,LH.mdV)
    mCtoV=zeros(Float64,m,LH.mdC)
    
   
    for iter=1:maxi
              
        
        #start with variable messages       
        for i=1:n #i references the variable node
            tem=u0[i]
            for j=1:LH.dV[i] #variable node i has degree dv[i]
                #jj=what is the position variable node i, in the connection to cn j
                jj=LH.VtoC[i,j,2]
                tem+=mCtoV[LH.VtoC[i,j,1] , jj ] #T is the sum of all the messages from cn's  
            end

            for j=1:LH.dV[i]
                jj=LH.VtoC[i,j,2]
                mVtoC[i,j]=tem- mCtoV[ LH.VtoC[i,j,1] , jj  ] 
            end
            
        end
        
        #now check message
        for i=1:m #look at check node i
            tem=1.0
            for j=1:(LH.dC[i]) #look at all variable nodes connected to i
                jj=LH.CtoV[i,j,2]
                tem*=tanh(mVtoC[LH.CtoV[i,j,1] , jj ]/2.0)     
            end
            for j=1:(LH.dC[i])
                jj=LH.CtoV[i,j,2]
                
                mCtoV[i,j]=2.0*atanh(tem/tanh(mVtoC[LH.CtoV[i,j,1] , jj ]/2.0) )
            end     
        end
     
        #now we attempt decoding
        for i=1:n
            mn[i]=u0[i]
            for j=1:LH.dV[i]
                cn=LH.VtoC[i,j,1]  #jth check node connected to variable node i
                #jj=find(CtoV[cn ,:,1].==i)[1]
                jj=LH.VtoC[i,j,2]
                
                mn[i]+=mCtoV[cn,jj]
            end
            if mn[i] <= 0.0
                bn[i]=1
            else
                bn[i]=0
            end
        end
        
        
        if isCW(LH,bn)==1
            return bn
        end
    end
    return bn
end
#message passing for the BIAWGN Channel
function biawgn_MPD(xn,vr,LH::ldpcH,maxi)
    #xn binary vector(0s and 1s), transmitted message
    #var AWGN variance
    #LH parity check matrix
    #maxi max iterations
   
    n=LH.n
    m=LH.m
    k=LH.k
    #prob of 0 sent given received xn_i
    #0 given -12= prob gaus <
    
    #This is if xn is 0s and 1s
    #u0=ones(Float64,n)/(2*vr) # set the llr messages
    #u0=u0.*(1-2*xn)
    
    #Otherwise if xn is 1s and -1s
    u0=ones(Float64,n)/(2*vr) # set the llr messages
    u0=u0.*(4*xn)
    
    mn=zeros(Float64,n) #llr decoded message
    bn=zeros(Uint8,n) #bits decode message
   
    jj=0
    tem=0.0
    temm=0
  
    mVtoC=zeros(Float64,n,LH.mdV)
    mCtoV=zeros(Float64,m,LH.mdC)
    
   
    for iter=1:maxi
              
        
        #start with variable messages       
        for i=1:n #i references the variable node
            tem=u0[i]
            for j=1:LH.dV[i] #variable node i has degree dv[i]
                #jj=what is the position variable node i, in the connection to cn j
                jj=LH.VtoC[i,j,2]
                tem+=mCtoV[LH.VtoC[i,j,1] , jj ] #T is the sum of all the messages from cn's  
            end

            for j=1:LH.dV[i]
                jj=LH.VtoC[i,j,2]
                mVtoC[i,j]=tem- mCtoV[ LH.VtoC[i,j,1] , jj  ] 
            end
            
        end
        
        #now check message
        for i=1:m #look at check node i
            tem=1.0
            for j=1:(LH.dC[i]) #look at all variable nodes connected to i
                jj=LH.CtoV[i,j,2]
                tem*=tanh(mVtoC[LH.CtoV[i,j,1] , jj ]/2.0)     
            end
            for j=1:(LH.dC[i])
                jj=LH.CtoV[i,j,2]
                
                mCtoV[i,j]=2.0*atanh(tem/tanh(mVtoC[LH.CtoV[i,j,1] , jj ]/2.0) )
            end     
        end
     
        #now we attempt decoding
        for i=1:n
            mn[i]=u0[i]
            for j=1:LH.dV[i]
                cn=LH.VtoC[i,j,1]  #jth check node connected to variable node i
                #jj=find(CtoV[cn ,:,1].==i)[1]
                jj=LH.VtoC[i,j,2]
                
                mn[i]+=mCtoV[cn,jj]
            end
            if mn[i] <= 0.0
                bn[i]=1
            else
                bn[i]=0
            end
        end
        
        
        if isCW(LH,bn)==1
            return bn
        end
    end
    return bn
end



end
