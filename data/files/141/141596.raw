# Julia Implementation of Horn-Schunk
module OpticalFlowAlgorithms

import Images: imfilter

function images_derivatives(img₁,img₂)

    k_x = [-1.0 1.0;-1.0 1.0]
    k_y = [-1.0 -1.0;1.0 1.0]
    k_t = ones(Float64,2,2)
    
    f_x = imfilter(img₁,k_x) + imfilter(img₂,k_x)
    f_y = imfilter(img₁,k_y) + imfilter(img₂,k_y)
    f_t = imfilter(img₁,-k_t) + imfilter(img₂,k_t)

    return f_x,f_y,f_t
end

function optical_flowHS(img₁,img₂,u₀,v₀,α::Float64,tol=1e-7)
    iter = 11
    # initialize u,v
    u = u₀ 
    v = v₀
    # compute the derivatives
    f_x,f_y,f_t = images_derivatives(img₁,img₂)
    # compute the average images
    k_av = [1/12 1/6 1/12;1/6 0 1/6;1/12 1/6 1/12]

    #while norm()

    for i in 1:iter

        #compute the local average of the flow vectors
        ū = imfilter(u,k_av)
        v̄ = imfilter(v,k_av)

        P = f_x .* ū + f_y .* v̄ + f_t
        D = α + (f_x).^2 + (f_y).^2

        u = ū - f_x .* (P ./ D)
        v = v̄ - f_y .* (P ./ D)

    end

    return u,v
end

export images_derivatives, optical_flowHS 
end

