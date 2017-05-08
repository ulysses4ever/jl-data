#! /usr/bin/julia

# Rosetta Code, Knapsack problem/Continuous

immutable KPCSupply{S<:String, T<:Real}
    item::S
    weight::T
    value::T
    uvalue::T
end
Base.isless(a::KPCSupply, b::KPCSupply) = a.uvalue<b.uvalue

function KPCSupply{S<:String, T<:Real}(item::S, weight::T, value::T)
    KPCSupply(item, weight, value, value/weight)
end

function solve{S<:String, T<:Real}(store::Array{KPCSupply{S,T},1},
                                   capacity::T)
    ksack = KPCSupply{S,T}[]
    kweight = zero(T)
    for s in sort(store, rev=true)
        if kweight + s.weight <= capacity
            kweight += s.weight
            push!(ksack, s)
        else
            w = capacity-kweight
            v = w*s.uvalue
            push!(ksack, KPCSupply(s.item, w, v, s.uvalue))
            break
        end
    end
    return ksack
end
    
store = [KPCSupply("beef", 38//10, 36//1),
         KPCSupply("pork", 54//10, 43//1),
         KPCSupply("ham", 36//10, 90//1),
         KPCSupply("greaves", 24//10, 45//1),
         KPCSupply("flitch", 4//1, 30//1),
         KPCSupply("brawn", 25//10, 56//1),
         KPCSupply("welt", 37//10, 67//1),
         KPCSupply("salami", 3//1, 95//1),
         KPCSupply("sausage", 59//10, 98//1)]

sack = solve(store, 15//1)

println("The store contains:")
println("        Item Weight  Unit Price")
for s in store
    println(@sprintf("%12s %4.1f    %6.2f",
                     s.item, float(s.weight), float(s.uvalue)))
end

println()
println("The thief should take:")
println("        Item Weight  Value")
for s in sack
    println(@sprintf("%12s %4.1f    %6.2f",
                     s.item, float(s.weight), float(s.value)))
end
w = mapreduce(x->x.weight, +, sack)
v = mapreduce(x->x.value, +, sack)
println(@sprintf("%12s %4.1f    %6.2f",
                 "Total", float(w), float(v)))
