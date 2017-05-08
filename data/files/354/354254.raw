using HDF5,JLD
E=load("Emb.jld","E")


nf=1999
freq=linspace(1e6,2e9,nf)

Nf=27

u=5
v=2
df=100
correlationx=zeros(Nf,nf-df)
correlationy=zeros(Nf,nf-df)
correlationz=zeros(Nf,nf-df)

for i=1:Nf
    for j=1:nf-df
      if i==13
        correlationx[i,j]=NaN
        correlationy[i,j]=NaN
        correlationz[i,j]=NaN
      else
        correlationx[i,j]=cor(vec(E[u,j:j+df,v]),vec(E[i,j:j+df,1]))
        correlationy[i,j]=cor(vec(E[u,j:j+df,v]),vec(E[i,j:j+df,2]))
        correlationz[i,j]=cor(vec(E[u,j:j+df,v]),vec(E[i,j:j+df,3]))
      end
    end
end



