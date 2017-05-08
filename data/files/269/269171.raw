type Salty{T<:Real}
    salinity::T
end

issalty(A) = false
issalty(A::Salty) = A.salinity > 0
