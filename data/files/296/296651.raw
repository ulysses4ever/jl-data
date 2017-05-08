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
end

function paraArray(campo::String)
    map( x -> reduce(push!, Char[], x), split (filter(c -> c != ' ', campo), '\n')[1:end-1])
  end

function campoMinado(campo ::String)
  if ehValido(campo)
    r = ""
    campoarr = paraArray(campo)

    valor = function(arr, x, y)
      if x > 0 && y > 0 && x < length(arr) && y < length(arr[x])
        if(arr[x,y] = 'X')
          1
        end
      end
      0
    end

    for i = [1:length(campoarr)]
       for j = [1:length(campoarr[i])]
          if campoarr[i][j] != 'X'
             contar =  valor(campoarr,i-1,j-1) + valor(campoarr,i,j-1) + valor(campoarr,i + 1,j - 1)
                    +  valor(campoarr,i-1,j)   + valor(campoarr,i+1,j)
                    +  valor(campoarr,i-1,j)   + valor(campoarr,i,j+1)   + valor(campoarr,i + 1, j + 1)
             insert!(campoarr[i], j, char(contar) )
          end
      end
    end
   return campoarr
  end
  throw(ArgumentError("Campo minado com formato incorreto!"))
end
