for modeln in ( :NormalPfModels, 
                :RNormalPfModels,
                :TPfModels,
                :RTPfModels )
    @eval begin
        function ordinarysamplingSIMval(BB::Int64, mm::$modeln, upval::Float64)
            μ = 0.0
            σ2 = 0.0
            for kk in 1:BB
                ans= ordinarysampling( mm, upval)
                μ += ans
                σ2 += ans^2
            end
            μ = μ/BB
            σ2 = σ2/BB - μ^2
            return (μ,σ2)
        end
        function ordinarysampling2SIMval(BB::Int64, mm::$modeln, upval::Float64)
            μ = 0.0
            σ2 = 0.0
            for kk in 1:BB
                ans= ordinarysampling2( mm, upval)
                μ += ans
                σ2 += ans^2
            end
            μ = μ/BB
            σ2 = σ2/BB - μ^2
            return (μ,σ2)
        end
    end
end

for modeln in ( :NormalPfModels, 
                :RNormalPfModels)
    @eval begin
        function importantsamplingSIMval(BB::Int64, mm::$modeln, upval::Float64)
            μ = 0.0
            σ2 = 0.0
            for kk in 1:BB
                ans= importantsampling( mm, upval)
                μ += ans
                σ2 += ans^2
            end
            μ = μ/BB
            σ2 = σ2/BB - μ^2
            return (μ,σ2)
        end
    end
end

for modeln in ( :TPfModels,
                :RTPfModels )
    @eval begin
        function condmcSIMval(BB::Int64, mm::$modeln, upval::Float64)
            μ = 0.0
            σ2 = 0.0
            for kk in 1:BB
                ans= condmc( mm, upval)
                μ += ans
                σ2 += ans^2
            end
            μ = μ/BB
            σ2 = σ2/BB - μ^2
            return (μ,σ2)
        end
    end
end

function condmcceSIMval(BB::Int64, mm::TPfModels, upval::Float64, muis::Vector{Float64}, varis::Vector{Float64} )
 
    μ = 0.0
    σ2 = 0.0
    for kk in 1:BB
        ans=condmcce( mm, upval, muis, varis )
        μ += ans
        σ2 += ans^2
    end
    μ = μ/BB
    σ2 = σ2/BB - μ^2
    
    return (μ,σ2)
end

function condmcceSIMval(BB::Int64, mm::RTPfModels, upval::Float64, muis::Vector{Float64}, varis::Vector{Float64}, gamis::Vector{Float64} )
    μ = 0.0
    σ2 = 0.0
    for kk in 1:BB
        ans=condmcce( mm, upval, muis, varis, gamis )
        μ += ans
        σ2 += ans^2
    end
    μ = μ/BB
    σ2 = σ2/BB - μ^2
    
    return (μ,σ2)  
end
