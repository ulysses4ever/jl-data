const e1 = 200 #siły elektromotoryczne
const e2 = 100 #
const R2 = 200 # w omach
const X2 = 300 # w omach
const i1 = 5
const i2 = 10


# wylicza przekładnię transformatora
function przekladnia(e1, e2)
    e1 /  e2
end


# wylicza przeliczoną na stronę pierwotną rezystancję uzwojenia wtórnego
function rez_2_prim(przek, R2)
    przek^2 * R2
end

#wylicza  przeliczoną na stronę pierwotną reaktancję rozproszeń uzwojenia wtórnego
function reak_2_prim(przek, X2)
    przek^2 * X2
end

# straty całkowite w uzwojeniu
function straty_uzwojen(i1, i2, r1, r2)
    i1^2 * r1 + i2^2 * r2
end

# moc
function moc_pierwotna(i1, e1)
    i1*e1
end

function moc_wtorna(i2, e2)
    i2 * e2
end


x = przekladnia(e1,e2)
R2_prim = rez_2_prim(x, R2)
X2_prim = reak_2_prim(x, X2)
straty = straty_uzwojen(i1,i2, R2, R2_prim)
sprawnosc = moc_pierwotna(i1, e1) / moc_wtorna(i2, e2)


# R1, R2_prim - rezystancja uzwojenia pierwotnego i przeliczona na stronę pierwotną, rezystancja uzwojenia wtórnego

# X1, X2_prim - reaktancje rozproszeń uzwojenia pierwotnego i przeliczona na stronę pierwotną reaktancji rozproszeń uzwojenia wtórnego


println("Przekładnia transformatora: ", x)
println("Rezystancja uzwojenia pierwotnego: ", R2)
println("Reaktancja rozproszeń uzwojenia pierwotnego: ", X2)
println("Straty całkowite w uzwojeniu: ", straty)
println("Sprawnosc transformatora: ", sprawnosc)

using Base.Test
@test_approx_eq 1. 0.999999999
