module Init

VERSION < v"0.4-" && using Docile

importall Objects


export crearparticulas, crearparedes

@doc doc"""Creates an random Array(Vector) of *dimension* dim with limits: liminf, limsup""" ->
function randuniform(a, b, c=1)
    a + rand(c)*(b - a)
end

@doc doc"""Evaluates if two Disks are overlapped""" ->
function solape(p1::Particula, p2::Particula)
    deltar = p1.r - p2.r
    r = norm(deltar)
    return r < (p1.radio + p2.radio)
end

@doc doc"""Creates a Disks enclosed in the box with boundaries at Lx1, Lx2, Ly1, Ly2; and with a random velocity
between vmim and vmax"""->
function crearparticula(Lx1, Lx2, Ly1, Ly2, vmin, vmax)
    radios = randuniform(0.5,1.0)[1]
    masas = randuniform(0.5,1.0)[1]
    cotainfx = Lx1 + radios
    cotasupx = Lx2 - radios
    cotainfy = Ly1 + radios
    cotasupy = Ly2 - radios
    x = randuniform(cotainfx, cotasupx)
    y = randuniform(cotainfy, cotasupy)
    v = randuniform(vmin, vmax, 2)
    p = Particula([x,y],v,radios, masas)
    p
end

@doc doc"""Creates N Disks enclosed in the box with boundaries at Lx1, Lx2, Ly1, Ly2; and with a random
velocity between vmin and vmax"""->
function crearparticulas(N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
    p = crearparticula(Lx1, Lx2, Ly1, Ly2, vmin, vmax)
    particulas = [p]
    for i in 2:N
        overlap = true
        while(overlap)
            p = crearparticula(Lx1, Lx2, Ly1, Ly2, vmin, vmax)
            arreglo = [false]
            for particula in particulas
                test = solape(particula, p)
                push!(arreglo,test)
            end
            k = findin(arreglo,true)
            if k == []
                overlap = false
            end
        end
        push!(particulas,p)
    end
    particulas
end

@doc doc"""Creates the box in which Disks will be enclosed. Its horizontal boundaries are at Lx1 and Lx2
(Lx1 < Lx2). Its vertical boundaries are at Ly1 and Ly2 (Ly1 < Ly2)."""->
function crearparedes(Lx1,Lx2,Ly1,Ly2)
    arreglo = Array(Pared,4)
    arreglo[1] = ParedVertical(Lx1,[Ly1,Ly2])
    arreglo[2] = ParedVertical(Lx2,[Ly1,Ly2])
    arreglo[3] = ParedHorizontal([Lx1,Lx2],Ly1)
    arreglo[4] = ParedHorizontal([Lx1,Lx2],Ly2)
    arreglo
end

end
