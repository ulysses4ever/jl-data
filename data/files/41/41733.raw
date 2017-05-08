module load_data

export loadPISA

using DataFrames

"""
Load a DataFrame of the evolutionary track corresponding to the given mass. For now, everything is solar metallicity.
"""
function loadPISA(mass; truncate=true)
    file = @sprintf("raw/PISA/TRK_M%.2f_Z0.02000_Y0.2880_XD2E5_ML1.68_AS05.DAT", mass)

    header_names = [:NMD, :LOGAGE, :Xc, :LOGL,  :LOGTE, :LOGTc, :LOGRHOc, :MCC, :LPP, :LCNO, :LGRA]
    df = readtable(file, header=false, separator=' ', allowcomments=true, names=header_names)
    if truncate
        #return only the columns we care about
        return df[[:LOGAGE, :LOGL, :LOGTE]]
    else
        return df
    end

end 

end
