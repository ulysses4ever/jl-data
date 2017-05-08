#! /usr/bin/julia

# Make a pretty graphic for a Rosetta Code task

using Color, Images, FixedPointNumbers

const w = 10
const h = 16
const cw = 4w
const ch = 4h
const cnum = 11
const fw = (cnum + 1)*cw
const snum = 3
const hskip = 2h
const fh = snum*ch + (snum + 1)*hskip
const bh = 3h

chips = zeros(RGB{Ufixed8}, cnum, snum)
chips[:,1] = colormap("Reds", cnum)
chips[:,2] = colormap("Greens", cnum)
chips[:,3] = colormap("Blues", cnum)

a = fill(RGB{Ufixed8}(0.5, 0.5, 0.5), fh, fw)
img = Image(a)

bwr = w:(1+fw-w)
bhr = 1:bh
cwr = 1:cw
chr = 1:ch

for i in 1:snum
    hoff = ch + (i-1)*(ch + hskip)
    img["x", bwr, "y", bhr+hoff-bh] = RGB(1, 1, 1)
    img["x", bwr, "y", bhr+hoff] = RGB(0, 0, 0)
    for j in 1:cnum
        woff = 2w + (j-1)*cw
        img["x", cwr+woff, "y", chr+hoff-2h] = chips[j, i]
    end
end

imwrite(img, "color_chips.ppm")
imwrite(img, "color_chips.png")
