using Dates
using DataFrames
using Distributions
using Gadfly
using BigFinance

include(joinpath(pwd(), "input.jl"))
include(joinpath(pwd(), "output.jl"))

function main(window)

    current_ticker, current_date, input_ui = input_pane(window)
    vbox(
        h1("Julia Trade Data Viewer") |> fontweight(300),
        vskip(1em),
        input_ui,
        lift(output_pane, current_ticker, current_date, typ=Any)
    ) |> pad(2em)
end
