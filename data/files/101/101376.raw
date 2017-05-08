#Interpolate spectra using Grid.jl

using Grid
using spec_io
using HDF5

#For example, 5800 - 6400, logg = 4.2 to 4.3 (for this specific run), and Z = -1.0 to -0.1. This would only require 540 spectra to be interpolated.

#Also, it just works on fractional grid indices, so supposedly adding in functionality to map index to value is up to me.
#I want to design a interpolator function, wherby I give it temp, logg, Z, and it returns a spectrum.

fid = h5open("libraries/PHOENIX_F_julia_hires.hdf5", "r")

(temps, loggs, Zs), grid = get_grid(fid)

#Go through the setup once, for the first pixel.




#Then go do the interpolation for all of the other pixels.



#=

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

=#

close(fid)
