# Copyright (C) 2012  Raniere Silva <r.gaia.cs@gmail.com>
#
# This file is part of 'CNPq Cuthill-McKee reversa'.
#
# 'CNPq Cuthill-McKee reversa' is free software: you can redistribute it
# and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# 'CNPq Cuthill-McKee reversa' is distributed in the hope that it will
# be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

# ppnf Pseudo-peripheral Node Finder
function ppnf(A)
    # No qualquer do grafo.
    r = 1
    L = rls(A, r)
    # println(L)
    stop = false
    it = 0
    while !stop && it < 10
        it = it + 1
        # println("iteration: $it")
        aux = min_degree(A, L[length(L)])
        # println("min_degree: $aux")
        auxL = rls(A, aux)
        # println(auxL)
        if length(auxL) > length(L)
            r = aux
            L = auxL
        else
            stop = true
        end
    end
    return aux
end

function rls(A, r)
    L = Any[]
    
    # TODO Tratar entrada.
    push(L, r)

    # TODO Tratar casos degenerados.
    push(L, adj(A, r))
    stop = false
    while !stop
        l = length(L)
        aux = rm_root_adj(adj(A, L[l]), L[l - 1])
        if isempty(aux)
            stop = true
        else
            push(L, aux)
        end
    end
    return L
end

function adj(A, r)
    l = Int[]
    for i in 1:size(A,1)
        for j in r
            if i != j && !contains(l, i) && A[i, j] != 0
                push(l, i)
            end
        end
    end
    return l
end

function rm_root_adj(l, r)
    new = Int[]
    for i in l
        if !contains(r, i)
            push(new, i)
        end
    end
    return new
end

function min_degree(A, l)
    r = l[1]
    g = size(A,1)
    for i in l
        aux = 0
        for j in 1:size(A,1)
            if A[i, j] != 0
                aux = aux + 1
            end
        end
        if aux < g
            g = aux
            r = i
        end
    end
    return r
end
