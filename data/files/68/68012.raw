#    Copyright (C) 2014 Cássio M. M. Pereira
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

module ClusterAnalysis

export adjusted_rand_index

function adjusted_rand_index(labels::Array{Int64}, expected::Array{Int64})
    a = b = c = d = 0
    if length(labels) != length(expected)
        error("Trying to compute Adjusted Rand Index for different length arrays!")
    end
    n = length(labels)
    for i = 1:n
        for j = (i+1):n
            if labels[i] == labels[j] && expected[i] == expected[j]
                a += 1
            elseif labels[i] == labels[j] && expected[i] != expected[j]
                b += 1
            elseif labels[i] != labels[j] && expected[i] == expected[j]
                c += 1
            else
                d += 1
            end
        end
    end
    m = n * (n-1) / 2.
    top = a - ((a+c)*(a+b)) / m
    bottom = ((a+c)+(a+b)) / 2.0 - ((a+c)*(a+b)) / m
    return bottom != 0.0 ? top / bottom : 0.0
end

end
