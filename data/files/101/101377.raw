#Interpolate spectra using Grid.jl
module interpolation

using Grid
using spec_io
using HDF5

export rawgrid
export interp_spec

#For example, 5800 - 6400, logg = 4.2 to 4.3 (for this specific run), and Z = -1.0 to -0.1. This would only require 540 spectra to be interpolated.

#Also, it just works on fractional grid indices, so supposedly adding in functionality to map index to value is up to me.
#I want to design a interpolator function, wherby I give it temp, logg, Z, and it returns a spectrum.

fid = h5open("libraries/PHOENIX_F_julia_hires.hdf5", "r")

(temps, loggs, Zs), wl, grid = get_grid(fid)
println("loaded grid")

rawgrid = copy(grid)

println("These parameters are stored in this grid")
println(temps)
println(loggs)
println(Zs)

println("Size and strides")
sizes = size(grid)
strds = strides(grid)
println(sizes)
println(strds)

Npix = size(grid)[4]
println(Npix)
strd = stride(grid, 4)

xt = temps[1]:100:temps[end]
indext = linspace(1, length(temps), length(temps))
print("\nWill interpolate over ")
for (j,k) in zip(xt, indext)
    print(" ", j, " ", k)
end
tintp = CoordInterpGrid(xt, indext, BCnearest, InterpLinear)

xl = loggs[1]:0.5:loggs[end]
indexl = linspace(1, length(loggs), length(loggs))
print("\nWill interpolate over ")
for (j,k) in zip(xl,indexl)
    print(" ", j, " ", k)
end
lintp = CoordInterpGrid(xl, indexl, BCnearest, InterpLinear)

xz = Zs[1]:0.5:Zs[end]
indexz = linspace(1, length(Zs), length(Zs))
print("\nWill interpolate over ")
for (j,k) in zip(xz, indexz)
    print(" ", j," ",  k)
end
zintp = CoordInterpGrid(xz, indexz, BCnearest, InterpLinear)

function get_indices(temp, logg, Z)
    return Float64[tintp[temp], lintp[logg], zintp[Z]]
end

#interp_invert!(grid, BCnan, InterpCubic, 1:3)   # solve for generalized interp. coefficients
interp_invert!(grid, BCnil, InterpCubic, 1:3)   # solve for generalized interp. coefficients
println("completed interp_invert!")

ic = InterpGridCoefs(eltype(grid), InterpCubic, sizes[:3], strds[:3])    # prepare for interpolation on this grid
println("InterpGridCoefs done")

#Do cubic spline interpolation for a spectrum
function interp_spec(temp, logg, Z)
    #First, set the grid position to the indices corresponding to these parameters
    indices = get_indices(temp, logg, Z)
    println("Setting position to", indices)
    set_position(ic, BCnil, false, false, indices)

    #Iterate over the pixels in the spectrum
    spec = Array(Float64, (Npix,))
    index = 1
    for i = 1:Npix
        spec[i] = interp(ic, grid, index)
        index += strd
    end

    return spec
end

# Function to take in parameters, interpolate the spectrum from the grid, 
# and then insert it into an HDF5 file.
function insert_into_grid(temp, logg, Z, fid::HDF5File)
    alpha = 0.0

    spec = interp_spec(temp, logg, Z)

    #create format string
    key = @sprintf("flux/t%0.0fg%0.1fz%0.1fa%0.1f", temp, logg, Z, alpha)
    fid[key] = spec
    dset = fid[key]

    #Format these values to be inserted into the header
    attrs(dset)["temp"] = temp
    attrs(dset)["logg"] = logg
    attrs(dset)["Z"] = Z
    attrs(dset)["alpha"] = alpha

end

# Create grid from lists of desired temperatures, loggs, and Zs
function create_grid(filename, temps, loggs, Zs)
    # Create the HDF5 file
    fid = h5open(filename, "w")

    # Add in the wl
    fid["wl"] = wl

    # Iterate through all of the combinations of temp, logg, and Z, 
    # filling in the grid
    for temp in temps
        for logg in loggs
            for Z in Zs
                insert_into_grid(temp, logg, Z, fid)
            end
        end
    end

    close(fid)

end


end
