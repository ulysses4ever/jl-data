module diferenciacion

export upbar

type upbar
f
d
end

function +(v::upbar,w::upbar)
    res=upbar(Any,Any)
    res.f=v.f+w.f
    res.d=v.d+w.d
    res
end
function +(v::upbar,a)
    res=upbar(Any,Any)
    w=upbar(a,0)
    res.f=v.f+w.f
    res.d=v.d+w.d
    res
end
function +(a,w::upbar)
    res=upbar(Any,Any)
    v=upbar(a,0)
    res.f=v.f+w.f
    res.d=v.d+w.d
    res
end
function -(v::upbar,w::upbar)
    res=upbar(Any,Any)
    res.f=v.f-w.f
    res.d=v.d-w.d
    res
end
function -(v::upbar,a)
    res=upbar(Any,Any)
    w=upbar(a,0)
    res.f=v.f-w.f
    res.d=v.d-w.d
    res
end
function -(a,w::upbar)
    res=upbar(Any,Any)
    v=upbar(a,0)
    res.f=v.f-w.f
    res.d=v.d-w.d
    res
end
function *(v::upbar,w::upbar)
    res=upbar(Any,Any)
    res.f=v.f*w.f
    res.d=(v.f*w.d)+(v.d*w.f)
    res
end
function *(v::upbar,a)
    res=upbar(Any,Any)
    w=upbar(a,0)
    res.f=v.f*w.f
    res.d=(v.f*w.d)+(v.d*w.f)
    res
end
function *(a,w::upbar)
    res=upbar(Any,Any)
    v=upbar(a,0)
    res.f=v.f*w.f
    res.d=(v.f*w.d)+(v.d*w.f)
    res
end
function /(v::upbar,w::upbar)
    res=upbar(Any,Any)
    res.f=v.f/w.f
    res.d=(v.d*w.f-v.f*w.d)/((w.f)^2)
    res 
end
function /(v::upbar,a)
    res=upbar(Any,Any)
    w=upbar(a,0)
    res.f=v.f/w.f
    res.d=(v.d*w.f-v.f*w.d)/((w.f)^2)
    res 
end
function /(a,w::upbar)
    res=upbar(Any,Any)
    v=upbar(a,0)
    res.f=v.f/w.f
    res.d=(v.d*w.f-v.f*w.d)/((w.f)^2)
    res 
end
function ^(u::upbar,a::Float64)
    res=upbar(Any,Any)
    res.f=u.f^a
    res.d=a*((u.f)^(a-1))*u.d
    res
end

end
