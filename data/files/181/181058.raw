# Copyright (C) 2012  Raniere Silva <r.gaia.cs@gmail.com>
#
# This file is part of 'CNPq Cuthill-McKee reversa'.
#
# 'CNPq Cuthill-McKee reversa' is free software: you can redistribute
# it and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation, either
# version 3 of the License, or (at your option) any later version.
#
# 'CNPq Cuthill-McKee reversa' is distributed in the hope that it
# will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
#
load("rcm.jl")
load("math_utils.jl")

# Exemplo corespondente a Figura 5.6 da Fernanda.
A = [1 0 0 1 0 1 0 0 0 0;
     0 1 1 0 1 0 1 0 0 1;
     0 1 1 1 1 0 0 0 0 0;
     1 0 1 1 0 1 0 0 1 0;
     0 1 1 0 1 0 1 0 0 0;
     1 0 0 1 0 1 1 1 0 0;
     0 1 0 0 1 1 1 1 0 0;
     0 0 0 0 0 1 1 1 0 0;
     0 0 0 1 0 0 0 0 1 0;
     0 1 0 0 0 0 0 0 0 1]

spy_text(A)
ord = rcm(A)
print("\n")
spy_text(A[ord, ord])
