importall Bukdu

type WelcomeController <: ApplicationController
end

function layout(::Layout, body, options)
    """
<html>
  <head><title>Bukdu</title></head>
  <body>$body<body>
</html>
"""
end

function index(::WelcomeController)
    text = """
# Bukdu 🌌

[https://github.com/wookay/Bukdu.jl](https://github.com/wookay/Bukdu.jl)

Bukdu is a web development framework for [Julia](http://julialang.org).

It's influenced by [Phoenix framework](http://phoenixframework.org).


# Bukdu on Heroku

You can run Bukdu on Heroku.

[https://github.com/wookay/heroku-bukdu](https://github.com/wookay/heroku-bukdu)

[https://github.com/wookay/heroku-buildpack-julia](https://github.com/wookay/heroku-buildpack-julia)
"""
    render(Markdown/Layout, text)
end

Router() do
    get("/", WelcomeController, index)
end


Bukdu.start(parse(Int,ENV["PORT"]); host=ip"0.0.0.0")

wait()

Bukdu.stop()
