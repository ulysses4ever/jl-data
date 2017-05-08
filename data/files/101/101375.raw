#Interpolate spectra using Grid.jl

#First, some tests to make sure I understand Grid.jl

using Grid

#So, for each pixel, we will have a (ntemp, nlogg, nZ) array
NPIX = 262144
#NPIX = 100
Ntemp = 10
Nlogg = 10
NZ = 10

#Define a two dimensional (Gaussian) function
function Gaussian(w, x, y; z=1)
    return exp(-0.5/z^2 * w.^2 .* x.^2 .* y.^2)
end

temps = linspace(2700, 4000, Ntemp)
loggs = linspace(2.5, 6.0, Nlogg)
Zs = linspace(-1.0, 1.0, NZ)

#Evaluate this function over a 2D grid, but with z changing.
arr = Array(Float64, (Ntemp, Nlogg, NZ, NPIX))
for k in 1:NPIX
    for j in 1:NZ
        for i in 1:Nlogg
            for h in 1:Ntemp
                arr[h, i, j, k] = temps[h] + loggs[i] + Zs[j] + k #this is set from the raw library
            end
        end
    end
end

println("loaded grid")

println("about to invert")
interp_invert!(copy(arr)[:,:,:,1], BCnan, InterpCubic) 
println("inverted subslice")
#low-level interface
#solve for the generalized interpolation coefficients (invert the matrix)
interp_invert!(arr, BCnan, InterpCubic, 1:3) 
println("inverted full")

#Prepare for interpolation onto this grid
ic = InterpGridCoefs(arr[:,:,:,1], InterpCubic) 

#set the position and extract coefficients
set_position(ic, BCnil, false, false, [5.5, 5.5, 2.5]) 

println("inverted matrix")

#loop through interpolations in each channel
out_spec = Array(Float64, NPIX)
for i=1:NPIX
    println("index ",i) 
    out_spec[i] = interp(ic, arr[:,:,:,i])
end
println(out_spec)

#It takes about 4 minutes to do one spectrum.

#We'll have to try some testing here to see if it's appropriate to shortcut things by passing interp_invert! a sliced matrix.

#Just do the inversion alone, then do it combined. Anyway, this entire code block isn't super important at the moment.
