#% Michalewicz Zbigniew "Genetic Algorithms + Data Structures = Evolution Programs"
#% Intel Core 2 DUO 2.1 GHz, 4 Gb RAM, 32 bits Win 7
#% The Julia Language: a fresh approach to technical computing.

function convert_binary_string(gene::Array{Int32,2}) 
  gl=length(gene[1,:])
  dgene=ones(Int32, gl)  
  for i=1:gl 
      dgene[i]=2.^(gl-1).*gene[i] # арифметический сдвиг 
      gl=gl-1                      
  end 
  return sum(dgene) 
end # convert_binary_string
#% @assert isequal(convert_binary_string([1 0 1 1 0 1 1 0]), 182)

function init_pop(popsize, chromlength)
  return randbit(popsize, sum(chromlength))
end # init_pop

function find_real_number(ch, minbound::Float64, maxbound::Float64)
    gl=length(ch[1,:])
    xs=convert_binary_string(ch)
    x=minbound+xs*((maxbound-minbound)/((2^gl)-1))
    return x
end # find_real_number
#%ch=[1 0 0 0 1 0 1 1 1 0 1 1 0 1 0 1 0 0 0 1 1 1]
#%find_real_number(ch,-1.,2.) #0.6371971695893215

function test_find_real_number(precision::Int32, minbound::Float64, maxbound::Float64)
  p=[10 100 1000 10000 100000 1000000]
  d=(maxbound-minbound)*p[precision]
  i=1
  while 2^i < d 
    i=i+1
  end
  for j=1:1000000
    f= find_real_number(randbit(1, i), minbound, maxbound)
    if  f < minbound && f > maxbound
      return false 
    end 
  end
  return true
end #  test_find_real_number
#% @assert isequal(test_find_real_number(6, 1., 12.), true)

function get_all_real_number(ch, dimension, chromlength, minbound, maxbound)
  rs=rand(1, dimension)
  for i=1:dimension
    #println(minbound[i], " : ", maxbound[i])
    rs[i]=find_real_number(get_gene(ch, i, chromlength), minbound[i], maxbound[i])
    #println(typeof(get_gene(ch, i, chromlength)),":", rs[i])
    #println(get_gene(ch, i, chromlength),":", rs[i])
  end
  return rs  
end

function test_get_all_real_number()
  xi=[15 18]
  ch=randbit(1,sum(xi))
  println(ch)
  for i=1:10
    get_all_real_number(ch,2, xi, [-1.5 1.0],[5. 15.])
  end    
end

function get_gene(ch, num_gene, chromlength)
  spoint=1
  for i=1:num_gene-1
    spoint=spoint+chromlength[i]
  end
  #println(spoint)
  #println("t=",typeof(ch))
  return ch[1, spoint:spoint+chromlength[num_gene]-1]
end

function test_get_gene()
  chl=[10:10:100];
  ch=randbit(1,sum(chl));
  for i=1:length(chl) 
    println(length(get_gene(ch, i,chl)), " : " ,get_gene(ch, i,chl))
  end
end  

function calc_fit(of::Function, ch, dimension, chromlength, minbound, maxbound)
  rs=get_all_real_number(ch, dimension, chromlength, minbound, maxbound)
  f=of(rs)
  return f, rs
end # 'calc_fit'
#% calc_fit(Rastrigin, randbit(1, 33), 2, [15 18], [-5.12 -5.12],[5.12 5.12]) == 1.7

function calc_fit_pop(of::Function, pop::Array{Int32,2}, dimension, chromlength, minbound, maxbound)
  s=size(pop, 1); fit=rand(1, s); arg=rand(s, dimension)
  for i=1:s
    (fit[i], arg[i,:]) = calc_fit(of, pop[i,:], dimension, chromlength, minbound, maxbound)
  end
  return fit, arg 
end # 'calc_fit_pop'
#% max(calc_fit_pop(Rastrigin, randbit(7000000, 33), 2, [15 18], [-5.12 -5.12],[5.12 5.12])[1])

function split_chromosome(ch, dimension, chromlength)
  spoint=1
  genes=randbit(dimension, chromlength[1]) #%Array(Int32, dimension, sum(chromlength))
  for i=1:dimension
   genes[i,:]=ch[spoint:spoint+chromlength[i]-1]
   #println(ch[spoint:spoint+chromlength[i]-1])
   spoint=spoint+chromlength[i]
  end
  return genes
end
# split_chromosome(randbit(sum([15 18])), 2, [15 18])

function find_all_real_number(ch, dimension, chromlength, minbound, maxbound)
  genes=split_chromosome(ch, dimension, chromlength)
  rs=rand(dimension)
  for i=1:dimension
    rs[i]=find_real_number(genes[i,:], minbound[i], maxbound[i])
    #println(genes[i,:], " : ", minbound[i]," : ", maxbound[i])
  end
  return rs #, genes
end

function proportionate_selection(popsize, sumfitness, fitness)
  partsum = 0;
  j = 0;
  randnum =  rand() * sumfitness;
  while (partsum < randnum && j < popsize)
    j = j+1;
    partsum = partsum + fitness[j];
  end
  return j
end  
#% 

function selection(pop, fitness) 
  sumfitness = sum(fitness)    
  #%fitness = fitness / sumfitness 
  (popsize, chromlength) = size(pop); 
  newpop=copy(pop)
  for i=1: popsize 
    newpop[i,:] = pop[proportionate_selection(popsize, sumfitness, fitness),:]
  end 
  return newpop
end # selection

# function selection(pop, fitvalue) 
#   #%shift=min(fitvalue) 
#   #%fitvalue=map(x->x+abs(shift)+0.1, fitvalue)
#   totalfit=sum(fitvalue);     
#   fitvalue=fitvalue/totalfit; 
#   #%println("fitvalue=",fitvalue)
#   fitvalue=cumsum(fitvalue);  #% fitvalue=[1 2 3 4],cumsum(fitvalue)=[1 3 6 10] 
#   (popsize, chromlength)=size(pop); 
#   newpop=copy(pop)
#   ms=sort(rand(1, popsize), 2);       
#   #%println("ms=", ms, "fitvalue=", fitvalue) 
#   fitin=1;  
#   newin=1; 
#   while newin <= popsize 
#       if ms[newin] < fitvalue[fitin]    
#         println(ms[newin],":", fitvalue[fitin])
#         newpop[newin,:]=pop[fitin,:];  
#         newin=newin+1; 
#       else 
#         fitin=fitin+1; 
#       end  
#   end 
#   return newpop
# end # selection

function crossover(pop, pc) 
    (popsize, chromlength)=size(pop)
    newpop=copy(pop)
    for i=1:2:(popsize-1) 
        if rand() < pc
            cpoint=int(round(rand()*chromlength))
            if cpoint==0 
                cpoint=1
            elseif cpoint==chromlength
                cpoint=chromlength-1
            end
            #%println("cpoint=", cpoint)
            #%println("ch=", pop[i,1:cpoint],":", pop[i+1,cpoint+1:chromlength])
            newpop[i,:]=[pop[i,1:cpoint] pop[i+1,cpoint+1:chromlength]]
            newpop[i+1,:]=[pop[i+1,1:cpoint] pop[i,cpoint+1:chromlength]] 
        else 
          newpop[i,:]=pop[i,:]
          newpop[i+1,:]=pop[i+1,:]
        end 
    end 
    return newpop
end

function mutation(pop, pm) 
  (popsize,chromlength)=size(pop)
  newpop=init_pop(popsize, chromlength)
  for i=1:popsize 
      if rand() < pm 
          mpoint=int(round(rand()*chromlength))
          #%println("mpoint=", mpoint)
          if mpoint==0 
            mpoint=1
          end
          newpop[i, :] = pop[i, :]
          if  newpop[i,mpoint] == 0 
              newpop[i, mpoint] = 1
          else 
              newpop[i,mpoint] = 0
          end 
      else 
          newpop[i,:]=pop[i,:] 
      end 
  end
  return newpop
end # mutation

function best(pop, fitvalue)  
  (popsize,chromlength)=size(pop); 
  bestindividual=pop[1,:]; 
  bestfit=fitvalue[1]; 
  for i=2:popsize 
     if fitvalue[i]>bestfit 
         bestindividual=pop[i,:]; 
         bestfit=fitvalue[i]; 
      end 
  end
  return bestindividual, bestfit
end # 'best'

function ga(myf::Function, dimension::Int32, popsize::Int32, 
  chromlength, minbound, maxbound, nb_gen::Int32)
  f=rand(1, popsize); rs=rand(popsize, dimension); br=rand(1, dimension)
  p=init_pop(popsize, chromlength); np=copy(p)
  #% max(calc_fit_pop(Rastrigin, randbit(7000000, 33), 2, [15 18], [-5.12 -5.12],[5.12 5.12]))
  f=calc_fit_pop(myf, p, dimension, chromlength, minbound, maxbound)[1]
  bf=best(p, f)[2]
  #%br=find_real_number(best(p, f)[1], minbound, maxbound) 
  for i=1:nb_gen
    (f,rs)=calc_fit_pop(myf, p, dimension, chromlength, minbound, maxbound)
    tmp=best(p, f)[2]
    if tmp > bf
      br=get_all_real_number(best(p, f)[1], dimension, chromlength, minbound, maxbound)
      bf=tmp
      println("New best fitness=", bf, " on iteration: ", i)
    end
    np=selection(p, f)
    np=mutation(np, 0.01)
    np=crossover(np, 0.25)
    p=copy(np)
  end
  return bf, br
end # ga
#% for i=1:10 println(ga(obj_fun2, 1, 50, 10,1. ,12., 150)) end
#% ga(Rastrigin, 2, 80, [15 18], [-5.12 -5.12],[5.12 5.12],200)

function obj_fun(x::Array{Float64,1})
  return x[1]*sin(10.0*pi*x[1])+1.0
end
#% Функция приспособленности
function obj_fun2(x::Array{Float64,1})
  return 10.*cos(3.*x[1])-4.*x[1]
end # obj_fun
function obj_fun36(x::Array{Float64,1})
  return 21.5+x[1]*sin(4.0*pi*x[1])+x[2]*sin(20.0*pi*x[2])
end
#% obj_fun36([1.052426 5.755330]) = 20.2526

function Rastrigin(x) #::Array{Float64,1})
  return 20+x[1]*x[1]+x[2]*x[2]-10*cos(2*pi*x[1])-10*cos(2*pi*x[2]);
end
#%Пространство: -5.12<=x[t]<=5.12
#%Максимум: F(4.52299,4.52299)  =80.7065
#%          F(-4.52299,4.52299) =80.7065
#%          F(4.52299,-4.52299) =80.7065
#%          F(-4.52299,-4.52299)=80.7065

function Griewank(x::Array{Float64,1})
  return 1./(((x[1]*x[1]+x[2]*x[2])/200.)-cos(x[1])*cos(x[2]/sqrt(2.))+2.)
end
#%    Пространство: -20<=x[t]<=20
#%    Максимум: F(0,0)=1

#%Функция Растригина. Число переменных 10. Максимумов - (10^10)-1 локальных и 1 глобальный.
function Rastrigin10(x::Array{Float64,1})
    y=-100;
    for i=1:10
      y=y+10.*cos(2.*pi*x[i])-x[i]*x[i]
    end
    return y
end
#%    Пространство: -5.12<=x[t]<=5.12
#%    Максимум: F(0,..,0)=0

#@elapsed ga()
#####################################################################
#http://www.ingber.com/ASA-README.html
#http://cs.adelaide.edu.au/~zbyszek/evol-systems.html