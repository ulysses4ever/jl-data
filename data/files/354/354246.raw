using PyPlot

function p_f_th(limite,sigma,n)
  pf=(exp(-limite^2/2/sigma^2)).^n
  return pf
end

alpha_list=[0.5,1,2]

th1=p_f_th(alpha_list[1],1,[1:n])
th2=p_f_th(alpha_list[2],1,[1:n])
th3=p_f_th(alpha_list[3],1,[1:n])

semilogy(linspace(1,n,n),th1,"k-",marker="o" ,label="\$ E_f=0.5\\sigma\$")
semilogy(linspace(1,n,n),th2,"k--",marker="o" ,label="\$ E_f=1\\sigma\$")
semilogy(linspace(1,n,n),th3,"k:",marker="o" ,label="\$ E_f=2\\sigma\$")
legend(loc=0)
grid()
ylim(0.0001,1)
xlabel("\$ n\$")
ylabel("\$ p \$")

savefig("fig1.pdf",bbox_inches="tight")


E = npzread("E_2.npy")
figure(figsize=(10,5))
semilogy(freq/1e6,E[:,1]./(freq.^2)*2e9^2,label="\$ E_x\$")
semilogy(freq/1e6,E[:,2]./(freq.^2)*2e9^2,label="\$ E_y\$")
semilogy(freq/1e6,E[:,3]./(freq.^2)*2e9^2,label="\$ E_z\$")
grid()
xlabel("\$ f\$/MHz")
ylabel("V/m")
ylim(0.1,3000)
legend(loc=0)
savefig("fig2.pdf",bbox_inches="tight")


#fig3

using Distributions
using PyPlot
using NPZ

#champ
E=npzread("data30r.npz")["E"]
freq=npzread("data30r.npz")["freq"]
moy_f=vec(mean(mean(E,1),3))
nf=length(freq)
function p_f_th(limite,sigma,n)
  pf=(exp(-limite^2/2/sigma^2)).^n
  return pf
end


#tirage des fonctions
a=vcat(int(linspace(1,26,26)),int(linspace(1,26,26)),int(linspace(1,26,26)))
b=sort(vcat(int(ones(26)),int(2*ones(26)),int(3*ones(26))))
d=hcat(a,b)

M=500
n=30#length(a)
alpha_list=[0.5,1,2]

th1=p_f_th(alpha_list[1],1,[1:n])
th2=p_f_th(alpha_list[2],1,[1:n])
th3=p_f_th(alpha_list[3],1,[1:n])

limit_Mat=cumsum(ones(M,nf,n),3)
for l=1:3
  failure_p=zeros(M,nf,n)
  for k=1:M
    println(k/M)
    perm=shuffle(a)
    choix=d[perm,:]
    for i=1:nf
      limit=alpha_list[l]*moy_f[i]*sqrt(2/pi)
      for j=1:n
        failure_p[k,i,j]=E[choix[j,1],i,choix[j,2]].>limit;
      end
    end
  end
  limittext=round(alpha_list[l]*100)/100
  failure=cumsum(failure_p,3).==limit_Mat
  prob_failure=squeeze(mean(failure,1),1)
  semilogy(linspace(1,n,n),mean(prob_failure,1)',ls="none",marker="o" ,label="\$ E_f=$limittext \\sigma\$")
end
semilogy(linspace(1,n,n),th1,"b" ,label="\$ E_f=0.5\\sigma\$ th.")
semilogy(linspace(1,n,n),th2,"g" ,label="\$ E_f=1\\sigma\$ th.")
semilogy(linspace(1,n,n),th3,"r" ,label="\$ E_f=2\\sigma\$ th.")
legend(loc=0)
grid()
ylim(0.0001,1)
xlabel("\$ n\$")
ylabel("\$ p \$")

savefig("fig3.pdf",bbox_inches="tight")




#fig3b

using Distributions
using PyPlot
using NPZ

#champ
E=npzread("data30r.npz")["E"]
freq=npzread("data30r.npz")["freq"]
moy_f=vec(mean(mean(E,1),3))
nf=length(freq)
function p_f_th(limite,sigma,n)
  pf=(exp(-limite^2/2/sigma^2)).^n
  return pf
end


#tirage des fonctions
a=vcat(int(linspace(1,30,30)),int(linspace(1,30,30)),int(linspace(1,30,30)))
b=sort(vcat(int(ones(30)),int(2*ones(30)),int(3*ones(30))))
d=hcat(a,b)

M=500
n=40#length(a)
alpha_list=[0.5,1,2]

th1=p_f_th(alpha_list[1],1,[1:n])
th2=p_f_th(alpha_list[2],1,[1:n])
th3=p_f_th(alpha_list[3],1,[1:n])

limit_Mat=cumsum(ones(M,nf,n),3)
for l=1:3
  failure_p=zeros(M,nf,n)
  for k=1:M
    println(k/M)
    perm=shuffle(a)
    choix=d[perm,:]
    for i=1:nf
      limit=alpha_list[l]*moy_f[i]*sqrt(2/pi)
      for j=1:n
        failure_p[k,i,j]=E[choix[j,1],i,choix[j,2]].>limit;
      end
    end
  end
  limittext=round(alpha_list[l]*100)/100
  failure=cumsum(failure_p,3).==limit_Mat
  prob_failure=squeeze(mean(failure,1),1)
  if l==1
    couleur="b"
  end
  if l==2
    couleur="g"
  end
  if l==3
    couleur="r"
  end
  semilogy(linspace(1,n,n),mean(prob_failure[100:500,:],1)',color=couleur ,ls="none",marker="o",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$100<f<500\$ (MHz)")
  #semilogy(linspace(1,n,n),mean(prob_failure[500:1000,:],1)',color=couleur,ls="none",marker="o",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$500<f<1000\$ (MHz)")
  semilogy(linspace(1,n,n),mean(prob_failure[1000:1500,:],1)',color=couleur,ls="none",marker="v",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$1000<f<1500\$ (MHz)")
  semilogy(linspace(1,n,n),mean(prob_failure[1500:2000,:],1)',color=couleur,ls="none",marker="s",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$1500<f<2000\$ (MHz)")
end
semilogy(0,0.000001,color="k",ls="none",marker="o",markerfacecolor = "w",markeredgecolor = "k" ,label="\$100<f<500\$ (MHz)")
semilogy(0,0.000001,color="k",ls="none",marker="v" ,markerfacecolor = "w",markeredgecolor = "k" ,label="\$1000<f<1500\$ (MHz)")
semilogy(0,0.000001,color="k",ls="none",marker="s" ,markerfacecolor = "w",markeredgecolor = "k" ,label="\$1500<f<2000\$ (MHz)")
semilogy(linspace(1,n,n),th1,"b" ,label="\$ E_f=0.5\\sigma\$ (th. Rayleigh)")
semilogy(linspace(1,n,n),th2,"g" ,label="\$ E_f=1\\sigma\$ (th. Rayleigh)")
semilogy(linspace(1,n,n),th3,"r" ,label="\$ E_f=2\\sigma\$ (th. Rayleigh)")
legend(loc=4)
grid()

ylim(0.0001,1)
xlabel("\$ n\$")
ylabel("\$ p \$")

savefig("fig3b.pdf",bbox_inches="tight")


#fig4

using Distributions
using PyPlot
using NPZ

#champ
E=npzread("data30nr.npz")["E"]
E=E[[1:12,14:end],:,:]
freq=npzread("data30nr.npz")["freq"]
moy_f=vec(mean(mean(E,1),3))
nf=length(freq)
function p_f_th(limite,sigma,n)
  pf=(exp(-limite^2/2/sigma^2)).^n
  return pf
end


#tirage des fonctions
a=vcat(int(linspace(1,26,26)),int(linspace(1,26,26)),int(linspace(1,26,26)))
b=sort(vcat(int(ones(26)),int(2*ones(26)),int(3*ones(26))))
d=hcat(a,b)

M=500
n=40#length(a)
alpha_list=[0.5,1,2]

th1=p_f_th(alpha_list[1],1,[1:n])
th2=p_f_th(alpha_list[2],1,[1:n])
th3=p_f_th(alpha_list[3],1,[1:n])

limit_Mat=cumsum(ones(M,nf,n),3)
for l=1:3
  failure_p=zeros(M,nf,n)
  for k=1:M
    println(k/M)
    perm=shuffle(a)
    choix=d[perm,:]
    for i=1:nf
      limit=alpha_list[l]*moy_f[i]*sqrt(2/pi)
      for j=1:n
        failure_p[k,i,j]=E[choix[j,1],i,choix[j,2]].>limit;
      end
    end
  end
  limittext=round(alpha_list[l]*100)/100
  failure=cumsum(failure_p,3).==limit_Mat
  prob_failure=squeeze(mean(failure,1),1)
  if l==1
    couleur="b"
  end
  if l==2
    couleur="g"
  end
  if l==3
    couleur="r"
  end
  semilogy(linspace(1,n,n),mean(prob_failure[100:500,:],1)',color=couleur ,ls="none",marker="o",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$100<f<500\$ (MHz)")
  #semilogy(linspace(1,n,n),mean(prob_failure[500:1000,:],1)',color=couleur,ls="none",marker="o",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$500<f<1000\$ (MHz)")
  semilogy(linspace(1,n,n),mean(prob_failure[1000:1500,:],1)',color=couleur,ls="none",marker="v",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$1000<f<1500\$ (MHz)")
  semilogy(linspace(1,n,n),mean(prob_failure[1500:2000,:],1)',color=couleur,ls="none",marker="s",markerfacecolor = "w",markeredgecolor = couleur)# ,label="\$1500<f<2000\$ (MHz)")
end
semilogy(0,0.000001,color="k",ls="none",marker="o",markerfacecolor = "w",markeredgecolor = "k" ,label="\$100<f<500\$ (MHz)")
semilogy(0,0.000001,color="k",ls="none",marker="v" ,markerfacecolor = "w",markeredgecolor = "k" ,label="\$1000<f<1500\$ (MHz)")
semilogy(0,0.000001,color="k",ls="none",marker="s" ,markerfacecolor = "w",markeredgecolor = "k" ,label="\$1500<f<2000\$ (MHz)")
semilogy(linspace(1,n,n),th1,"b" ,label="\$ E_f=0.5\\sigma\$ (th. Rayleigh)")
semilogy(linspace(1,n,n),th2,"g" ,label="\$ E_f=1\\sigma\$ (th. Rayleigh)")
semilogy(linspace(1,n,n),th3,"r" ,label="\$ E_f=2\\sigma\$ (th. Rayleigh)")
legend(loc=4)
grid()

ylim(0.0001,1)
xlabel("\$ n\$")
ylabel("\$ p \$")

savefig("fig4.pdf",bbox_inches="tight")
