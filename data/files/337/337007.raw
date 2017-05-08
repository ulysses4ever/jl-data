# PWStudyDataFrame.jl
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

using Match
require("BRFSSDataFrame")

function PWStudyDataFrame(filename)
	df = BRFSS2013DataFrame(filename)
	pwdf = DataFrame(entry_number = Uint64[], EMPLOY1 = Uint8[], QLACTLM2 = Uint8[], RRCLASS2 = Uint8[], SEX = Uint8[], _AGEG5YR = Uint8[], _RFBING5 = Uint8[], _RFBMI5 = Uint8[], _TOTINDA = Uint8[])

	entry_number = 0

	for entry in eachrow(df)
		entry_number += 1

		EMPLOY1 = NA
		QLACTLM2 = NA
		RRCLASS2 = NA
		SEX = NA
		_AGEG5YR = entry[:_AGEG5YR] - 1
		_RFBING5 = NA
		_RFBMI5 = NA
		_TOTINDA = entry[:_TOTINDA] - 1

		if (typeof(entry[:EMPLOY1]) == NAtype) || (typeof(entry[:QLACTLM2]) == NAtype) ||  (typeof(entry[:RRCLASS2]) == NAtype) || (typeof(entry[:SEX]) == NAtype) || (typeof(entry[:_BMI5CAT]) == NAtype) || (typeof(entry[:_RFBING5]) == NAtype)
			continue
		end

		EMPLOY1 = @match entry[:EMPLOY1] begin
			1 => 0
			2 => 0
			3 => 1
			4 => 1
			_ => continue
		end

		RRCLASS2 = @match entry[:RRCLASS2] begin
			1 => 0
			2 => 1
			3 => 1
			4 => 1
			5 => 1
			6 => 1
			_ => continue
		end

		SEX = @match entry[:SEX] begin
			1 => 0
			2 => 1
			_ => continue
		end

		QLACTLM2 = @match entry[:QLACTLM2] begin
			1 => 1
			2 => 0
			_ => continue
		end

		_RFBING5 = @match entry[:_RFBING5] begin
			1 => 0
			2 => 1
			_ => continue
		end

		# Some entries in the BRFSS data have bogus _RFBMI5 data,
		# so we recreate _RFBMI5 from _BMI5CAT.
		_RFBMI5 = @match entry[:_BMI5CAT] begin
			1 => 0
			2 => 0
			3 => 1
			4 => 1
			_ => continue
		end

		# Filter out people that refused to give their age
		if _AGEG5YR > 12
			continue
		end

		# Filter out people that refused or don't know their race
		if RRCLASS2 > 5
			continue
		end

		# Filter out pregnant people
		if SEX == 1
			if (typeof(entry[:PREGNANT]) == NAtype) || (entry[:PREGNANT] != 2)
				continue
			end
		end

		# Filter out people that have missing activity values
		if _TOTINDA > 1
			continue
		end

		push!(pwdf, (entry_number, EMPLOY1, QLACTLM2, RRCLASS2, SEX, _AGEG5YR, _RFBING5, _RFBMI5, _TOTINDA))
	end

	return pwdf
end
