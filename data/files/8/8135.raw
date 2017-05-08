module DitherImage

export ditherimage

function ditherimage(img::Array{Float64,2}, t::Task)
    width = size(img, 1)
    height = size(img, 2)
    tmp = copy(img)
    out = zeros(Float64, width, height)

    for i = 1:height
        for j = 1:width
            weights = consume(t)
            weights_sum = sum(weights)

            if tmp[j, i] >= 0.5
                out[j, i] = 1.0
            else
                out[j, i] = 0.0
            end

            diff = tmp[j, i] - out[j, i]

            if j < width
                tmp[j + 1, i] += diff * weights[1] / weights_sum
            end

            if i < height
                if j > 1
                    tmp[j - 1, i + 1] += diff * weights[2] / weights_sum
                end

                tmp[j, i + 1] += diff * weights[3] / weights_sum

                if j < width
                    tmp[j + 1, i + 1] += diff * weights[4] / weights_sum
                end
            end
        end
    end

    out
end

function ditherimage(img::Array{Float64,2})
    ditherimage(img, @task begin
        while true
            produce([7, 3, 5, 1])
        end
    end)
end

end #module
