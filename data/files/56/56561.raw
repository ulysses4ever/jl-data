## 1. Malas costumbres

# Implementación MUY ingenua de la derivada
function derivada(ff, x0, h)
    der = (ff(x0+h)-ff(x0))/h
    return der
end

# La función "caballito de batalla"
ftest(x) = 3x^3-2

derivada(ftest,1.0,1e-4)

# Aquí implementamos numéricamente el límite $h\to0$
for i=1:16
    h = 1/10^i
    der = derivada(ftest,1.0,h)
    err = abs(1.0 - der/9.0)
    println("$h\t $der\t $err")
end

# Implementación un poco menos ingenua de la derivada
derivada2(ff, x0, h) = (ff(x0+h/2)-ff(x0-h/2))/h

derivada2(x->3x^3-2, 1.0, 1e-6), derivada2(ftest, 1.0, 1e-6)

for i=1:16
    h = 1/10^i
    der = derivada2(ftest,1.0,h)
    err = abs(1.0 - der/9.0)
    println("$h\t $der\t $err")
end

## 2. Un par ordenado

# La definición del tipo Dual la hacemos paramétricamente
type Dual{T <: Real}
    fun :: T
    der :: T
end

# Dual(c::T<:Real) = Dual(c, zero(c))
Dual{T<:Real}(c::T) = Dual{T}(c, zero(T))

# Probando, probando....
Dual(0,1), Dual(3)

+(u::Dual,w::Dual) = Dual( u.fun+w.fun, u.der+w.der)

-(u::Dual,w::Dual) = Dual( -(u.fun,w.fun), -(u.der,w.der) )

*(u::Dual,w::Dual) = Dual( u.fun*w.fun, u.der*w.fun+u.fun*w.der )

function /(u::Dual,w::Dual)
    ff = u.fun/w.fun
    dd = (u.der-ff*w.der)/w.fun
    Dual( ff, dd )
end

# La razón de la siguiente implementación de ^ es para evitar un aviso de julia
# cuando la potencia es un número entero
^(u::Dual, a::Integer) = Dual( u.fun^a, a*u.fun^(a-1)*u.der )

function ^(u::Dual, a::Real)
    ff = u.fun^(a-1)
    Dual( ff*u.fun, a*ff*u.der)
end

# Esto se incluye para operar con números comunes
for op in (:+, :-, :*, :/)
    @eval begin
        $op(u::Dual, c::Real) = $op(u, Dual(c))
        $op(c::Real, u::Dual) = $op(Dual(c), u)
    end
end
+(u::Dual) = u
-(u::Dual) = Dual(-u.fun, -u.der)

# Probando, probando....
Dual(1.3)+1

ftest( Dual(1,1) )

#ans.der

ftest( Dual(1.0,1.0) )

ftest(x) = (3x^2-8x+5)/(7x^3-1)

ftest( Dual(1,1) )

ftest( Dual(1//1,1//1) )

tt = ((:(Base.exp),:(Base.exp)), (:(Base.log),:(x->1/x)), 
    (:(Base.sin),:(Base.cos)), (:(Base.cos),:(x->-sin(x))), 
    (:(Base.tan),:(x->(sec(x))^2)))

for (ff,dd) in tt
    @eval begin
        function $ff(u::Dual)
            Dual( $ff(u.fun), u.der*$dd(u.fun))
        end
    end
end

# Probando, probando...
exp(Dual(1.0, 1.0)), log( Dual(2.0, 1.0))

ff = x -> sin(x^3-2/x^6)
ff( Dual(2.0,1.0) )

387 * cos(255/32) / 32