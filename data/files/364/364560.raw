stod(str::String) = convert(Float64,parse(str))::Float64

line2Arr(str::String) = [stod(x) for x in split(str::String)]::Array{Float64}

function loadInit(init::IO)
        initLines=readlines(init)
        (ni, nh, no) = int(split(initLines[1]))
        Theta1 = zeros(nh,ni+1)
        for i=1:nh
                Theta1[i,:] = line2Arr(initLines[1+i])
        end
        Theta2 = zeros(no, nh+1)
        for i=1:no
                Theta2[i,:] = line2Arr(initLines[1+nh+i])
        end

        return ni, nh, no, Theta1, Theta2
end
