module QuandlCache
    
    function quandlload(handle)
       key = filename(handle)
       if isreadable(key)
         s = open(key, "r")
         data = deserialize(key)
         close(s)
         return data
       else
         data = quandl(handle)
         s = open(key, "w")
         serialize(s, data)
         close(s)
         return data
       end
    end

    function filename(handle)
	"tmp/" + handle
    end
end
