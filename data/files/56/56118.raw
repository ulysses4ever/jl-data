module Quant

using Datetime, Series

export firstday,
       op, hi, lo, cl, vm, aj,  
       SeriesPairDateFloat64, ArraySeriesPairDateFloat64

  # objects to test values
  const op = readseries(Pkg.dir("Jig/src/quant/data/spx.csv"), value=2)
  const hi = readseries(Pkg.dir("Jig/src/quant/data/spx.csv"), value=3)
  const lo = readseries(Pkg.dir("Jig/src/quant/data/spx.csv"), value=4)
  const cl = readseries(Pkg.dir("Jig/src/quant/data/spx.csv"), value=5)
  const vm = readseries(Pkg.dir("Jig/src/quant/data/spx.csv"), value=6)
  const aj = readseries(Pkg.dir("Jig/src/quant/data/spx.csv"), value=7)
  
  # const to test structure
  const SeriesPairDateFloat64 = eval(:(SeriesPair{Date{ISOCalendar}, Float64}))
  const ArraySeriesPairDateFloat64 = eval(:(Array{SeriesPair{Date{ISOCalendar}, Float64}, 1}))

  # const to test dates
  const firstday = date(1970, 1,2)

end
