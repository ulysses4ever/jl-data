using DitherImage
using Base.Test
using Images
using TestImages

img = testimage("lena_gray_256")
imA = convert(Array{Float64, 2}, data(img))
imA_out = ditherimage(imA)
img_expected = load("lena_dither.png")
imA_expected = convert(Array{Float64, 2}, data(img_expected))

w = size(imA_out, 1)
h = size(imA_out, 2)
@test w == size(imA_expected, 1)
@test h == size(imA_expected, 2)

for i = 1:h
    for j = 1:w
        @test imA_out[w, h] == imA_expected[w, h]
    end
end
