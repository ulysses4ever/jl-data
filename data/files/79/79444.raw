using Helpme
using Base.Test

for (error, fnstr, suggestion) in Helpme.testbase
	results = Helpme.search(error, fnstr)
	@test suggestion in map(x->x.suggestion, results)
end