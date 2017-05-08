
# Programa que calcula la máxima subcadena comun entre dos cadenas.

  function lcs(a,b)
  a = "A scrambled version 13, 3, 2, 21, 1, 1, 8, 5 (OEIS A117540) of the first eight Fibonacci numbers appear as one of the clues left by murdered museum"
  b = "curator Jacque Sauniere in D. Brown's novel The Da Vinci Code Brown 2003, pp. 43, 60-61, and 189-192). In the Season 1 episode 'Sabotage' (2005) o"
  len_a = length(a)
  len_b = length(b)
  tabla = [Int64, (len_a+1,len_b+1)]
    for i = 1:len_a+1
        for j = 1:len_b+1
            if i == 1 || j == 1
                   tabla[i,j] = 1
            elseif a[i-1] == b[j-1]
                tabla[i,j] = tabla[i-1,j-1] + 1
            else
                tabla[i,j] = max(tabla[i-1,j],tabla[i,j-1])
            end
        end
    end
  print(lcs(a,b))
  return tabla[len_a,len_b]
  end;

