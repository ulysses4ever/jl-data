importall Bukdu

type WelcomeController <: ApplicationController
end

function layout(::Layout, body, options)
    """
<html>
  <head><title>Bukdu 🌌 </title></head>
  <body>$body<body>
</html>
"""
end

function index(::WelcomeController)
    repo = LibGit2.GitRepo(Pkg.dir("Bukdu"))
    commit = string(LibGit2.revparseid(repo, "HEAD"))
    text = """
# Bukdu 🌌

[Bukdu](https://github.com/wookay/Bukdu.jl) is a web development framework for [Julia](http://julialang.org).

It's influenced by [Phoenix framework](http://phoenixframework.org).


# Bukdu on Heroku

You can run Bukdu on [Heroku](https://www.heroku.com/).

 * [heroku-bukdu](https://github.com/wookay/heroku-bukdu)

 * [heroku-buildpack-julia](https://github.com/wookay/heroku-buildpack-julia)


# Welcome

This page is running on Bukdu commit [$commit](https://github.com/wookay/Bukdu.jl/commit/$commit) in Juila $(VERSION)

See the full code at [welcome.jl](https://github.com/wookay/heroku-bukdu/blob/master/welcome.jl).
"""
    render(Markdown/Layout, text)
end

Router() do
    get("/", WelcomeController, index)
end


Bukdu.start(parse(Int,ENV["PORT"]); host=ip"0.0.0.0")

wait()

Bukdu.stop()
