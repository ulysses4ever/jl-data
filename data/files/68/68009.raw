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

using Base.Test
using ClusterAnalysis

lbls = vec([1 1 1 2 2 2])
expected = vec([2 2 2 3 3 3])

@test 1.0 == ClusterAnalysis.adjusted_rand_index(lbls, expected)

lbls = vec([1 1 1 2 2 2])
expected = vec([1 2 1 1 2 1])

@test_approx_eq_eps -0.2162 ClusterAnalysis.adjusted_rand_index(lbls, expected) e-2

