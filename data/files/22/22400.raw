using NetCDF
using DataFrames

"""
Reads in one of the World Bank Databases from a directory.
Returns the Data Cube [time,country,1,series] and information about
the dimensions.  Requires the *_Data.csv, *_Series.csv, and
*_Country.csv in the directory.
_Currently only tested for WDI_csv!!_ (2015 Version)

    dc, years, series, countries, countryInfo, variableInfo = WorldBankDataToCube("../WDI_csv")
"""
function WorldBankDataToCube(folder::AbstractString = "WDI_csv")

    folder = joinpath(pwd(), folder)
    
    # read in data and metadata
    data                   = WorldBankDataToDataFrame(folder)
    years,series,countries = getDims(data)
    countryInfo            = getCountryInfo(folder)
    variableInfo           = getVariableInfo(folder)
    
    nTime      = length(years)
    nSeries    = length(series)
    nCountries = length(countries)

    # transform
    dc = fill(-9999.0f0,(nTime,nCountries,1,nSeries))
    fillDataCube!(dc, data, years, series, countries, nTime, nSeries, nCountries)

    #return
    dc, years, series, countries, countryInfo, variableInfo
end

####################################################
# functions for reading in Data
####################################################

function fillDataCube!(dc::AbstractArray,
                       data::DataFrames.DataFrame,
                       years::AbstractArray,
                       series::AbstractArray,
                       countries::AbstractArray,
                       nTime::Integer,
                       nSeries::Integer,
                       nCountries::Integer)
    # transform data into cube dc[time,country,1,var]
    # vector scan version, as slow as R :-)
    #=
    for i in 1:nSeries
        indSeries = data[:Indicator_Code] .== series[i]
        for j in 1:nCountries
            indCountries = data[:Country_Code] .== countries[j]
            indRow = indSeries & indCountries
            row = find(indRow)
            if length(row) == 1
                for k in 1:nTime
                    print("\r$i/$nSeries, $j/$nCountries, $k/$nTime.")
                    tmp = data[symbol("x",years[k])][row][1]
                    dc[k,j,1,i] = typeof(tmp) <: Number && tmp 
                end
            elseif length(row) > 1
                error("more than one fitting row: $(series[i]), $(countries[j])")
            end
        end
    end
    =#
    icc = 1
    iic = 1
    nr = DataFrames.nrow(data)
    for i in 1:nr
        if mod(i,10000) == 0
            print("\r", round(i/nr*100), "%")
        end 
        cc = data[:Country_Code][i]::UTF8String
        ic = data[:Indicator_Code][i]::UTF8String
        while (ic != series[iic]) || (cc != countries[icc])
            iic += 1
            if iic > nSeries
                iic = 1
                icc += 1
            end
            if icc > nCountries
                stop("data should be ordered by [:Country_Code, :Series_Code]")
            end
        end
        if cc == countries[icc] && ic == series[iic]
            for t in 1:nTime
                # typestable version
                col = symbol("x",years[t])
                if !data[col].na[i]
                    dc[t,icc,1,iic] = data[col].data[i]
                end
            end
        end
    end
    println("")
    nothing
end
    
    
function WorldBankDataToDataFrame(folder::AbstractString)
    files = readdir(folder)
    fileData = files[ [ ismatch(r"^[^.~].+_Data\.csv$",files[i])
                        for i in eachindex(files) ] ][1]
    df = DataFrames.readtable(joinpath(folder,fileData))
    DataFrames.sort!(df, cols = [:Country_Code,:Indicator_Code])
end

function getDims(data::DataFrames.DataFrame)

    colnames = names(data)
    colnames = [ string(colnames[i])
                 for i in eachindex(colnames) ] 
    indTime  = [ ismatch(r"x[0-9]{4}", colnames[i])
                 for i in eachindex(colnames) ]
    
    vTime         = [ colnames[i][2:5]
                      for i in find(indTime) ]
    
    vIndCodes     = Array(sort(unique(data[:Indicator_Code])))
    vCountryCodes = Array(sort(unique(data[:Country_Code])))

    vTime,vIndCodes,vCountryCodes
end


function getCountryInfo(folder::AbstractString)
    files = readdir(folder)
    filesCountries = files[ [ ismatch(r"^[A-Za-z].+_Country\.csv", files[i])
                              for i in eachindex(files) ] ][1]
    countries = DataFrames.readtable( joinpath(folder,filesCountries) )
    sort!(countries, cols = [:Country_Code])

    #remove regions
    countryIndex = bitunpack(~countries[:Region].na)
    
    countries[ countryIndex, [:Country_Code,:Short_Name,:Region,:Income_Group] ]
end

function getVariableInfo(folder::AbstractString)
    files = readdir(folder)
    filesSeries = files[ [ ismatch(r"^[A-Za-z].+_Series\.csv$", files[i])
                           for i in eachindex(files) ] ][1]

    # read in data
    # it would be nice to make this on the fly
    # slurp...
    ss = open(readall, joinpath(folder, filesSeries))
    removeNonAscii!(ss)
    cleanLineBreaks!(ss)
    cleanAccidentallyEscapedQuoteCharacters!(ss)
    series = DataFrames.readtable(IOBuffer(ss))

    
    DataFrames.sort!(series, cols = [:Series_Code])
    nSeries = DataFrames.nrow(series)
    
    ## separate topic column into hierarchies
    # the number of hierarchies
    maxwidth = 0
    for i in 1:nSeries
        maxwidth = max( maxwidth,
                        length( find(i -> i == convert(UInt8, ':'),
                                     series[:Topic][i].data ) ) + 1 )
    end
 
    # fille hierarchies with data
    topic = fill("",(nSeries,maxwidth))
    for i in 1:nSeries
        tmp = split(series[:Topic][i], ':')
         for j in 1:length(tmp)
            topic[i,j] = strip(string(tmp[j]))
        end
    end

    # extract unit from inbetween parentheses of the indicator name
    seriesUnit = fill("",nSeries)
    for i in 1:nSeries
        tmp = split(series[:Indicator_Name][i],'(')
        if length(tmp) > 1
            seriesUnit[i] = strip(string(tmp[2]),[' ',')'])
        else
            seriesUnit[i] = "Number"
        end
    end
    
    # Build the resulting dataframe
    res = series[:,[:Series_Code,:Indicator_Name]]
    res[:unit] = seriesUnit
    for i in 1:maxwidth
        res[symbol("Topic_",i)] = topic[:,i]
    end

    res
end

############################################################
# some helper functions
############################################################

# non ascii characters are replaced by " "
function removeNonAscii!(s::AbstractString)
    for i in eachindex(s.data)
        # remove all non ascii stuff
        if s.data[i] >= 0x80 
            s.data[i] = b" "[1]
        end
    end
    nothing
end

# "\n"   -> " "
# "\r\n" -> "\n"
function cleanLineBreaks!(s::AbstractString)
    cr = false
    for i in eachindex(s.data)
        if s.data[i] == b"\n"[1]
            if !cr
                s.data[i] = b" "[1]
            end
            cr = false
        elseif s.data[i] == b"\r"[1]
            s.data[i] = b" "[1]
            cr = true
        else
            cr = false
        end
    end
    nothing
end

# it was that one escaped quote character!!
# '\"' -> '"'
function cleanAccidentallyEscapedQuoteCharacters!(s::AbstractString)
    es = false
    for i in eachindex(s.data)
        if es  && s.data[i] == b"\""[1]
            s.data[i-1] = b" "[1]
        end
        es = s.data[i] == b"\\"[1]
    end
end


#####################################################
# main
#####################################################
wbdatafilename = "worldbank.nc"




println("reading in data")

dc,years,series,countries,countryInfo,variableInfo = WorldBankDataToCube()

println("creating dimensions variables")
ncdimTime   = NcDim( "time",    size(dc,1), atts = Dict{Any, Any}("units"=>"year"),         values = convert(Array{ASCIIString}, years)     )
ncdimSpace  = NcDim( "country", size(dc,2), atts = Dict{Any, Any}("units"=>"country code"), values = convert(Array{ASCIIString}, countries) )
ncdimSeries = NcDim( "series",  size(dc,4), atts = Dict{Any, Any}("units"=>"series code"),  values = convert(Array{ASCIIString}, series)    )

println("creating variables")
vars = NetCDF.NcVar[ NcVar("global", [ncdimTime,ncdimSpace,ncdimSeries], t = Float32) ]
for i in names(countryInfo)[2:end]
    push!( vars, NcVar(string(i), ncdimSpace, t = ASCIIString) )
end
for i in names(variableInfo)[2:end]
    push!( vars, NcVar(string(i), ncdimSeries, t = ASCIIString) )
end

println("creating file")
if isfile(wbdatafilename)
    rm(wbdatafilename)
end
nc = NetCDF.create( wbdatafilename, vars )

println("adding global variables")
NetCDF.putvar( nc, "global", size(squeeze(dc, 3)) )

println("adding country info vars")
for i in names(countryInfo)[2:end]
    NetCDF.putvar( nc, string(i), convert(Array{ASCIIString}, countryInfo[i].data) )
end

println("adding variable info vars")
for i in names(variableInfo)[2:end]
    NetCDF.putvar( nc, string(i), convert(Array{ASCIIString}, variableInfo[i].data) )
end

println("closing file")
NetCDF.close(nc)
println("DONE")




        

    
            

    
        
                         
    
