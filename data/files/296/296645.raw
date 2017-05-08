module CampoMinado end

export campoMinado
export ehValido

function ehValido(campo ::String)
 length(campo) == 0 || ( ismatch(r"(O|X|\n)", campo) && checarTamanhoDeLinhasDo(campo))
end

function checarTamanhoDeLinhasDo(campo::String)
  strs = split(campo, '\n')

  if length(strs) == 0
    return false
  end

  w = map (x -> mapreduce(z-> 1, +, x) , strs[1:end-1])

  if length(w) == 0
    return false
  end

  m = maximum(w);
  return all(z ->  m == z, w)
  end


campoMinado(campo ::String) = ehValido(campo) ? campo : throw(ArgumentError("Campo minado com formato incorreto!"))
