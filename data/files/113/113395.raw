VERSION < v"0.4-" && using Dates
using Compat
using DataFrames
using Distributions
using Gadfly
using BigFinance
import Compose.mm

thisdir=dirname(@__FILE__)
include(joinpath(thisdir, "input.jl"))
include(joinpath(thisdir, "output.jl"))

function main(window)
    current_ticker, current_date, input_ui = input_pane(window)
    vbox(
        h1("Julia Trade Data Viewer") |> fontweight(300),
        vskip(1em),
        input_ui,
        lift(output_pane, current_ticker, current_date, typ=Any)
    ) |> pad(2em)
end
