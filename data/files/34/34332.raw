module AIDA

export parse_aidaFile
using LightXML

abstract AIDA1D

type Cloud1D <: AIDA1D
	name::String
	title::String
	path::String
	conversionLowerEdge::Float32
	conversionUpperEdge::Float32
	conversionBins::Int32
	maxEntries::Int32
	data::Array{Float64,1}
end

type Histogram1D <: AIDA1D
	name::String
	title::String
	path::String
	xLeftEdges::Array{Float64,1}
	weights::Array{Float64,1}
	errors::Array{Float64,1}
end

function parse_histogram1d(xmlHistogram1d)
	attrs = attributes_dict(xmlHistogram1d)
	name = attrs["name"]
	title = attrs["title"]
	path = attrs["path"]
	axis = find_element(xmlHistogram1d, "axis")
	axis_attrs = attributes_dict(axis)
	nxBins = int(axis_attrs["numberOfBins"])
	xMin = float64(axis_attrs["min"])
	xMax = float64(axis_attrs["max"])
	weights = zeros(Float64, nxBins)
	errors = zeros(Float64, nxBins)
	data1d = find_element(xmlHistogram1d, "data1d")
	for e in child_elements(data1d)
		binNum = attribute(e, "binNum")
		if binNum == "OVERFLOW"
			continue
		end
		ibin = int(binNum)
		weights[ibin+1] = float64(attribute(e, "entries"))
		errors[ibin+1] = float64(attribute(e, "weightedRms"))
	end

	return Histogram1D(
	name,
	title,
	path,
	linspace(xMin, xMax, nxBins+1),
	weights,
	errors
	)
end

function parse_cloud1d(xmlCloud1d)
	attrs = attributes_dict(xmlCloud1d)
	n = attrs["name"]
	t = attrs["title"]
	p = attrs["path"]
	convUp = float64(attrs["conversionUpperEdge"])
	convLow = float64(attrs["conversionLowerEdge"])
	convBins = int32(attrs["conversionBins"])
	max = int32(attrs["maxEntries"])
	d = Float32[]
	entries1d = find_element(xmlCloud1d, "entries1d")
	if entries1d != nothing
		for e in child_elements(entries1d)
			push!(d, float64(attribute(e, "valueX", required=true)))
		end
	else
		hist1d = find_element(xmlCloud1d, "histogram1d")
		return parse_histogram1d(hist1d)
	end
	return Cloud1D(
	n,
	t,
	p,
	convLow,
	convUp,
	convBins,
	max,
	d
	)
end

function parse_aidaFile(filename::String)
	xdoc = parse_file(filename)
	xroot = root(xdoc)
	aida1dList = AIDA1D[]
	for cloud in get_elements_by_tagname(xroot, "cloud1d")
		push!(aida1dList, parse_cloud1d(cloud))
	end
	for cloud in get_elements_by_tagname(xroot, "histogram1d")
		push!(aida1dList, parse_histogram1d(cloud))
	end

	cloud1dList = Cloud1D[]
	histogram1dList = Histogram1D[]
	for a in aida1dList
		if typeof(a) == Cloud1D
			push!(cloud1dList, a)
		elseif typeof(a) == Histogram1D
			push!(histogram1dList, a)
		end
	end
	return cloud1dList, histogram1dList
end
end # module
