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

function spy_text(A)
    (m,n) = size(A)
    for i in 1:m
        for j in 1:n
            if A[i,j] != 0
                print("X ")
            else
                print("  ")
            end
        end
        print("\n")
    end
end

function matrix2graph(A)
    # Apenas para matrizes simétricas.
    f = open("temp.gv", "w")
    write(f, "graph G {\n")
    (m,n) = size(A)
    # j corresponde as colunas
    for j in 1:n
        # i corresponde as linhas
        for i in 1:j-1
            if A[i,j] != 0
                write(f, "$i -- $j;\n")
            end
        end
    end
    write(f, "}")
    close(f)
    system("dot -Teps -o temp.eps temp.gv")
end
