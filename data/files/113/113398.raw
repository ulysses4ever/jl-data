import Escher.render

const start_date = Date("2014-02-03")
const date_range = Date("2014-02-02"):Date("2014-02-05")

# Input signals

if !isdefined(Main, :_metadata_loaded)
    include(joinpath(pwd(), "ticker-metadata.jl"))
    const _metadata_loaded = true
end

render(t::Escher.Clip, state) =
    render(Escher.Container(t.tile), state) &
        [:style => [:overflow => Escher.name(t.overflow)], :className => "scrollbar"]

function ticker_list(selected, filter_categories, startstr, current_ticker)
    list = length(filter_categories) == 0 ?
             tickers : gettickers(filter_categories)
    list = startstr == "" ? list : filter(x -> beginswith(x, startstr), list)

    map(list) do t
        item = (t == selected ? fillcolor("#9ba", t |> pad(0.5em)) : t |> pad(0.5em))
        constant(t, clickable(item)) >>> current_ticker
    end |> vbox |> clip(auto) |> size(10em, 25em)
end

function input_pane()
    current_date = Input(start_date)
    current_ticker = Input("A")
    search_string = Input("")
    selected_categories = Input([])

    hbox(
        datepicker(start_date, range=date_range) >>> current_date,
        hskip(1em),
        lift((x, y, z) -> ticker_list(x, y, z, current_ticker),
             current_ticker, selected_categories, search_string)
    )
end
