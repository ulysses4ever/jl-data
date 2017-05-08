# BRFSSThesisStudy.jl
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
using DataFrames
using GLM
using Gadfly
require("PWStudyDataFrame")

function binary_plot(data, name)
	zero_count = 0
	one_count = 0

	for entry in data
		@match entry begin
			0 => zero_count += 1
			1 => one_count += 1
		end
	end

	plotdata = DataFrame(Values = [0, 1], Count = [zero_count, one_count])
	graph = plot(plotdata, x="Values", y="Count", Guide.title(name), Scale.x_discrete, Geom.bar(position=:dodge))
	draw(PNG("output/$name.png", 8inch, 7inch), graph)
end

function twelve_plot(data, name)
	zero_count = 0
	one_count = 0
	two_count = 0
	three_count = 0
	four_count = 0
	five_count = 0
	six_count = 0
	seven_count = 0
	eight_count = 0
	nine_count = 0
	ten_count = 0
	eleven_count = 0
	twelve_count = 0

	for entry in data
		@match entry begin
			0 => zero_count += 1
			1 => one_count += 1
			2 => two_count += 1
			3 => three_count += 1
			4 => four_count += 1
			5 => five_count += 1
			6 => six_count += 1
			7 => seven_count += 1
			8 => eight_count += 1
			9 => nine_count += 1
			10 => ten_count += 1
			11 => eleven_count += 1
			12 => twelve_count += 1
		end
	end

	plotdata = DataFrame(Values = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], Count = [zero_count, one_count, two_count, three_count, four_count, five_count, six_count, seven_count, eight_count, nine_count, ten_count, eleven_count, twelve_count])
	graph = plot(plotdata, x="Values", y="Count", Guide.title(name), Scale.x_discrete, Geom.bar(position=:dodge))
	draw(PNG("output/$name.png", 8inch, 7inch), graph)
end

function descriptive_statistics(data)
	describe(data)

	ds_table = DataFrame(Variable = Symbol[], SampleProportion = Float64[], SampleSize = Int64[])

	println("Pearson Correlations:")
	for a in names(data)
		for b in names(data)
			print("$a and $b : ")
			println(cor(data[a], data[b]))
		end

		push!(ds_table, (a, mean(data[a]), length(data[a])))
	end
	println("")

	writetable("output/desc_stats.csv", ds_table)
end

function analyze(name, regression)
	println("=== $name ===")
	println(regression)

	println("Confidence Intervals:")
	println(confint(regression))
	println("")

	println("Variance-Covariance Matrix:")
	println(vcov(regression))
	println("")

	info_table = coeftable(regression).mat
	coef_table = DataFrame(Variable = Symbol[], Odds = Float64[], StdErr = Float64[], ZValue = Float64[], Significance = Float64[])
	i = 1

	for variable in regression.mf.terms.eterms
		push!(coef_table, (variable, info_table[i, 1], info_table[i, 2], info_table[i, 3], info_table[i, 4]))
		i += 1
	end

	writetable("output/coefs_$name.csv", coef_table)
end

println("--- COMPUTING ---")
println("")

data = PWStudyDataFrame("input/LLCP2013.ASC")

println(data)
println("")

binary_plot(data[:EMPLOY1], "EMPLOY1")
binary_plot(data[:QLACTLM2], "QLACTLM2")
binary_plot(data[:RRCLASS2], "RRCLASS2")
binary_plot(data[:SEX], "SEX")
twelve_plot(data[:_AGEG5YR], "_AGEG5YR")
binary_plot(data[:_RFBING5], "_RFBING5")
binary_plot(data[:_RFBMI5], "_RFBMI5")
binary_plot(data[:_TOTINDA], "_TOTINDA")

# NOTES:
##
## Adding RRCLASS2 blows EMPLOY1 out of the water?
## EMPLOY1 isn't pertinent here
## Interaction terms aren't pertinent here
binge = fit(GeneralizedLinearModel, _RFBING5 ~ EMPLOY1 + SEX + _AGEG5YR, data, Binomial(), LogitLink())

# NOTES:
## Adding RRCLASS2 blows SEX out of the water?
## SEX isn't pertinent here
## Interaction terms aren't pertinent here
physical_limitation = fit(GeneralizedLinearModel, QLACTLM2 ~ EMPLOY1 + RRCLASS2 + _AGEG5YR, data, Binomial(), LogitLink())

# NOTES:
## SEX isn't pertinent here
## RRCLASS2 isn't pertinent here
## Interaction terms aren't pertinent here
physical_activity = fit(GeneralizedLinearModel, _TOTINDA ~ EMPLOY1 + _AGEG5YR, data, Binomial(), LogitLink())

# NOTES:
## The intercept isn't pertinent here?!?!?
## EMPLOY1 isn't pertinent here
## SEX*_AGEG5YR isn't pertinent here
## RRCLASS2*_AGEG5YR isn't pertinent here
ow_ob = fit(GeneralizedLinearModel, _RFBMI5 ~ EMPLOY1 + SEX + RRCLASS2 + _AGEG5YR + SEX*RRCLASS2, data, Binomial(), LogitLink())

println("--- DESCRIPTIVE STATISTICS ---")
println("")

descriptive_statistics(data)

println("--- RESULTS ---")
println("")

analyze("_RFBING5 (Binge Drinking)", binge)
analyze("QLACTLM2 (Physical Limitation)", physical_limitation)
analyze("_TOTINDA (Physical Activity)", physical_activity)
analyze("_RFBMI5 (Overweight or Obese)", ow_ob)
