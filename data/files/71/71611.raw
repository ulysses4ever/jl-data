type Ray
    o::Vector{Float64}
    d::Vector{Float64}
    Ray(o,d)=if length(o)!=3 || length(d)!=3; error("only 3d"); else; new(o,d); end
end

type Plane
    p::Vector{Float64}
    n::Vector{Float64}
    kEps::Float64
    Plane(p,n,k)=if length(p)!=3 || length(n)!=3; error("only 3d"); else; new(p,n,k); end
end
Plane(p,n) = Plane(p,n,0.0)

function hit(pln::Plane, ray::Ray)
    t=dot((pln.p-ray.o),pln.n)/(dot(ray.d,pln.n))
    if t>pln.kEps
        return true
    else
        return false
    end
end

function test()
    pln = Plane([0,0,-20.0],[0,0,1.0])
    ray1 = Ray([0,0,0],[0,0,-1])
    ray2 = Ray([0,0,0],[1,0,0])
    ray3 = Ray([0,0,0],[0,1,0])
    hit(pln,ray1)?println("hit"):println("not hit")
    hit(pln,ray2)?println("hit"):println("not hit")
    hit(pln,ray3)?println("hit"):println("not hit")
end
