module Signals

const libipps = dlopen("libipps")

### Arithmetic Functions
## AddC 

#Case 1. Not-in-place operations on floating point data
for (fname, elty) in ((:ippsAddC_32f ,:Float32   ),
                      (:ippsAddC_64f ,:Float64   ),
                      (:ippsAddC_32fc,:Complex64 ),
                      (:ippsAddC_64fc,:Complex128) )
    @eval begin
        # AddC: Adds a constant value to each element of a vector        
        # Y = X + val
        function AddC!(X::Union(Ptr{$elty},Array{$elty}), val::$elty, Y::Union(Ptr{$elty},Array{$elty}))
  	    assert(length(X) == length(Y))
            len = length(X);  
            p = ccall(dlsym(libipps,($(string(fname)))), 
                      Ptr{Uint8},
                      (Ptr{$elty},$elty, Ptr{$elty},Int32),
                      X, val, Y, len)
            Y
        end
        function AddC(val::$elty,Y::Union(Ptr{$elty},Array{$elty}))
	          AddC!(Y, val, similar(Y))
        end
    end
end

# Case 2. Not-in-place operations on integer data
for (fname, elty) in ((:ippsAddC_8u_Sfs  ,:Uint8  ),
                      (:ippsAddC_16s_Sfs ,:Int16  ),
                      (:ippsAddC_16u_Sfs ,:Uint16 ),
		                  (:ippsAddC_32s_Sfs ,:Int32  ))

    @eval begin
        # AddC: Adds a constant value to each element of a vector        
        # Y = X + val
        function AddC!(X::Union(Ptr{$elty},Array{$elty}), val::$elty, Y::Union(Ptr{$elty},Array{$elty}), scaleFactor::Int32)
  	    assert(length(X) == length(Y))
            len = length(X);  
            p = ccall(dlsym(libipps,($(string(fname)))), 
                      Ptr{Uint8},
                      (Ptr{$elty},$elty, Ptr{$elty},Int32,Int32),
                      X, val, Y, len, scaleFactor)
            Y
        end
        function AddC(val::$elty,Y::Union(Ptr{$elty},Array{$elty}), scaleFactor::Int32)
	          AddC!(Y, val, similar(Y), scaleFactor)
        end
    end
end

# Case 3. In-place operations on floating point data.
for (fname, elty) in ((:ippsAddC_32f_I ,:Float32   ),
                      (:ippsAddC_64f_I ,:Float64   ),
                      (:ippsAddC_32fc_I,:Complex64 ),
                      (:ippsAddC_64fc_I,:Complex128) )
    @eval begin
        # AddC: Adds a constant value to each element of a vector        
        # Y = Y + val
        function AddC!(val::$elty,Y::Union(Ptr{$elty},Array{$elty}))
            len = length(Y);  
            p = ccall(dlsym(libipps,($(string(fname)))), 
                      Ptr{Uint8},
                      ($elty,Ptr{$elty},Int32),
                      val, Y, len)
            Y
        end
    end
end

# Case 4. In-place operations on integer data.
for (fname, elty) in ((:ippsAddC_8u_ISfs  ,:Uint8  ),
                      (:ippsAddC_16s_ISfs ,:Int16  ),
                      (:ippsAddC_16u_ISfs ,:Uint16 ),
		                  (:ippsAddC_32s_ISfs ,:Int32  ))

    @eval begin
        # AddC: Adds a constant value to each element of a vector        
        # Y = Y + val
        function AddC!(val::$elty, Y::Union(Ptr{$elty},Array{$elty}), scaleFactor::Int32)
            len = length(Y);  
            p = ccall(dlsym(libipps,($(string(fname)))), 
                      Ptr{Uint8},
                      ($elty,Ptr{$elty},Int32,Int32),
                      val, Y, len, scaleFactor)
            Y
        end

    end
end

## Add

## ...

end  # module Signals
