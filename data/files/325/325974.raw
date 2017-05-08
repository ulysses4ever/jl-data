using Escher
using Markdown
using Gadfly
using Distributions
using Reactive
using SerialPorts

function main(window)
    push!(window.assets, "layout2")
    push!(window.assets, "icons")
    push!(window.assets, "widgets")

    serial = serialport("/dev/ttyACM0", 250000)

    try
        serial = open(serial)
    catch err
        println("caught error, serial might be already open")
        println(err)
    end

    desc = md"""
    # Hello, World!
    You can write any **Markdown** text and place it in the middle of other
    tiles.
    """ |> pad(1em)

    αᵗ = Input(1.0)
    βᵗ = Input(1.0)
    z_axis_inp = Input(1.0)

    plot_beta(α, β) =
        plot(x -> pdf(Beta(α, β), x), 0, 1)

    t = tabs([hbox(icon("home")),
                      hbox(icon("info-outline")),
                      hbox(icon("settings")),
                      hbox(iconbutton("search"))])

    lift(αᵗ, βᵗ, z_axis_inp) do α, β, z_axis
        ui = vbox(
            maxwidth(3, t),
            vbox(md"## Dynamic plot",
                hbox(vbox(
                    hbox("Alpha: " |>
                        width(4em), slider(1:100) >>> αᵗ) |>
                        packacross(center),
                    hbox("Beta: "  |>
                        width(4em), slider(1:100) >>> βᵗ) |>
                        packacross(center)),
                    plot_beta(α,β) |> drawing((4*2/3)inch, 2inch)),
                  md"## Axes",
                  hbox("Z: " |> width(4em), slider(0:0.1:100) >>> z_axis_inp)
                    |> packacross(center)
            ) |> pad(2em))
        move_cmd = string("G1 X",z_axis," F10000\n")
        write(serial, move_cmd)
        @show move_cmd
        ui
    end
end
