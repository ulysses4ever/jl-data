module CampoMinado end

export campoMinado
export ehValido

function ehValido(campo ::String)
 length(campo) == 0 || ( ismatch(r"((X{1}\s{1}|O{1}\s{1})\n{1})+", campo) && checarTamanhoDeLinhasDo(campo))
end

function checarTamanhoDeLinhasDo(campo::String)
  strs = split(campo, '\n')

  if length(strs) != 0
    w = map (x -> mapreduce(z-> 1, +, x) , strs[1:end-1])

    if length(w) != 0
        m = maximum(w);
        return all(z ->  m == z, w)
      end
    return false
  end

function paraArray(campo::String)
    map( x -> reduce(push!, Char[], x), split (filter(c -> c != ' ', campo), '\n')[1:end-1])
  end

function campoMinado(campo ::String)
  if ehValido(campo)
    r = ""
    for c in campo
     r = r * string(c == 'O'? '0' : c)
    end
   return r
  end
  throw(ArgumentError("Campo minado com formato incorreto!"))
end
