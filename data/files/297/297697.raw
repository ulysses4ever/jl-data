
ColumnType = Union(Array{Int64,1},Array{Float64,1},Array{AbstractString,1})
#this should probably be a list, but array works for now
DataFrameType = Array{ColumnType,1}

#function to parse a string into an int,float etc
#should probably be a multimethod. Get stuff working, then fix.


function parseStringToInt64(aString)
    return parse (Int64, aString)
end

function parseStringToFloat64(aString)
    return parse (Float64, aString)
end

#strictly not required, added for the sake of uniformity and in case
#need to do non standard string parsing.
function parseStringToString(aString)
    return strip(aString)
end



function moveDataFromRowsOfCSVToDataframeDataStructure(inMemDataSet,columnTypes)
  #initialize parsing functions
  #an array of functions of signature str ->  types that dataframe can hold. 
  #TODO create this automatically by sampling the dataset. For now, hardcode to match the dataset column types



  parserfunctions = []
  for j = 1:length(columnTypes);
    colType = columnTypes[j]
    if ( colType == "INT64")
        push!(parserfunctions, parseStringToInt64);
    elseif ( colType == "FLOAT64")
        push!(parserfunctions, parseStringToFloat64);
    elseif ( colType == "STR")
        push!(parserfunctions, parseStringToString);
    else
       throw (ColumnTypeException(colType));
    end
  end 

  #initialize dataframe
  dataframe = ColumnType[];
  for i = 1:length(columnTypes);
    
    colType = columnTypes[i]
    if ( colType == "INT64")
        push!(dataframe, Int64[]);
    elseif ( colType == "FLOAT64")
        push!(dataframe, Float64[]);
    elseif ( colType == "STR")
        push!(dataframe, AbstractString[]);
    else
       throw (ColumnTypeException(colType));
    end
    
  end 

  for x in 1:length(inMemDataSet)
    rowValues = split(inMemDataSet[x],',');
    try
        
        numberOfCSV = length(rowValues)
        for k = 1:numberOfCSV
            push!(dataframe[k], (parserfunctions[k](rowValues[k])))
        end
        
    catch
        println("Exception caught");
        println(x);
        println( C);
    end
    
 end
end

function loadFromFile(fileName)
 return readall(open(fileName));
end



#Exception to be thrown when we don't know what a column type means
type ColumnTypeException <: Exception
    var::Symbol
end
Base.showerror(io::IO, e::ColumnTypeException) = print(io, e.var, "No handler");

function loadAndMeasure(fileName)
    println("reading file into memory");
    @time A = loadFromFile(fileName);
    println ("splitting in-memory dataset into rows");
    @time B = split(A,'\n');
    A=0; #deallocate
    println ("loading into dataframe");


    

    #this is the dataset schema. Ideally should be inferred from the dataset/headers. For now hardcoded to match the dataset
    columnTypes = AbstractString[];
    
    #schema for the 100 million row data set with 25 random integers per row, no nulls    
    #for i = 1:25
    #    push!(columnTypes, "INT64"); 
    #end

    #schema for the 100 million row data set with 24 columns in the pattern int, float, string, all random   
    for i = 1:8
        push!(columnTypes, "INT64"); 
        push!(columnTypes, "FLOAT64"); 
        push!(columnTypes, "STR"); 
    end

    @time moveDataFromRowsOfCSVToDataframeDataStructure(B,columnTypes);
    B=0; #dellocate

end

#rough equivalent of R's
# system.time(read.table("mixedmillionrowdataset.csv", sep=",", header=FALSE, skipNul=TRUE))  
#and
# system.time(fread("mixedmillionrowdataset.csv", sep=",", header=FALSE)) 
#gc_disable() #uncomment to disable gc
loadAndMeasure("mixedthousandrowdataset.csv");

