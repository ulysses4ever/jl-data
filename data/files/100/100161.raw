using HardSphere
using PyPlot
using PyCall
pygui(true)

@pyimport matplotlib.patches as patch
@pyimport matplotlib.animation as animation


N = 3
Lx1 = 0
Lx2 = 10
Ly1 = 0
Ly2 = 10
vmin = -5
vmax = 5
tinicial = 0
tmax = 100

q = HardSphere.simulacionanimada(tinicial, tmax, N, Lx1, Lx2, Ly1, Ly2, vmin, vmax);

pos = [[q[1][k] for k in j:N:length(q[1])] for j in 1:N];
vel = [[q[2][k] for k in j:N:length(q[1])] for j in 1:N];

fig = plt.figure()
ax = fig[:add_axes]([0.05, 0.05, 0.9, 0.9])
ax[:set_xlim](Lx1, Lx2)
ax[:set_ylim](Ly1, Ly2)
c = patch.Circle(pos[1][1],q[4][1].radio) #En pos[1][1] el primer 1 se refiere a la particula, en tanto que el
#segundo se refiere al evento. En q[4] el 1 se refiere a la particula
circulos = [c]
ax[:add_patch](c)

for k in 2:N
    c = patch.Circle(pos[k][1],q[4][k].radio)
    push!(circulos,c)
    ax[:add_patch](c)
end

function animate(i)

        z = [i/10 > t for t in q[3]]
        k = findfirst(z,false) - 1

    if k == 0
        for j in 1:N
            circulos[j][:center] = (pos[j][1][1], pos[j][1][2])
        end
        #circulos[2][:center] = (pos2[1][1],pos2[1][2])

    else
        #if q[3][k] < i/10 < q[3][k+1]
        for j in 1:N
            circulos[j][:center] = (pos[j][k][1] + vel[j][k][1]*(i/10-q[3][k]), pos[j][k][2] + vel[j][k][2]*(i/10-q[3][k]))
        #circulos[2][:center] = (pos2[k][1] + vel2[k][1]*(i/10-q[3][k]), pos2[k][2] + vel2[k][2]*(i/10-q[3][k]))
        end


    end
        return (circulos,)
end

anim = animation.FuncAnimation(fig, animate, frames=1000, interval=20, blit=false, repeat = false)
