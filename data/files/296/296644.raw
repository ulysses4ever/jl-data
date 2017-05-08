module CampoMinado end

export campoMinado
export checarCampo

function checarCampo(campo ::String)
 length(campo) == 0 || ( ismatch(r"(O|X|\n)", campo) && checarTamanhoDeLinhasDo(campo))
end

function checarTamanhoDeLinhasDo(campo::String)
  w = map (x -> mapreduce(z-> 1, +, x) ,  split(campo, '\n')[1:end-1])
  m = maximum(w);
  return all(z ->  m == z, w)
  end

campoMinado(campo ::String) = campo
