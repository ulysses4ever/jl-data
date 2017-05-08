module ThreeValuedLogic

#=
truth tables from multiple sources
exists and forall are from
http://es.cs.uni-kl.de/publications/datarsg/BrSc05.pdf
=#

import Base:convert, promote_rule, show, showcompact,
            (!), (&), (|), ($), (*), (<=), (>=), (>), (<), (==),
            (===), (!=), (.==)

export True, Maybe, False,
       unk,tru,fal,not,and,or,xor,imp,(→),
       ltn,lte,gte,gtn,eql,neq,
       logictable


abstract ThreeValued <: Integer

immutable TVL <: ThreeValued
    v::Int8

    function TVL(v::Int8)
        if one(Int8) <= v < (one(Int8)<<2)
            new(v)
        else
            throw(DomainError)
        end
    end
    function TVL(v::Bool)
        new( (v ? TRUE3 : FALSE3) )
    end
end


# set to 1..3 so we can index immediately
const False = TVL( one(Int8)     )
const Maybe = TVL( one(Int8) << 1)
const True  = TVL((one(Int8) << 1) + one(Int8) )

convert(::Type{TVL},x::Bool) = (x ? True : False)
promote_rule(::Type{TVL}, ::Type{Bool}) = TVL

const TVLnames = ("False","Maybe","True");
function show(io::IO, x::TVL)
    print(io, TVLnames[x.v])
end
const TVLchars = ("F","?","T");
function showcompact(io::IO, x::TVL)
    print(io, TVLchars[x.v])
end

isFalse(x::TVL)  = (x===False)
isFalse(x::Bool) = (x===false)
isTrue(x::TVL)   = (x===True)
isTrue(x::Bool)  = (x===true)
isMaybe(x::TVL)  = (x===Maybe)

const TVLnot = (True,Maybe,False);
not(x::TVL) = TVLnot[x.v]
not(x::Bool) = (x ? False : True)
(!)(x::TVL) = not(x)

const TVLunk = (False,True,False);
unk(x::TVL) = TVLunk[x.v]
unk(x::Bool) = False

const TVLtru = (False,True,True);
tru(x::TVL) = TVLtru[x.v]
tru(x::Bool) = True

const TVLfal = (False,False,True);
fal(x::TVL) = TVLfal[x.v]
fal(x::Bool) = False


const TVLand = ((False,False,False),(False,Maybe,Maybe),(False,Maybe,True));
(and)(x::TVL, y::TVL) = TVLand[x.v][y.v]
(&)(x::TVL, y::TVL) = (and)(x,y)

const TVLor = ((False,Maybe,True),(Maybe,Maybe,True),(True,True,True));
(or)(x::TVL, y::TVL) = TVLor[x.v][y.v]
(|)(x::TVL, y::TVL) = (or)(x,y)

const TVLxor = ((False,Maybe,True),(Maybe,Maybe,Maybe),(True,Maybe,False));
(xor)(x::TVL, y::TVL) = TVLxor[x.v][y.v]
($)(x::TVL, y::TVL) = (xor)(x,y)

const TVLimp = ((True,True,True),(Maybe,Maybe,True),(False,Maybe,True));
(imp)(x::TVL, y::TVL) = TVLimp[x.v][y.v]
(→)(x::TVL, y::TVL) = (imp)(x,y)

const TVLltn = ((False,True,True),(False,False,True),(False,False,False));
(ltn)(x::TVL, y::TVL) = TVLltn[x.v][y.v]
(<)(x::TVL, y::TVL) = (ltn)(x,y)

const TVLlte = ((True,True,True),(False,True,True),(False,False,True));
(lte)(x::TVL, y::TVL) = TVLlte[x.v][y.v]
(<=)(x::TVL, y::TVL) = (lte)(x,y)

const TVLgtn = ((False,False,False),(True,False,False),(True,True,False));
(gtn)(x::TVL, y::TVL) = TVLgte[x.v][y.v]
(>)(x::TVL, y::TVL) = (gtn)(x,y)

const TVLgte = ((True,False,False),(True,True,False),(True,True,True));
(gte)(x::TVL, y::TVL) = TVLgte[x.v][y.v]
(>=)(x::TVL, y::TVL) = (gte)(x,y)

const TVLeql = ((True,Maybe,False),(Maybe,True,Maybe),(False,Maybe,True));
(eql)(x::TVL, y::TVL) = TVLeql[x.v][y.v]
(==)(x::TVL, y::TVL) = (eql)(x,y)

const TVLneq = ((False,Maybe,True),(Maybe,False,Maybe),(True,Maybe,False));
(neq)(x::TVL, y::TVL) = TVLneq[x.v][y.v]
(!=)(x::TVL, y::TVL) = (neq)(x,y)

for L in [:and, :or, :xor, :imp, :ltn, :lte, :gte, :gtn, :eql, :neq]
    @eval begin
        ($L)(x::Bool, y::TVL) = ($L)(promote(x,y)...)
        ($L)(x::TVL, y::Bool) = ($L)(promote(x,y)...)
    end
end

function exists(v::Array{TVL,1})
    if any(isTrue, v)
        True
    elseif all(isFalse, v)
        False
    else
        Maybe
    end
end

function forall(v::Array{TVL,1})
    if all(isTrue, v)
        True
    elseif any(isFalse, v)
        False
    else
        Maybe
    end
end


#=
    quick show of logic ops and  their tables
=#


logictbls=Dict(zip(["and","or ","xor","imp","ltn","lte","gte","gtn","eql","neq"],
                   [TVLand,TVLor,TVLxor,TVLimp,TVLltn,TVLlte,TVLgte,TVLgtn,TVLeql,TVLneq]));

logictable() = ("unk","tru","fal","not","and","or","xor","imp","ltn","lte","gte","gtn","eql","neq")

function logictable(tblname::ASCIIString)
    tname = length(tblname) >= 3 ? tblname[1:3] : string(tblname,"  ")[1:3]
    if tname == "not" || tname == "unk"
       return unitable(tname, (tname=="not" ? TVLnot : TVLunk))
    elseif tname == "tru" || tname == "fal"
       return unitable(tname, (tname=="tru" ? TVLtru : TVLfal))
    end
    tbl = logictbls[tname]
    println()
    println("    ",tname[1:3],"   |  ","False","  ","Maybe","  ","True ")
    println("   ","-------+-----------------------")
    for i in 1:3
        print("    ",["False","Maybe","True "][i]," |  ")
        for j in 1:3
            a = tbl[i][j]
            print( (a===True ? "True " : a),"  " )
        end
        println()
    end
end

function unitable(name::ASCIIString, tbl::Tuple)
    println()
    println("    ",name,"   |  ")
    println("   ","-------+--------")
    for i in 1:3
        print("    ",["False","Maybe","True "][i]," |  ")
        println(tbl[i])
    end
end

end # Module
