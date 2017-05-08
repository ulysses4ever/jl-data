######################################
#
#Parameter values
#
######################################
alpha=0.3
delta=1.0
beta=0.95

######################################
#
#Define grids for k and a
#
######################################
nx=11
nz=3
x_grid=linspace(0.01,1.00,nx)
z_grid=linspace(0.5,1.5,nz)

#####################################
#
# reward function
#
########################################
function reward(x,y,z)
  c=z*x^alpha+(1.0-delta)*x-y
  if (c>0) then
    u=log(c)
  else
    u=-Inf
  end
  return u
end
################################################
#value function iteration
#################################################
function max_fun(r,w,d0,x,z,x_grid)
  return d0, 2.0


function solved(r,x_grid,z_grid,d0,v0)
   nx,nz=size(v0)
   done=false
   count=0
   v=copy(v0)
   d=copy(d0)
   maxit=100
   while(! done) # not done
     w=beta*v
     for j=1:nz
        for i=1:nx
        d[i,j], v[i,j]=max_fun(r, w[:,j], d0[i,j],x_grid[i],z_grid[j],x_grid)
        end
     end
     count=count+1
     println(count)
     done=(count>maxit)
     d0=copy(d)
     v0=copy(v)
   end
   return d,v
end

v0=zeros(nx,nz)
d0=ones(Int64,nx,nz)

d,v=solved(reward,beta, x_grid,z_grid,d0,v0)