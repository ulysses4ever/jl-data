module ResidueClass

import Base: print, println,  *, /, -, +, ==, divrem, div, rem, copy, one, zero, sign, convert

using Polynomial

export Residue


### TO DO

##
# residue class ring with value a mod p^i
immutable Residue{T}

	val::T
	## generator of ideal
	p::T
	# power of ideal
	i::Int64
	# Ideal m = p^i, saved so that its computational more efficient
	m::T

	function Residue(val::T, p::T, i::Int, m::T) 
		sign(val) >= 0 ? new(val,p,i,m) : new(val+m,p,i,m)
	end
end

## Factory ##
Residue{T}(a::T, p::T) = Residue{T}(rem(a,p), p, 1, p)
Residue{T}(a::T, p::T, i::Int) = (m = p^i; Residue{T}(a % m, p, i, m))
Residue{T}(a::T, p::T, i::Int, m::T) = Residue{T}(a % m, p, i, m)
Residue{T}(newVal::T, a::Residue{T}) = Residue{T}(newVal % a.m, a.p, a.i, a.m)
ResidueInRange{T}(newVal::T, a::Residue{T}) = Residue{T}(newVal, a.p, a.i, a.m)
# erzeugt aus einer Liste von Polynomen die entsprechenden Polynome über dem Restklassenring
function Residue{T}(a::Vector{Poly{T}}, p::T, i::Int)
	m = p^i
	array = Array{Poly{Residue{T}}}(size(a))
	for k=1:length(a)
		array[k] = Poly(Residue{T}(a[k].a, p, i, m), a[k].var)
	end
	return array
end

function Residue{T}(a::Vector{T}, p::T, i::Int, m::T)
	array = Array{Residue{T}}(size(a))
	for k=1:length(a)
		array[k] = Residue{T}(a[k] % m, p, i, m)
	end
	return array
end

Residue{T}(a::Vector{T}, p::T, i::Int) = Residue(a, p, i, p^i)
Residue{T}(a::Vector{T}, p::T) = Residue(a, p, 1, p)

convert{T}(t::Type{Residue{T}}, a::Residue{T}) = a

copy(a::Residue) = Residue(a.val, a)
one{T}(a::Residue{T}) = Residue(one(T), a.p, a.i, a.m)
zero{T}(a::Residue{T}) = Residue(zero(T), a)

# REVIEW
one{T}(t::Type{Residue{T}}) = one(T)
zero{T}(t::Type{Residue{T}}) = zero(T)

# ## Printing ##

print(io::IO, a::Residue) = (a.i == 1) ? print(io, "$(a.val) mod $(a.p)") :  print(io, "$(a.val) mod $(a.p)^$(a.i)=$(a.m)")

# ## Equates ##
==(a::Residue, b::Residue) = ((a.p != b.p) || (a.i != b.i)) ? false : a.val == b.val
==(a::WeakRef,b::Residue{WeakRef}) = (Residue(a % b.m, b) == b)
==(a::Residue{WeakRef},b::WeakRef) = ==(b,a)

## Arithmetics ##

sign{T}(a::Residue{T}) = sign(a.val)

# plus #
+{T}(a::Residue{T}, b::Residue{T}) = (a.m != b.m) ? error("Can't add residues!") : Residue(a.val+b.val, a)
+{T}(a::Residue{T}, b::T) = Residue(a.val+b, a)
+{T}(a::T, b::Residue{T}) = +(b,a)

# minus #
-{T}(a::Residue{T}, b::Residue{T}) = (a.m != b.m) ? error("Can't add residues!") : Residue(a.val - b.val, a)
-{T}(a::Residue{T}, b::T) = Residue(rem(a.val - b,a.m), a)
-{T}(a::T, b::Residue{T}) = -(b,a)

# unary minus #
-{T}(a::Residue{T}) = Residue(-a.val, a)

# # multiply #
*{T}(a::T, b::Residue{T}) = Residue(rem(a * b.val, b.m), b)
*{T}(a::Residue{T}, b::T) = *(b,a)
*{T}(a::Residue{T}, b::Residue{T}) = (a.m != b.m) ? error("Can't multiply! Quotients ($(a.m) and $(b.m))") : Residue(a.val*b.val, b)
function *{T}(a::Vector{Residue{T}}, b::Residue{T})
	c = Array{Residue{T}}(size(a))
	for i=1:length(a)
		c[i] = a[i] * b
	end
	return c
end
 *{T}(a::Residue{T}, b::Vector{Residue{T}}) = *(b,a)


function ^{T}(a::Residue{T}, n::Int)
    
    if n == 0 
    	return ResidueInRange(one(T), a)
    end
    # a^-n = (a^-1)^n
    a_new = n > 0 ? a : inverse(a)
    b = copy(a_new)
    for k in reverse(digits(abs(n),2))[2:end]
        b = (k == 1) ? (b * b) * a_new : b * b
    end
    return b
end

# a is invertibale iff gcd(a, a.m) == 1, bezout coefficient s is then the inverse
function inverse{T}(a::Residue{T})
	(gcd, s, t) = gcdx(a.val, a.m)
    if gcd != one(T)
    	error("Value has no Inverse")
    end
    return Residue(s, a)
end

# division #

function divrem{T}(a::Residue{T}, b::Residue{T})
	if (a.m != b.m) 
		error("Quotients ($(a.m) and $(b.m))")
	end
	(div, rem) = divrem(a.val, b.val)
	return (Residue(div, a), Residue(rem, a))
end

div{T}(a::Residue{T}, b::Residue{T}) = divrem(a,b)[1]
rem{T}(a::Residue{T}, b::Residue{T}) = divrem(a,b)[2]
/{T}(a::Residue{T}, b::Residue{T}) = a * inverse(b)


# function gcdx{T}(a::Residue{T}, b::Residue{T}) 
# 	(gcd, s, t) = gcdx(a.val, b.val)
# 	return (Residue(gcd, a), Residue(s, a), Residue(t, a))
# end

# gcd{T}(a::Residue{T}, b::Residue{T}) = Residue(gcd(a.val, b.val), a)

end