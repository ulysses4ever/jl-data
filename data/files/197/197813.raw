
export keywords


function key_segment_lines(code::String,engine::SegmentWorker)
    
    # nlines = copy(engine.lines)
    fileopen = open(code,"r")

    	tempresult = Array(String,0,2)

    	try
    	  	temparray = readall(fileopen)

    	  	if length(temparray) != 0
    		tempresult = key_segment_words(join(temparray),engine)
	    	end

    	finally
	    		close(fileopen)
	    end # end try

	    return tempresult
    # end  # end if else
end




function key_segment_words(code::String,engine::SegmentWorker) 

	if engine.symbol == false
		code = replace(code,r"[^\u2e80-\u3000\u3021-\ufe4fa-zA-Z0-9]", " ")
    end
    topn = copy(engine.topn)
    tempvector = ccall(key_vector_num_result_key,Ptr{Void},(Ptr{Void},Ptr{Uint8},Int),engine.private.worker,pointer(code),topn)
    
    sz = ccall(get_vector_num_size_key,Uint32,(Ptr{Void},),tempvector)
    res_char = ccall(keyword_char_key,Ptr{Ptr{Uint8}},(Ptr{Void},),tempvector)
    res_num  = ccall(keyword_num_key,Ptr{Float64},(Ptr{Void},),tempvector)

    temparray_char = pointer_to_array(res_char,sz)
    temparray_num = pointer_to_array(res_num,sz)
    result_char =  Array(UTF8String,sz)
    result_num =  Array(Float64,sz)
    
    for num in 1:sz 
          result_char[num] = bytestring(temparray_char[num])
          result_num[num] = copy(temparray_num[num])
    end

    ccall(free_vector_num_base_key,Void,(Ptr{Void},),tempvector)
    ccall(free_char_key,Void,(Ptr{Ptr{Uint8}},),res_char)
    ccall(free_num_p_key,Void,(Ptr{Float64},),res_num)

	if engine.symbol == false
		tempbool = !(result_char .== " ")
		result_char = result_char[ tempbool ]
		result_num  = result_num[ tempbool ]
    end

    result = [result_char result_num]

    return result
end # cut_words

function keywords(code::String,engine::SegmentWorker)
	
	if engine.private.worker_type != "keywords"
		error("""worker's type is not "keywords".""")
	end

    if isfile(code) 

        encoding = copy(engine.encoding)

        if engine.detect==true
            code = transcode(code,encoding,engine.detect)
        end

        key_segment_lines(code,engine)
    else

    	 return key_segment_words(code,engine)
    end

end # segment()

