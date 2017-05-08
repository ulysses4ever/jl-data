module Polynomial

import Base: print, println,  *, /, -, +, ==, divrem, div, rem, copy, one, zero, gcd, gcdx, lcm, call

using ResidueClass

export Poly, deg, ZeroPoly, Monom, lc, shift, Ring, EEA

## Comments ##
#
# No implicit type promotion to mymic closedness of mathematical operations in rings and fields
#
# Algorithms mostly based on Modern Computer Algebra (MCA) from Joachim von zu Gathen Jürgen Gerhard (Edition 2013)
#


immutable Poly{T}
	
    a::Vector{T}
    var::Symbol

    function Poly(a::Vector{T}, var::Symbol)
    	# delete leading zeros
    	i = length(a)
    	while a[i] == 0 && i > 1
    		i -= 1
    	end
    	i < length(a) ? new(a[1:i], var) : new(a,var)
    end
end

## Factory ##

Poly{T}(a::Vector{T}, var) = Poly{T}(a, symbol(var))
Poly{T}(a::Vector{T}) = Poly{T}(a, :X)

# returns poly X^d
function Monom{T}(sample::T, d::Int, var)
	a = Array{T}(d+1)
	for k in 1:d
		a[k] = zero(sample)
	end
	a[d+1] = one(sample)
	return Poly(a, symbol(var))
end

copy(p::Poly) = Poly(p.a, p.var)
one{T}(p::Poly{T}) = Poly([one(p[0])], p.var)
zero{T}(p::Poly{T}) = Poly([zero(p[0])], p.var)

one{T}(t::Type{Poly{T}}) = Poly([one(T)], :x)
# zero{T}(t::Type{Poly{T}}) = ZeroPoly(T, :x)


## Evaluation ##

# with this can poly p be evaluated with p(arg)
function call{T}(p::Poly{T},arg::T)
	# implementation of Horners Rule
	n = length(p.a)
	val = p.a[n]
	for i in n-1:-1:1
    	val *= arg
    	val += p.a[i]
	end
	return val
end


## Wieso klappt das nicht?!?

# with this can poly p be evaluated with p(arg)
# function call{T}(p::Poly{ResidueClass.Residue{T}},arg::T)
# 	# implementation of Horners Rule
# 	n = length(p.a)
# 	val = p.a[n]
# 	for i in n-1:-1:1
#     	val *= arg
#     	val += p.a[i]
# 	end
# 	return val
# end

## Printing ##

function printExponent(io::IO, var, i::Number)

	if i==0
	elseif i == 1
		print(io, var)
	else
		print(io, var,"^",i)
	end
end

function print{T<:Number}(io::IO, p::Poly{T})

	n = length(p.a)
	printed = false
	_one = one(p[0])
	_zero = zero(p[0])
	for i in n:-1:1 
		c = p.a[i]
		if i < n && c > _zero && printed
			print(io, "+")
		end
		if (c != _zero) && (c!= _one || i == 1)
			print(io,c)
			printed = true
		end
		if (c != _zero) 
			printExponent(io, p.var, i-1)
			printed = true
		end
	end
	if !printed
		return  print(io, "0")
	end
end

function print{T}(io::IO, p::Poly{T})

	n = length(p.a)
	printed = false
	_one = one(p[0])
	_zero = zero(p[0])
	for i in n:-1:1 
		c = p.a[i]
		if i < n && c != _zero && printed
			print(io, "+")
		end
		if (c != _zero) && (c != _one || i == 1)
			print(io,"(",c,")")
			printed = true
		end
		if (c != _zero )
			printExponent(io, p.var, i-1)
			printed = true
		end
	end
	if !printed
		return  print(io, "0")
	end
end

## Indexing ##

getindex{T}(p::Poly{T}, i) = (i+1 > length(p.a) ? zero(p[0]) : p.a[i+1])

function setindex!{T}(p::Poly{T}, x, i0::Real)

	delta = i0+1 - length(p.a)
	if delta > 0
		_zero = zero(p[0])
		extension = Array{T}(delta)
		for k in 1:delta
			extension[k] = _zero
		end 
		extension[delta] = convert(T,x)
		p.a = [p.a; extension]
	else 
		p.a[i0+1] = convert(T,x)
	end
	return p
end


deg(p::Poly) = length(p.a) - 1

lc(p::Poly) = last(p.a)
sign(p::Poly) = sign(lc)

## Equates ##
function ==(p::Poly, q::Poly)
	if deg(p) != deg(q)
		return false
	elseif deg(p) > 0 && (p.var != q.var)
		return false
	else 
		for i in 0:deg(p)
			if p[i] != q[i]
				return false
			end
		end
	end
	return true
end

==(a::WeakRef,p::Polynomial.Poly{WeakRef}) = deg(p) > 0 ? false : a == p[0]
==(p::Polynomial.Poly{WeakRef},a::WeakRef) = ==(a,p)

## Arithmetics ##

# plus #

function +{T,S}(p::Poly{T}, q::Poly{S})

	if p.var != q.var 
		error("Can't add polynomials with var $(p.var) and $(q.var)")
	end

	return Poly([p[i] + q[i] for i=0:max(deg(p), deg(q))], p.var)
end

function +{T}(p::Poly{T}, s::T)

	if deg(p) == 0
		return p[0] + s
	end

	q = copy(p)
	q[0] += s 
	return q
end

+{T}(s::T, p::Poly{T}) = +(p,s)

# minus #

function -{T}(p::Poly{T}, q::Poly{T})

	if p.var != q.var 
		error("Can't add polynomials with var $(p.var) and $(q.var)")
	end

	return Poly([p[i] - q[i] for i=0:max(deg(p), deg(q))], p.var)
end

function -(p::Poly, s::Number)

	if deg(p) == 0
		return p[0] - s
	end

	q = copy(p)
	q[0] -= s 
	return q
end

-(s::Number, p::Poly) = -(p,s)

# unary minus #
-(p::Poly) = Poly(-p.a, p.var)

# multiply #

*{T}(a::T, p::Poly{T}) = Poly(a * p.a, p.var)
*{T}(p::Poly{T}, a::T) = *(a,p)

function *{T}(p::Poly{T}, q::Poly{T})

	if p.var != q.var 
		error("Can't multiply polynomials with var $(p.var) and $(q.var)")
	end
	n = deg(p)
	m = deg(q)

	c = Array{T}(n+m+1)
	# because of residue class -> m has to be known
	for k=1:n+m+1
		c[k]=zero(p[0])
	end
	for i in 1:n+1
		if p[i-1] != 0
    		c[i:m+i] += p[i-1] * q.a
    	end
	end 

	return Poly(c, p.var)

end

function ^{T}(p::Poly{T}, n::Int)
    
    if n < 0 
    	error("Cannot raise an polynomial p to a negative power -n")
    elseif n == 0
    	return one(p)
    end
    b = copy(p)
    for k in digits(n,2)[2:end]
        b = (k == 1) ? (b * b) * p : b * b
    end
    return b
end

# division #

function divrem{T}(p::Poly{T}, q::Poly{T})

	n = deg(p)
	m = deg(q)

	m > n && return (ZeroPoly(T, q.var), q)

	q_coeff = Array{T}(n-m+1)
	for k in 1:n-m+1
		q_coeff[k] = zero(p[0])
	end
	r = copy(p)
	u = one(p[0]) / lc(q)
	try u = convert(T, u)
	catch	
		error("For divrem(p,q) is lc(q)=$(lc(q)) not a unit in $(T)")
	end

	for i in n-m:-1:0 
		if deg(r) == m+i
			q_coeff[i+1] = lc(r) * u
			r = r - shift(q_coeff[i+1] * q, i)
		else 
            q_coeff[i+1] = zero(p[0])
		end
	end

	return (Poly(q_coeff, q.var), r)
end

div{T}(p::Poly{T}, q::Poly{T}) = divrem(p,q)[1]
rem{T}(p::Poly{T}, q::Poly{T}) = divrem(p,q)[2]

function /{T}(p::Poly{T}, q::Poly{T})
	(div, rem) = divrem(p,q)
	if deg(rem) > 0 || rem[0] == zero(p[0])
		error("$(q) is no divisor of $(p)!")
	else
		return div
	end
end

function /{T}(p::Poly{T}, a::T)
    new_p = copy(p)
    for i in 1:length(p.a)
        p.a[i] /= a
    end
    return p
end


# For positive Integers multiplication with X^i
# For negative Integers a multiplication with X^-i, whereby we drop coefficients with j-i < 0,
# e.g. i = -2: X^5 + X -> X^3
function shift{T}(p::Poly{T}, i::Int)

	if i > 0
		zeros = Array{T}(i)
		for k in 1:i
			zeros[k] = zero(p[0])
		end
		return Poly([zeros; p.a], p.var)
	else 
		if abs(i) > deg(p) 
			return ZeroPoly(p[0], p.var)
		end
		return Poly(p.a[i+1:length(p.a)], p.var)
	end
end

## help functions ##

function isMonom{T}(p::Poly{T})

    lc(p) != one(p[0]) && return false
	_zero = zero(p[0])
 	deg(p) == _zero && return true

	for i in deg(p)-1:-1:0
		p[i] != _zero && return false
	end

	return true
end


#######################################################################################################################
#	A L G O R I T H M S	
#######################################################################################################################


#######################################################################################################################
# E X T E N D E D  E U C L I D E A N  A L G O R I T H M (EEA)  F O R  Z  A N D  k[X]
#
# Implementation after MCA Algoriithm 3.14
#
# Input: f,g in R = Z or k[X]
# Output: normalized gcd(f,g) and s,t in R, such that s * f + t * g = gcd(f,g) (Bezout - Coefficients)
#

lu{T}(a::Poly{T}) = (a == zero(a[0])) ? one(a[0]) : lc(a)
lu{T<:Int}(a::T) =  (a == 1) ? one(T) : sign(a)

normal(a::Int) = abs(a)
normal{T}(a::Poly{T}) = a / lu(a)

## EEA / gcdx in Julia
function gcdx{T}(f::Poly{T}, g::Poly{T})

	 _one = one(g[0])
    _zero = zero(f[0])

    rho0 = lu(f)
    rho1 = lu(g)
    r0 = normal(f)
    r1 = normal(g)
    s0 = (rho0 == _one || rho0 == -_one) ? rho0 : rho0^-1
    s1 = _zero
    t0 = _zero
    t1 = (rho1 == _one || rho1 == -_one) ? rho1 : rho1^-1

    while r1 != _zero
        q = div(r0, r1)
        println("q:",q)
        rho2 = lu(r0 - q * r1)
        if rho2 == _zero
        	break
        end
        # eventually gcd in Z[x] possible, if-else necessary since 2 / 1 = 2.0 -> InexactError
        if (rho0 == _one || rho0 == -_one) 
        	r2 = (r0 - q*r1) * rho2
        	s2 = (s0 - q*s1) * rho2
        	t2 = (t0 - q*t1) * rho2
        	r2 = (r0 - q*r1) * rho2
        else 
        	s2 = (s0 - q*s1) / rho2
        	t2 = (t0 - q*t1) / rho2
        	r0 = r1
        	r1 = r2
        end
        rho0 = rho1
        rho1 = rho2
        t0 = t1
        t1 = t2
        s0 = s1
        s1 = s2
    end
    
    return (r0, s0, t0)
end

# efficient implementation if gcdx final
gcd{T}(f::Poly{T}, g::Poly{T}) = gcdx(f,g)[1]

lcm{T}(f::Poly{T}, g::Poly{T}) = (f * g) / gcd(f,g)


###########
##
## Interpolation

## Newton Interpolation
#  Implementation after Zippel, Effective Polynomial Computing (1993), p.217
function NewtonInterpol{T}(p::Poly{T}, values::Vector{T})

	(deg(p) != length(values)-1) &&	error("Not enough points to interpolate")

	f = zero(p)
	q = one(p)
	for a in values
		q_a = q(a)
		f = q_a != 0 ? f + (q_a^-1) * q * (p(a)-f(a)) : f
		q = Poly([-a, one(a)], p.var) * q
	end
	return f
end








end




















