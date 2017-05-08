# zad1 done. zad 2
# a)
exp(0.18)
exp([1,2])
# b)
eye(10)
#c
A = [1 2 3; 0 -1 0; 3 2 1]
inv(A)
#d
B = (A*A)'
show(B)

#zad 3
σ2 = 0.5
gaussian1d(x, m, s) = 1/sqrt(2*s*π)*exp(-(x-m)^2/(2*s))
gaussian1d(0.2, 0.2, 0.3)
gaussian1d(0, 0, 1)

function gaussian1d_b(x, m, s)
  σ2 = 2*s
  return 1.0/sqrt(σ2*π) * exp(-(x-m)^2 / σ2)
end;

gaussian1d_b(0, 0, 1)

#zad 4
x = [0 0.2 0.5]
m = [0 0.2 0]
s = [1.0 0.3 1]

gaussian1d(x, m, s) = 1./sqrt(s*2*π).*exp(-(x-m).^2/(2*s))
println(gaussian1d(x, m, s))

A = [x; m; s]'
for i in 1:3
  println(gaussian1d(A[i,1],A[i,2],A[i,3]))
end


#zad 5
using Images
using ImageView

function toGrayscaleArray(o)
  return convert(Array, data(convert(Image{Gray}, float32(separate(o)))));
end;

function loadImage(image)
  return toGrayscaleArray(imread(image));
end;

function loadFingerprints()
  folder="D:/biometryczne/odciski"
  files = ["$folder/$i\_$j.jpg" for i in 1:8, j in 1:4][:]
  show(files)
  return [loadImage(image) for image in files ]
end;

function showFingerprint(o)
  view(convert(Image, o))
end;

fingerprints = loadFingerprints()

fingerprint = fingerprints[2]
showFingerprint(fingerprint)

raw = reinterpret(Float32, (fingerprint))

mean(raw)
std(raw)


lerp(x, min, max) = (x - min) ./ max

a = minimum(raw)
b = maximum(raw)

using Color

Color.colormap("RdBu")

function colorize(grayscaleImage, colorMap)
  cm = colormap(colorMap)
  return map( x -> cm[max(1, min(round(Int32, 100 *  x), 100))], grayscaleImage );
end;

view(colorize(raw, "RdBu"))
moreContrast = 1.0 - lerp(raw * 1.3, a, b)
showFingerprint(colorize(moreContrast, "Greens"))
