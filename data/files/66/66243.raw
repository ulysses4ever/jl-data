importall Bukdu

type WelcomeController <: ApplicationController
end

function layout(::Layout, body)
    """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Bukdu 🌌 </title>
    <link rel="stylesheet" href="/css/style.css" />
</head>
<body>
$body
</body>
</html>
"""
end

global counter = 0

function index(::WelcomeController)
    commit = Bukdu.Server.commit_short
    text = """
# Bukdu 🌌

[Bukdu](https://github.com/wookay/Bukdu.jl) is a web development framework for [Julia](http://julialang.org).

It's influenced by [Phoenix framework](http://phoenixframework.org).


# Bukdu on Heroku

You can run Bukdu on [Heroku](https://www.heroku.com/).

 * Heroku: Create new app like this.

   - [heroku-bukdu](https://github.com/wookay/heroku-bukdu)

 * Heroku: Add two buildpacks on **Settings** -> **Add buildpack**

   - [https://github.com/rcaught/heroku-buildpack-cmake](https://github.com/rcaught/heroku-buildpack-cmake)

   - [https://github.com/pinx/heroku-buildpack-julia](https://github.com/pinx/heroku-buildpack-julia)

  ```sh
λ ~/work/heroku-bukdu \$ heroku buildpacks
=== bukdu Buildpack URLs
1. https://github.com/rcaught/heroku-buildpack-cmake
2. https://github.com/pinx/heroku-buildpack-julia
```

 * Get more information: [https://devcenter.heroku.com/categories/deployment](https://devcenter.heroku.com/categories/deployment)


# Welcome

This page is running in the Bukdu commit [$commit](https://github.com/wookay/Bukdu.jl/commit/$commit) with Juila $(VERSION)

See the full code of [welcome.jl](https://github.com/wookay/heroku-bukdu/blob/master/welcome.jl).

$counter
"""
    global counter += 1
    render(Markdown/Layout, text)
end

Router() do
    get("/", WelcomeController, index)
end

Endpoint() do
    plug(Plug.Static, at= "/", from= "public")
    plug(Router)
end

Bukdu.start(parse(Int,ENV["PORT"]); host=ip"0.0.0.0")

(Endpoint)("/")
Base.JLOptions().isinteractive==0 && wait()

Bukdu.stop()
