#Defino las funciones k_1, k_2, k_3, k_4

k_1(x,t,f,h)=f(x,t)
k_2(x,t,f,h)=f(x+h*0.5*k_1(x,t,f,h),t+0.5*h)
k_3(x,t,f,h)=f(x+h*0.5*k_2(x,t,f,h),t+0.5*h)
k_4(x,t,f,h)=f(x+h*k_3(x,t,f,h),t+0.5*h)


#Asi defini la funcion que calcula un paso de los tres metodos

function one_step(f,x0,t0,h)

    eu_nueva=x0+h*f(x0,t0)
    ptm_nueva=x0+h*f(x0+h*0.5*f(x0,t0),t0+h*0.5)
    rk4_nueva=x0+h*(1/3*k_1(x0,t0,f,h)+1/6*k_2(x0,t0,f,h)+1/6*k_3(x0,t0,f,h)+1/3*k_4(x0,t0,f,h))

    eu_nueva,ptm_nueva,rk4_nueva
end

#Pero luego tengo problemas con la funcion que aplica los tres metodos, tengo dos funciones que hacen esto
#La primera toma el tipo de metodo como argumento, la segunda no pregunta nada y hace los tres metodos, ninguna de las dos funciones funciona :(

function integrar(m,f,x0,t0,tf,h)

    eu=Vector{Float64}[[x0]]
    ptm=Vector{Float64}[[x0]]
    rk4=Vector{Float64}[[x0]]
    t=Float64[t0]

    if string(m)=="euler"

        for ti in t0:h:tf

            eu_nueva=x0 + h*f(x0,ti)

            x0=eu_nueva


            push!(t,ti)
            push!(eu,[x0])

        end

    t,hcat(eu...)'


    elseif string(m)=="midpoint"

        for i in t0:h:tf

            ptm_nueva=x0+h*f(x0+h*0.5*f(x0,t0),t0+h*0.5)

            t0=t0+h
            x0=ptm_nueva


            push!(t,t0)
            push!(ptm,[x0])

        end

    t,hcat(ptm...)'

    else

        print ("Espero que te guste el método de Runge--Kutta de cuarto grado, por que eso es lo que voy a hacer")

            for i in t0:h:tf

                rk4_nueva=x0+h*(1/3*k_1(x0,t0,f,h)+1/6*k_2(x0,t0,f,h)+1/6*k_3(x0,t0,f,h)+1/3*k_4(x0,t0,f,h))

                t0=t0+h
                x0=rk4_nueva


                push!(t,t0)
                push!(rk4,[x0])

            end


         t,hcat(rk4...)'


        end

end




function methods_integration(f,x0,t0,tf,h)
    e0=x0
    ptm0=x0
    rk40=x0

    eu=Vector{Float64}[[e0]]
    ptm=Vector{Float64}[[ptm0]]
    rk4=Vector{Float64}[[rk40]]
    t=Float64[t0]


    for ti in t0:h:tf

        eu_nueva=e0+h*f(e0,ti)
        ptm_nueva=ptm0+h*f(ptm0+h*0.5*f(ptm0,ti),ti+h*0.5)
        rk4_nueva=rk40+h*(1/3*k_1(rk40,ti,f,h)+1/6*k_2(rk40,ti,f,h)+1/6*k_3(rk40,ti,f,h)+1/3*k_4(rk40,ti,f,h))

        e0=eu_nueva
        ptm0=ptm_nueva
        rk40=rk4_nueva

        push!(t,ti)
        push!(eu,[e0])
        push!(ptm,[ptm0])
        push!(rk4,[rk40])

    end
    t,hcat(eu...,ptm...,rk4...)'
end