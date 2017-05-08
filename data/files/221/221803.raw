using MeasurementSets
using CasaCore.Tables
using Base.Test

srand(123)

let name = tempname()*".ms"
    ms = Table(name)
    Tables.addRows!(ms,5)

    ant1 = Array(Int32,5)
    ant2 = Array(Int32,5)
    uvw  = Array(Float64,3,5)
    time = Array(Float64,5)
    data      = Array(Complex64,4,109,5)
    model     = Array(Complex64,4,109,5)
    corrected = Array(Complex64,4,109,5)
    freq = Array(Float64,109,1)

    rand!(ant1)
    rand!(ant2)
    rand!(uvw)
    rand!(time)
    rand!(data)
    rand!(model)
    rand!(corrected)
    rand!(freq)

    ms["ANTENNA1"] = ant1
    ms["ANTENNA2"] = ant2
    ms["UVW"]      = uvw
    ms["TIME"]     = time
    ms["DATA"]           = data
    ms["MODEL_DATA"]     = model
    ms["CORRECTED_DATA"] = corrected

    spw = Table("$name/SPECTRAL_WINDOW")
    Tables.addRows!(spw,1)
    spw["CHAN_FREQ"] = freq
    unlock(spw)
    ms[kw"SPECTRAL_WINDOW"] = "Table: $name/SPECTRAL_WINDOW"

    u = squeeze(uvw[1,:],1)
    v = squeeze(uvw[2,:],1)
    w = squeeze(uvw[3,:],1)
    @test MeasurementSets.uvw(ms) == (u,v,w)
    @test MeasurementSets.antennas(ms) == (ant1+1,ant2+1)
    @test MeasurementSets.frequency(ms) == squeeze(freq,2)
end

