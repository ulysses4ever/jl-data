# Pkg.add("DataFrames")   ###添加程序包

using DataFrames        ###调用函数包

# Pkg.update()

for i in 1:3
  println("i = $i")
end

# Pkg.add("QuantEcon")
#
# Pkg.add("PyPlot")
# Pkg.add("Winston")
using Winston
ts_length = 100
epsilon_values = randn(ts_length)
plot(epsilon_values)

#Pkg.add("PyPlot")
using PyPlot
ts_length = 100
epsilon_values = Array(Float64, ts_length)
for i in 1:ts_length
  epsilon_values[i] = randn()
end
plot(epsilon_values, "b-")

words = ["foo", "bar"]
for word in words
  println("Hello $word")
end

i=1
data=0
while i <= ts_length
  data=epsilon_values[i]
  println("the $i number is $data \n");
  i=i+1;
end

function generate_epsilon(n)
  epsilons=randn(n);
  for i in 1:n
    println(epsilons[i])
  end
  return epsilons
end

data=generate_epsilon(100)
plot(data)

Pkg.add("Distributions")
using Distributions
function plot_histogram(distribution, n)
  epsilon_values = rand(distribution, n) # n draws from distribution
  ### PyPlot.plt.hist(epsilon_values)   这条语句里面不嫩实现
end
lp = Laplace()
plot_histogram(lp, 500)

### Exercise

### 1.2.1

function factorial2(n)
  produit=1;
  for i in 1:n
    produit=produit*i;
    i=i+1;
  end
  return produit
end

factorial2(10)
factorial(10)

### 1.2.2
function binomial_rv(n,p)
  count=0;
  for i in 1:n
    if rand()>p
      count=count+1;
    end
  end
  return  count;
end

binomial_rv(100,0.5)

### 1.2.3

function pi_simulatation(n)
  r1=rand(n);
  r2=rand(n);
  count=0;
  for i in 1:n
    radiun=sqrt(r1[i]^2+r2[i]^2);
    if radiun<=1
      count=count+1;
    end
  end
  pi=count/n*4;
  return pi
end
pi_simulatation(1000000)


### 1.2.4

function Flip_coin()
  updown=Array(Int64,10);
  for i in 1:10
    updown[i]=int(rand()>0.5);
  end
  println(updown)
  for j in 1:8
    if sum(updown[j:(j+2)])==3
           println("pay")
      break
    end
  end
end

Flip_coin()


### 1.2.5

function generate_ts(n,alpha)
  epsilons=randn(n)
  xt=randn(n);
  xt[1]=epsilons[1];
  for i in 2:n
    xt[i]=alpha*xt[i-1]+epsilons[i];
  end
  return xt
end

ts1=generate_ts(200,0.9)
plot(ts1)

### 1.2.6

a=generate_ts(300,0.0)
b=generate_ts(300,0.8)
c=generate_ts(300,0.98)
