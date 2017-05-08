# Programa que calcula la máxima subcadena comun entre dos cadenas.

function lcs(a,b,len_a,len_b)
a = "A scrambled version 13, 3, 2, 21, 1, 1, 8, 5 (OEIS A117540) of the first eight Fibonacci numbers appear as one of the clues left by murdered museum"
b = "curator Jacque Sauniere in D. Brown's novel The Da Vinci Code Brown 2003, pp. 43, 60-61, and 189-192). In the Season 1 episode 'Sabotage' (2005) o"
len_a = length(a)
len_b = length(b)
tabla = [len_a+1,len_b+1]
    for i = 1:len_a
        for j = 1:len_b
            if a[i] == b[j]
                if i == 0 || j == 0
                   tabla[i,j] = 0
                end
                if a[i-1] == b[j-1]
                    tabla[i,j] = tabla[i-1,j-1]
                end
            tabla[i,j] = max(tabla[i-1,j],tabla[i,j-1])
            end
         end
    end 
    return tabla[len_a,len_b]
print(lcs(a,b,len_a,len_b))
end;

