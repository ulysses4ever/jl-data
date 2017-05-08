module CorrelationCurveFit

using LsqFit

export HyperModel, GeomModel, ExpModel, FitHyperModel, FitGeomModel, FitExpModel

HyperModel(xdata, p) = 1 ./ (p[1] + p[2] .* xdata)
function FitHyperModel(xData, yData)
	p0 = linreg(xData, 1 ./ yData)
	fit = curve_fit(HyperModel, xData, yData, p0)
	return fit
end

GeomModel(xdata, p) = 1 ./ (p[1] + p[2] * (1- (1 - p[3]).^xdata))
function FitGeomModel(xData, yData) 
	hyperFit = FitHyperModel(xData, yData)
	b0 = hyperFit.param[1] + hyperFit.param[2] * 100
	b1 = hyperFit.param[2] * 100
	b2 = 0.01
	p0 = [b0, b1, b2]
	fit = curve_fit(GeomModel, xData, yData, p0)
end

ExpModel(xdata, p) = 1 ./ (p[1] + p[2] - p[2] .* exp(-xdata ./ p[3]))
function FitExpModel(xData, yData)
	hyperFit = FitHyperModel(xData, yData)
	b0 = hyperFit.param[1] + hyperFit.param[2] * 100
	b1 = hyperFit.param[2] * 100
	b2 = 100
	p0 = [b0, b1, b2]
	fit = curve_fit(ExpModel, xData, yData, p0)
	return fit
end

end # module
