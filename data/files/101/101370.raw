"""
Read in spectral data. 

Provides the DataSpectrum object as well as tools to read in synthetic spectra.

Each wls, fls, and sigmas should be stored as a 2D array.

Load and return a "Dataset" object.

"""
module spec_io


using HDF5 

export DataSpectrum, openData
export loadSpec
export get_grid

type DataSpectrum
    wls::Array{Float64, 2}
    fls::Array{Float64, 2}
    sigmas::Array{Float64, 2}
end

#Allow any 2D, floating point arrays to be given, but convert these to Float64 for computation.
DataSpectrum(wls::Array{FloatingPoint, 2}, fls::Array{FloatingPoint, 2}, sigmas::Array{FloatingPoint, 2}) = DataSpectrum(float64(wls), float64(fls), float64(sigmas))

"""
openData

Initialize a DataSpectrum type from a filename.

Example code:
    mySpec = openData("data/WASP14-2009-06-14.hdf5")
    println(mySpec.wls[1:10,1])
    println(typeof(mySpec))
    println(typeof(mySpec.fls))
"""
function openData(filename::String)
    fid = h5open(filename, "r")
    #Julia is indexed by column, row
    wls = fid["wls"][:,:]
    fls = fid["fls"][:,:]
    sigmas = fid["sigmas"][:,:]
    close(fid)
    return DataSpectrum(wls, fls, sigmas)
end


#Perhaps first we need to extend the HDF5 type to have some more attributes, for example arrays that provide keyword access?

"""
loadFlux

Return a flux array from an HDF5 grid that has been "stuffed."
"""
function loadSpec(temp, logg, Z, alpha, fid::HDF5File)
    #Convert the parameters to a lookup key using the format string. 
    #There really aren't too many ways to simplify this, since @sprintf is a macro  
    #It needs to see four arguments, since there are four format strings, so we can't use
    #splatting like vars and vars... to save typing.
    key = @sprintf("flux/t%0.0fg%0.1fz%0.1fa%0.1f", temp, logg, Z, alpha)

    #Load and the spectrum from the (HDF5) file, convert to Float64
    spec = fid[key][:]
    return float64(spec)
end

"""
get_grid

Load all of the spectra stored in the HDF5 file into a large array in memory.

"""
function get_grid(fid::HDF5File)
    #Go through all of the possible flux keys, and parse the parameter values 
    #from the header into unique lists.

    wl = read(fid, "wl")

    alpha = 0.0 #Ignore alpha for now to simplify things
    flux = fid["flux"]
    temps = Any[]
    loggs = Any[]
    Zs = Any[]
    keys = Any[]
    for obj in flux
        attr = attrs(obj)
        push!(temps, read(attr, "temp"))
        push!(loggs, read(attr, "logg"))
        push!(Zs, read(attr, "Z"))
        push!(keys, name(obj))
    end


    temps = sort!(unique(temps))
    loggs = sort!(unique(loggs))
    Zs = sort!(unique(Zs))

    dset = fid[keys[1]]
    Npix = size(dset)[1]

    #Now, create a 4D array that is (Ntemp, Nlogg, NZ, Npix). 
    #The pixels are obviously the fastest changing dimension, but here they are 
    #put in the spot reserved for the slowest changing index. This is because the
    #interpolation routines for which this grid will be used will have pixel number 
    #as the slowest changing dimension.
    #Read all spectra into it
    grid = Array(Float64, (length(temps), length(loggs), length(Zs), Npix))
    for (t, temp) in enumerate(temps)
        for (l, logg) in enumerate(loggs)
            for (z, Z) in enumerate(Zs)
                grid[t, l, z, :] = loadSpec(temp, logg, Z, alpha, fid)
            end
        end
    end
        
    #Return both the parameter keys to the grid and the grid itself

    return (temps, loggs, Zs), wl, grid
end



end
