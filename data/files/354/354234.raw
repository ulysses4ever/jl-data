using Distributions
using PyPlot
using HDF5,JLD


function p_f_th(limite,sigma,n)
  pf=(exp(-limite^2/2/sigma^2)).^n
  return pf
end



#champ
E=load("Emb30.jld","E")
moy_f=vec(mean(mean(E,1),3))
nf=100
freq=linspace(20e6,2e9,nf)

#tirage des fonctions
a=vcat(int(linspace(1,26,26)),int(linspace(1,26,26)),int(linspace(1,26,26)))
b=sort(vcat(int(ones(26)),int(2*ones(26)),int(3*ones(26))))
c=hcat(a,b)

M=500
n=30#length(a)
alpha_list=[0.5,1,2]

th1=p_f_th(alpha_list[1]*sqrt(pi/2),1,[1:n])
th2=p_f_th(alpha_list[2]*sqrt(pi/2),1,[1:n])
th3=p_f_th(alpha_list[3]*sqrt(pi/2),1,[1:n])

limit_Mat=cumsum(ones(M,nf,n),3)
for l=1:3
  failure_p=zeros(M,nf,n)
  for k=1:M
    println(k/M)
    perm=shuffle(a)
    choix=c[perm,:]
    for i=1:nf
      limit=alpha_list[l]*moy_f[i]
      for j=1:n
        failure_p[k,i,j]=E[choix[j,1],i,choix[j,2]].>limit;
      end
    end
  end
  limittext=round(alpha_list[l]*100)/100
  failure=cumsum(failure_p,3).==limit_Mat
  prob_failure=squeeze(mean(failure,1),1)
  semilogy(linspace(1,n,n),mean(prob_failure,1)',marker="o" ,label="\$ E_s=$limittext \\mu\$")
end
semilogy(linspace(1,n,n),th1,label="\$ E_s=0.5\\mu\$ th.")
semilogy(linspace(1,n,n),th2,label="\$ E_s=1\\mu\$ th.")
semilogy(linspace(1,n,n),th3,label="\$ E_s=2\\mu\$ th.")
legend(loc=0)
grid()
ylim(0.0001,1)
xlabel("\$ n\$")
ylabel("\$ p_f \$")


