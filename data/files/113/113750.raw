!(VERSION.minor > 3) && println("Required Julia 0.4")

module JuliaIntro

# Pkg.clone("git@github.com:wookay/PageDown.git")
using PageDown

push!(LOAD_PATH, "src")
import Slide: pages

export page
export clear
export @page, @current, @next, @prev, @go, @first, @last, @step, @open


page = Page(1, 1, pages, "IMG"=>"짤")

function __init__()
  Base.Markdown.term(STDOUT, @first)
end

end # module
