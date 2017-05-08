import Escher.render

const start_date = Date("2014-02-03")
const date_range = Date("2014-02-02"):Date("2014-02-05")

# Input signals

if !isdefined(Main, :_metadata_loaded)
    include(joinpath(pwd(), "ticker-metadata.jl"))
    const _metadata_loaded = true
end

function ticker_list(selected, filter_categories, startstr, current_ticker)
    list = length(filter_categories) == 0 ?
             tickers : gettickers([filter_categories...])
    list = startstr == "" ? list : filter(x -> beginswith(x, startstr), list)

    map(list) do t
        item = (t == selected ? fillcolor("#9ba", pad(0.5em, t)) : pad(0.5em, t))
        constant(t, clickable(item)) >>> current_ticker
    end |> vbox |> clip(auto) |> size(10em, 20em) 
end

function category_list(selection_stream, selected)
    map(categories) do c
        hbox(pairwith(c, checkbox(c in selected)) >>> selection_stream, hskip(2em), c) |> pad(0.5em)
    end |> vbox |> clip(auto) |> size(20em, 25em) 
end

function update_selection(prev, s)
    added, category = s
    if added
        push!(prev, category)
    else
        pop!(prev, category)
    end
    return prev
end

function input_pane(window)
    push!(window.assets, "date")
    push!(window.assets, "widgets")

    current_date = Input(start_date)
    current_ticker = Input("A")
    search_string = Input("")
    selection_stream = Input{Any}((nothing, nothing))
    selected_categories = foldl(update_selection, Set(String[]), selection_stream)

    hbox(
        datepicker(start_date, range=date_range) >>> current_date,
        hskip(1em),
        vbox(
            textinput(label="Search", floatinglabel=false) >>> search_string,
            lift((x, y, z) -> ticker_list(x, y, z, current_ticker),
                 current_ticker, selected_categories, search_string)
         ),
         hskip(1em),
         lift(cs -> category_list(selection_stream, cs), selected_categories)
    )
end
