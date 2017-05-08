include("../perfutil.jl")
include("./ipp.jl")

### IPP benchamark - testing Julia performance against IPP


## AddC 
function addC_vectorized(X,val) 
  Y = X + val
end
function addC_vectorized!(X,val) 
  X = X + val
end

function addC_devectorized!(X,val) 
  for i = 1:size(X,1)
    X[i] = X[i] + val
  end
end
function addC_devectorized(X,val) 
  Y = similar(X)
  for i = 1:length(X)
    Y[i] = X[i] + val
  end
end

function addC_ipps!(X,val) 
  IPP.Signals.AddC!(val,X)
end
function addC_ipps(X,val) 
  Y = IPP.Signals.AddC(val,X)
end

# floating point data
for elty in (Float32, Float64, Complex64, Complex128)

    len   = 2^16 # Array length
    X     = ones (elty, len)
    Y     = ones (elty, len)
    Z     = zeros(elty, len)
    val   = convert(elty, -1)  

    println("AddC out-of-place for type $elty")
    @timeit (addC_ipps         (X,val) ) "ippslib"       "AddC out-of-place"
    @timeit (addC_vectorized   (X,val) ) "vectorized"    "AddC out-of-place"
    @timeit (addC_devectorized (X,val) ) "de-vectorized" "AddC out-of-place"

    println("AddC in-place for type $elty")
    @timeit (addC_ipps!        (X,val) ) "ippslib"       "AddC in-place"
    @timeit (addC_vectorized!  (X,val) ) "vectorized"    "AddC in-place"
    @timeit (addC_devectorized!(X,val) ) "de-vectorized" "AddC in-place"

end

# integer data

function addC_ipps!(X,val,scale) 
  IPP.Signals.AddC!(val,X,scale)
end
function addC_ipps(X,val,scale) 
  Y = IPP.Signals.AddC(val,X,scale)
end

for elty in (Uint8, Int16, Uint16, Int32)

    len   = 2^16 # Array length
    X     = ones (elty, len)
    Y     = ones (elty, len)
    Z     = zeros(elty, len)
    val   = convert(elty,  1)  
    scale = convert(Int32, 0)  

    println("AddC out-of-place for type $elty")
    @timeit (addC_ipps         (X,val,scale) ) "ippslib"       "AddC out-of-place"
    @timeit (addC_vectorized   (X,val      ) ) "vectorized"    "AddC out-of-place"
    @timeit (addC_devectorized (X,val      ) ) "de-vectorized" "AddC out-of-place"

    println("AddC in-place for type $elty")
    @timeit (addC_ipps!        (X,val,scale) ) "ippslib"       "AddC in-place"
    @timeit (addC_vectorized!  (X,val      ) ) "vectorized"    "AddC in-place"
    @timeit (addC_devectorized!(X,val      ) ) "de-vectorized" "AddC in-place"

end

