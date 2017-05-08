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

load("math_utils.jl")

function test(A)
    spy_text(A)
    print("\n")
    bandwidth_text(A)
    print("\n")
    profile_text(A)
    print("\n")
end

# Cuthill:1969:ReducingBandwidth
A = [1 1 0 0;
     1 1 1 0;
     0 1 1 1;
     0 0 1 1]
test(A)

A = [1 1 0 1 0;
     1 1 1 0 1;
     0 1 1 0 0;
     1 0 0 1 1;
     0 1 0 1 1]
test(A)

A = [1 1 1 1 0 0 0;
     1 1 0 0 0 0 0;
     1 0 1 0 1 0 0;
     1 0 0 1 0 1 1;
     0 0 1 0 1 0 0;
     0 0 0 1 0 1 0;
     0 0 0 1 0 0 1]
test(A)

# Liu:1976:ComparativeCuthillMcKee
A = [1 0 1 0 1 0 0;
     0 1 0 1 0 1 0;
     1 0 1 0 1 0 0;
     0 1 0 1 1 0 1;
     1 0 1 1 1 0 0;
     0 1 0 0 0 1 0;
     0 0 0 1 0 0 1]
test(A)

A = [1 1 1 1 1 1 1;
     1 1 0 0 0 0 0;
     1 0 1 0 0 0 0;
     1 0 0 1 0 0 0;
     1 0 0 0 1 0 0;
     1 0 0 0 0 1 0;
     1 0 0 0 0 0 1]
test(A)

# George:1979:NodeFinder
A = [1 1 0 1 0 0 0 0;
     1 1 0 0 0 0 0 0;
     0 0 1 0 1 0 1 1;
     1 0 0 1 0 0 0 1;
     0 0 1 0 1 0 0 0;
     0 0 0 0 0 1 1 1;
     0 0 1 0 0 1 1 0;
     0 0 1 1 0 1 0 1]
test(A)

# Fernanda:2005:ReordenacaoCCCG,
A = [4 1 2 .5 2;
     1 .5 0 0 0;
     2 0 3 0 0;
     .5 0 0 .625 0;
     2 0 0 0 16]
test(A)

A = [1 1 0 0 0 1 0 0;
     1 1 0 0 0 0 0 0;
     0 0 1 0 1 0 1 1;
     0 0 0 1 0 0 1 1;
     0 0 1 0 1 0 0 0;
     1 0 0 0 0 1 0 1;
     0 0 1 1 0 0 1 0;
     0 0 1 1 0 1 0 1]
test(A)

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
test(A)
