module QuandlCache

    export quandlcache
    
    function quandlcache(handle)
       key = filename(handle)
       if isreadable(key)
         open(key, "r") do s
           data = deserialize(s)
         end
         return data
       else
         data = quandl(handle)
         open(key, "w") do s
           serialize(s, data)
         end
         return data
       end
    end

    function filename(handle)
	"tmp/" + handle
    end
end
