immutable Frame
    num::Int
end

Base.string(f::Frame) = string(f.num)

immutable RelativeOrbit
    num::Int
end

Base.string(r::RelativeOrbit) = string(r.num)

validate(r::RelativeOrbit,p::Platform{:ALOS})      = 1<=r.num<=671
validate(r::RelativeOrbit,p::Platform{:ERS1})      = 0<=r.num<=2410
validate(r::RelativeOrbit,p::Platform{:ERS2})      = 0<=r.num<=500
validate(r::RelativeOrbit,p::Platform{:JERS1})     = 0<=r.num<=658
validate(r::RelativeOrbit,p::Platform{:RADARSAT1}) = 0<=r.num<=342
validate(r::RelativeOrbit,p::Platform{:SEASAT})    = 0<=r.num<=243
