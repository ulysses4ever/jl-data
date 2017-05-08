using derivadas
function newton(f::Function, x, n)  #f es la función de la que buscas raíces y x es el punto inicial, n es el número de pasos



    for i=1:n
        y=inter(x,1.0)
        g=f(y)
        #println("$g")
        w=x-g.f/g.d
        x=w
    end
    x
end

newton(f, x, n)