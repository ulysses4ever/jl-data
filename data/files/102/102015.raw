module sequenceCompare
    export DTWDistance

    # http://en.wikipedia.org/wiki/Dynamic_time_warping
    function DTWDistance{T}(s::Array{T}, t::Array{T})
        n, m = size(s,2), size(t, 2)
        DTW = zeros(n+1,m+1)
        #println("sizeof DTW: ", size(DTW))
        DTW[:,1], DTW[1,:] = Inf, Inf
        DTW[1,1] = 0

        for i=2:n+1
            for j=2:m+1
                #println("i=", i, "/", n, " j=", j, "/", m, " size(s)=", size(s), " size(t)=", size(t))
                cost = sum((s[:,i-1] - t[:,j-1]).^2)

                DTW[i,j] = cost + min(DTW[i-1, j  ], #insertion
                                      DTW[i  , j-1], #deletion
                                      DTW[i-1, j-1]) #match
                #println("cost is ", cost, " i=", i, "/", n, " j=", j, "/", m, " DTW=", DTW[i,j])
            end
        end

        return DTW[n+1,m+1]
    end

    # note. there is also a windowed version for better performance!  See the wikipedia article
    function DTWDistance{T}(s::Array{T}, t::Array{T}, w::Int64)
        n, m = size(s,2), size(t, 2)
        w = max(w, abs(n-m))
        DTW = zeros(n+1,m+1)
        #println("sizeof DTW: ", size(DTW))
        DTW[:,:] = Inf
        DTW[1,1] = 0

        for i=2:n+1
            for j=max(2, i-w):min(m+1, i+w)
                #println("i=", i, "/", n, " j=", j, "/", m, " size(s)=", size(s), " size(t)=", size(t))
                cost = sum((s[:,i-1] - t[:,j-1]).^2)

                DTW[i,j] = cost + min(DTW[i-1, j  ], #insertion
                                      DTW[i  , j-1], #deletion
                                      DTW[i-1, j-1]) #match
                #println("cost is ", cost, " i=", i, "/", n, " j=", j, "/", m, " DTW=", DTW[i,j])
            end
        end

        return DTW[n+1,m+1]
    end

    function HaversineDistance{T}(lat1::T, lon1::T, lat2::T, lon2::T)
        REarth = 6371.
        lat, lon = (lat1-lat2)*π/180., (lon1-lon2)*π/180.
        lat1, lat2 = lat1*π/180., lat2*π/180.
        a = sin(lat/2)*sin(lat/2)+cos(lat1)*cos(lat2)*sin(lon/2)*sin(lon/2)
        d = 2*atan2(sqrt(a), sqrt(1-a))
        d = REarth*d

        return d
    end

    function RMSE{T}(pred::T, real::T)
        return sqrt(mean((pred-real).*(pred-real)))
    end

    function RMSLE{T}(pred::T, real::T)
    return sqrt(mean((log(pred+1)-log(real+1)).^2))
    end


    function meanHaversideDistance{T}(lat1::T, lon1::T, lat2::T, lon2::T)
        return mean(HaversideDistance{T}(lat1, lon1, lat2, lon2))
    end

    function TravelTimePredict(submission, answers)
        return RMSLE(submission, answers) 
    end

    function DestinationPredict(submission, answers)
        lat_sub, lon_sub = submission[:,1], submission[:,2]
        lat_real, lon_real = answers[:,1], answers[:,2]
        return meanHaversineDistance(lat_sub, lon_sub, lat_real, lon_real) 
    end

end