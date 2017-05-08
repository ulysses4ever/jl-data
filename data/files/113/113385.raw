using Dates
using DataFrames
using Distributions
using Gadfly
using BigFinance

include(joinpath(pwd(), "input.jl"))
include(joinpath(pwd(), "output.jl"))

function main(window)
    push!(window.assets, "date")
    vbox(
        h1("Julia Trade Data Viewer"),
        vskip(2em),
        input_pane()
    ) |> pad(1em)
end
