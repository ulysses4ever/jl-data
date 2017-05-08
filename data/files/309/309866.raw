using DataStructures
using Logging

import Base.show
# package code goes here

Logging.configure(level=DEBUG)
typealias TT_TYPE Array{UInt,1}
typealias IDX_TYPE UInt
typealias TV_TYPE Array{Real,1}

function __init__()
	println("loading MJPlayGround.jl")
	Logging.configure(level=DEBUG)
end

function init()
	global vvals = TV_TYPE()
	global pvals = TV_TYPE()
	global vidx = 1
	global pidx = 1
	global tt = TT_TYPE()
end


#export
#	Var, Par, @test, @var, @test1

#the AD types below
const TYPE_V = 1	#variable node
const TYPE_P = 2	#param node
const TYPE_OU = 3	#unary op
const TYPE_OB = 4  	#binary op
abstract Placeholder
immutable AD_V <: Placeholder
	idx::IDX_TYPE  #index on tape
	t::Uint    #type code
end
immutable AD_P <: Placeholder
	idx::IDX_TYPE  #index on tape
	t::Uint    #type code
end
immutable AD_O <: Placeholder
	idx::IDX_TYPE  #index on tape
    t::Uint    #type code	 
end

function AD_V(tt::TT_TYPE,val=NaN)
	push!(tt,vidx)
	push!(tt,TYPE_V)
	push!(vvals,val)
	global vidx +=1
	this = AD_V(length(tt),TYPE_V)
	return this
end

function AD_P(tt::TT_TYPE,val=NaN)
	push!(tt,pidx)
	push!(tt,TYPE_P)
	push!(pvals,val)
	global pidx +=1
	this = AD_P(length(tt),TYPE_P)
	return this
end

function AD_O(tt::TT_TYPE,oc, lidx::UInt)
	push!(tt,lidx)
	push!(tt,oc)
	push!(tt,TYPE_OU)
	this = AD_O(length(tt),TYPE_OU)
	return this
end


function AD_O(tt::TT_TYPE,oc, lidx::UInt, ridx::UInt)
	push!(tt,ridx)
	push!(tt,lidx)
	push!(tt,oc)
	push!(tt,TYPE_OB)
	this = AD_O(length(tt),TYPE_OB)
	return this
end


function Base.show(io::IO,m::AD_V)
	print("AD_V[",m.idx,"]")
end

function Base.show(io::IO,m::AD_P)
	print("AD_P[",m.idx,"]")
end

function Base.show(io::IO,m::AD_O)
	# print("(",m.l)
	# print(string(getOpSym(m)))
	# if(!isnull(m.r))
	# 	print(m.r.value)
	# end
	# print(")")
	print("AD_O[",m.idx,"]")
end




#Operator overloading function for AD types
const OP = (:+,:-,:*,:/,:sin,:cos)

function getOpSym(oc)
	return OP[oc]
end

const B_OP_START = 1
const B_OP_END = 4
for oc = B_OP_START:1:B_OP_END
	o = OP[oc]
	debug("setup operator ",o)
	eval(quote
			($o)(l::Placeholder,r::Placeholder) =
			begin
				debug("at",OP[$(oc)])
				this = AD_O(tt,$(oc),l.idx,r.idx)
				return this
			end
		end)
end

const U_OP_START = 5
const U_OP_END = 6
for oc = U_OP_START:1:U_OP_END
	o = OP[oc]
	debug("setup operator ",o)
	eval(quote
			($o)(l::Placeholder) =
			begin
				debug("at",$(oc))
				this = AD_O(tt,$(oc),l.idx)
				return this
			end
		end)
end

function evaluate(tt::TT_TYPE,idx::IDX_TYPE)
	println("enter - ",idx)
	ret = NaN
	if(idx != 0)
		ntype = tt[idx] #type node
		idx -= 1
		if(ntype == TYPE_P)
			ret = pvals[tt[idx]]
			idx -=1
		elseif(ntype == TYPE_V)
			ret = vvals[tt[idx]]
			idx -= 1
		elseif(ntype == TYPE_OB)
			oc = tt[idx]
			assert(B_OP_START<= oc <= B_OP_END)
			idx -= 1
			lidx = tt[idx]
			idx -= 1
			ridx = tt[idx]
			idx -= 1
			println("before left - ",lidx)
			(lval,idx) = evaluate(tt,lidx)
			println("before right - ",idx)
			(rval,idx) = evaluate(tt,ridx)
			ret = evaluate(oc,lval,rval)
		else
			oc = tt[idx]
			assert(U_OP_START <= oc <= U_OP_END)
			idx -= 1
			lidx = tt[idx]
			idx -= 1
			println("unary before  - ",idx)
			(lval,idx) = evaluate(tt,lidx)
			ret = evaluate(oc,lval)
		end
		println("now - ",idx)
	end
	assert(!isnan(ret))
	println("exit - ",idx)
	return ret,idx
end

function evaluate(oc::UInt,lval::Real,rval::Real)
	assert(B_OP_START<= oc <= B_OP_END)
	ex = Expr(:call,OP[oc],lval,rval)
	println("evaluate:",ex)
	return eval(ex)
end


function evaluate(oc::UInt,lval::Real)
	assert(U_OP_START<= oc <= U_OP_END)
	ex = Expr(:call,OP[oc],lval)
	println("evaluate:",ex)
	return eval(ex)
end


## Interface method
function feval(tt::TT_TYPE)
	(val,idx) = evaluate(tt,convert(UInt,length(tt)))
	assert(idx == 0)
	return val
end


#macro rewrite(expr)
#	print(expr)
#	debug("rewrite ",expr)
#	return :(4+3)
#end

macro var(x)
	quote
	debug("var - ",$(esc(x)i))
	#v = Var($global_idxi)
	#$(esc(global_idx)) += 1
	global global_idx += 1
	#push!(s,v)
	end
end

macro test(args...)
	println("---",length(args))
	arg1 = args[1]
	arg2 = args[2]
	code = quote
		local a = $(esc(m))
		#local b = $expr;
		local c = $(esc(arg1))
		dump($(esc(arg1)))
	end
	return code
end

ex = :(3+3)

macro test1(ex)
	code =:()
	code = :($code;ex=3 
		#dump($(esc(ex)))
		#println($(esc(ex)))
		#a = $(esc(ex))
		#dump($ex)
		#println(eval($(ex)))
	 	#$(ex), $(esc(ex))
	)
	return code
end

macro test2(ex...)
	quote
		x = 1
		$(esc(ex...))
		nothing
	end
end


macro p(n)
    if typeof(n) == Expr 
       println(n.args)
    end
    eval(n)
end

macro f(x)
       quote
           s = 4
           (s, $(esc(s)))
       end
end

macro dotimes(n,body)
	quote
		for i=1:$(esc(n))
			$(esc(body))
		end
	end
end
