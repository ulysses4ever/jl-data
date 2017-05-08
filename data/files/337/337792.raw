module SPH

using Vec

type Particles{T}
    count
    ★p
    p
    v
    Δp
    ω
    δ
    λ

    Particles(count::Int64) = new(count,
                                  Array(Vec3{Float64}, count),
                                  Array(Vec3{Float64}, count),
                                  Array(Vec3{Float64}, count),
                                  Array(Vec3{Float64}, count),
                                  Array(Vec3{Float64}, count),
                                  Array(Vec3{Float64}, count),
                                  Array(Vec3{Float64}, count))
end

end

function main()
  a = Vec3{Float64}(1.0,2.0,3.0)
  b = Vec3{Float64}(3.0,2.0,1.0)

  @code_native a⋅b
end

main()

