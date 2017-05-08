#! /usr/bin/julia

# Rosetta Code, Bitmap/Histogram


using Color, Images, FixedPointNumbers
 
ima = imread("bitmap_histogram_in.jpg")
imb = convert(Image{Gray{Ufixed8}}, ima)

g = float(imb.data)
b = g .> median(g)
fill!(imb, Gray(0.0))
imb[b] = Gray(1.0)

imwrite(imb, "bitmap_histogram_out.png")

