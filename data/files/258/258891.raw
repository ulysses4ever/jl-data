module diferenciacion_automatica

export EvaluarDerivar

type EvaluarDerivar
ev
der
end

function +(A::EvaluarDerivar,B::EvaluarDerivar)
	EvaluarDerivar(A.ev+B.ev,A.der+B.der)
end

+(A::EvaluarDerivar,c::Number)= EvaluarDerivar(A.ev+c,A.der)

function -(A::EvaluarDerivar,B::EvaluarDerivar)
	EvaluarDerivar(A.ev-B.ev,A.der-B.der)
end

-(A::EvaluarDerivar,c::Number)= EvaluarDerivar(A.ev-c,A.der)

function *(A::EvaluarDerivar,B::EvaluarDerivar)
	EvaluarDerivar(A.ev*B.ev,A.ev*B.der+A.der*B.ev)
end

function *(c::Number,A::EvaluarDerivar)
	EvaluarDerivar(c*A.ev,c*A.der)
end

function /(A::EvaluarDerivar,B::EvaluarDerivar)
	EvaluarDerivar(A.ev/B.ev, (A.der*B.ev-A.ev*B.der)/(B.ev^2))
end

function ^(A::EvaluarDerivar, a::Integer)
	EvaluarDerivar(A.ev^a, a*(A.ev^(a-1))*A.der)
end

function ^(A::EvaluarDerivar, a::Number)
	EvaluarDerivar(A.ev^a, a*(A.ev^(a-1))*A.der)
end

import Base.exp

function exp(A::EvaluarDerivar)
	EvaluarDerivar(exp(A.ev),A.der*exp(A.ev))
end

import Base.log

function log(A::EvaluarDerivar)
	EvaluarDerivar(log(A.ev), A.der/A.ev)
end

import Base.sin

function sin(A::EvaluarDerivar)
	EvaluarDerivar(sin(A.ev), cos(A.ev)*A.der)
end

import Base.cos

function cos(A::EvaluarDerivar)
	EvaluarDerivar(cos(A.ev), -A.der*sin(A.ev))
end

import Base.tan
import Base.sec

function tan(A::EvaluarDerivar)
	EvaluarDerivar(tan(A.ev), A.der*sec(A.ev)^2)
end


end #modulo
