

new_var(Q, Nel) = zeros(Q,Q,Nel)

function deriv_x!(elems::Array{Element2d,1}, f::Array{Float64,3}, dx::Array{Float64,3})

    Q = size(f,1)
    ws = zeros(Q,Q)
    Nel = length(elems)
    for e = 1:Nel
        deriv_x!(elems[e], sub(f,:,:,e), sub(dx,:,:,e), ws)
    end
end

function deriv_y!(elems::Array{Element2d,1}, f::Array{Float64,3}, dy::Array{Float64,3})

    Q = size(f,1)
    ws = zeros(Q,Q)
    Nel = length(elems)
    for e = 1:Nel
        deriv_y!(elems[e], sub(f,:,:,e), sub(dy,:,:,e), ws)
    end
end
