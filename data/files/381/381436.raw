module ZenFab

using Escher

include("config.jl")

include(Pkg.dir("Escher", "src", "cli", "serve.jl"))

cd(Pkg.dir("ZenFab", "src"))

escher_serve()

using Blink
a = Blink.init() # initialise the atom-shell process
w = Window(a) # Open a new window
loadurl(w, "localhost:5555/escher_machine_ui.jl") # Load a web pages

while true
    true
end

end # module
