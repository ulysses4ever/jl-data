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

function rcm(A)
    # TODO Determinar o vértice inicial.
    v = 7

    # TODO Loop percorrendo os vizinhos.
    (adj, grau) = matrix2adj(A)
    # print("$adj\n")
    (grau_s, grau_p) = sortperm(grau)
    # print("$grau_s\n")
    # print("$grau_p\n")
    visited = falses(size(A,1))
    queue = Int[]
    news = zeros(Int, size(A,1))
    count = 1
    push(queue, v)
    visited[v] = true
    while !isempty(queue)
        v = shift(queue)
        news[v] = count
        count = count + 1
        for w in grau_p
            # print("$w\n$(contains(adj[v],w)) && $(visited[w] == false)\n")
            if contains(adj[v],w) && visited[w] == false
                push(queue, w)
                visited[w] = true
            end
        end
        print("v = $v queue = $queue\n")
    end

    # TODO Ordenação inversa.
    (s,p) = sortperm(news)
    return reverse(p)
end

function matrix2adj(A)
    # Matrix to Adjacent List
    # A: input matrix
    (m,n) = size(A)
    A = abs(A) >= 10^(-6)
    adj = Any[]
    grau = zeros(n)
    for i = 1:m
        aux = Int[]
        for j = 1:n
            if i != j && A[i,j]
                push(aux, j)
            end
        end
       grau[i] = length(aux)
       push(adj, aux)
   end
   return (adj, grau)
end
