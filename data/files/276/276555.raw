# BRFSSDataFrame.jl
# Part of brfss-thesis-study by Philip Wernersbach <philip.wernersbach@gmail.com>
#
# You should have been notified of where to download the source code for this
# program. If you have not been notified, please contact Philip Wernersbach
# at <philip.wernersbach@gmail.com>, as this constitues a violation of the
# GNU Affero General Public License version 3 that this software was distributed
# under.
#
#    Copyright (C) 2015  Philip Wernersbach
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Affero General Public License as published
#    by the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.
#
#    You should have received a copy of the GNU Affero General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

using DataFrames

typealias BRFSSDataFrame DataFrame
typealias BRFSS2013DataFrame DataFrame

function extract_brfss2013_ascii_data(filename)
	df = DataFrame(DRNK3GE5 = Uint8[], EMPLOY1 = Uint8[], LSATISFY = Uint8[], PREGNANT = Uint8[], QLACTLM2 = Uint8[], RRCLASS2 = Uint8[], SEX = Uint8[], _AGEG5YR = Uint8[], _BMI5CAT = Uint8[], _RFBING5 = Uint8[], _RFBMI5 = Uint8[], _TOTINDA = Uint8[])

	open(filename, "r") do file
		for line in eachline(file)
			DRNK3GE5 = NA
			EMPLOY1 = NA
			LSATISFY = NA
			PREGNANT = NA
			QLACTLM2 = NA
			RRCLASS2 = NA
			SEX = NA
			_AGEG5YR = NA
			_BMI5CAT = NA
			_RFBING5 = NA
			_RFBMI5 = NA
			_TOTINDA = NA

			try
				DRNK3GE5 = parse(Uint8, line[198:199])
			catch
				DRNK3GE5 = NA
			end

			try
				EMPLOY1 = parse(Uint8, line[151])
			catch
				EMPLOY1 = NA
			end

			try
				LSATISFY = parse(Uint8, line[533])
			catch
				LSATISFY = NA
			end

			try
				PREGNANT = parse(Uint8, line[179])
			catch
				PREGNANT = NA
			end

			try
				QLACTLM2 = parse(Uint8, line[180])
			catch
				QLACTLM2 = NA
			end

			try
				RRCLASS2 = parse(Uint8, line[412])
			catch
				RRCLASS2 = NA
			end

			try
				SEX = parse(Uint8, line[178])
			catch
				SEX = NA
			end

			try
				_AGEG5YR = parse(Uint8, line[2177:2178])
			catch
				_AGEG5YR = NA
			end

			try
				_BMI5CAT = parse(Uint8, line[2196])
			catch
				_BMI5CAT = NA
			end

			try
				_RFBING5 = parse(Uint8, line[2207])
			catch
				_RFBING5 = NA
			end

			try
				_RFBMI5 = parse(Uint8, line[2197])
			catch
				_RFBMI5 = NA
			end

			try
				_TOTINDA = parse(Uint8, line[2267])
			catch
				_TOTINDA = NA
			end

			push!(df, (DRNK3GE5, EMPLOY1, LSATISFY, PREGNANT, QLACTLM2, RRCLASS2, SEX, _AGEG5YR, _BMI5CAT, _RFBING5, _RFBMI5, _TOTINDA))
		end
	end

	return df
end


function BRFSS2013DataFrame(filename)
	return extract_brfss2013_ascii_data(filename)
end
