module Rates
  importall Quandl
  importall QuandlCache
  importall Gadfly

  export layers

  token = get(ENV, "QUANDL_TOKEN", "")
  print(string("using token ",token))
  set_auth_token(token)

  function layers(handles)
    function drawlayer(handle)
      data = quandlcache(handle)
      layer(x = [1:length(data.values[:,1])], y = data.values[:,1], Geom.point)
    end
    map(drawlayer, handles)
  end

  plot(layers(["RATEINF/CPI_RUS"]))

end
