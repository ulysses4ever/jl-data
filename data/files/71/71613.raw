# 光线
type Ray
    o::Vector{Float64}
    d::Vector{Float64}
    Ray(o,d)=if length(o)!=3 || length(d)!=3; error("only 3d"); else; new(o,d); end
end

# 存储交点信息
type ShadeRec
    n::Vector{Float64}
    hitp::Vector{Float64}
    ShadeRec(n,hitp)=if length(hitp)!=3 || length(n)!=3; error("only 3d"); else; new(n,hitp); end
end

# 无限平面
type Plane
    p::Vector{Float64}
    n::Vector{Float64}
    kEps::Float64
    Plane(p,n,k)=if length(p)!=3 || length(n)!=3; error("only 3d"); else; new(p,n,k); end
end
Plane(p,n) = Plane(p,n,0.0)

# 平面相交测试
function hit(pln::Plane, ray::Ray)
    t=dot((pln.p-ray.o),pln.n)/(dot(ray.d,pln.n))
    if t>pln.kEps
        sr = ShadeRec(ray.o+t*ray.d,pln.n)
        return true, sr # 相交时返回交点信息
    else
        return false
    end
end

# 世界


# 视平面


function test()
    pln = Plane([0,0,-20.0],[0,0,1.0])
    ray1 = Ray([0,0,0],[0,0,-1])
    ray2 = Ray([0,0,0],[1,0,0])
    ray3 = Ray([0,0,0],[0,1,0])
    hit(pln,ray1)[1]?println("hit"):println("not hit")
    hit(pln,ray2)[1]?println("hit"):println("not hit")
    hit(pln,ray3)[1]?println("hit"):println("not hit")
end
